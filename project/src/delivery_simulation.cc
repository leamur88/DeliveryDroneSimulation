#include "delivery_simulation.h"
#include "entity_base.h"
#include "json_helper.h"
#include "drone.h"


namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	factories_  = new CompositeFactory();
	AddFactory(new DroneFactory());
	AddFactory(new CustomerFactory());
	AddFactory(new PackageFactory());
	AddFactory(new RobotFactory());

}

DeliverySimulation::~DeliverySimulation() {
	for (int i = 0; i < factories_->GetFactories().size(); i++){
		delete factories_->GetFactories()[i];
	}
	delete factories_;
}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
	IEntity* entity = factories_->CreateEntity(val);
  	return entity;
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	factories_->AddFactory(factory);
}

void DeliverySimulation::AddEntity(IEntity* entity) {
	EntityBase* temp = dynamic_cast<EntityBase*> (entity);
	temp->SetId(countId);
	this->countId++;
  	entities_.push_back(entity);
}

void DeliverySimulation::SetGraph(const IGraph* graph) {g = graph;}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	Drone* temp_D;
	Robot* temp_R;
	int smallestSize = 900;
	int index;
	
	//Decides which  object should deliver package based on which one has the least amount of packages already
	for (int i = 0; i < entities_.size(); i++){
		if (JsonHelper::GetString(entities_[i]->GetDetails(), "type") == "drone") {
			temp_D = dynamic_cast<Drone*>(entities_[i]);
			if (temp_D->IsDead() == false) {
				if (temp_D->GetPackages().size() <= smallestSize) {
					index = i;
					smallestSize = temp_D->GetPackages().size();
				}
			}
		}
		if (JsonHelper::GetString(entities_[i]->GetDetails(), "type") == "robot") {
			temp_R = dynamic_cast<Robot*>(entities_[i]);
			if (temp_R->IsDead() == false) {
				if (temp_R->GetPackages().size() <= smallestSize) {
					index = i;
					smallestSize = temp_R->GetPackages().size();
				}
			}
		}
	}

	//Schedule Delivery
	if (JsonHelper::GetString(entities_[index]->GetDetails(), "type") == "drone") {
		temp_D = dynamic_cast<Drone*>(entities_[index]);
		temp_D->ClearObservers();
		for (int i = 0; i < observers.size(); i++){
			temp_D->SetObserver(observers[i]);
		}
		Package* p = dynamic_cast<Package*>(package);
		Customer* c = dynamic_cast<Customer*>(dest);
		p->SetCustomer(c);
		temp_D->SetGraph(g);
		temp_D->AddPackage(p);
	}

	if (JsonHelper::GetString(entities_[index]->GetDetails(), "type") == "robot") {
		temp_R = dynamic_cast<Robot*>(entities_[index]);
		temp_R->ClearObservers();
		for (int i = 0; i < observers.size(); i++){
			temp_R->SetObserver(observers[i]);
		}
		Package* p = dynamic_cast<Package*>(package);
		Customer* c = dynamic_cast<Customer*>(dest);
		p->SetCustomer(c);
		temp_R->SetGraph(g);
		temp_R->AddPackage(p);
	}
	
	picojson::object obj = JsonHelper::CreateJsonNotification();
	JsonHelper::AddStringToJsonObject(obj, "value", "scheduled");
	for (int i = 0; i < observers.size(); i++){
		observers[i]->OnEvent(JsonHelper::ConvertPicojsonObjectToValue(obj), *package);
	}
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {
	observers.push_back(observer);
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
	for (int i = 0; i < observers.size(); i++){
		if (observers[i] == observer){
			observers.erase(observers.begin() + i);
			break;
		}
	}
}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

std::vector<IEntityObserver*> DeliverySimulation::GetObservers() { return observers; }

void DeliverySimulation::Update(float dt) {
	for (int i = 0; i < entities_.size(); i++){

		if (JsonHelper::GetString(entities_[i]->GetDetails(), "type") == "drone") {
			Drone* drone = dynamic_cast<Drone*>(entities_[i]);
			
			//Reschedule packages of Drone's with dead batteries
			if (drone->IsDead()) {
				std::vector<Package*> packages = drone->GetPackages();
				for (int i = 0; i < packages.size(); i++) {
					ScheduleDelivery(packages.at(i), packages.at(i)->GetCustomer());
				}
			}
			
			drone->UpdatePosition(dt);
		}

		if (JsonHelper::GetString(entities_[i]->GetDetails(), "type") == "robot") {
			Robot* robot = dynamic_cast<Robot*>(entities_[i]);
			
			//Reschedule packages of Drone's with dead batteries
			if (robot->IsDead()) {
				std::vector<Package*> packages = robot->GetPackages();
				for (int i = 0; i < packages.size(); i++) {
					ScheduleDelivery(packages.at(i), packages.at(i)->GetCustomer());
				}
			}
			
			robot->UpdatePosition(dt);
		}

		if (JsonHelper::GetString(entities_[i]->GetDetails(), "type") == "package"){
			Package* package = dynamic_cast<Package*>(entities_[i]);
			if (package->IsDelivered()){
				std::vector<float> hide{1, 1, 1};
				package->UpdatePosition(hide);
			}
		}
	}
}


// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {

	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
