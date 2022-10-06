#include "LogicSystem.h"
#include "LogicComponent.h"
#include "IGameObject.h"
using namespace LEDA;

void LogicSystem::registerGameObject(IGameObject* obj) {
	this->objects.push_back(obj);
	LogicComponent* logic = getComponent<LogicComponent>(*obj);

	if (logic == nullptr) return;
	
	logic->init();
	objects.push_back(obj);
}