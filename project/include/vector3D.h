/**
 * @file vector3D.h
 */
#ifndef VECTOR3D_H_
#define VECTOR3D_H_
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
	 * @brief The main class for the generation of Vector3D objects.
	 *
	 *  Calls to \ref Vector3D constructor to get a new Vector3D.
	 *  This class will also contain all of the necessary getters and arithmetic operations
	 *  for the vectors.
	 */
	class Vector3D{

		public:
			/**
			* @brief This is the constructor for the Vector3D class. It takes in a float vector to serve as it's vector.
			*
			* This is the general constructor for the Vector3D. This will allow significantly smoother vector opeations
			* for the relationships between the drone, customer, and package classes.
			*
			*
			* @param[in] vec Float Vector
			*/
			Vector3D(std::vector<float> vec);
			/**
			* @brief This is the constructor for the Vector3D class.
			*
			* This is the general constructor for the Vector3D. This will allow significantly smoother vector opeations
			* for the relationships between the drone, customer, and package classes.
			*
			*
			*/
			Vector3D();

			/**
			 * @brief This is overloading the + operation between two Vector3D objects
			 *
			 * This will return a Vector3D of the addition of two vectors
			 *
			 * @param[in] other The other vector you want to add to this one
			 *
			 * @return A new vector object made up of the sum of the one's used in the function.
			 */
			Vector3D& operator+(const Vector3D& other);

			/**
			 * @brief This is overloading the - operation between two Vector3D objects
			 *
			 *  This will return a Vector3D of the subtraction of two vectors
			 *
			 * @param[in] other The other vector you want to subtract to this one
			 *
			 * @return A new vector object made up of the difference of the one's used in the function.
			 */
			Vector3D& operator-(const Vector3D& other);

			/**
			 * @brief This is overloading assignment operator for Vector3D objects
			 *
			 * @param[in] other The vector that this vector will be set to.
			 *
			 * @return the updated Vector object
			 */
			Vector3D& operator=(const Vector3D& other);

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

			/**
			 * @brief This will return the float vector within this Vector3D object
			 *
			 * @return Float Vector
			 */
			std::vector<float>& GetVector();


			/**
			 * @brief This will set the vector within Vector3D to the parameter
			 *
			 * @param[in] other New vector
			 *
			 */
			void SetVector(std::vector<float> other);

			/**
			 * @brief This will scale the vector by a factor of s;
			 *
			 * @param[in] s This is the factor by which the vector will be scaled by.
			 *
			 */
			void Scale(float s);
			/**
		   * @brief Function to calculate the magnitde of two vectors.
		   *
		   * @param[in] vector1 The first vector that will be used.
		   * @param[in] vector2 The second vector that will be used.
		   *
		   * @return The magnitude of the difference of the two vectors.
		   */
		  float Distance(std::vector<float> vector1, std::vector<float> vector2);

		private:
			std::vector<float> vec;

	};

}
#endif
