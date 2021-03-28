/**
 * @file drone.h
 */
#ifndef DRONE_H_
#define DRONE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "deliveryobjects.h"



namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
	/**
	 * @brief The main class for the generation of Drones.
	 *
	 * Calls to \ref Drone constructor to get a new drone.
	 *  This class will also contain all of the necessary getters for the drones.
	 */
	class Drone : public csci3081::DeliveryObject {
	// TODO: Add documentation to these functions
		public:
		/**
		 * @brief This is the constructor for the drone class. It takes in 2 float vectors, a predefined speed, a predefined radius, and a picojson object
		 * 
		 * This is the general constructor for the Drones. It initializes all of the drones attributes using the
		 * input parameters. The first parameter is the drones position vector, the second is the drones direction 
		 * vector, the following two are additional attributes, and the last is the drone picojson object itself.
		 *
		 * 
		 * @param[in] pos Position vector for the drone. 
		 * @param[in] direction Direction vector for the drone. 
		 * @param[in] speed speed of the drone. 
		 * @param[in] radius radius of the drone. 
		 * @param[in] picojson The drone's picojson object. 
		 * 
		 */
		Drone(std::vector<float> pos, std::vector<float> direction, double speed, double radius, const picojson::object& obj);

		/**
		 * @brief This is the Destructor for a Drone object
		 */
		~Drone();

		/**
		 * @brief This function will set a package for the object object
		 * 
		 * @param[in] package The package that the object will carry.
		 */

		void SetPackage(Package* package);

		/**
		 * @brief This function will pickup the package and return whether or not it is in range to be picked up.
		 * 
		 *  The object will call to see if it is within range of the package.
		 * 
		 * @return Whether or not the package can be picked up.
		 */
		bool Pickup();

		/**
		 * @brief This function will dropoff the package and return whether or not it is in range to be dropped off successfully.
		 * 
		 *  The object will call this function to see if it is within range of the customer.
		 * 
		 * @return Whether or not the package can be dropped off.
		 */
		bool DropOff();

		/**
		 *  @brief This will update the position of the object.
		 * 
		 *  The object will update it's position vector using 3D vector arithemetic.
		 * 
		 * @param[in] float the amount of time that will have passed between calls.
		 */
		void UpdatePosition(float dt);

		/**
		 * @brief This function sets the drone's new destination as the customers position
		 * 
		 * This is only called the first time when the drone is within radius of the package
		 */
		void GoDropOff();

		/**
		 * @brief returns whether or not the package has been picked up yet
		 * 
		 * This is used to determine whether or not the packages position needs to be updated alongside the drones
		 * 
		 * @return Whether or not the package has been picked up
		 */
		bool IsPackagePickedUp(){return pickedUpPackage;}

		private:
			bool pickedUpPackage;
		};

}
#endif