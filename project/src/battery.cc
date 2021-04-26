#include "battery.h"

namespace csci3081{

Battery::Battery(float max){
    MaxCharge = max;
    BatteryLife = max;
    Dead = false;
}

Battery::Battery(){
    MaxCharge = 10000;
    BatteryLife = MaxCharge;
    Dead = false;
}

float Battery::ChargeRemaining(){
    return BatteryLife;
}

bool Battery::IsDead(){
    return Dead;
}

Battery& Battery::operator=(const Battery& other){
    MaxCharge = other.MaxCharge;
    BatteryLife = other.MaxCharge;
    Dead = other.Dead;
}

void Battery::DepleteBattery(float amount){
    BatteryLife -= amount;
    if (BatteryLife <= 0){
        Dead = true;
    }
}

void Battery::SetMaxCharge(float capacity){
    MaxCharge = capacity;
	if (BatteryLife > capacity){
		BatteryLife = capacity;
	}
}

}
