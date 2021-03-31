#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "robot.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class RobotTest : public ::testing::Test {
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

TEST_F(RobotTest, RobotConstructor) {
  picojson::object obj = JsonHelper::CreateJsonObject();
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
  Robot d(position_to_add, direction_to_add, speed, radius, obj);
  d.SetId(55);

  ASSERT_FLOAT_EQ(d.GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(d.GetPosition()[1], position_to_add[1]+12.0);
  ASSERT_FLOAT_EQ(d.GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(d.GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(d.GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(d.GetDirection()[2], direction_to_add[2]);
  ASSERT_FLOAT_EQ(d.GetSpeed(), speed);
  ASSERT_FLOAT_EQ(d.GetRadius(), radius);
  ASSERT_FLOAT_EQ(d.GetVersion(), 1);
  ASSERT_FLOAT_EQ(d.GetId(), 55);
  EXPECT_TRUE(d.GetType().compare("Robot") == 0);
}

TEST_F(RobotTest, RobotPackageCustomerRelationship) {
  picojson::object obj = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add;
  position_to_add.push_back(500);
  position_to_add.push_back(200);
  position_to_add.push_back(-10);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  double radius = 1.0;
  double speed = 30;
  Robot d(position_to_add, direction_to_add, speed, radius, obj);

  picojson::object obj1 = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add1;
  position_to_add1.push_back(499.5);
  position_to_add1.push_back(200);
  position_to_add1.push_back(-10.5);
  std::vector<float> direction_to_add1;
  direction_to_add1.push_back(1);
  direction_to_add1.push_back(0);
  direction_to_add1.push_back(0);
  float w = 10.0;
  Package p1(position_to_add1, direction_to_add1, w, obj1);

  picojson::object obj2 = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add2;
  position_to_add2.push_back(505);
  position_to_add2.push_back(200);
  position_to_add2.push_back(-20);
  std::vector<float> direction_to_add2;
  direction_to_add2.push_back(1);
  direction_to_add2.push_back(0);
  direction_to_add2.push_back(0);
  Package p2(position_to_add2, direction_to_add2, w, obj2);

  d.SetPackage(&p1);
  ASSERT_FLOAT_EQ(d.getPackage()->GetPosition().at(0), 499.5);
  ASSERT_FLOAT_EQ(d.getPackage()->GetPosition().at(1), 200);
  ASSERT_FLOAT_EQ(d.getPackage()->GetPosition().at(2), -10.5);
  d.SetPackage(&p2);
  ASSERT_FLOAT_EQ(d.getPackage()->GetPosition().at(0), 505);
  ASSERT_FLOAT_EQ(d.getPackage()->GetPosition().at(1), 200);
  ASSERT_FLOAT_EQ(d.getPackage()->GetPosition().at(2), -20);

}
}  // namespace csci3081