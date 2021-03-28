/**
 * @file package.h
 */
#ifndef PACKAGE_H_
#define PACKAGE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "customer.h"

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
	/**
	 * @brief The main class for the generation of Packages.
	 *
	 *  Calls to \ref Package constructor to get a new package.
	 *  This class will also contain all of the necessary getters for the packages.
	 */
	class Package : public csci3081::EntityBase {
		public:

			/**
			 * @brief This is the constructor for the Package class. It takes in 2 float vectors, a float value, and a picojson object
			 * 
			 * This is the general constructor for the Package. It initializes all of the package's attributes using the
			 * input parameters. The first parameter is the package's position vector, the second is the drone's direction 
			 * vector. Both of these will be used as a part of a Vector2D object. Next, the float value is for the weight 
			 * of the drone. The last attribute is the package picojson object itself.
			 * 
			 *
			 * 
			 * @param[in] pos Position vector for the package. 
			 * @param[in] direction Direction vector for the package. 
			 * @param[in] weight Package's weight.
			 * @param[in] picojson The drone's picojson object. 
			 * 
			 */
			Package(std::vector<float> position, std::vector<float> destination, float weight, const picojson::object& obj);

			/**
			 * @brief This is the default constructor for the Package Class
			 * 
			 * This will mainly be used when instantiating stand alone packages before setting them to a specified one
			 */
			Package();

			/**
			 * @brief This is the Destructor for a Package object
			 */
			~Package();

			/**
			 * @brief This is function simply returns the position vector for a given Package.
			 * 
			 * This function takes in no inputs and will return the package's position vector.
			 *
			 * @return Package Position Vector
			 */
			const std::vector<float>& GetPosition() const;

			/**
			 * @brief This is function simply returns the destination vector for a given Package.
			 * 
			 * This function takes in no inputs and will return the package's destination vector (i.e. the customers position).
			 *
			 * @return Package Destination Vector
			 */
			const std::vector<float>& GetDestination() const;

			/**
			 * @brief This is function updates the packages position.
			 * 
			 * This function will be used mainly after the package has been picked up.
			 *
			 * @param[in] pos the new position
			 */	
			void UpdatePosition(std::vector<float>& pos);

			/**
			 * @brief This is function simply returns the destination vector for a given Package.
			 * 
			 * This function takes in no inputs and will return the package's destination vector.
			 *
			 * @return Package Destination Vector
			 */
			const std::vector<float>& GetDirection() const;

			/**
			 * @brief This sets the weight of the package
			 * 
			 * @param[in] w The new weight
			 */
			void SetWeight(float w);

			/**
			 * @brief This sets the weight of the package
			 * 
			 * @return the weight
			 */
			float GetWeight();

			/**
			 * @brief This will set the customer of the package
			 * 
			 * On top that it will also update the the direction vector to the customers position vector
			 */
			void SetCustomer(Customer* c);


			/**
			 * @brief This function is called when the package has been delivered to the customer
			 * 
			 */
			void Deliver(){delivered = true;}

			/**
			 * @brief This function is called to see if the package has been delivered to the customer
			 * 
			 * It is used to know that the package is no longer needed to be visible in the simulation
			 * 
			 * @return Whether or not the package has been delivered yet
			 */
			bool IsDelivered(){return delivered;}

			/**
			 * @brief This function is called to see if the drone is in the correct position for package pickup
			 * 
			 * It is used to know if the delivery state of simluation should change
			 * 
			 * @return a float value representing the pickup radius of the package
			 */
			float GetRadius();



		private:
			std::vector<float> destination;
			float weight;
			Customer* customer;
			bool delivered = false;
			float radius;

	};
}
#endif