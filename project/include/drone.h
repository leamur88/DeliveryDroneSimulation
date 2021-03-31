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
		 * vector, the following three are additional attributes, and the last is the drone picojson object itself.
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
		 * @brief This function is used to determine which update function the drone should use
		 * 
		 * Depending on the path variable, set at construction, the Drone will update its position in 
		 * three different ways: beeline, smartpath, or parabolic.
		 *
		 * @param[in] dt the amount of time passed between each update call
		 */
		void UpdatePosition(float dt);

		/**
		 *  @brief This will update the position of the drone using the beeline path.
		 *
		 *  The drone will update it's position vector using beeline path.
		 *
		 * @param[in] float the amount of time that will have passed between calls.
		 */
		void UpdateBeeline(float dt);

		/**
		 * @brief This function will pickup the package and return whether or not it is in range to be picked up.
		 * 
		 *  The object will call to see if it is within range of the package.
		 * 
		 * @return Whether or not the package can be picked up.
		 */
		bool Pickup();

		/**
		 * @brief This function will check if the drone is range to start going ascending or descending over the package.
		 *
		 *  The drone's update beeline function calls this function to make sure it is in range to descned towards the package.
		 *
		 * @return if the drone is in range to descending towards the package.
		 */
		bool IsPickupMode();

		/**
		 * @brief This function will dropoff the package and return whether or not it is in range to be dropped off successfully.
		 *
		 *  The drone will call this function to see if it is within range of the customer.
		 *
		 * @return Whether or not the package can be dropped off.
		 */
		bool DropOff();

		/**
		 * @brief This function will check if the drone is range to start going ascending or descending over the customer.
		 *
		 *  The drone's update beeline function calls this function to make sure it is in range to ascend or descend towards the customer.
		 *
		 * @return if the drone is in range to descending towards the customer.
		 */
		bool IsDropOffMode();

		/**
		 * @brief This function sets the drone's new destination as the customers position
		 *
		 * This is only called the first time when the drone is within radius of the package
		 */
		void GoDropOff();

		/**
		 * @brief updates the drones position whenever it is ascending with the package
		 * 
		 * This not only updates the drones position but stops it if it exceeds the height limit
		 * 
		 * @return an int representing if the ascension was successful or the hieght limit was hit
		 */
		int Ascend(float dt);
		
		/**
		 * @brief updates the drones position whenever it needs to descend
		 * 
		 * This not only updates the drones position but stops to descension if the drone has hit its destination
		 * 
		 * @return an int representting if the ascension was successful or the destination was hit.
		 */
		int Descend(float dt);
		
		/**
		 *  @brief This will update the position of the drone using smart path.
		 *
		 *  The drone will update it's position vector using smart path.
		 *
		 * @param[in] float the amount of time that will have passed between calls.
		 */
		void UpdateSmartPath(float dt);

		/**
		 *  @brief This will set the destination vector within the Drone class.
		 *
		 *  The drone will access the current destination vector and update it.
		 *
		 * @param[in] dir This is the new destination the drone will fly to.
		 *
		 */
		void SetDestination(const std::vector<float>& dir);

		/**
		 * @brief This function will set a package for the object object
		 * 
		 * @param[in] package The package that the object will carry.
		 */

		void SetPackage(Package* package);

		void SetPath(std::string path);

		private:
			bool pickedUpPackage;
			std::vector<float> destination;
			std::string path = "default";
		};

}
#endif
