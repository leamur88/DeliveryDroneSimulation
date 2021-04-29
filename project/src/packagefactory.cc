#include "packagefactory.h"

namespace csci3081 {

    PackageFactory::PackageFactory(){
    }


    IEntity* PackageFactory::CreateEntity(const picojson::object& entity){
        if (JsonHelper::GetString(entity, "type") == "package") {

            std::vector<float> position = JsonHelper::GetStdFloatVector(entity, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(entity, "direction");
			float weight = 10.0;
			if (JsonHelper::ContainsKey(entity, "weight")){
				weight = JsonHelper::GetDouble(entity, "weight");
			}
            

            Package* p = new Package(position, direction, weight, entity);

            return p;
        }
        return NULL;
    }




}
