#include "drone.h"
#include<cstdlib>

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


const std::vector<float>& Drone::GetPosition() const { return position; }

const std::vector<float>& Drone::GetDirection() const { return direction; }

void Drone::SetPackage(Package* package){
    this->package = package;
    SetDestination(package->GetPosition());
}

void Drone::SetDirection(const std::vector<float>& dir){
    for (int i=0; i < dir.size();i++){
        this->direction[i] = dir[i];
    }
}

void Drone::SetDestination(const std::vector<float>& dir){
    destination.clear();
    for (int i=0; i < dir.size();i++){
        this->destination.push_back(dir[i]);
    }
}


void Drone::UpdatePosition(float dt){
    if (battery->IsDead()){
        return;
    }

    if (!package->IsDelivered()){
        printf("Drone's position: %.2f %.2f %.2f\n" , position[0],position[1],position[2]);
        printf("Packages's position: %.2f %.2f %.2f\n" , this->package->GetPosition()[0],this->package->GetPosition()[1],this->package->GetPosition()[2]);
    }

    battery->DepleteBattery(dt);

    //Calculate updated position
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

    //Sets the height to be taller than all of the buildings
    position[1] = 287.0;

    if (pickedUpPackage){
        this->package->UpdatePosition(newLoc.GetVector());
    }

}

bool Drone::Pickup(){
    if(abs( (int) (position[0] - package->GetPosition()[0])) <= radius){
        if(abs( (int) (position[2] - package->GetPosition()[2])) <= radius){
            pickedUpPackage = true;
            return true;
        }
    }
    return false;
}

bool Drone::DropOff(){
    if(abs( (int) (position[0] - package->GetDestination()[0])) <= radius){
        if(abs( (int) (position[2] - package->GetDestination()[2])) <= radius){
            package->Deliver();
            return true;
        }
    }
    return false;
}

const double Drone::GetSpeed() const{
    return this->speed;
}

void Drone::GoDropOff(){
    printf("Time to go drop off the package!\n");
    SetDestination(package->GetDestination());
}

void Drone::SetPackageRoute(std::vector< std::vector<float>> packageRoute) {
  this->packageRoute = packageRoute;
}

void Drone::SetCustomerRoute(std::vector< std::vector<float>> customerRoute) {
  this->customerRoute = customerRoute;
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
      if(temp2 <= .2) {
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
      if( temp1 <= .2) {
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


}
