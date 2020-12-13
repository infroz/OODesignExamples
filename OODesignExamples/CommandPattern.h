#pragma once
#include <string>
#include <iostream>
#include <list>

/*
	To run this example call Customer::run();
*/

using namespace std;

class Order // Command
{
public:
    virtual void Execute() = 0;
};

class Chef // Receiver
{
public:
	void CookBurger() {
		cout << "Cook - Im making a classic Burger\n";
	}

	void CookCustom(string o) {
		cout << "Cook - Im making a special order now: " + o + ".\n";
	}
};

class Bartender // Receiver
{
public:
	void PrepDrink(string drink) {
		cout << "Bartender - Im making a " << drink << "!\n";
	}

};


class DrinkOrder : public Order // ConcreteCommand
{
private:
	Bartender* receiver;
	string drink;
public:
	DrinkOrder(Bartender* rcv, string type) : receiver(rcv), drink(type){}
	void Execute() override {
		receiver->PrepDrink(drink);
	}
};

class BurgerOrder : public Order // ConcreteCommand
{
private:
	Chef* receiver;
public:
	BurgerOrder(Chef* rcv) : receiver(rcv){}
	void Execute() override {
		receiver->CookBurger();
	}
};

class CustomOrder : public Order // ConcreteCommand
{
private:
	Chef* receiver;
	string order;
public:
	CustomOrder(Chef* rcv, string o) : receiver(rcv), order(o)
	{
	}
	void Execute() override {
		receiver->CookCustom(order);
	}
};

class Waiter // Invoker
{
private:
	list<Order*> queue;
public:
	Waiter()
	{
	}
	void placeOrder(Order* order)
	{
		cout << "Waiter -  has accepted an order.\n";
		queue.push_back(order);
	}

	void sendOldestOrder() {
		if (queue.empty())
			return;

		cout << "Waiter - An order has been sent to a receiver (producer)\n";
		queue.front()->Execute();
		queue.pop_front();

	}

	void deleteOrder(Order* order) {
		queue.remove(order);
	}

	void deleteLatest() {
		cout << "Waiter - An order has been sent to a receiver (producer)\n";
		queue.pop_back();
	}
};

class Customer // client
{
public:
	void run() {
		// Initializing invoker and receiver
		Waiter waiter;
		Chef chef;
		Bartender bartender;

		// Client creates orders
		BurgerOrder order(&chef);
		CustomOrder cOrder(&chef, "French Toast");
		DrinkOrder drinkOrder(&bartender, "Margarita");
		DrinkOrder drinkOrder2(&bartender, "Moscow Mule");

		// Waiter takes orders
		waiter.placeOrder(&order);
		waiter.placeOrder(&cOrder);
		waiter.placeOrder(&drinkOrder);
		waiter.placeOrder(&drinkOrder2);

		//  Waiter misplaced order
		waiter.deleteLatest();

		// Waiter sends orders
		waiter.sendOldestOrder();
		waiter.sendOldestOrder();
		waiter.sendOldestOrder();
		waiter.sendOldestOrder(); // This order wont be executed as it doesnt exist
	}
};

