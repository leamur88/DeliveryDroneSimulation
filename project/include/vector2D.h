/**
 * @file vector2D.h
 */
#ifndef VECTOR2D_H_
#define VECTOR2D_H_
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
	 * @brief The main class for the generation of Vector2D objects used in the robot's UpdatePosition method.
	 *
	 *  Calls to \ref Vector2D constructor to get a new Vector2D.
	 *  This class will also contain all of the necessary getters and arithmetic operations
	 *  for the vectors.
	 */
	class Vector2D{
		
		public:
			/**
			* @brief This is the constructor for the Vector2D class. It takes in a float vector to serve as it's vector.
			* 
			* This is the general constructor for the Vector2D. This will allow significantly smoother vector opeations 
			* for the relationships between within the DeliveryObject classes and their Path Classes as well..
			*
			* @param[in] vec Float Vector
			* 
			*/
			Vector2D(std::vector<float> vec);
			
			/**
			* @brief This is the constructor for the Vector2D class.
			*
			* This is the general constructor for the Vector2D. This will allow significantly smoother vector opeations
			* for the relationships within the DeliveryObject classes and their Path Classes as well.
			*
			*/
			Vector2D();

			/**
			 * @brief This is overloading the + operation between two Vector2D objects
			 * 
			 *  This will return a Vector2D of the addition of two vectors
			 * 
			 * @param[in] other The other vector you want to add to this one
			 * 
			 * @return A new vector object made up of the sum of the one's used in the function.
			 */
			Vector2D& operator+(const Vector2D& other);

			/**
			 * @brief This is overloading the - operation between two Vector2D objects
			 * 
			 *  This will return a Vector2D of the subtraction of two vectors
			 * 
			 * @param[in] other The other vector you want to subtract to this one
			 * 
			 * @return A new vector object made up of the difference of the one's used in the function.
			 */
			Vector2D& operator-(const Vector2D& other);

			/**
			 * @brief This is overloading assignment operator for Vector2D objects
			 * 
			 * @param[in] other The vector that this vector will be set to.
			 * 
			 * @return the updated Vector object
			 */
			Vector2D& operator=(const Vector2D& other);

			/**
			 * @brief This will return the float vector within Vector2D
			 * 
			 * @return Float Vector
			 */
			std::vector<float>& GetVector();


			/**
			 * @brief This will set the vector within Vector2D to the parameter
			 * 
			 * @param[in] other New vector
			 * 
			 */
			void SetVector(std::vector<float> other);

			/**
		   	* @brief Function to calculate the magnitde of two vectors.
		   	*
		   	* @param[in] vector1 The first vector that will be used.
		   	* @param[in] vector2 The second vector that will be used.
		   	*
		   	* @return The magnitude of the difference of the two vectors.
		   	*/
		  	float Distance(std::vector<float> vector1, std::vector<float> vector2);

			/**
			 * @brief This will scale the vector by a factor of s;
			 *
			 * @param[in] s This is the factor by which the vector will be scaled by.
			 *
			 */
			void Scale(float s);

			/**
			 * @brief This will normalize a Vector
			 *
			 *  This will normalize the vector object it is called on. This means that this vectors new magnitude will be equal to 1
			 *  and it will shrink proportionally so the vector still has the same direction.
			 */
			void Normalize();

			/**
			 * @brief This will return the magnitude of a Vector
			 *
			 * This will return the magnitude of a vector as a float
			 *
			 * @return The magnitude of a vector
			 */
			float Magnitude();

		private:
			std::vector<float> vec;
	};

}
#endif