/**
 * @file delivery_paths.h
 */
#ifndef DELIVERY_PATH_H_
#define DELIVERY_PATH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include "deliveryobjects.h"
#include "drone.h"
#include "robot.h"
//#include "robot.h"
namespace csci3081 {
	class Drone;
	class Robot;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
	/**
	 * @brief This serves as an interface for the strategy pattern class for path generation.
	 *
	 * This is a very straightforward interface that includes a virtual \ref UpdatePath method and it contains the deliveryobject whose paths will be updated.
	 */
	class iDeliveryPaths {
		public:
			/**
			 * @brief This virtual function needs to be overriden by all path algorithms
			 * 
			 * It should be implemented so that both the customerpath and the packagepath are updated in the deliveryobjects object
			 */
            virtual void UpdatePath() = 0;

			/**
			 * @brief This updates a path objects delivery object pointer
			 * 
			 * @param[in] o The Delivery Object that needs an updated path
			 * 
			 * The deliveryobject that is specified will have it's paths updated
			 */
			void SetObject(DeliveryObject* o){
				this->o = o;
			}
			
		protected:
			DeliveryObject* o;
		};

}
#endif