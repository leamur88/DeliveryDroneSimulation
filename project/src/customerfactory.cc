#include "customerfactory.h"

namespace csci3081 {

    CustomerFactory::CustomerFactory(){
    }


    IEntity* CustomerFactory::CreateEntity(const picojson::object& entity){
        if (JsonHelper::GetString(entity, "type") == "customer") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(entity, "position");
            
            return new Customer(position, entity);
        }
        return NULL;
    }





}