#pragma once
#include <list>
#include "Resource.h"

class ObjectPool
{
private:
	std::list<Resource*> resourcePool;
public:
	Resource* getResource();
};

