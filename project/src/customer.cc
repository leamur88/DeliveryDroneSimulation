#include "customer.h"


namespace csci3081{

Customer::Customer(std::vector<float> location, const picojson::object& details){
    for (int i=0; i < location.size();i++){
        this->position.push_back(location[i]);
    }

    details_ = details;
    type = "customer";
}

Customer::Customer(){}

Customer::~Customer(){}

const std::vector<float>& Customer::GetDirection() const{
    return direction;
}
const std::vector<float>& Customer::GetPosition() const{
    return position;
}
    
}