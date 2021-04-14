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


		std::vector<float> mid = {(o->getPackage()->GetPosition()[0] - o->GetPosition()[0])/2, 0, (o->getPackage()->GetPosition()[2] - o->GetPosition()[2])/2};
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
			Vector2D step = next - midpoint;
			float mag1 = step.Magnitude();
			float y = (1 - ((mag1*mag1)/(magnitude*magnitude))) * 300;
			next_pos[1] += y + o->GetPosition()[1];
			//push position into path
			packageRoutetemp.push_back(next_pos);
			//printf("Drone Y: %f \n", o->GetPosition()[1]);
		}

		packageRoutetemp[100][1] = o->getPackage()->GetPosition()[1];
		//set as path to package
		o->SetPackageRoute(packageRoutetemp);
		//o->SetCustomerRoute(GetPath(o->getPackage()->GetPosition(),o->getPackage()->GetDestination()));

		//initialize customer route vector

		std::vector<std::vector<float>> customerRoutetemp;
		//initialize the increment
		Vector3D pLocation(o->getPackage()->GetPosition());
		Vector3D clocation(o->getPackage()->GetDestination());
		Vector3D distancE = clocation - pLocation;
		//distancE.GetVector()[1] = 0;
		increment =  distancE.Magnitude()/100;
		magnitude = (distancE.Magnitude())/2; 

		

		//find the unit vector
		distancE.Normalize();


		mid = {(o->getPackage()->GetDestination()[0] - o->getPackage()->GetPosition()[0])/2, (o->getPackage()->GetDestination()[1] - o->getPackage()->GetPosition()[1])/2, (o->getPackage()->GetDestination()[2] - o->getPackage()->GetPosition()[2])/2};
		Vector3D midpoint2(mid);
		midpoint2 = midpoint2 + pLocation;

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		customerRoutetemp.push_back(o->getPackage()->GetPosition());
		for (int i = 1; i < 101; i++){
			//next position on x axis
			std::vector<float> next_pos = {i*increment * distancE.GetVector()[0], i*increment * distancE.GetVector()[1], i*increment * distancE.GetVector()[2]};
			Vector3D next(next_pos);
			next = next + pLocation;
			next_pos = next.GetVector();

			Vector3D step = next - midpoint2;
			float mag1 = step.Magnitude();
			float y = (1 - ((mag1*mag1)/(magnitude*magnitude))) * 300;
			next_pos[1] += y;
			// printf("Drone Y: %f \n", o->GetPosition()[1]);
			// printf("Y: %f \n", y);
			printf("Location: %f %f %f \n", next_pos[0], next_pos[1], next_pos[2]);
			//convert height based on formula
			//float y = -((i)*(i-(100*increment)))/100;
			//push position into path
			customerRoutetemp.push_back(next_pos);
		}
		//customerRoutetemp[100][1] = o->getPackage()->GetDestination()[1];
		//set as path to package
		o->SetCustomerRoute(customerRoutetemp);
	}

	std::vector<std::vector<float>> ParabolicPath::GetPath(std::vector<float> start, std::vector<float> end){
		std::vector<std::vector<float>> tempRoute;
		Vector3D begin(start);
		Vector3D finish(end);
		Vector3D distance = finish - begin;
		//distancE.GetVector()[1] = 0;
		float increment =  distance.Magnitude()/100;
		float magnitude = (distance.Magnitude())/2; 

		

		//find the unit vector
		distance.Normalize();


		std::vector<float> mid = {(end[0] - start[0])/2, (end[0] - start[0])/2, (end[0] - start[0])/2};
		Vector3D midpoint(mid);
		midpoint = midpoint + begin;

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		tempRoute.push_back(o->getPackage()->GetPosition());
		for (int i = 1; i < 101; i++){
			//next position on x axis
			std::vector<float> next_pos = {i*increment * distance.GetVector()[0], i*increment * distance.GetVector()[1], i*increment * distance.GetVector()[2]};
			Vector3D next(next_pos);
			next = next + begin;
			next_pos = next.GetVector();

			Vector3D step = next - midpoint;
			float mag1 = step.Magnitude();
			float y = (1 - ((mag1*mag1)/(magnitude*magnitude))) * 300;
			next_pos[1] += y;
			// printf("Drone Y: %f \n", o->GetPosition()[1]);
			// printf("Y: %f \n", y);
			printf("Location: %f %f %f \n", next_pos[0], next_pos[1], next_pos[2]);
			//convert height based on formula
			//float y = -((i)*(i-(100*increment)))/100;
			//push position into path
			tempRoute.push_back(next_pos);
		}
		//customerRoutetemp[100][1] = o->getPackage()->GetDestination()[1];
		//set as path to package
		return tempRoute;
	}
}