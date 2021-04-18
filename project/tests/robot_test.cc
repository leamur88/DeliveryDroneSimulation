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
  //Note: we cannot test the robot & package relationship because that requires the use of smart path.
  //Smartpath uses the graph variable which we do not have access to. This will always cause a segmentation fault.
}

}  // namespace csci3081