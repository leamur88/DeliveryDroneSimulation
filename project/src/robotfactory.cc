#include "robotfactory.h"

namespace csci3081 {

    RobotFactory::RobotFactory(){
    }

    //coomment
    IEntity* RobotFactory::CreateEntity(const picojson::object& entity){
        if (JsonHelper::GetString(entity, "type") == "robot") {

            std::vector<float> position = JsonHelper::GetStdFloatVector(entity, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(entity, "direction");
            double radius = JsonHelper::GetDouble(entity, "radius");
            double speed = JsonHelper::GetDouble(entity, "speed");

            //return new Robot(position, direction, speed, radius, entity);
        }
        printf("unable to create entity\n");
        return NULL;
    }





}