#include "ObjectPool.h"


Resource* ObjectPool::getResource()
{
	if (resourcePool.empty())
	{
		// Fetching new resource
		return new Resource;
	}
	else
	{
		// Fetching existing and ready resource
		Resource* resource = resourcePool.front();
		resourcePool.pop_front();

		return resource;
	}
}

void ObjectPool::returnResource(Resource* object)
{
	object->clean();
	resourcePool.push_back(object);
}