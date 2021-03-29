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

		 * @brief This is function simply returns the position vector for a given drone.
		 *
		 * This function will return the float vector.
		 *
		 * @return Drone Position Vector
		 */
		const std::vector<float>& GetPosition() const;

		/**
		 * @brief This is function simply returns the direction vector for a given drone.
		 *
		 * This function will return the float vector.
		 *
		 *
		 * @return Drone Direction Vector
		 */
		const std::vector<float>& GetDirection() const;


		/**
		 *  @brief This will set the direction vector within the Drone class.
		 *
		 *  The drone will access the current direction vector and update it.
		 *
		 * @param[in] dir This is the new direction the drone will fly in.
		 *
		 */
		void SetDirection(const std::vector<float>& dir);

		/**
		 *  @brief This will set the direction vector within the Drone class.
		 *
		 *  The drone will access the current direction vector and update it.
		 *
		 * @param[in] dir This is the new direction the drone will fly in.
		 *
		 */
		void SetDestination(const std::vector<float>& dir);

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

		 * @brief This function will pickup the package and return whether or not it is in range to be picked up.
		 *
		 *  The drone will call to see if it is within range of the package.
		 *
		 * @return Whether or not the package can be picked up.
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
		 * @brief This function will set a package for the drone object
		 *
		 * @param[in] package The package that the drone will carry.
		 */
		bool IsDropOffMode();

		/**
		 * @brief This function will set a package for the drone object
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
		 * @brief Returns the package the drone is currently going to or carrying
		 *
		 * This is used within Delivery Simulation mainly
		 *
		 * @return current package
		 */
		Package* getPackage(){return package;}
		/**
		 *  @brief This will update the position of the drone using smart path.
		 *
		 *  The drone will update it's position vector using smart path.
		 *
		 * @param[in] float the amount of time that will have passed between calls.
		 */
		void UpdateSmartPath(float dt);

		void SetPackageRoute(std::vector< std::vector<float>> packageRoute);
		void SetCustomerRoute(std::vector< std::vector<float>> customerRoute);

		private:
			bool pickedUpPackage;
			Battery* battery;
			Package* package;
			std::vector< std::vector<float>> packageRoute;
			std::vector< std::vector<float>> customerRoute;
			int packageRouteStep = 1;
			int customerRouteStep = 1;
		};

}
#endif
