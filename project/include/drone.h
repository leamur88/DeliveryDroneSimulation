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
		 * @brief This function will set a package for the object object
		 *
		 * @param[in] package The package that the object will carry.
		 */
		void SetPackage();

		void SetPath(std::string path);

		void AddPackage(Package* newPackage);

		private:
			bool pickedUpPackage;
			std::vector<float> destination;
			std::string path = "default";
		};

}
#endif
