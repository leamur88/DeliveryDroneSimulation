/**
 * @file dronefactory.h
 */
#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <string>
#include "json_helper.h"
#include "drone.h"


namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
    /**
     * @brief The main class for the generation of drones for the delivery simulation class.
     *
     * It creates drone objects through the create entity function
     */
    class DroneFactory : public IEntityFactory{
        public:
            /**
             * @brief This is the default constructor for the drone factory
             * 
             * It takes in no parameters, and it does not need to initialize anything
             */
            DroneFactory();

            /**
             * @brief This returns a drone if the entity is meant to be a drone
             * 
             * It will ensure that the entity is meant to be a drone.
             * If it is not, it will return null. If it is, it will return a drone.
             * 
             * @param[in] entity The picojson object of the desired entity
             * 
             * @return null or a drone object
             */
            IEntity* CreateEntity(const picojson::object& entity);


    };


}
#endif