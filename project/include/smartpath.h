/**
 * @file smartpath.h
 */
#ifndef SMART_PATH_H_
#define SMART_PATH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "delivery_paths.h"
namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
	/**
	 * @brief This serves as part of a broader strategy pattern for setting the paths of deliveryobjects. This specific concrete strategy returns a smart path.
	 *
	 * The smartpath algorithm actually does most of the work by itself. Using the graph variable in the deliveryobject, you simply need to make a function call with the start and end points and it will
	 * return the route you needed.
	 */
	class SmartPath : public csci3081::iDeliveryPaths{
		public:
			/**
			 * @brief This is the Constructor for a SmartPath
			 * 
			 * This will be used to instantiate the smart path object used in delivery objects. Once
			 * instantiated the smartpath object can update a delivery objects paths to using the smartpath 
			 * algorithm.
			 */
		   	SmartPath();

		   	/**
			 * @brief This is how the SmartPath Object updates the Delivery Objects paths
			 * 
			 * This is called upon when a delivery object needs its paths to be updated, likely due to a change in packages.
			 */
           	void UpdatePath();

	};

}
#endif