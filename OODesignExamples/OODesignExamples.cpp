#include <iostream>
#include <list>
#include "ObjectPool.h"
#include "Resource.h"

int main()
{
    ObjectPool* glassPool = new ObjectPool;
    std::list<Resource*> glassesInUse;


    // Requesting a glass

    glassesInUse.push_back(glassPool->getResource()); // This will request a resource to our in use list



    delete glassPool;
}
