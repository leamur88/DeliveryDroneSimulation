// #include "gtest/gtest.h"
// #include <EntityProject/project_settings.h>
// #include "../include/delivery_simulation.h"
// #include <EntityProject/entity.h>
// #include "json_helper.h"
// #include "drone.h"
// #include "beelinepath.h"
//
//
// #include <iostream>
//
// namespace csci3081 {
//
// using entity_project::IEntity;
//
// class BeelineTest : public ::testing::Test {
//  protected:
//   virtual void SetUp() {
//     system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
//   }
//   virtual void TearDown() {}
//
//   IDeliverySystem* system;
// };
//
// /*******************************************************************************
//  * Test Cases
//  ******************************************************************************/
//
//
//
// TEST_F(BeelineTest, UpdatePathTests) {
//     picojson::object obj = JsonHelper::CreateJsonObject();
//     JsonHelper::AddStringToJsonObject(obj, "type", "drone");
//     std::vector<float> position_to_add;
//     position_to_add.push_back(600);
//     position_to_add.push_back(300);
//     position_to_add.push_back(300);
//     JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
//     std::vector<float> direction_to_add;
//     direction_to_add.push_back(1);
//     direction_to_add.push_back(0);
//     direction_to_add.push_back(0);
//     JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
//     double radius = 1.0;
//     JsonHelper::AddFloatToJsonObject(obj,"radius",radius);
//     double speed = 30;
//     JsonHelper::AddFloatToJsonObject(obj,"speed",speed);
//
//     Drone* d = new Drone(position_to_add, direction_to_add, speed, radius, obj);
//
//     picojson::object obj2 = JsonHelper::CreateJsonObject();
//     JsonHelper::AddStringToJsonObject(obj2, "type", "package");
//     std::vector<float> position_to_add2;
//     position_to_add2.push_back(500);
//     position_to_add2.push_back(250);
//     position_to_add2.push_back(-200);
//     JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add2);
//     std::vector<float> destination_to_add2;
//     destination_to_add2.push_back(200);
//     destination_to_add2.push_back(200);
//     destination_to_add2.push_back(200);
//     JsonHelper::AddStdFloatVectorToJsonObject(obj2, "destination", destination_to_add2);
//
//     Package* p = new Package(position_to_add2, destination_to_add2, 2.0, obj2);
//
//     picojson::object obj3 = JsonHelper::CreateJsonObject();
//     JsonHelper::AddStringToJsonObject(obj3, "type", "customer");
//     std::vector<float> position_to_add3;
//     position_to_add3.push_back(-100);
//     position_to_add3.push_back(286);
//     position_to_add3.push_back(-150);
//     JsonHelper::AddStdFloatVectorToJsonObject(obj3, "position", position_to_add3);
//
//     Customer* c = new Customer(position_to_add3, obj3);
//
//     p->SetCustomer(c);
//
//     d->SetPath("beeline");
//
//     d->AddPackage(p);
//
//     std::vector <std::vector<float>> packroute = d->GetPackageRoute();
//     std::vector <std::vector<float>> custroute = d->GetCustomerRoute();
//
//     ASSERT_FLOAT_EQ(packroute.at(0).at(0), 600);
//     ASSERT_FLOAT_EQ(packroute.at(0).at(1), 300);
//     ASSERT_FLOAT_EQ(packroute.at(0).at(2), 300);
//
//     ASSERT_FLOAT_EQ(packroute.at(1).at(0), 600);
//     ASSERT_FLOAT_EQ(packroute.at(1).at(1), 315);
//     ASSERT_FLOAT_EQ(packroute.at(1).at(2), 300);
//
//     ASSERT_FLOAT_EQ(packroute.at(2).at(0), 500);
//     ASSERT_FLOAT_EQ(packroute.at(2).at(1), 315);
//     ASSERT_FLOAT_EQ(packroute.at(2).at(2), -200);
//
//     ASSERT_FLOAT_EQ(packroute.at(3).at(0), 500);
//     ASSERT_FLOAT_EQ(packroute.at(3).at(1), 250);
//     ASSERT_FLOAT_EQ(packroute.at(3).at(2), -200);
//
//     ASSERT_FLOAT_EQ(custroute.at(0).at(0), 500);
//     ASSERT_FLOAT_EQ(custroute.at(0).at(1), 250);
//     ASSERT_FLOAT_EQ(custroute.at(0).at(2), -200);
//
//     ASSERT_FLOAT_EQ(custroute.at(1).at(0), 500);
//     ASSERT_FLOAT_EQ(custroute.at(1).at(1), 315);
//     ASSERT_FLOAT_EQ(custroute.at(1).at(2), -200);
//
//     ASSERT_FLOAT_EQ(custroute.at(2).at(0), -100);
//     ASSERT_FLOAT_EQ(custroute.at(2).at(1), 315);
//     ASSERT_FLOAT_EQ(custroute.at(2).at(2), -150);
//
//     ASSERT_FLOAT_EQ(custroute.at(3).at(0), -100);
//     ASSERT_FLOAT_EQ(custroute.at(3).at(1), 286);
//     ASSERT_FLOAT_EQ(custroute.at(3).at(2), -150);
// }
// }  // namespace csci3081
