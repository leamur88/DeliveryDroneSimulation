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
		if (packages.size() <= 0 ){
			return;
		}
  	Vector3D vec;
  	if(this->package->IsDelivered() == false){
		// std::cout << JsonHelper::GetString(details_, "name") << std::endl;
		// printf("%f\n", battery->ChargeRemaining());
		if (battery->IsDead()){
			RemovePackages();
			return;
		}
		battery->DepleteBattery(dt);


		if (pickedUpPackage == false ) {
		float distance = vec.Distance(this->position, this->package->GetPosition());

			if (distance < this->package->GetRadius()){
				pickedUpPackage = true;

				picojson::object obj = JsonHelper::CreateJsonNotification();
				JsonHelper::AddStringToJsonObject(obj, "value", "en route");
				for (int i = 0; i < observers.size(); i++){
					observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj), *package);
				}

				picojson::object obj1 = JsonHelper::CreateJsonNotification();
				JsonHelper::AddStringToJsonObject(obj1, "value", "moving");
				JsonHelper::AddStdVectorVectorFloatToJsonObject(obj1, "path", customerRoute);
				for (int i = 0; i < observers.size(); i++){
					observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj1), *this);
				}
			}
		}
		else{
			float distance = vec.Distance(this->position, this->package->GetDestination());
			if(distance < this->package->GetRadius()){
				this->package->Deliver();
				picojson::object obj = JsonHelper::CreateJsonNotification();
				JsonHelper::AddStringToJsonObject(obj, "value", "delivered");
				for (int i = 0; i < observers.size(); i++){
				observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj), *package);
				}
				this->packages.erase(this->packages.begin());
				pickedUpPackage = false;
				customerRouteStep = 1;
				packageRouteStep = 1;
				SetPackage();
			}
		}

		if(pickedUpPackage && this->package->IsDelivered() == false) {
			float temp2 = vec.Distance(this->position, customerRoute.at(customerRouteStep - 1));
			if(temp2 <= .5) {
				customerRouteStep +=1;
			}
			Vector3D init(position);
			Vector3D update(customerRoute.at(customerRouteStep - 1));
			Vector3D change = update - init;
			change.Normalize();
			change.Scale(dt);
			change.Scale(speed);
			Vector3D newLoc = init + change;
			position.clear();
			for (int i=0; i < newLoc.GetVector().size();i++){
				this->position.push_back(newLoc.GetVector()[i]);
			}
			this->package->UpdatePosition(this->position);
		}
		else if (pickedUpPackage == false && this->package->IsDelivered() == false) {
			float temp1 = vec.Distance(this->position, packageRoute.at(packageRouteStep - 1));
			if( temp1 <= .5) {
				packageRouteStep +=1;
			}
			Vector3D init(position);
			Vector3D update(packageRoute.at(packageRouteStep - 1));
			Vector3D change = update - init;
			change.Normalize();
			change.Scale(dt);
			change.Scale(speed);
			Vector3D newLoc = init + change;
			position.clear();
			for (int i=0; i < newLoc.GetVector().size();i++){
				this->position.push_back(newLoc.GetVector()[i]);
			}
		}
  	}
		if (battery->IsDead()){
			picojson::object obj1 = JsonHelper::CreateJsonNotification();
			JsonHelper::AddStringToJsonObject(obj1, "value", "idle");
			for (int i = 0; i < observers.size(); i++){
			  observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj1), *this);
			}
		}
}

void Drone::SetPackage(){
	if(this->packages.size() >= 1) {
		this->package = packages.at(0);
		StrategyPath->UpdatePath();
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

void Drone::SetPath(std::string path){
	this->path = path;
	if (path.compare("beeline")==0){
		this->StrategyPath = new BeelinePath();
	}
	else if (path.compare("smart")==0){
		this->StrategyPath = new SmartPath();
	} else if (path.compare("parabolic")==0){
		printf("setting parabolic\n");
		this->StrategyPath = new ParabolicPath();
		printf("set parabolic\n");
	}
	else{
		//default route
		this->StrategyPath = new BeelinePath();
	}
	StrategyPath->SetObject(this);
}

void Drone::AddPackage(Package* newPackage){
	this->packages.push_back(newPackage);
	if (packages.size() ==1){
		printf("Should set package\n");
		SetPackage();
	}
}


}
