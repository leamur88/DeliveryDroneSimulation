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
		 *  @brief This will set the direction vector within the Drone class.
		 * 
		 *  The drone will access the current direction vector and update it.
		 * 
		 * @param[in] dir This is the new direction the drone will fly in.
		 * 
		 */
		void SetDestination(const std::vector<float>& dir){
            destination.clear();
            for (int i=0; i < dir.size();i++){
                this->destination.push_back(dir[i]);
            }
        }


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
		 * @brief This function will set a package for the object object
		 * 
		 * @param[in] package The package that the object will carry.
		 */

		void SetPackage(Package* package);

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

		protected:
			std::vector<float> destination;
			double speed;
			bool moving;
			Battery* battery;
			Package* package;
		};

}
#endif