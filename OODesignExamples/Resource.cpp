#include "Resource.h"
Resource::Resource() {
	cleaned = true;
}

void Resource::clean() // functions a "reset" function
{
	cleaned = true;
}

void Resource::use()
{
	cleaned = false;
}

bool Resource::check() {
	return cleaned;
}