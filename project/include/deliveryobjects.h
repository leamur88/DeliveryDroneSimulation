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

		/**
		 * @brief Set the Object's Package Route
		 * 
		 * @param[in] packageRoute The new packageRoute
		 * 
		 * This updates the packageRoute to be used in the Update function.
		 */
		void SetPackageRoute(std::vector< std::vector<float>> packageRoute){
			this->packageRoute = packageRoute;
		}

		/**
		 * @brief Set the Object's Customer Route
		 * 
		 * @param[in] customerRoute The new customerRoute
		 * 
		 * This updates the customerRoute to be used in the Update function.
		 */
		void SetCustomerRoute(std::vector< std::vector<float>> customerRoute){
			this->customerRoute = customerRoute;
		}

		/** 
		 * @brief This updates the Object's Battery's Max Charge
		 * 
		 * @param[in] capacity The new Max Battery Capacity
		 * 
		 * This function is used if the capacity of a battery is supposed to be something other than the default value
		 */
		void SetBatteryCapacity(float capacity){
    		battery->SetMaxCharge(capacity);
		}

		/**
		 * @brief Returns the package vector that the will go to
		 *
		 * This is used within Delivery Simulation mainly
		 *
		 * @return Packages vector
		 */
		std::vector<Package*> GetPackages() {
			return this->packages;
		}

		/**
		 * @brief This sets the graph that the object's paths are using
		 * 
		 * @param[in] graph The graph that the object will use
		 * 
		 * This is mainly used in the SmartPath Algorithm
		 */
		void SetGraph(const IGraph* graph) {g = graph;}

		/**
		 * @brief Adds observer to the observers list 
		 * 
		 * @param[in] observer The observer to be added to the observers list
		 * 
		 * This is used so that the observers in deliverySim can be notified of changes for each object
		 */
		void SetObserver(IEntityObserver* observer){
			this->observers.push_back(observer);
		}

		/**
		 * @brief This removes the all observers in the observers list
		 * 
		 * This is used when an object runs out of battery and no longer needs its observers
		 */
		void ClearObservers(){
			observers.clear();
		}

		/**
		 * @brief This removes the first package in the packages list
		 * 
		 * This is used when an object delivers a package and needs to move onto the next one.
		 */
		void RemovePackage(){
			packages.erase(this->packages.begin());
		}

		/**
		 * @brief This returns whether or not the battery used still has charge remaining
		 * 
		 * @return True if out of battery, False otherwise
		 */
		bool IsDead() {
			return battery->IsDead();
		}

		/**
		 * @brief This removes the all packages in the packages list
		 * 
		 * This is used when an object runs out of battery and no longer needs its packages
		 */
		void RemovePackages() {
			for (int i = 0; i < packages.size(); i++) {
				packages.erase(packages.begin());
			}
		}

		/**
		 * @brief This returns the graph that the object's paths will use
		 * 
		 * This is mainly used in the SmartPath Algorithm
		 * 
		 * @return The graph that the object is using in the simulation
		 */
		const IGraph* GetGraph() {
			return this->g;
		}

		/**
		 * @brief This function returns the route the object will take to get to the package
		 * 
		 * This is only used for testing
		 * 
		 * @return A std::vector< std::vector<float>> that signifies the route the 
		 * the object will take to get to the package
		 */
		const std::vector< std::vector<float>> GetPackageRoute(){
			return this->packageRoute;
		}

		/**
		 * @brief This function sets the carrying capacity for the delivery object
		 * 
		 * This funciton is used during the production of delivery objects
		 * 
		 * @param[in] carryingCap The new carrying capacity
		 */
		void SetCarryingCap(double carryingCap){
			this->carryingCapacity = carryingCap;
		}

		/**
		 * @brief This function returns the carrying capacity for the delivery object
		 * 
		 * This is only used for testing
		 * 
		 * @return Carrying Capacity
		 */
		const double GetCarryingCap(){
			return this->carryingCapacity;
		}
		
		/**
		 * @brief This function sets the maximum speed for the delivery object
		 * 
		 * This funciton is used during the production of delivery objects.
		 * Also, this function will lower the delivery objects initial speed to it's maxSpeed if it is 
		 * greater than the max speed.
		 * 
		 * @param[in] carryingCap The new maximum speed
		 */
		void SetMaxSpeed(double maxSpeed){
			if(maxSpeed < this->speed){
				speed = maxSpeed;
			}
			this->maxSpeed = maxSpeed;
		}

		/**
		 * @brief This function returns the route the object will take to get to the customer
		 * 
		 * This is only used for testing
		 * 
		  * @return A std::vector< std::vector<float>> that signifies the route the 
		 * the object will take to get to the package
		 */

		const std::vector< std::vector<float>> GetCustomerRoute(){
			return this->customerRoute;
		}

		

		protected:
			const IGraph* g;
			std::vector< std::vector<float>> packageRoute;
			std::vector< std::vector<float>> customerRoute;
			int packageRouteStep = 1;
			int customerRouteStep = 1;
			double speed;
			bool moving;
			Battery* battery;
			Package* package;
			std::vector<Package*> packages;
			std::vector<IEntityObserver*> observers;
			bool pickedUpPackage;
			bool GoToCustomer;
			std::vector<Package*> currPackages;
			double carryingCapacity;
			double currentCarrying=0;
			double maxSpeed;
		};

}
#endif
