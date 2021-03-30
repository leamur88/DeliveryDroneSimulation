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
            std::string path = JsonHelper::GetString(entity, "path");

            return new Drone(position, direction, speed, radius, path, entity);
        }
        printf("unable to create entity\n");
        return NULL;
    }





}