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
     * @brief This factory creates drones and is a part of the overall factory pattern used to create entities for the simulation.
     *
     * Drone objects are much more complex than customers and thus have a more complex createEntity function. On top of the normal Drone constructor, 
	 * the create entity function also checks for and sets what path to use, the battery capacity, and what model the drone is.
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