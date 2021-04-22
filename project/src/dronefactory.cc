#include "dronefactory.h"


namespace csci3081 {

    DroneFactory::DroneFactory(){
    }


    IEntity* DroneFactory::CreateEntity(const picojson::object& entity){
        if (JsonHelper::GetString(entity, "type") == "drone") {

            std::vector<float> position = JsonHelper::GetStdFloatVector(entity, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(entity, "direction");
            double radius = JsonHelper::GetDouble(entity, "radius");
            double speed = JsonHelper::GetDouble(entity, "speed");
            std::string model = JsonHelper::GetString(entity, "model");

            Drone* d = new Drone(position, direction, speed, radius, entity);
            if(model.compare("Q-36-02"){
                
            }
            if (JsonHelper::ContainsKey(entity, "path")){
                d->SetPath(JsonHelper::GetString(entity, "path"));
            }else {
                d->SetPath("default");
            }

            if (JsonHelper::ContainsKey(entity, "battery_capacity")){
                d->SetBatteryCapacity(JsonHelper::GetDouble(entity, "battery_capacity"));
            }


            return d;
        }
        printf("unable to create entity\n");
        return NULL;
    }

}
