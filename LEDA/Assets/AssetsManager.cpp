#include "AssetsManager.h"
#include <fstream>

using namespace LEDA;

bool  AssetsManager::loadNext(std::ifstream) {
	return true; // If successfully loaded
}
void* AssetsManager:: getAsset(std::string) {}