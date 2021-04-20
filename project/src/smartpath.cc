#include "smartpath.h"	

namespace csci3081{
	SmartPath::SmartPath(){}

	void SmartPath::UpdatePath(){
		std::vector <float> tempackroute = o->getPackage()->GetPosition();
		tempackroute.at(1) = o->getPackage()->GetStartPosition().at(1);
		o->SetPackageRoute(o->GetGraph()->GetPath(o->GetPosition(), tempackroute) );
		o->SetCustomerRoute(o->GetGraph()->GetPath(tempackroute, o->getPackage()->GetDestination()));
	}
}