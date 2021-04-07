#include "smartpath.h"	

namespace csci3081{
	SmartPath::SmartPath(){}

	void SmartPath::UpdatePath(){
		d->SetPackageRoute(d->GetGraph()->GetPath(d->GetPosition(), d->getPackage()->GetPosition() ) );
		d->SetCustomerRoute(d->GetGraph()->GetPath(d->getPackage()->GetPosition(), d->getPackage()->GetDestination()));
	}
}