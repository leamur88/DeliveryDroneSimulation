#include "package.h"

namespace csci3081{

Package::Package(std::vector<float> pos, std::vector<float> destination, float weight, const picojson::object& details){
    
    for (int i=0; i < pos.size();i++){
        this->position.push_back(pos[i]);
    }

    for (int i=0; i < destination.size();i++){
        this->direction.push_back(destination[i]);
    }
    this->Dynamic = true;
    this->weight = weight;
    this->type = "package";
    details_ = details;
}

Package::Package(){}

Package::~Package(){}

const std::vector<float>& Package::GetPosition() const{
    return position;
}

const std::vector<float>& Package::GetDirection() const{
    return direction;
}

const std::vector<float>& Package::GetDestination() const{
    return destination;
}

void Package::UpdatePosition(std::vector<float>& pos){
    position.clear();
    std::vector<float> correction {0,.25,0};

    for (int i=0; i < pos.size();i++){
        this->position.push_back(pos[i] - correction[i]);
    }
}

void Package::SetWeight(float w){
    this->weight = w;
}

float Package::GetWeight(){
    return weight;
}

void Package::SetCustomer(Customer* c){
    customer = c;
    destination.clear();
    for (int i=0; i < c->GetPosition().size();i++){
        this->destination.push_back(c->GetPosition()[i]);
    }
}
    
}