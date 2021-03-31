#include "robot.h"
#include <cstdlib>
#include <iostream>

namespace csci3081 {


Robot::Robot(std::vector<float> pos, std::vector<float> direction, double speed, double radius, const picojson::object& details){
	
	for (int i=0; i < pos.size();i++){
		if (i==1){
			this->position.push_back(pos[i]+12);
		}
		else{
			this->position.push_back(pos[i]);
		}
		
	}

	for (int i=0; i < direction.size();i++){
	  this->direction.push_back(direction[i]);  
	}
	this->radius = radius;
	this->speed = speed;
	this->type = "Robot";
	this->pickedUpPackage = false;
	this->Dynamic = true;
	this->battery = new Battery();
	details_ = details;
}

Robot::~Robot(){delete battery;}

void Robot::UpdatePosition(float dt){
	Vector2D vec;
  if(this->package->IsDelivered() == false){
	if (battery->IsDead()){
		return;
	}
	battery->DepleteBattery(dt);
	if (pickedUpPackage == false ) {
	  float distance = vec.Distance(this->position, this->package->GetPosition());
	  if (distance < this->package->GetRadius()){
		pickedUpPackage = true;
	  }
	}else{
	  float distance = vec.Distance(this->position, this->package->GetDestination());
	  if(distance < this->package->GetRadius()){

		this->package->Deliver();
	  }
	}

	if(pickedUpPackage && !this->package->IsDelivered()) {
	  float temp2 = vec.Distance(this->position, customerRoute.at(customerRouteStep - 1));
	  if(temp2 <= .5) {
		customerRouteStep +=1;
	  }
	  Vector2D init(position);
	  Vector2D update(customerRoute.at(customerRouteStep - 1));
	  Vector2D change = update - init;
	  change.Normalize();
	  change.Scale(dt);
	  change.Scale(speed);
	  Vector2D newLoc = init + change;
	  position.clear();
	  for (int i=0; i < newLoc.GetVector().size();i++){
		  this->position.push_back(newLoc.GetVector()[i]);
	  }
	  this->package->UpdatePosition(this->position);
	}
	
	else if (!pickedUpPackage && !this->package->IsDelivered()) {
	  //Vector2D temp1 = 
	  float temp1 = vec.Distance(this->position, packageRoute.at(packageRouteStep - 1));
	  if( temp1 <= .5) {
		packageRouteStep +=1;
	  }
	  Vector2D init(position);
	  Vector2D update(packageRoute.at(packageRouteStep - 1));
	  Vector2D change = update - init;
	  change.Normalize();
	  change.Scale(dt);
	  change.Scale(speed);
	  Vector2D newLoc = init + change;
	  position.clear();
	  for (int i=0; i < newLoc.GetVector().size();i++){
		  this->position.push_back(newLoc.GetVector()[i]);
	  }
	}
  }
}


void Robot::SetPackage(Package* package){
  this->package = package;
}

}