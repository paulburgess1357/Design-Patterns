#pragma once

// Concept From: Head First Design Patterns
// Example in C++ written by: Paul Burgess

// The decorator pattern attaches additional responsibilities to an object
// dynamically.  Decorators provide a flexible alternative to subclassing for
// extending functionality.

// The decorator pattern involves a set of decorator classes that are used to
// wrap concrete classes.  Decorator classes mirror the type of the components
// they decorate (either through interface or inheritance)


#include "Print.hpp"
#include <string>
#include <iostream>


// ---------------- Interface ----------------
class IConsumable {

public:
	IConsumable()
		:m_description{ "No Description Found" },
		m_cost{ 0.00f }{
	}
	virtual ~IConsumable() = default;
	virtual std::string get_description() const = 0;
	virtual float get_cost() const = 0;

protected:
	std::string m_description;
	float m_cost;
};


// ---------- Concrete Implementation ----------
class Espresso : public IConsumable {
public:
	Espresso() {
		m_description = "Espresso";
		m_cost = 1.99f;
	}

	virtual ~Espresso() = default;

	std::string get_description() const override {
		return m_description;
	}

	float get_cost() const override {
		return m_cost;
	}
};

class HouseBlend : public IConsumable {
public:
	HouseBlend() {
		m_description = "House Blend";
		m_cost = 2.99f;
	}

	virtual ~HouseBlend() = default;

	std::string get_description() const override {
		return m_description;
	}

	float get_cost() const override {
		return m_cost;
	}
};


// --------- Decorators (Wrappers) ---------
class SprinklesDecorator : public IConsumable {
public:
	SprinklesDecorator(IConsumable* consumable)
		:m_consumable{ consumable } {

		m_description = " + Sprinkles";
		m_cost = 0.20f;

	}

	std::string get_description() const override {
		return m_consumable->get_description() + m_description;
	}

	float get_cost() const override {
		return m_consumable->get_cost() + m_cost;
	}

private:
	IConsumable* m_consumable;
};

class WhippedCreamDecorator : public IConsumable {
public:
	WhippedCreamDecorator(IConsumable* consumable)
		:m_consumable{ consumable } {

		m_description = " + Whipped Cream";
		m_cost = 0.40f;

	}

	std::string get_description() const override {
		return m_consumable->get_description() + m_description;
	}

	float get_cost() const override {
		return m_consumable->get_cost() + m_cost;
	}

private:
	IConsumable* m_consumable;
};

class CherryDecorator : public IConsumable {
public:
	CherryDecorator(IConsumable* consumable)
		:m_consumable(consumable) {

		m_description = " + Cherry";
		m_cost = 0.10f;
	}

	std::string get_description() const override {
		return m_consumable->get_description() + m_description;
	}

	float get_cost() const override {
		return m_consumable->get_cost() + m_cost;
	}

private:
	IConsumable* m_consumable;
};


// ---------------- Example ----------------
inline void decorator_1() {

	// Create basic beverage
	IConsumable* coffee_type = new HouseBlend;
	print(coffee_type->get_description());
	print(coffee_type->get_cost());
	print("\n=======================\n");

	// Add sprinkles
	IConsumable* coffee_w_sprinkles = new SprinklesDecorator(coffee_type);
	print(coffee_w_sprinkles->get_description());
	print(coffee_w_sprinkles->get_cost());
	print("\n=======================\n");

	// Add Whipped Cream
	IConsumable* coffee_w_sprinkles_whipped_cream = new WhippedCreamDecorator(coffee_w_sprinkles);
	print(coffee_w_sprinkles_whipped_cream->get_description());
	print(coffee_w_sprinkles_whipped_cream->get_cost());
	print("\n=======================\n");

	// Add Cherry	
	IConsumable* coffee_w_sprinkles_whipped_cream_cherry = new CherryDecorator(coffee_w_sprinkles_whipped_cream);
	print(coffee_w_sprinkles_whipped_cream_cherry->get_description());
	print(coffee_w_sprinkles_whipped_cream_cherry->get_cost());
	print("\n=======================\n");

	// Simple coffee with whipped cream
	IConsumable* espresso_coffee = new Espresso;
	IConsumable* espresso_coffee_w_whipped_cream = new WhippedCreamDecorator(espresso_coffee);
	print(espresso_coffee_w_whipped_cream->get_description());
	print(espresso_coffee_w_whipped_cream->get_cost());

	delete coffee_type;
	delete coffee_w_sprinkles;
	delete coffee_w_sprinkles_whipped_cream;
	delete coffee_w_sprinkles_whipped_cream_cherry;
	delete espresso_coffee;
	delete espresso_coffee_w_whipped_cream;

}

