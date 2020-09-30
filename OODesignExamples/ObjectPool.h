#pragma once
#include <list>
#include <iostream>
/*
	To run call ObjectPoolPattern::run();
*/

class Resource
{
public:
	bool clean = true;
};

class ReusablePool
{
private:
	std::list<Resource*> _available;
public:
	ReusablePool() {
	}

	ReusablePool(int startSize) {
		std::cout << "Creating a pool of " << startSize << " resources.\n";
		for (int i = 0; i < startSize; i++)
			_available.push_back(new Resource());
	}

	void returnResource(Resource* object)
	{
		object->clean = true; // Calls a "reset" function
		_available.push_back(object); // adds resource back to pool
		std::cout << "Resource has been returned to pool!\n";
	}

	Resource* getResource()
	{
		Resource* rtn;

		if (_available.empty()) {
			std::cout << "Pool empty! Creating new resource.\n";
			rtn = new Resource();
		} else {
			std::cout << "Fetching resource from pool.\n";
			// Gets resource and removes it from the list
			rtn = _available.front(); _available.pop_front();
		}
		rtn->clean = false; // Once used no longer clean...
		return rtn;
	}

	int size() {
		return _available.size();
	}

};

class ObjectPoolPattern 
{
public:
	void run() {
		// Creates a pool containing 1 resources
		ReusablePool glassWare(1);
		list<Resource*> inUse;
		std::cout << "Requesting a glass resource - ";
		inUse.push_back(glassWare.getResource());
		std::cout << "Requesting a glass resource - ";
		inUse.push_back(glassWare.getResource());
		
		std::cout << "Returning glass resource - ";
		glassWare.returnResource(inUse.front());
		inUse.pop_front();

		std::cout << "Requesting a glass resource - ";
		inUse.push_back(glassWare.getResource());

		std::cout << "Returning glass resource - ";
		glassWare.returnResource(inUse.front());
		inUse.pop_front();
		std::cout << "Returning glass resource - ";
		glassWare.returnResource(inUse.front());
		inUse.pop_front();

		std::cout << "Pool now contains " << glassWare.size() << " resources.\n";
	}
};