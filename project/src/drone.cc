#include "drone.h"
#include "json_helper.h"
#include <cstdlib>
#include <iostream>

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
	if (path == "beeline"){
		//this->StrategyPath = new BeelinePath();
	}
	else if (path == "smart"){

	}
	else{
		//default route
		this->StrategyPath = new BeelinePath(this);
	}
	StrategyPath->SetDrone(this);
	
	details_ = details;
}

Drone::~Drone(){delete battery;}

void Drone::UpdatePosition(float dt){
  	Vector3D vec;
  	if(this->package->IsDelivered() == false){

		if (battery->IsDead()){
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
}

void Drone::SetPackage(){
	if(this->packages.size() >= 1) {
		this->package = packages.at(0);
		
		if (path == "smart"){
			this->SetPackageRoute(g->GetPath(GetPosition(), package->GetPosition() ) );
			this->SetCustomerRoute(g->GetPath(package->GetPosition(), package->GetDestination()));
			printf("Calling SetPackage\n");
			picojson::object obj = JsonHelper::CreateJsonNotification();
			JsonHelper::AddStringToJsonObject(obj, "value", "moving"); 
			JsonHelper::AddStdVectorVectorFloatToJsonObject(obj, "path", packageRoute); 
			for (int i = 0; i < observers.size(); i++){
				observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj), *this);
			}
		}
		else{
			StrategyPath->UpdatePath();
			picojson::object obj1 = JsonHelper::CreateJsonNotification();
			JsonHelper::AddStringToJsonObject(obj1, "value", "moving"); 
			JsonHelper::AddStdVectorVectorFloatToJsonObject(obj1, "path", packageRoute); 
			for (int i = 0; i < observers.size(); i++){
				observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj1), *this);
			}
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
}

void Drone::AddPackage(Package* newPackage){
	this->packages.push_back(newPackage);
	if (packages.size() ==1){
		printf("Should set package\n");
		SetPackage();
	}
}


}
