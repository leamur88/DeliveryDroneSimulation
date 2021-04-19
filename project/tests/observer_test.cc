#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "entity_base.h"
#include "delivery_simulation.h"
#include "drone.h"
#include "package.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class ObserverTest : public ::testing::Test {
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
TEST_F(ObserverTest, AddObserver) {
    IEntityObserver* observer;
    DeliverySimulation test;
    test.AddObserver(observer);

    ASSERT_FLOAT_EQ(test.GetObservers().size(), 1);

}

TEST_F(ObserverTest, RemoveObserver) {
    IEntityObserver* observer;
    IEntityObserver* observer2;
    DeliverySimulation test;
    test.AddObserver(observer);
    test.AddObserver(observer2);
    test.RemoveObserver(observer);

    ASSERT_FLOAT_EQ(test.GetObservers().size(), 1);

}

TEST_F(ObserverTest, OnEvent) {
    IEntityObserver* observer;
    IEntityObserver* observer2;
    DeliverySimulation test;


    test.AddObserver(observer);
    test.AddObserver(observer2);
    int loopCount = 0;
    for(int i = 0; i < test.GetObservers().size(); i++){
      loopCount++;
    }

    ASSERT_FLOAT_EQ(loopCount, test.GetObservers().size());

}


}  // namespace csci3081
