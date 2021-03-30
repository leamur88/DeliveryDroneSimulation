#include "drone.h"
#include <cstdlib>
#include <iostream>

namespace csci3081 {


Drone::Drone(std::vector<float> pos, std::vector<float> direction, double speed, double radius, std::string path, const picojson::object& details){
    
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
    this->path = path;
    details_ = details;
}

Drone::~Drone(){delete battery;}


void Drone::SetPackage(Package* package){
    this->package = package;
    SetDestination(package->GetPosition());
}

void Drone::UpdateBeeline(float dt){
    if (battery->IsDead()){
        return;
    }

    if (!package->IsDelivered()){
        printf("Drone's position: %.2f %.2f %.2f\n" , position[0],position[1],position[2]);
        printf("Packages's position: %.2f %.2f %.2f\n" , this->package->GetPosition()[0],this->package->GetPosition()[1],this->package->GetPosition()[2]);
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
        position[1] = 287.0;
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
    
    else if(isPickUp&&!isDropOff){
        Descend(dt);
    }
    
    else if (isDropOff){
        Descend(dt);
    }
   
    //Sets the height to be taller than all of the buildings

    if (pickedUpPackage){
        this->package->UpdatePosition(position);
    }
}

void Drone::UpdatePosition(float dt){
    if (path == "beeline"){
        printf("beeline\n");
        UpdateBeeline(dt);
    }
    else if (path == "smart"){
        printf("smart\n");
        UpdateSmartPath(dt);
    }
    
    //As a failsafe for now
    else{
        printf("Path not specified, will go with beeline\n");
        UpdateBeeline(dt);
    }
    
}

//change #1: should be drone radius + package radius, need getRaius inside package
bool Drone::Pickup(){
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
    }else if(DropOff()){
        return 1;
    }
    this->position.at(1) = this->position.at(1)-(1*this->speed*dt);
    return 2;
}

const double Drone::GetSpeed() const{
    return this->speed;
}


void Drone::GoDropOff(){
    printf("Time to go drop off the package!\n");
    SetDestination(package->GetDestination());
}

void Drone::UpdateSmartPath(float dt){
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

void Drone::SetPackageRoute(std::vector< std::vector<float>> packageRoute) {
  this->packageRoute = packageRoute;
}

void Drone::SetCustomerRoute(std::vector< std::vector<float>> customerRoute) {
  this->customerRoute = customerRoute;
}



}
