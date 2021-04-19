#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "drone.h"
#include "parabolicpath.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class ParabolicTest : public ::testing::Test {
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

	TEST_F(ParabolicTest, ParabolicUpdate){
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
		d.SetPath("parabolic");
		d.SetId(55);

		std::vector<float> position_to_add1;
		position_to_add1.push_back(490.5);
		position_to_add1.push_back(-100.3);
		position_to_add1.push_back(43.1);

		float weight = 10.2;
		picojson::object package1 = JsonHelper::CreateJsonObject();
		Package p1(position_to_add1,direction_to_add,weight,package1);
		p1.SetId(52);

		std::vector<float> position_to_add3;
		position_to_add3.push_back(-150);
		position_to_add3.push_back(400.2);
		position_to_add3.push_back(550);
		picojson::object customer1 = JsonHelper::CreateJsonObject();
		Customer c1(position_to_add3,customer1);
		c1.SetId(56);

		p1.SetCustomer(&c1);

		d.AddPackage(&p1);

		d.SetPackage();

		std::vector<std::vector<float>> packroute = d.GetPackageRoute();

		std::vector<std::vector<float>> custroute = d.GetCustomerRoute();

		ParabolicPath path;

		std::vector<std::vector<float>> testpackroute = path.GetPath(position_to_add, position_to_add1);

		std::vector<std::vector<float>> testcustroute = path.GetPath(position_to_add1, position_to_add3);

		for (int i = 0; i < packroute.size(); i++){
			for (int j = 0; i < 3; i++){
				ASSERT_FLOAT_EQ(packroute[i][j], testpackroute[i][j]);
			}
		}

		for (int i = 0; i < custroute.size(); i++){
			for (int j = 0; i < 3; i++){
				ASSERT_FLOAT_EQ(custroute[i][j], testcustroute[i][j]);
			}
		}









	}
}