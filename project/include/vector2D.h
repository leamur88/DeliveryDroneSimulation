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
	 * @brief The main class for the generation of Vector2D objects.
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
			* for the relationships between different class objects.
			*
			* @param[in] vec Float Vector
			* 
			*/
			Vector2D(std::vector<float> vec);

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

		private:
			std::vector<float> vec;

		
	};

}
#endif