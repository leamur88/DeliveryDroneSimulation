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
	details_ = details;
}

Drone::~Drone(){delete battery;}

void Drone::UpdatePosition(float dt){
	if (this->packages.size() <= 0){
	  return;
	}
	if (path == "beeline"){
		UpdateBeeline(dt);
	}
	else if (path == "smart"){
		UpdateSmartPath(dt);
	}

	//As a failsafe for now
	else{
		//printf("Path not specified, will go with beeline\n");
		UpdateBeeline(dt);
	}

}


void Drone::UpdateBeeline(float dt){
	if (battery->IsDead()){
		return;
	}

	if (!package->IsDelivered()){
		// printf("Drone's position: %.2f %.2f %.2f\n" , position[0],position[1],position[2]);
		// printf("Packages's position: %.2f %.2f %.2f\n" , this->package->GetPosition()[0],this->package->GetPosition()[1],this->package->GetPosition()[2]);
	}

	battery->DepleteBattery(dt);

	bool isPickUp = IsPickupMode();
	bool isDropOff = IsDropOffMode();

	if(!isPickUp&&!isDropOff){
		Vector3D init(position);
		Vector3D update(destination);
		Vector3D change = update - init;
		change.Normalize();
		change.Scale(dt);
		change.Scale(speed);
		Vector3D newLoc = init + change;
		position.clear();
		for (int i=0; i < newLoc.GetVector().size();i++){
			this->position.push_back(newLoc.GetVector()[i]);
		}
		position[1] = 315.0;
	}
	else if(isPickUp&&pickedUpPackage&&!isDropOff){

		if(Ascend(dt)==1){
			Vector3D init(position);
			Vector3D update(destination);
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
	else if(!pickedUpPackage && isDropOff){
		if(Ascend(dt)==1){
			Vector3D init(position);
			Vector3D update(destination);
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
	else if(isPickUp&&!isDropOff){
		//printf("here\n");
		Descend(dt);
	}

	else if (isDropOff){
		Descend(dt);
	}

	if (pickedUpPackage){
		this->package->UpdatePosition(position);
	}
}


bool Drone::Pickup(){
	if(abs( (int) (position[0] - package->GetStartPosition()[0])) <= radius+ (package->GetRadius())){
		if(abs( (int) (position[1] - package->GetStartPosition()[1])) <= radius+ (package->GetRadius())){
			if(abs( (int) (position[2] - package->GetStartPosition()[2])) <= radius+ (package->GetRadius())){
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
				return true;
			}
		}
	}
	return false;
}

bool Drone::IsPickupMode(){
	if(abs( (int) (position[0] - package->GetStartPosition()[0])) <= radius + (package->GetRadius())){
		if(abs( (int) (position[2] - package->GetStartPosition()[2])) <= radius+ (package->GetRadius())){
			return true;
		}
	}
	return false;
}

bool Drone::DropOff(){
	if(abs( (int) (position[0] - package->GetDestination()[0])) <= radius+(package->GetCustRadius())){
		if(abs( (int) (position[1] - package->GetDestination()[1])) <= radius+(package->GetCustRadius())){
			if(abs( (int) (position[2] - package->GetDestination()[2])) <= radius+(package->GetCustRadius())){
				package->Deliver();
				picojson::object obj = JsonHelper::CreateJsonNotification();
				JsonHelper::AddStringToJsonObject(obj, "value", "delivered"); 
				for (int i = 0; i < observers.size(); i++){
				  observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj), *package);
				}
				this->packages.erase(this->packages.begin());
				pickedUpPackage = false;
				SetPackage();
				
				return true;
			}
		}
	}
	return false;
}

bool Drone::IsDropOffMode(){
	if(abs( (int) (position[0] - package->GetDestination()[0])) <= radius+(package->GetCustRadius())){
		if(abs( (int) (position[2] - package->GetDestination()[2])) <= radius+(package->GetCustRadius())){
			return true;
		}
	}
	return false;
}

int Drone::Ascend(float dt){
	if(this->position.at(1)>=287.0){
		return 1;
	}
	this->position.at(1) = this->position.at(1)+(1*speed*dt);
	return 2;
}

int Drone::Descend(float dt){
	if(Pickup()){
		GoDropOff();
		return 0;
	}
	else if(DropOff()){
		return 1;
	}
	this->position.at(1) = this->position.at(1)-(1*this->speed*dt);
	return 2;
}

void Drone::GoDropOff(){
	//printf("Time to go drop off the package!\n");
	SetDestination(package->GetDestination());
}


void Drone::UpdateSmartPath(float dt){
  //printf("in update smart path\n");
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
	}else{
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
	}else if (pickedUpPackage == false && this->package->IsDelivered() == false) {
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
			SetDestination(package->GetPosition());
			std::vector<std::vector<float>> packageRoutetemp;
			std::vector<float> current_pos = this->GetPosition();
			packageRoutetemp.push_back(current_pos);
			std::vector<float> current_pos_high = this->GetPosition();
			current_pos_high[1] = 315.0;
			packageRoutetemp.push_back(current_pos_high);
			std::vector<float> destination_pos = package->GetPosition();
			destination_pos[1] = 315.0;
			packageRoutetemp.push_back(destination_pos);
			std::vector<float> destination_pos_low = package->GetPosition();
			packageRoutetemp.push_back(destination_pos_low);
			this->SetPackageRoute(packageRoutetemp);

			std::vector<std::vector<float>> customerRoutetemp;
			customerRoutetemp.push_back(destination_pos_low);
			customerRoutetemp.push_back(destination_pos);
			std::vector<float> destination_pos1 = package->GetDestination();
			destination_pos1[1] = 315.0;
			customerRoutetemp.push_back(destination_pos1);
			std::vector<float> destination_pos_low1 = package->GetDestination();
			customerRoutetemp.push_back(destination_pos_low1);
			this->SetCustomerRoute(customerRoutetemp);

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

void Drone::SetDestination(const std::vector<float>& dir){
	destination.clear();
	for (int i=0; i < dir.size();i++){
		this->destination.push_back(dir[i]);
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
