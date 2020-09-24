#pragma once
#include <string>

class Resource
{
private:
	bool cleaned;
public:
	Resource();
	void clean();
	void use();
	bool check();
};

