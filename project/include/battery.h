/**
 * @file battery.h
 */
#ifndef BATTERY_H_
#define BATTERY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
	/**
	 * @brief The main class for the generation of Battery.
	 *
	 * Calls to \ref Battery constructor to get a new battery.
	 *  This class will also contain all of the necessary getters for the batteries.
	 */
	class Battery{
		public: 
		/**
		* @brief This is the constructor for the battery class. It takes in a float for the MaxCharge attribute
		* 
		* This is the general constructor for the batteries. It initializes all of the batteries attributes using the
		* input parameter. The batteries will automatically be initialized with maximum charge.
		*
		* @param[in] max Maximum Charge for the Battery.
		*/
		Battery(float max);

		/**
		 * @brief This is the default constructor for the Battery Class
		 * 
		 * This will mainly be used when instantiating stand alone batteries before setting them to a specified one
		 */
		Battery();

		/**
		 * @brief This function simply returns whether or not the drone is out of battery.
		 * 
		 * This function takes in no parameters and will return true if the drone is out of battery or false otherwise.
		 * 
		 * @return True if the drone is out of battery, otherwise it will return False
		 */
		bool IsDead();

		

		/**
		 * @brief This function returns the amount of charge remaining in the battery.
		 * 
		 * This function takes in no parameters and will return the amount of charge remaining in the battery.
		 * 
		 * @return The amount of charge remaining in the battery, stored in "BatteryLife"
		 */
		float ChargeRemaining();


		/**
		 * @brief This is the assignment constructor
		 * 
		 * This is used to assign a Battery to an already created one.
		 * 
		 * @param[in] other The Battery that this is being assigned to.
		 */
		Battery& operator=(const csci3081::Battery& other);

		/**
		 * @brief This function is used to deplete the charge within a battery
		 * 
		 * @param[in] amount The amount that will be subtracted from BatteryLife
		 */
		void DepleteBattery(float amount);


		/**
		 * @brief Set's the Max Charge of a battery
		 * 
		 * @param[in] capacity The new max capacity of the battery
		 * 
		 * This function is mainly used in the Drone and Robot Factories if a max charge is specified within the Json Object
		 */
		void SetMaxCharge(float capacity);

		private:
		float MaxCharge;
		float BatteryLife;
		bool Dead;
	};

}
#endif