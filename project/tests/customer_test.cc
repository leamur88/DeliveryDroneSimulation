#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "drone.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class CustomerTest : public ::testing::Test {
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



TEST_F(CustomerTest, CustomerConstructor) {
  picojson::object obj = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add;
  position_to_add.push_back(92);
  position_to_add.push_back(0);
  position_to_add.push_back(-44.56);
  Customer c(position_to_add, obj);
  c.SetId(101982);

  ASSERT_FLOAT_EQ(c.GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(c.GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(c.GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(c.GetVersion(), 1);
  ASSERT_FLOAT_EQ(c.GetId(), 101982);
  EXPECT_TRUE(c.GetType().compare("customer") == 0);
}
}  // namespace csci3081
