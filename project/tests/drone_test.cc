#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "drone.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class DroneTest : public ::testing::Test {
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

	TEST_F(DroneTest, DroneConstructor) {
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
		Drone d(position_to_add, direction_to_add, speed, radius, obj);
		d.SetPath("default");
		d.SetId(55);
		ASSERT_FLOAT_EQ(d.GetPosition()[0], position_to_add[0]);
		ASSERT_FLOAT_EQ(d.GetPosition()[1], position_to_add[1]);
		ASSERT_FLOAT_EQ(d.GetPosition()[2], position_to_add[2]);
		ASSERT_FLOAT_EQ(d.GetDirection()[0], direction_to_add[0]);
		ASSERT_FLOAT_EQ(d.GetDirection()[1], direction_to_add[1]);
		ASSERT_FLOAT_EQ(d.GetDirection()[2], direction_to_add[2]);
		ASSERT_FLOAT_EQ(d.GetSpeed(), speed);
		ASSERT_FLOAT_EQ(d.GetRadius(), radius);
		ASSERT_FLOAT_EQ(d.GetVersion(), 1);
		ASSERT_FLOAT_EQ(d.GetId(), 55);
		EXPECT_TRUE(d.GetType().compare("drone") == 0);
	}

	TEST_F(DroneTest, DronePackageCustomerRelationship) {	
		picojson::object drone = JsonHelper::CreateJsonObject();
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
		Drone d(position_to_add, direction_to_add, speed, radius, drone);
		std::cout <<"here2\n";
		d.SetCarryingCap(100.0);
    	d.SetMaxSpeed(55.0);
		d.SetBatteryCapacity(10);
		d.SetPath("default");
		std::cout <<"here1\n";
		d.SetId(55);

		std::vector<float> position_to_add1;
		position_to_add1.push_back(490.5);
		position_to_add1.push_back(-100.3);
		position_to_add1.push_back(43.1);

		float weight = 10.2;
		picojson::object package1 = JsonHelper::CreateJsonObject();
		Package p1(position_to_add1,direction_to_add,weight,package1);
		p1.SetId(52);

		std::vector<float> position_to_add2;
		position_to_add2.push_back(200);
		position_to_add2.push_back(12.4);
		position_to_add2.push_back(367);
		weight = 12.9;
		picojson::object package2 = JsonHelper::CreateJsonObject();
		Package p2(position_to_add2,direction_to_add,weight,package2);
		p2.SetId(54);

		std::vector<float> position_to_add3;
		position_to_add3.push_back(-150);
		position_to_add3.push_back(400.2);
		position_to_add3.push_back(550);
		picojson::object customer1 = JsonHelper::CreateJsonObject();
		Customer c1(position_to_add3,customer1);
		c1.SetId(56);

		std::vector<float> position_to_add4;
		position_to_add4.push_back(350);
		position_to_add4.push_back(220);
		position_to_add4.push_back(-36);
		picojson::object customer2 = JsonHelper::CreateJsonObject();
		Customer c2(position_to_add3,customer2);
		c2.SetId(57);

		p1.SetCustomer(&c1);
		p2.SetCustomer(&c2);

		d.AddPackage(&p1);
		d.AddPackage(&p2);

		
		ASSERT_FLOAT_EQ(p1.GetId(), d.getPackage()->GetId());
		ASSERT_FLOAT_EQ(d.getPackage()->GetPosition()[0], p1.GetPosition()[0]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetPosition()[1], p1.GetPosition()[1]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetPosition()[2], p1.GetPosition()[2]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetDestination()[0], c1.GetPosition()[0]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetDestination()[1], c1.GetPosition()[1]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetDestination()[2], c1.GetPosition()[2]);

		d.RemovePackage();
		d.SetPackage();
		ASSERT_FLOAT_EQ(p2.GetId(), d.getPackage()->GetId());
		ASSERT_FLOAT_EQ(d.getPackage()->GetPosition()[0], p2.GetPosition()[0]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetPosition()[1], p2.GetPosition()[1]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetPosition()[2], p2.GetPosition()[2]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetDestination()[0], c2.GetPosition()[0]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetDestination()[1], c2.GetPosition()[1]);
		ASSERT_FLOAT_EQ(d.getPackage()->GetDestination()[2], c2.GetPosition()[2]);
	}

}  // namespace csci3081
