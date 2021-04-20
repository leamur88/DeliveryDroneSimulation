/**
 * @file beelinepath.h
 */
#ifndef BEELINE_PATH_H_
#define BEELINE_PATH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "delivery_paths.h"
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
	class BeelinePath : public csci3081::iDeliveryPaths{
		public:
			/**
			 * @brief This is the Constructor for a BeelinePath
			 * 
			 * This will be used to instantiate the smart path object used in delivery objects. Once
			 * instantiated the BeelinePath object can update a delivery objects paths to using the BeelinePath 
			 * algorithm.
			 */
			BeelinePath();

			/**
			 * @brief This is how the BeelinePath Object updates the Delivery Objects paths
			 * 
			 * This is called upon when a delivery object needs its paths to be updated, likely due to a change in packages.
			 */
			void UpdatePath();
	};

}
#endif