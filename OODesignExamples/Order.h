#pragma once

class Order
{
public:
	virtual ~Order() = default;
	virtual void execute() = 0;
};

