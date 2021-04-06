#include "beelinepath.h"	

namespace csci3081{
	BeelinePath::BeelinePath(Drone* d){
		this->d = d;
	}

	void BeelinePath::UpdatePath(){
		std::vector<std::vector<float>> packageRoutetemp;
		std::vector<float> current_pos = d->GetPosition();
		packageRoutetemp.push_back(current_pos);
		std::vector<float> current_pos_high = d->GetPosition();
		current_pos_high[1] = 315.0;
		packageRoutetemp.push_back(current_pos_high);
		std::vector<float> destination_pos = d->getPackage()->GetPosition();
		destination_pos[1] = 315.0;
		packageRoutetemp.push_back(destination_pos);
		std::vector<float> destination_pos_low = d->getPackage()->GetPosition();
		packageRoutetemp.push_back(destination_pos_low);
		d->SetPackageRoute(packageRoutetemp);

		std::vector<std::vector<float>> customerRoutetemp;
		customerRoutetemp.push_back(destination_pos_low);
		customerRoutetemp.push_back(destination_pos);
		std::vector<float> destination_pos1 = d->getPackage()->GetDestination();
		destination_pos1[1] = 315.0;
		customerRoutetemp.push_back(destination_pos1);
		std::vector<float> destination_pos_low1 = d->getPackage()->GetDestination();
		customerRoutetemp.push_back(destination_pos_low1);
		d->SetCustomerRoute(customerRoutetemp);
	}
}
