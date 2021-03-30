/**
 * @file deliveryobjects.h
 */
#ifndef DELIVERY_OBJECTS_H_
#define DELIVERY_OBJECTS_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include "battery.h"
#include "vector3D.h"
#include "vector2D.h"
#include "package.h"


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
	class DeliveryObject : public csci3081::EntityBase {
		public:

		/**
		 * @brief This is function simply returns the position vector for a given object.
		 * 
		 * This function will return the float vector.
		 *
		 * @return object Position Vector
		 */
		const std::vector<float>& GetPosition() const{return position;}

		/**
		 * @brief This is function simply returns the direction vector for a given object.
		 * 
		 * This function will return the float vector.
		 *
		 * 
		 * @return object Direction Vector
		 */
		const std::vector<float>& GetDirection() const{return direction;}


		/**
		 *  @brief This will update the position of the object.
		 * 
		 *  The object will update it's position vector using 3D vector arithemetic.
		 * 
		 * @param[in] float the amount of time that will have passed between calls.
		 */
		virtual void UpdatePosition(float dt) = 0;


		/**
		 * @brief returns the speed of a given object
		 * 
		 * @return The speed of the object
		 */
		const double GetSpeed() const{return speed;}


		/**
		 * @brief Returns the package the object is currently going to or carrying
		 * 
		 * This is used within Delivery Simulation mainly
		 * 
		 * @return current package
		 */
		Package* getPackage(){return package;}

		void SetPackageRoute(std::vector< std::vector<float>> packageRoute){
			this->packageRoute = packageRoute;
		}

		void SetCustomerRoute(std::vector< std::vector<float>> customerRoute){
			this->customerRoute = customerRoute;
		}

		void SetBatteryCapacity(float capacity){
    		battery->SetMaxCharge(capacity);
		}

		protected:
			std::vector< std::vector<float>> packageRoute;
			std::vector< std::vector<float>> customerRoute;
			int packageRouteStep = 1;
			int customerRouteStep = 1;
			double speed;
			bool moving;
			Battery* battery;
			Package* package;
		};

}
#endif