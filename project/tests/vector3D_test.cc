#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "vector3D.h"
#include<cmath>



#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class Vector3DTest : public ::testing::Test {
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


TEST_F(Vector3DTest, VectorConstructor) {
  std::vector<float> vec1;
  vec1.push_back(92);
  vec1.push_back(0);
  vec1.push_back(-44.56);
  Vector3D v(vec1);

  ASSERT_FLOAT_EQ(v.GetVector()[0], vec1[0]);
  ASSERT_FLOAT_EQ(v.GetVector()[1], vec1[1]);
  ASSERT_FLOAT_EQ(v.GetVector()[2], vec1[2]);

  std::vector<float> vec2;
  vec2.push_back(10);
  vec2.push_back(0);
  vec2.push_back(12);

  v.SetVector(vec2);

  ASSERT_FLOAT_EQ(v.GetVector()[0], vec2[0]);
  ASSERT_FLOAT_EQ(v.GetVector()[1], vec2[1]);
  ASSERT_FLOAT_EQ(v.GetVector()[2], vec2[2]);

}

TEST_F(Vector3DTest, VectorOperations) {
  std::vector<float> vec1;
  vec1.push_back(92);
  vec1.push_back(0);
  vec1.push_back(-44.56);
  std::vector<float> vec2;
  vec2.push_back(10);
  vec2.push_back(0);
  vec2.push_back(12);
  Vector3D v1(vec1);
  Vector3D v2(vec2);

  Vector3D v3 = v2+v1;
  Vector3D v4 = v2-v1;


  ASSERT_FLOAT_EQ(v3.GetVector()[0], vec2[0]+vec1[0]);
  ASSERT_FLOAT_EQ(v3.GetVector()[1], vec2[1]+vec1[1]);
  ASSERT_FLOAT_EQ(v3.GetVector()[2], vec2[2]+vec1[2]);

  ASSERT_FLOAT_EQ(v4.GetVector()[0], vec2[0]-vec1[0]);
  ASSERT_FLOAT_EQ(v4.GetVector()[1], vec2[1]-vec1[1]);
  ASSERT_FLOAT_EQ(v4.GetVector()[2], vec2[2]-vec1[2]);

  v2.Scale(2);
  ASSERT_FLOAT_EQ(v2.GetVector()[0], vec2[0]*2);
  ASSERT_FLOAT_EQ(v2.GetVector()[1], vec2[1]*2);
  ASSERT_FLOAT_EQ(v2.GetVector()[2], vec2[2]*2);

  ASSERT_FLOAT_EQ(v2.Magnitude(), sqrt(976));

  std::vector<float> vec3;
  vec3.push_back(10);
  vec3.push_back(0);
  vec3.push_back(10);

  Vector3D v5(vec3);
  float mag = v5.Magnitude();
  v5.Normalize();
  ASSERT_FLOAT_EQ(v5.GetVector()[0], vec3[0]/mag);
  ASSERT_FLOAT_EQ(v5.GetVector()[1], vec3[1]/mag);
  ASSERT_FLOAT_EQ(v5.GetVector()[2], vec3[2]/mag);
  ASSERT_FLOAT_EQ(v5.Magnitude(), 1);


  Vector3D v6;
  float distance = v6.Distance(vec2, vec3);
  ASSERT_FLOAT_EQ(distance, 2.0);
}
}  // namespace csci3081
