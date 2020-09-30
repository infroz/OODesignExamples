#pragma once
#include <iostream>

/*
	To run this example call ChainOfResponsibility::run();
*/

class OrderHandler
{
private:
	OrderHandler* next;

	bool working() { // Call this function on a seperate thread using async
		//std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulates work-time
		return true; // Returns true when complete
	}
public:
	OrderHandler() {
		next = 0;
	}

	void setSuccsessor(OrderHandler* n) {
		next = n;
	}

	
	virtual void handle(std::string i)
	{
		next->handle(i);
	}
};

class BartenderHandler : public OrderHandler
{
private:
	OrderHandler *waiter;
public:
	void setWaiter(OrderHandler* n) { waiter = n; };

	void handle(std::string i) {
		if (i == "1 drink") {
			std::cout << "Bartender handled order " + i + "\n";
			waiter->handle(i);
		} else {
			std::cout << "Bartender is handling order " + i + " and passed it on\n";
			OrderHandler::handle(i);
		}
	}
};

class ChefHandler : public OrderHandler
{
	void handle(std::string i) {
		std::cout << "Chef is handling order " + i + " and passed it on\n";
		OrderHandler::handle(i);
	}
};

class WaiterHandler : public OrderHandler
{
public:
	void handle(std::string i)
	{
		std::cout << "Waiter is serving order " + i + "\n";
	}
};

class ChainOfResponsibility {
public:
	void run()
	{
		BartenderHandler bartender;
		ChefHandler chef;
		WaiterHandler waiter;

		bartender.setSuccsessor(&chef);
		bartender.setWaiter(&waiter); // shortcut to waiter
		chef.setSuccsessor(&waiter);

		bartender.handle("1 drink");
		bartender.handle("1 meal 2 drinks");
	}
};