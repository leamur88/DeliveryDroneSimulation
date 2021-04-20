/**
 * @file robotfactory.h
 */
#ifndef ROBOT_FACTORY_H_
#define ROBOT_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <string>
#include "json_helper.h"
#include "robot.h"


namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
    /**
     * @brief The main class for the generation of robots for the delivery simulation class.
     *
     * It creates robot objects through the create entity function
     */
    class RobotFactory : public IEntityFactory{
        public:
            /**
             * @brief This is the default constructor for the robot factory
             * 
             * It takes in no parameters, and it does not need to initialize anything
             */
            RobotFactory();

            /**
             * @brief This returns a robot if the entity is meant to be a robot
             * 
             * It will ensure that the entity is meant to be a robot.
             * If it is not, it will return null. If it is, it will return a robot.
             * 
             * @param[in] entity The picojson object of the desired entity
             * 
             * @return null or a robot object
             */

            IEntity* CreateEntity(const picojson::object& entity);


    };


}
#endif