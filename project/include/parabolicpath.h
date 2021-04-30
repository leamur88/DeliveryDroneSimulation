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
#include "vector2D.h"
#include "drone.h"
#include "robot.h"
namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
	/**
	 * @brief This serves as part of a broader strategy pattern for setting the paths of deliveryobjects. This specific concrete strategy returns a parabolic path.
	 *
	 * This class requires the use of a helper function to create the two paths for any package. The \ref UpdatePath method utilizes the \ref GetPath method in order to create paths. 
	 * The \ref GetPath method creates a parabolic path using the formula explained in lab 14 and the start and end points. Our specific parablolic path uses 50 steps in order to ensure a smooth porabola.
	 */
	class ParabolicPath : public csci3081::iDeliveryPaths{
		public:
			/**
			 * @brief This is the Constructor for a ParabolicPath
			 * 
			 * This will be used to instantiate the smart path object used in delivery objects. Once
			 * instantiated the ParabolicPath object can update a delivery objects paths to using the ParabolicPath 
			 * algorithm.
			 */
			ParabolicPath();

			/**
			 * @brief This is how the ParabolicPath Object updates the Delivery Objects paths
			 * 
			 * This is called upon when a delivery object needs its paths to be updated, likely due to a change in packages.
			 */
            void UpdatePath();
			
			/**
			 * @brief This is a helper function for Update path
			 * 
			 * 
			 * @param[in] start The starting point of the parabola
			 * @param[in] end The ending point of the parabola
			 * 
			 * This is what actually updates the path for a given starting vector and an ending vector.
			 * It splits up the beeline path into small increments and implements a parabolic algorithm to determine
			 * the y value for each segment
			 * 
			 * @return Parabolic Path for the two given endpoints
			 */
			std::vector<std::vector<float>> GetPath(std::vector<float> start, std::vector<float> end);
		};

}
#endif