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
		d.SetCarryingCap(100.0);
   		d.SetMaxSpeed(55.0);
		d.SetBatteryCapacity(10);
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

	TEST_F(ParabolicTest, GetPath){
		ParabolicPath path;
		std::vector<float> position_to_add1;
		position_to_add1.push_back(490.5);
		position_to_add1.push_back(-100.3);
		position_to_add1.push_back(43.1);

		std::vector<float> position_to_add3;
		position_to_add3.push_back(-150);
		position_to_add3.push_back(400.2);
		position_to_add3.push_back(550);

		std::vector<std::vector<float>> Route = path.GetPath(position_to_add1, position_to_add3);

		std::vector<std::vector<float>> tempRoute;
		Vector3D begin(position_to_add1);
		Vector3D finish(position_to_add3);
		Vector3D distance = finish - begin;

		float increment =  distance.Magnitude()/50;
		float Start_Mid_Magnitude = (distance.Magnitude())/2; 

		//find the unit vector
		Vector3D unit = distance;
		unit.Normalize();

		std::vector<float> mid = {(position_to_add3[0] - position_to_add1[0])/2, (position_to_add3[1] - position_to_add1[1])/2, (position_to_add3[2] - position_to_add1[2])/2};
		Vector3D midpoint(mid);
		midpoint = midpoint + begin;

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		tempRoute.push_back(position_to_add1);
		for (int i = 1; i < 51; i++){
			//next position on x axis
			std::vector<float> next_pos = {i*increment * unit.GetVector()[0], i*increment * unit.GetVector()[1], i*increment * unit.GetVector()[2]};
			Vector3D next(next_pos);
			next = next + begin;
			next_pos = next.GetVector();

			Vector3D step = next - midpoint;
			float Next_Mid_Magnitude = step.Magnitude();
			float y = (1 - (pow(Next_Mid_Magnitude,2)/pow(Start_Mid_Magnitude,2))) * 300;
			next_pos[1] += y;

			tempRoute.push_back(next_pos);
		}

		for (int i = 0; i < Route.size(); i++){
			for (int j = 0; i < 3; i++){
				ASSERT_FLOAT_EQ(Route[i][j], tempRoute[i][j]);
			}
		}
	}

	









}