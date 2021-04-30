/**
 * @file compositefactory.h
 */
#ifndef COMPOSITE_FACTORY_H_
#define COMPOSITE_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <string>
#include "json_helper.h"


namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
    /**
     * @brief Like the name suggests, this is the class that creates the composite factory for our factory pattern.
     *
	 * Like any composite factory, this class allows us to treat a group of objects as one. In this case, we are treating the factories vector as a single object where
	 * we can simply call create entity and the correct one will be made by looping over every factory in factories.
     */
    class CompositeFactory : public IEntityFactory{
        public:
            /**
             * @brief This is the default constructor for the composite factory
             * 
             * It takes in no parameters, and it does not need to initialize anything
             */
            CompositeFactory();

            /**
             * @brief This adds a factory to the factories vector
             * 
             * These factories can generate any object used in the simulation
             * 
             * @param[in] factory The factory to be added
             */
            void AddFactory(IEntityFactory* factory);

            /**
             * @brief This returns an entity using the factories in the factories vector
             * 
             * It will loop through the vector until the correct entity is returned
             * If the correct factory does not exist then it will return null
             * 
             * @param[in] entity The picojson object of the desired entity
             * 
             * @return null or the expected IEntity object
             */
            IEntity* CreateEntity(const picojson::object& entity);

            /**
             * @brief this simply returns the factories vector
             * 
             * Mainly used in the destructor of the delivery simulation class
             * 
             * @return The factories vector
             */
            std::vector<IEntityFactory*>& GetFactories(){return factories;}

        private:
            std::vector<IEntityFactory*> factories;

    };


}
#endif