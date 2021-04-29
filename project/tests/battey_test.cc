#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "drone.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class BatteryTest : public ::testing::Test {
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



TEST_F(BatteryTest, BatteryConstructor) {
    Battery battery(100);


    EXPECT_FALSE(battery.IsDead());
    ASSERT_FLOAT_EQ(100, battery.ChargeRemaining());
	ASSERT_FLOAT_EQ(100, battery.GetMaxCharge());


    battery.DepleteBattery(60);
    ASSERT_FLOAT_EQ(40, battery.ChargeRemaining());
	ASSERT_FLOAT_EQ(100, battery.GetMaxCharge());

	battery.SetMaxCharge(20);

	ASSERT_FLOAT_EQ(20, battery.ChargeRemaining());
	ASSERT_FLOAT_EQ(20, battery.GetMaxCharge());

    Battery battery2 = battery;

    battery.DepleteBattery(60);
    EXPECT_TRUE(battery.IsDead());

    ASSERT_FLOAT_EQ(20, battery2.ChargeRemaining());
    EXPECT_FALSE(battery2.IsDead());
}
}  // namespace csci3081
