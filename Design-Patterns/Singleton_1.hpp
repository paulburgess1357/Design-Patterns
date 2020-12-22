#pragma once
#include <string>
#include <iostream>

// Concept and example from: Refactor Guru Design Patterns
// Example in C++ written by: Paul Burgess

// Singleton Pattern
// Software design pattern that restricts the number of class instances to a
// single instance.


class Singleton {

public:
	// Normal constructor is private (below)

	// Delete copy constructor
	Singleton(Singleton& rhs) = delete;

	// Delete assignment constructor
	void operator=(const Singleton&) = delete;

	// Create singleton object on first run.  On second run,
	// return the existing instance of the object
	static Singleton* get_instance(const std::string& name) {
		if (m_singleton == nullptr) {
			m_singleton = new Singleton(name);
		}
		return m_singleton;
	}

	void see_name() const {
		std::cout << m_singleton_name << std::endl;
	}

private:
	Singleton(const std::string& name)
		:m_singleton_name(name) {
	}

	std::string m_singleton_name;
	static Singleton* m_singleton;

};

Singleton* Singleton::m_singleton = nullptr;

inline void singleton_1() {

	Singleton* my_singleton_object = Singleton::get_instance("Comet");
	my_singleton_object->see_name();

	my_singleton_object = Singleton::get_instance("Halley");
	my_singleton_object->see_name();

	delete my_singleton_object;
	
}