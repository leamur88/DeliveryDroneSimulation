/**
 * @file customerfactory.h
 */
#ifndef CUSTOMER_FACTORY_H_
#define CUSTOMER_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <string>
#include "json_helper.h"
#include "customer.h"


namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
    /**
     * @brief The main class for the generation of customers for the delivery simulation class.
     *
     * It creates customer objects through the create entity function
     */
    class CustomerFactory : public IEntityFactory{
        public:
            /**
             * @brief This is the default constructor for the customer factory
             * 
             * It takes in no parameters, and it does not need to initialize anything
             */
            CustomerFactory();

            /**
             * @brief This returns a customer if the entity is meant to be a customer
             * 
             * It will ensure that the entity is meant to be a customer.
             * If it is not, it will return null. If it is, it will return a customer.
             * 
             * @param[in] entity The picojson object of the desired entity
             * 
             * @return null or a customer object
             */
            IEntity* CreateEntity(const picojson::object& entity);

    };


}
#endif