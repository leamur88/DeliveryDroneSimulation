#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "vector2D.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class Vector2DTest : public ::testing::Test {
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




TEST_F(Vector2DTest, VectorConstructor) {
  std::vector<float> vec1;
  vec1.push_back(92);
  vec1.push_back(0);
  vec1.push_back(-44.56);
  Vector2D v(vec1);

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

TEST_F(Vector2DTest, VectorOperations) {
  std::vector<float> vec1;
  vec1.push_back(92);
  vec1.push_back(0);
  vec1.push_back(-44.56);
  std::vector<float> vec2;
  vec2.push_back(10);
  vec2.push_back(0);
  vec2.push_back(12);
  Vector2D v1(vec1);
  Vector2D v2(vec2);

  Vector2D v3 = v2+v1;
  Vector2D v4 = v2-v1;


  ASSERT_FLOAT_EQ(v3.GetVector()[0], vec2[0]+vec1[0]);
  ASSERT_FLOAT_EQ(v3.GetVector()[1], vec2[1]+vec1[1]);
  ASSERT_FLOAT_EQ(v3.GetVector()[2], vec2[2]+vec1[2]);

  ASSERT_FLOAT_EQ(v4.GetVector()[0], vec2[0]-vec1[0]);
  ASSERT_FLOAT_EQ(v4.GetVector()[1], vec2[1]-vec1[1]);
  ASSERT_FLOAT_EQ(v4.GetVector()[2], vec2[2]-vec1[2]);

}
}  // namespace csci3081
