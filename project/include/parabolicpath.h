/**
 * @file parabolicpath.h
 */
#ifndef PARABOLIC_PATH_H_
#define PARABOLIC_PATH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "delivery_paths.h"
#include "entity_base.h"
#include "vector3D.h"
#include "drone.h"
#include "robot.h"
namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
	/**
	 * @brief This serves as an intermediary class for all of the objects that pickup and deliver packages.
	 *
	 * This class should never actually be instantiated as a real object. It can be used to help dynamic 
     * casting. On top of that, it helps keep the DRY priniciple in place for our code. 
	 */
	class ParabolicPath : public csci3081::iDeliveryPaths{
		public:
			ParabolicPath();

            void UpdatePath();

		protected:
			Drone* d;
            Robot* r;
		};

}
#endif