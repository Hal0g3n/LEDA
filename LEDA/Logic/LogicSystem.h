#include <vector>
#include "ISystem.h"

namespace LEDA {

	class LogicSystem: public ISystem {
		std::vector<IGameObject*> objects{};

	public:
		// Called on Intialize
		LogicSystem() {};

		// Called on Destroy
		~LogicSystem() { for (IGameObject* obj : objects) delete obj; };

		void init() {};
		void update() { for (IGameObject* obj : objects) obj->update(); };
		void free() { for (IGameObject* obj : objects) obj->destroy(); objects.clear(); };
		
		// Called on new Game Object
		void registerGameObject(IGameObject*);
	};
}