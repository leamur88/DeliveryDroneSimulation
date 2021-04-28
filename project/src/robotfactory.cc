#include "robotfactory.h"

namespace csci3081 {

    RobotFactory::RobotFactory(){
    }

    IEntity* RobotFactory::CreateEntity(const picojson::object& entity){
        if (JsonHelper::GetString(entity, "type") == "robot") {

            std::vector<float> position = JsonHelper::GetStdFloatVector(entity, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(entity, "direction");
            double radius = JsonHelper::GetDouble(entity, "radius");
            double speed = JsonHelper::GetDouble(entity, "speed");

            Robot* r = new Robot(position, direction, speed, radius, entity);

            if (JsonHelper::ContainsKey(entity, "battery_capacity")){
                r->SetBatteryCapacity(JsonHelper::GetDouble(entity, "battery_capacity"));
            }
			
			r->SetCarryingCap(10.0);
            r->SetMaxSpeed(60.0);
			r->SetBatteryCapacity(300);
			if (JsonHelper::ContainsKey(entity, "model")){
				std::string model = JsonHelper::GetString(entity, "model");
				if(model.compare("R-2D-02")==0){
					r->SetCarryingCap(40.0);
					r->SetMaxSpeed(40.0);
					r->SetBatteryCapacity(200);
				}
				else if (model.compare("R-2D-03")==0){
					r->SetCarryingCap(10.0);
					r->SetMaxSpeed(100.0);
					r->SetBatteryCapacity(30);
				}
				else if (model.compare("R-2D-04")==0){
					r->SetCarryingCap(20.0);
					r->SetMaxSpeed(30.0);
					r->SetBatteryCapacity(600);
				}
				else if (model.compare("R-2D-05")==0){
					r->SetCarryingCap(15.0);
					r->SetMaxSpeed(60.0);
					r->SetBatteryCapacity(120);
				}
			}
            return r;
        }
        return NULL;
    }





}