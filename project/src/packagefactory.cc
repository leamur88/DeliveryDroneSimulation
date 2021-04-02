#include "packagefactory.h"

namespace csci3081 {

    PackageFactory::PackageFactory(){
    }


    IEntity* PackageFactory::CreateEntity(const picojson::object& entity){
        if (JsonHelper::GetString(entity, "type") == "package") {

            std::vector<float> position = JsonHelper::GetStdFloatVector(entity, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(entity, "direction");
            float weight = 10.0;

            Package* p = new Package(position, direction, weight, entity);

            return p;
        }
        printf("unable to create entity\n");
        return NULL;
    }




}
