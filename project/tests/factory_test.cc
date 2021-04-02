#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "compositefactory.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class FactoryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(FactoryTest, DroneFactory) {
  DroneFactory* dronefactory = new DroneFactory();
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "drone");
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  double radius = 1.0;
  JsonHelper::AddFloatToJsonObject(obj,"radius",radius);
  double speed = 30;
  JsonHelper::AddFloatToJsonObject(obj,"speed",speed);
  
  IEntity* entity = dronefactory->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());
  delete dronefactory;
}

TEST_F(FactoryTest, PackageFactory) {
  PackageFactory* packagefactory = new PackageFactory();
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "package");
  std::vector<float> position_to_add;
  position_to_add.push_back(14.8);
  position_to_add.push_back(19.5);
  position_to_add.push_back(-22.63);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(7);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  IEntity* entity = packagefactory->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());
  delete packagefactory;
}

TEST_F(FactoryTest, CustomerFactory) {
  CustomerFactory* customerfactory = new CustomerFactory();
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "customer");
  std::vector<float> position_to_add;
  position_to_add.push_back(4.7);
  position_to_add.push_back(5000.232);
  position_to_add.push_back(-2210.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  IEntity* entity = customerfactory->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());
  delete customerfactory;
}

TEST_F(FactoryTest, CompositeFactory) {
  CompositeFactory* compositefactory = new CompositeFactory();
  compositefactory->AddFactory(new DroneFactory());
	compositefactory->AddFactory(new CustomerFactory());
	compositefactory->AddFactory(new PackageFactory());
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  double radius = 1.0;
  double speed = 30;

  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "drone");
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  JsonHelper::AddFloatToJsonObject(obj,"radius",radius);
  JsonHelper::AddFloatToJsonObject(obj,"speed",speed);
  IEntity* drone = compositefactory->CreateEntity(obj);
  // Checks that the returned entity is not NULL
  ASSERT_NE(drone, nullptr) << "The entity created";
  system->AddEntity(drone);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(drone->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(drone->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(drone->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(drone->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(drone->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(drone->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());


  picojson::object obj1 = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj1, "type", "package");
  JsonHelper::AddStdFloatVectorToJsonObject(obj1, "position", position_to_add);
  JsonHelper::AddStdFloatVectorToJsonObject(obj1, "direction", direction_to_add);
  IEntity* package = compositefactory->CreateEntity(obj1);

  // Checks that the returned entity is not NULL
  ASSERT_NE(package, nullptr) << "The entity created";
  system->AddEntity(package);
  ASSERT_EQ(2, system->GetEntities().size());
  ASSERT_FLOAT_EQ(package->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(package->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(package->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(package->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(package->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(package->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[1]->GetDetails()).serialize(), picojson::value(obj1).serialize());




  picojson::object obj2 = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj2, "type", "customer");
  JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add);
  IEntity* customer = compositefactory->CreateEntity(obj2);

  // Checks that the returned entity is not NULL
  ASSERT_NE(customer, nullptr) << "The entity created";
  system->AddEntity(customer);
  ASSERT_EQ(3, system->GetEntities().size());
  ASSERT_FLOAT_EQ(customer->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(customer->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(customer->GetPosition()[2], position_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[2]->GetDetails()).serialize(), picojson::value(obj2).serialize());

}
}  // namespace csci3081
