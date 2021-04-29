/**
 * @file robot.h
 */
#ifndef ROBOT_H_
#define ROBOT_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "deliveryobjects.h"
#include "delivery_paths.h"


namespace csci3081 {
	class iDeliveryPaths;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
	/**
	 * @brief The main class for the generation of robots.
	 *
	 * Calls to \ref robot constructor to get a new robot.
	 *  This class will also contain all of the necessary getters for the robots.
	 */
	class Robot : public csci3081::DeliveryObject {
		public:
		/**
		 * @brief This is the constructor for the robot class. It takes in 2 float vectors, a predefined speed, a predefined radius, and a picojson object
		 * 
		 * This is the general constructor for the robots. It initializes all of the robots attributes using the
		 * input parameters. The first parameter is the robots position vector, the second is the robots direction 
		 * vector, the following two are additional attributes, and the last is the robot picojson object itself.
		 *
		 * 
		 * @param[in] pos Position vector for the robot. 
		 * @param[in] direction Direction vector for the robot. 
		 * @param[in] speed speed of the robot. 
		 * @param[in] radius radius of the robot. 
		 * @param[in] picojson The robot's picojson object. 
		 * 
		 */
		Robot(std::vector<float> pos, std::vector<float> direction, double speed, double radius, const picojson::object& obj);

		/**
		 * @brief This is the Destructor for a robot object
		 */
		~Robot();

		/**
		 *  @brief This will update the position of the robot.
		 * 
		 *  The robot will update it's position vector using 3D vector arithemetic.
		 * 
		 * @param[in] float the amount of time that will have passed between calls.
		 */
		void UpdatePosition(float dt);

		/**
		 * @brief This function will set a package for the robot object
		 * 
		 * @param[in] package The package that the robot will carry.
		 */
		void SetPackage();

		/**
		 * @brief Add a Package to the packages vector
		 * 
		 * @param[in] newPackage The new package to be added to the package vector
		 */
		void AddPackage(Package* newPackage);

		/**
		 * @brief This function will set the robot's next path vector to follow to be the one to the customer
		 * 
		 * This function is used to switch from picking up packages to now dropping them off. This will be called
		 * when a robot has picked up it's max weight capacity or all possible packages available. It will also be called 
		 * after a package has been dropped off to see if it needs to drop off more packages or go back to picking them up.
		 *
		 */
		void GoToCustomerPath();

		private:
			iDeliveryPaths* StrategyPath;
		};

}
#endif