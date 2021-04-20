#include "beelinepath.h"	

namespace csci3081{
	BeelinePath::BeelinePath(){}

	void BeelinePath::UpdatePath(){
		std::vector<std::vector<float>> packageRoutetemp;
		std::vector<float> current_pos = o->GetPosition();
		packageRoutetemp.push_back(current_pos);
		std::vector<float> current_pos_high = o->GetPosition();
		current_pos_high[1] = 315.0;
		packageRoutetemp.push_back(current_pos_high);
		std::vector<float> destination_pos = o->getPackage()->GetPosition();
		destination_pos[1] = 315.0;
		packageRoutetemp.push_back(destination_pos);
		std::vector<float> destination_pos_low = o->getPackage()->GetPosition();
		destination_pos_low.at(1) = o->getPackage()->GetStartPosition().at(1);
		packageRoutetemp.push_back(destination_pos_low);
		o->SetPackageRoute(packageRoutetemp);

		std::vector<std::vector<float>> customerRoutetemp;
		customerRoutetemp.push_back(destination_pos_low);
		customerRoutetemp.push_back(destination_pos);
		std::vector<float> destination_pos1 = o->getPackage()->GetDestination();
		destination_pos1[1] = 315.0;
		customerRoutetemp.push_back(destination_pos1);
		std::vector<float> destination_pos_low1 = o->getPackage()->GetDestination();
		customerRoutetemp.push_back(destination_pos_low1);
		o->SetCustomerRoute(customerRoutetemp);
	}
}
