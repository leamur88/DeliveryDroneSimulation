#include "drone.h"
#include "json_helper.h"
#include <cstdlib>
#include <iostream>
#include "parabolicpath.h"
#include "beelinepath.h"
#include "smartpath.h"

namespace csci3081 {


Drone::Drone(std::vector<float> pos, std::vector<float> direction, double speed, double radius, const picojson::object& details){
	for (int i=0; i < pos.size();i++){
		this->position.push_back(pos[i]);

	}

	for (int i=0; i < direction.size();i++){
		this->direction.push_back(direction[i]);
	}
	this->radius = radius;
	this->speed = speed;
	this->type = "drone";
	this->pickedUpPackage = false;
	this->Dynamic = true;
	this->battery = new Battery();
	details_ = details;
}

Drone::~Drone(){
	delete battery;
	delete StrategyPath;
}

void Drone::UpdatePosition(float dt){
	if(packages.size() <= 0){
		return;
	}
	if (battery->IsDead()){
		if(currPackages.size() >= 1){
			picojson::object obj1 = JsonHelper::CreateJsonNotification();
			JsonHelper::AddStringToJsonObject(obj1, "value", "idle");
			for (int i = 0; i < observers.size(); i++){
				observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj1), *this);
			}
			for (int i=0; i < currPackages.size(); i++){
				std::vector <float> tempPackLoc;
				tempPackLoc.push_back(this->currPackages[i]->GetPosition().at(0));
				tempPackLoc.push_back(this->currPackages[i]->GetStartPosition().at(1));
				tempPackLoc.push_back(this->currPackages[i]->GetPosition().at(2));
				this->currPackages[i]->UpdatePosition(tempPackLoc);
				
			}
		}
		
		currPackages.clear(); //Change with new vector of current packages
		RemovePackages();
		return;
	}
	battery->DepleteBattery(dt);
	Vector3D vec;
	if (!GoToCustomer){
		float distance = vec.Distance(this->position, this->package->GetPosition());
		if (distance < this->package->GetRadius()){
			this->currPackages.push_back(this->package);
			currentCarrying+=this->package->GetWeight();
			picojson::object obj = JsonHelper::CreateJsonNotification();
			JsonHelper::AddStringToJsonObject(obj, "value", "en route");
			for (int j = 0; j < observers.size(); j++){
				observers[j]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj), *package);
			}
			SetPackage();
			return;
		}
		else{
			float temp1 = vec.Distance(this->position, packageRoute.at(packageRouteStep - 1));
			if( temp1 <= .5) {
				packageRouteStep +=1;
			}
			Vector3D init(position);
			Vector3D update(packageRoute.at(packageRouteStep - 1));
			Vector3D change = update - init;
			change.Normalize();
			change.Scale(dt);
			float newspeed = this->maxSpeed - (this->maxSpeed/2)*(currentCarrying/carryingCapacity);

			if(newspeed >= speed){
				newspeed = speed;
			}
			change.Scale(newspeed);
			Vector3D newLoc = init + change;
			position.clear();
			for (int i=0; i < newLoc.GetVector().size();i++){
				this->position.push_back(newLoc.GetVector()[i]);
			}
			for (int i=0; i < currPackages.size(); i++){
				this->currPackages[i]->UpdatePosition(this->position);
			}
		}

	}
	else{
		float distance = vec.Distance(this->position, this->package->GetDestination());
		if(distance < this->package->GetCustRadius()){
			this->package->Deliver();
			picojson::object obj = JsonHelper::CreateJsonNotification();
			JsonHelper::AddStringToJsonObject(obj, "value", "delivered");
			for (int i = 0; i < observers.size(); i++){
				observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj), *package);
			}
			this->currentCarrying -= this->package->GetWeight();
			this->packages.erase(this->packages.begin());
			this->currPackages.erase(this->currPackages.begin());
			GoToCustomerPath();
		}else{
			float temp2 = vec.Distance(this->position, customerRoute.at(customerRouteStep - 1));
			if(temp2 <= .5) {
				customerRouteStep +=1;
			}
			Vector3D init(position);
			Vector3D update(customerRoute.at(customerRouteStep - 1));
			Vector3D change = update - init;
			change.Normalize();
			change.Scale(dt);
			float newspeed = this->maxSpeed - (this->maxSpeed/2)*(currentCarrying/carryingCapacity);

			if(newspeed >= speed){
				newspeed = speed;
			}
			change.Scale(newspeed);
			Vector3D newLoc = init + change;
			position.clear();
			for (int i=0; i < newLoc.GetVector().size();i++){
				this->position.push_back(newLoc.GetVector()[i]);
			}
			for (int i=0; i < currPackages.size(); i++){
				this->currPackages[i]->UpdatePosition(this->position);
			}
		}
	}
}

void Drone::SetPackage(){
	if(this->packages.size() >= 1) {
		
		if ((currPackages.size() == packages.size()) || currentCarrying + this->packages[currPackages.size()]->GetWeight() > carryingCapacity){
			GoToCustomer = true;
			GoToCustomerPath();
			return;
		}
		this->package = packages.at(currPackages.size());
		StrategyPath->UpdatePath();
		packageRouteStep = 1;
		picojson::object obj = JsonHelper::CreateJsonNotification();
		JsonHelper::AddStringToJsonObject(obj, "value", "moving");
		JsonHelper::AddStdVectorVectorFloatToJsonObject(obj, "path", packageRoute);
		for (int i = 0; i < observers.size(); i++){
			observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj), *this);
		}
	}
	else{
		picojson::object obj1 = JsonHelper::CreateJsonNotification();
		JsonHelper::AddStringToJsonObject(obj1, "value", "idle");
		for (int i = 0; i < observers.size(); i++){
		  observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj1), *this);
		}
	}
}

void Drone::GoToCustomerPath(){
	if (currPackages.size() >= 1){
		this->package = currPackages[0];
		StrategyPath->UpdatePath();
		customerRouteStep = 1;
		picojson::object obj1 = JsonHelper::CreateJsonNotification();
		JsonHelper::AddStringToJsonObject(obj1, "value", "moving");
		JsonHelper::AddStdVectorVectorFloatToJsonObject(obj1, "path", customerRoute);
		for (int i = 0; i < observers.size(); i++){
			observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj1), *this);
		}
	}
	else{
		GoToCustomer = false;
		SetPackage();
	}

}

void Drone::SetPath(std::string path){
	this->path = path;
	if (path.compare("beeline")==0){
		this->StrategyPath = new BeelinePath();
	}
	else if (path.compare("smart")==0){
		this->StrategyPath = new SmartPath();
	} else if (path.compare("parabolic")==0){
		this->StrategyPath = new ParabolicPath();
	}
	else{
		//default route
		this->StrategyPath = new BeelinePath();
	}
	StrategyPath->SetObject(this);
}

void Drone::AddPackage(Package* newPackage){
	this->packages.push_back(newPackage);
	if (packages.size() == 1){
		SetPackage();
	}
}


}
