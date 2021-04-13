#include "parabolicpath.h"	

namespace csci3081{
	ParabolicPath::ParabolicPath(){}

	void ParabolicPath::UpdatePath(){
		printf("SUCCESSFULLY UPDATED PARABOLIC PATH" );
		//initialize package route vector
		std::vector<std::vector<float>> packageRoutetemp;
		//initialize the increment
		Vector3D dlocation = Vector3D(d->GetPosition());
		Vector3D plocation = Vector3D(d->getPackage()->GetPosition());
		Vector3D distance = plocation - dlocation;
		float increment =  distance.Magnitude()/100;

		//find the unit vector
		distance.Normalize();

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		for (int i = 1; i < 100; i++){
			//next position on x axis
			std::vector<float> next_pos = {increment * distance.GetVector()[0], distance.GetVector()[1], increment * distance.GetVector()[2]};
			Vector3D next = Vector3D(next_pos);
			next = next + dlocation;
			next_pos = next.GetVector();

			//convert height based on formula
			float y = -((i)*(i-(100*increment)))/100;
			next_pos[1] += y;
			//push position into path
			packageRoutetemp.push_back(next_pos);
		}

		//set as path to package
		d->SetPackageRoute(packageRoutetemp);













		//initialize customer route vector
		std::vector<std::vector<float>> customerRoutetemp;
		//initialize the increment
		//plocation = Vector3D(d->getPackage()->GetPosition());
		Vector3D clocation = Vector3D(d->getPackage()->GetDestination());
		distance = clocation - plocation;
		increment =  distance.Magnitude()/100;

		//find the unit vector
		distance.Normalize();

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		for (int i = 1; i < 100; i++){
			//next position on x axis
			std::vector<float> next_pos = {increment * distance.GetVector()[0], distance.GetVector()[1], increment * distance.GetVector()[2]};
			Vector3D next = Vector3D(next_pos);
			next = next + plocation;
			next_pos = next.GetVector();

			//convert height based on formula
			float y = -((i)*(i-(100*increment)))/100;
			next_pos[1] += y;
			//push position into path
			customerRoutetemp.push_back(next_pos);
		}

		//set as path to package
		d->SetCustomerRoute(customerRoutetemp);
	}
}