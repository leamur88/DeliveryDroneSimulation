#include "parabolicpath.h"	

namespace csci3081{
	ParabolicPath::ParabolicPath(){}

	void ParabolicPath::UpdatePath(){
		std::vector <float> tempackroute = o->getPackage()->GetPosition();
		tempackroute.at(1) = o->getPackage()->GetStartPosition().at(1);
		o->SetPackageRoute(GetPath(o->GetPosition(),tempackroute));
		o->SetCustomerRoute(GetPath(tempackroute,o->getPackage()->GetDestination()));
	}

	std::vector<std::vector<float>> ParabolicPath::GetPath(std::vector<float> start, std::vector<float> end){
		std::vector<std::vector<float>> tempRoute;
		Vector3D begin(start);
		Vector3D finish(end);
		Vector3D distance = finish - begin;

		float increment =  distance.Magnitude()/50;
		float Start_Mid_Magnitude = (distance.Magnitude())/2; 

		//find the unit vector
		Vector3D unit = distance;
		unit.Normalize();

		std::vector<float> mid = {(end[0] - start[0])/2, (end[1] - start[1])/2, (end[2] - start[2])/2};
		Vector3D midpoint(mid);
		midpoint = midpoint + begin;

		//loop through the x axis in incriments of distance/50, assigning the height based on a parabolic formula
		tempRoute.push_back(start);
		for (int i = 1; i < 51; i++){
			//next position on x axis
			std::vector<float> next_pos = {i*increment * unit.GetVector()[0], i*increment * unit.GetVector()[1], i*increment * unit.GetVector()[2]};
			Vector3D next(next_pos);
			next = next + begin;
			next_pos = next.GetVector();

			Vector3D step = next - midpoint;
			float Next_Mid_Magnitude = step.Magnitude();
			float y = (1 - (pow(Next_Mid_Magnitude,2)/pow(Start_Mid_Magnitude,2))) * 300;
			next_pos[1] += y;

			tempRoute.push_back(next_pos);
		}

		return tempRoute;
	}
}