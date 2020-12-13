#include <iostream>
#include <list>
#include "future"
#include "CommandPattern.h"
#include "ObjectPool.h"
#include "ChainOfResponsibility.h"

int main()
{
	ChainOfResponsibility cm;

	cm.run();
}
