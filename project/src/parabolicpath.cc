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
		float magnitude = (distance.Magnitude())/2; 

		


		//find the unit vector
		distance.Normalize();


		std::vector<float> mid = {51*increment * distance.GetVector()[0], 0, 51*increment * distance.GetVector()[2]};
		Vector2D midpoint(mid);
		midpoint = midpoint + dlocation;

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		packageRoutetemp.push_back(o->GetPosition());
		for (int i = 1; i < 101; i++){
			//next position on x axis
			std::vector<float> next_pos = {i*increment * distance.GetVector()[0], 0, i*increment * distance.GetVector()[2]};
			Vector2D next(next_pos);
			next = next + dlocation;
			next_pos = next.GetVector();

			//convert height based on formula
			//float y = -((i)*(i-(100*increment)))/100;
			Vector2D step = next - midpoint;
			float mag1 = step.Magnitude();
			float y = (1 - ((mag1*mag1)/(magnitude*magnitude))) * 300;
			next_pos[1] += y + o->GetPosition()[1];
			printf("mag1: %f \n", mag1);
			printf("magnitude: %f \n", magnitude);
			printf("Y: %f \n", y);
			printf("Total: %f \n", next_pos[1]);
			//push position into path
			packageRoutetemp.push_back(next_pos);
		}

		packageRoutetemp[100][1] = o->getPackage()->GetPosition()[1];
		//set as path to package
		o->SetPackageRoute(packageRoutetemp);













		//initialize customer route vector
		std::vector<std::vector<float>> customerRoutetemp;
		//initialize the increment
		//plocation = Vector3D(d->getPackage()->GetPosition());
		Vector2D clocation(o->getPackage()->GetDestination());
		distance = clocation - plocation;
		increment =  distance.Magnitude()/100;
		magnitude = (distance.Magnitude())/2; 

		

		//find the unit vector
		distance.Normalize();


		mid = {51*increment * distance.GetVector()[0], 0, 51*increment * distance.GetVector()[2]};
		Vector2D midpoint2(mid);
		midpoint2 = midpoint2 + plocation;

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		customerRoutetemp.push_back(o->getPackage()->GetPosition());
		for (int i = 1; i < 101; i++){
			//next position on x axis
			std::vector<float> next_pos = {i*increment * distance.GetVector()[0], 0, i*increment * distance.GetVector()[2]};
			Vector2D next(next_pos);
			next = next + plocation;
			next_pos = next.GetVector();

			Vector2D step = next - midpoint2;
			float mag1 = step.Magnitude();
			float y = (1 - ((mag1*mag1)/(magnitude*magnitude))) * 300;
			next_pos[1] += y + o->GetPosition()[1];

			//convert height based on formula
			//float y = -((i)*(i-(100*increment)))/100;
			//push position into path
			customerRoutetemp.push_back(next_pos);
		}
		customerRoutetemp[100][1] = o->getPackage()->GetDestination()[1];
		//set as path to package
		o->SetCustomerRoute(customerRoutetemp);
	}
}