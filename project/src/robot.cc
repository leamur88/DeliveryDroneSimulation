#include "robot.h"
#include <cstdlib>
#include <iostream>

namespace csci3081 {


Robot::Robot(std::vector<float> pos, std::vector<float> direction, double speed, double radius, const picojson::object& details){
    
    for (int i=0; i < pos.size();i++){
        this->position.push_back(pos[i]);
        
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
    Vector3D vec;
  if(this->package->IsDelivered() == false){
    if (battery->IsDead()){
        return;
    }
    battery->DepleteBattery(dt);
    if (pickedUpPackage == false ) {
      float distance = vec.magnitude(this->position, this->package->GetPosition());
      if (distance < this->package->GetRadius()){
        pickedUpPackage = true;
      }
    }else{
      float distance = vec.magnitude(this->position, this->package->GetDestination());
      if(distance < this->package->GetRadius()){
        // std::vector<float> newPos (3,10000.0);
        // this->package->UpdatePosition(newPos);
        this->package->Deliver();
      }
    }

    if(pickedUpPackage && this->package->IsDelivered() == false) {
      float temp2 = vec.magnitude(this->position, customerRoute.at(customerRouteStep - 1));
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
      float temp1 = vec.magnitude(this->position, packageRoute.at(packageRouteStep - 1));
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



bool Robot::Pickup(){
    if(abs( (int) (position[0] - package->GetStartPosition()[0])) <= radius+ (package->GetRadius())){
        if(abs( (int) (position[1] - package->GetStartPosition()[1])) <= radius+ (package->GetRadius())){
            if(abs( (int) (position[2] - package->GetStartPosition()[2])) <= radius+ (package->GetRadius())){
                pickedUpPackage = true;
                return true;
            }
        }
    }
    return false;
}

void Robot::SetPackage(Package* package){
    this->package = package;
    SetDestination(package->GetPosition());
}

}