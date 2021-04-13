#include "smartpath.h"	

namespace csci3081{
	SmartPath::SmartPath(){}

	void SmartPath::UpdatePath(){
		o->SetPackageRoute(o->GetGraph()->GetPath(o->GetPosition(), o->getPackage()->GetPosition() ) );
		o->SetCustomerRoute(o->GetGraph()->GetPath(o->getPackage()->GetPosition(), o->getPackage()->GetDestination()));
	}
}