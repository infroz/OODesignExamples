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

class BurgerOrder : public Order // ConcreteCommand
{
private:
	Chef* receiver;
public:
	BurgerOrder(Chef* rcv) : receiver(rcv)
	{
	}
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

		cout << "Waiter - An order has been sent to the chef\n";
		queue.front()->Execute();
		queue.pop_front();

	}
};

class Customer // client
{
public:
	void run() {
		// Initializing invoker and receiver
		Waiter waiter;
		Chef chef;

		// Client creates orders
		BurgerOrder order(&chef);
		CustomOrder cOrder(&chef, "French Toast");

		// Waiter takes orders
		waiter.placeOrder(&order);
		waiter.placeOrder(&cOrder);

		// Waiter sends orders
		waiter.sendOldestOrder();
		waiter.sendOldestOrder();
	}
};

