#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "drone.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class PackageTest : public ::testing::Test {
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

TEST_F(PackageTest, PackageConstructor) {
  picojson::object obj = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  float w = 10.0;
  Package p(position_to_add, direction_to_add, w, obj);
  p.SetId(103);
  
  ASSERT_FLOAT_EQ(p.GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(p.GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(p.GetPosition()[2], position_to_add[2]);
  
  ASSERT_FLOAT_EQ(p.GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(p.GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(p.GetDirection()[2], direction_to_add[2]);
  ASSERT_FLOAT_EQ(p.GetWeight(), 10.0);
  ASSERT_FLOAT_EQ(p.GetVersion(), 1);
  ASSERT_FLOAT_EQ(p.GetId(), 103);
  EXPECT_TRUE(p.GetType().compare("package") == 0);
  p.SetWeight(55.7);
  ASSERT_FLOAT_EQ(p.GetWeight(), 55.7);
}

TEST_F(PackageTest, PackageCustomerRelationship) {
  picojson::object obj2 = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add2;
  position_to_add2.push_back(505);
  position_to_add2.push_back(200);
  position_to_add2.push_back(-20);
  std::vector<float> direction_to_add2;
  float w = 10.0;
  direction_to_add2.push_back(1);
  direction_to_add2.push_back(0);
  direction_to_add2.push_back(0);
  Package p2(position_to_add2, direction_to_add2, w, obj2);

  picojson::object obj3 = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add3;
  position_to_add3.push_back(500.5);
  position_to_add3.push_back(0);
  position_to_add3.push_back(-9.5);
  Customer c1(position_to_add3, obj3);

  picojson::object obj4 = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add4;
  position_to_add4.push_back(400);
  position_to_add4.push_back(0);
  position_to_add4.push_back(-40);
  Customer c2(position_to_add4, obj4);

  p2.SetCustomer(&c1);
  
  ASSERT_FLOAT_EQ(p2.GetDestination()[0], position_to_add3[0]);
  ASSERT_FLOAT_EQ(p2.GetDestination()[1], position_to_add3[1]);
  ASSERT_FLOAT_EQ(p2.GetDestination()[2], position_to_add3[2]);
  
  p2.SetCustomer(&c2);
  ASSERT_FLOAT_EQ(p2.GetDestination()[0], position_to_add4[0]);
  ASSERT_FLOAT_EQ(p2.GetDestination()[1], position_to_add4[1]);
  ASSERT_FLOAT_EQ(p2.GetDestination()[2], position_to_add4[2]);
}

}  // namespace csci3081
