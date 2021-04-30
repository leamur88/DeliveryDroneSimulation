/**
 * @file packagefactory.h
 */
#ifndef PACKAGE_FACTORY_H_
#define PACKAGE_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <string>
#include "json_helper.h"
#include "package.h"


namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
    /**
     * @brief This factory creates packages and is a part of the overall factory pattern used to create entities for the simulation.
     *
     * Package objects are not all that complex and that is reflected in the create entity function. The only additional check within the create entity object is the packages weight. Otherwise,
	 * the weight of the package gets set to 10.
     */
    class PackageFactory : public IEntityFactory{
        public:
            /**
             * @brief This is the default constructor for the package factory
             * 
             * It takes in no parameters, and it does not need to initialize anything
             */
            PackageFactory();

            /**
             * @brief This returns a package if the entity is meant to be a package
             * 
             * It will ensure that the entity is meant to be a package.
             * If it is not, it will return null. If it is, it will return a package.
             * 
             * @param[in] entity The picojson object of the desired entity
             * 
             * @return null or a package object
             */
            IEntity* CreateEntity(const picojson::object& entity);
    };


}
#endif