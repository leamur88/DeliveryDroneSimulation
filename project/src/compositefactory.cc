#include "compositefactory.h"
#include "entity_base.h"
namespace csci3081 {

    CompositeFactory::CompositeFactory(){
    }

    void CompositeFactory::AddFactory(IEntityFactory* factory){
        factories.push_back(factory);
    }

    IEntity* CompositeFactory::CreateEntity(const picojson::object& entity){
        for (int i =0; i<factories.size(); i++){
            IEntity* temp = factories[i]->CreateEntity(entity);
            if (temp != NULL){
                return temp;
            }
        }
        return NULL;
    }





}