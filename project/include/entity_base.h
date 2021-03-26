/**
 *@file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <string>


namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
	/**
	 * @brief The base class for creating entities.
	 *
	 * This class can be used as the base for all entities in the delivery system.
	 * The overall design is up to you (the student), but all entities must implement
	 * the IEntity interface.
	 *
	 * See the documentation for IEntity for more information
	 */
	class EntityBase : public IEntity {
		public:
	
			virtual ~EntityBase() {}
			/**
			 * @brief This is function simply returns the ID for a given Entity.
			 * 
			 * This function takes in no inputs and will return the entities ID.
			 *
			 * 
			 * @return Entity ID
			 */
			int GetId() const{return Id;}

			/**
			 * @brief This is function simply returns the name for a given Entity.
			 * 
			 * This function takes in no inputs and will return the entities name.
			 *
			 * 
			 * @return Entity Name
			 */
			const std::string& GetName(){return name;}

			/**
			 * @brief This is function simply returns the name for a given entity.
			 * 
			 * This function takes in no inputs and will return the entities type.
			 *
			 * 
			 * @return Entity Name
			 */
			const std::string& GetType(){return type;}

			/**
			 * @brief This is function simply returns the position vector for a given entity.
			 * 
			 * This function takes in no inputs and will return the entities position vector.
			 *
			 * 
			 * @return entity Position Vector
			 */
			const std::vector<float>& GetPosition(){return position;}

			/**
			 * @brief This is function simply returns the direction vector for a given entity.
			 * 
			 * This function takes in no inputs and will return the entities direction vector.
			 *
			 * 
			 * @return entity Direction Vector
			 */
			const std::vector<float>& GetDirection(){return direction;}

			
			/**
			 * @brief This is function simply returns the radius for a given entity.
			 * 
			 * This function takes in no inputs and will return the entities radius.
			 *
			 * 
			 * @return entity Radius
			 */
			float GetRadius() const{return radius;}

			/**
			 * @brief This sets the Id  for a given object
			 * 
			 * @param[in] ID the new object's ID
			 */
			void SetId(int ID) {Id = ID;}

			
			/**
			 * @brief This is function simply returns the version of a given entity.
			 * 
			 * This function takes in no inputs and will return the entities operating version.
			 *
			 * 
			 * @return entity Operating Version
			 */
			int GetVersion() const{return version;}

			/**
			 * @brief This is function simply returns whether or not an entity is dynamic.
			 * 
			 * This function takes in no inputs and will return whether or not an entity is dynamic.
			 *
			 * 
			 * @return If entity Is Dynamic
			 */
			bool IsDynamic() const{return Dynamic;}

			/**
			 * 
			 * @brief returns the picojson object for a given object
			 * 
			 * @return The Object's picojson object
			 * 
			 */
		
			const picojson::object& GetDetails() { return details_; }
			
	protected:
		picojson::object details_;
		std::string name;
		int Id;
		float radius = 1.;
		std::string type;
		int version = 1;
		std::vector<float> position;
		std::vector<float> direction;
		bool Dynamic = false;
	};

}  // namespace csci3081


#endif  // ENTITY_BASE_H_
