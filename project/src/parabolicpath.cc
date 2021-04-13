#include "parabolicpath.h"	

namespace csci3081{
	ParabolicPath::ParabolicPath(){}

	void ParabolicPath::UpdatePath(){
		printf("SUCCESSFULLY UPDATING PARABOLIC PATH" );
		//initialize package route vector
		std::vector<std::vector<float>> packageRoutetemp;
		//initialize the increment
		Vector2D dlocation(o->GetPosition());
		Vector2D plocation(o->getPackage()->GetPosition());
		Vector2D distance = plocation - dlocation;
		float increment =  distance.Magnitude()/100;

		//find the unit vector
		distance.Normalize();

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		packageRoutetemp.push_back(o->GetPosition());
		for (int i = 1; i < 101; i++){
			//next position on x axis
			std::vector<float> next_pos = {i*increment * distance.GetVector()[0], distance.GetVector()[1], i*increment * distance.GetVector()[2]};
			Vector2D next(next_pos);
			next = next + dlocation;
			next_pos = next.GetVector();

			//convert height based on formula
			//float y = -((i)*(i-(100*increment)))/100;
			
			next_pos[1] = 257;
			//push position into path
			packageRoutetemp.push_back(next_pos);
		}

		//set as path to package
		o->SetPackageRoute(packageRoutetemp);













		//initialize customer route vector
		std::vector<std::vector<float>> customerRoutetemp;
		//initialize the increment
		//plocation = Vector3D(d->getPackage()->GetPosition());
		Vector2D clocation(o->getPackage()->GetDestination());
		distance = clocation - plocation;
		increment =  distance.Magnitude()/100;

		//find the unit vector
		distance.Normalize();

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		customerRoutetemp.push_back(o->getPackage()->GetPosition());
		for (int i = 1; i < 101; i++){
			//next position on x axis
			std::vector<float> next_pos = {i*increment * distance.GetVector()[0], distance.GetVector()[1], i*increment * distance.GetVector()[2]};
			Vector2D next(next_pos);
			next = next + plocation;
			next_pos = next.GetVector();

			//convert height based on formula
			//float y = -((i)*(i-(100*increment)))/100;
			next_pos[1] = 254;
			//push position into path
			customerRoutetemp.push_back(next_pos);
		}

		//set as path to package
		o->SetCustomerRoute(customerRoutetemp);
	}
}