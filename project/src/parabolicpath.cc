#include "parabolicpath.h"	

namespace csci3081{
	ParabolicPath::ParabolicPath(){}

	void ParabolicPath::UpdatePath(){
		o->SetPackageRoute(GetPath(o->GetPosition(),o->getPackage()->GetPosition()));
		o->SetCustomerRoute(GetPath(o->getPackage()->GetPosition(),o->getPackage()->GetDestination()));
	}

	std::vector<std::vector<float>> ParabolicPath::GetPath(std::vector<float> start, std::vector<float> end){
		std::vector<std::vector<float>> tempRoute;
		Vector3D begin(start);
		Vector3D finish(end);
		Vector3D distance = finish - begin;

		float increment =  distance.Magnitude()/100;
		float magnitude = (distance.Magnitude())/2; 

		

		//find the unit vector
		distance.Normalize();
		Vector3D unit();


		std::vector<float> mid = {(end[0] - start[0])/2, (end[1] - start[1])/2, (end[2] - start[2])/2};
		Vector3D midpoint(mid);
		midpoint = midpoint + begin;

		//loop through the x axis in incriments of distance/100, assigning the height based on a parabolic formula
		tempRoute.push_back(start);
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

			tempRoute.push_back(next_pos);
		}

		return tempRoute;
	}
}