#include "LogicSystem.h"

using namespace LEDA;

void LogicSystem::registerGameObject(IGameObject* obj) {
	this->objects.push_back(obj);
	obj->init();
}