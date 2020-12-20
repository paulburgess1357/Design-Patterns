#pragma once

// Concept From: Head First Design Patterns
// Example in C++ written by: Paul Burgess

// Strategy Pattern

// The strategy pattern defines a family of algorithms, encapsulates each
// one, and makes them interchangeable.

// The below example encapsulates duck behaviors (algorithms) and makes them
// easily applicable to various types of ducks (interchangeable)


#include <iostream>
#include <memory>

// ---------- Flying Behavior (Algorithm) ----------
// Fly behaviors are interchangeable
class IFlyBehavior {

public:
	IFlyBehavior() = default;
	virtual ~IFlyBehavior() = default;
	virtual void fly() const = 0;
};

class FlyWithWings : public IFlyBehavior {
public:
	void fly() const override {
		std::cout << "I'm flying!" << std::endl;
	}
};

class FlyNoWay : public IFlyBehavior {
public:
	void fly() const override {
		std::cout << "I can't fly!" << std::endl;
	}
};

class RocketShipFly : public IFlyBehavior {
public:
	void fly() const override {
		std::cout << "I am faster than a rocket ship flying!" << std::endl;
	}
};


// ---------- Quacking Behavior (Algorithm) ----------
// Quack behaviors are interchangeable
class IQuackBehavior {

public:
	IQuackBehavior() = default;
	virtual ~IQuackBehavior() = default;
	virtual void quack() const = 0;
};

class Quack : public IQuackBehavior {
public:
	void quack() const override {
		std::cout << "Quack!" << std::endl;
	}
};

class CantQuack : public IQuackBehavior {
public:
	void quack() const override {
		std::cout << "<< Silence >>" << std::endl;
	}
};

class Squeak : public IQuackBehavior {
public:
	void quack() const override {
		std::cout << "Squeak Squeak" << std::endl;
	}
};


// Parent Duck
class Duck {

public:
	Duck(std::unique_ptr<IFlyBehavior> fly_behavior_ptr, std::unique_ptr<IQuackBehavior> quack_behavior_ptr)
		:m_fly_behavior_ptr{ std::move(fly_behavior_ptr) },
		m_quack_behavior_ptr{ std::move(quack_behavior_ptr) }{
	}

	virtual ~Duck() = default;

	virtual void display() const = 0;

	virtual void perform_fly() const {
		m_fly_behavior_ptr->fly();
	}
	virtual void perform_quack() const {
		m_quack_behavior_ptr->quack();
	}

	void float_in_water() const {
		std::cout << "All ducks can float!" << std::endl;
	}

	void set_fly_behavior(std::unique_ptr<IFlyBehavior> fly_behavior_ptr) {
		m_fly_behavior_ptr = std::move(fly_behavior_ptr);
	}

	void set_quack_behavior(std::unique_ptr<IQuackBehavior> quack_behavior_ptr) {
		m_quack_behavior_ptr = std::move(quack_behavior_ptr);
	}

private:
	std::unique_ptr<IFlyBehavior> m_fly_behavior_ptr;
	std::unique_ptr<IQuackBehavior> m_quack_behavior_ptr;
};


// Types of Ducks
class SillyDuck_CanFly_CantQuack : public Duck {
public:
	SillyDuck_CanFly_CantQuack()
		:Duck(std::make_unique<FlyWithWings>(), std::make_unique<CantQuack>()) {
	}

	void display() const override {
		std::cout << "I am a silly duck!" << std::endl;
	}
};

class RocketDuck : public Duck {
public:
	RocketDuck()
		:Duck(std::make_unique<RocketShipFly>(), std::make_unique<Squeak>()) {
	}

	void display() const override {
		std::cout << "I am a rocket powered duck!" << std::endl;
	}
};


inline void strategy_2() {

	std::cout << "Silly Duck" << std::endl;
	SillyDuck_CanFly_CantQuack flying_duck_cant_quack;
	flying_duck_cant_quack.display();
	flying_duck_cant_quack.perform_fly();
	flying_duck_cant_quack.perform_quack();

	std::cout << "Rocket Duck" << std::endl;
	RocketDuck rocket_duck;
	rocket_duck.display();
	rocket_duck.perform_fly();
	rocket_duck.perform_quack();

	// Update the rocket duck to change its quack dynamically!
	rocket_duck.set_quack_behavior(std::make_unique<Quack>());
	rocket_duck.perform_quack();
}