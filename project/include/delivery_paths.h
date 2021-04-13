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
	 * @brief This serves as an intermediary class for all of the objects that pickup and deliver packages.
	 *
	 * This class should never actually be instantiated as a real object. It can be used to help dynamic 
     * casting. On top of that, it helps keep the DRY priniciple in place for our code. 
	 */
	class iDeliveryPaths {
		public:
            virtual void UpdatePath() = 0;

			void SetObject(DeliveryObject* o){
				this->o = o;
			}
			
		protected:
			DeliveryObject* o;
		};

}
#endif