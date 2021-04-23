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
            
			Drone* d = new Drone(position, direction, speed, radius, entity);
			if (JsonHelper::ContainsKey(entity, "model")){
				std::string model = JsonHelper::GetString(entity, "model");
				if(model.compare("Q-36-02")==0){
					d->SetCarryingCap(20.0);
					d->SetMaxSpeed(55.0);
				}
				else if (model.compare("Q-36-03")==0){
					d->SetCarryingCap(10.0);
					d->SetMaxSpeed(40.0);
				}
				else if (model.compare("Q-36-04")==0){
					d->SetCarryingCap(19.0);
					d->SetMaxSpeed(30.0);
				}
				else if (model.compare("Q-36-05")==0){
					d->SetCarryingCap(15.0);
					d->SetMaxSpeed(60.0);
				}
				else{
					d->SetCarryingCap(10.0);
					d->SetMaxSpeed(60.0);
				}
			} 
            else{
                d->SetCarryingCap(10.0);
                d->SetMaxSpeed(60.0);
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
