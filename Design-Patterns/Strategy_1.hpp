#pragma once
#include "Print.hpp"
#include <memory>

// Concept From: Head First Design Patterns
// Example in C++ written by: Paul Burgess

// The strategy pattern defines a family of algorithms, encapsulates each
// one, and makes them interchangeable.

// The below example encapsulates weapon behaviors (algorithms) and makes them
// easily applicable to various types of characters (interchangeable)


// ---------- Weapon (algorithms) ----------
class WeaponBehavior {
public:
	WeaponBehavior() = default;
	virtual ~WeaponBehavior() = default;
	virtual void use_weapon() const = 0;
};

class KnifeBehavior : public WeaponBehavior {
	void use_weapon() const override {
		print("Using a knife!");
	}
};

class BowAndArrowBehavior : public WeaponBehavior {
	void use_weapon() const override {
		print("Aiming a bow!");
	}
};

class AxeBehavior : public WeaponBehavior {
	void use_weapon() const override {
		print("Chopping an axe!");
	}
};

class SwordBehavior : public WeaponBehavior {
	void use_weapon() const override {
		print("Swinging a sword!");
	}
};

class NoWeapon : public WeaponBehavior {
	void use_weapon() const override {
		print("No weapon exists! Uh oh!");
	}
};


// ----------------- Characters -----------------
// Weapon behaviors are interchangeable
class Character {

public:
	Character()
		:m_weapon{ std::move(std::make_unique<NoWeapon>()) } {
	}

	virtual ~Character() = default;

	void set_weapon(std::unique_ptr<WeaponBehavior> weapon) {
		m_weapon = std::move(weapon);
	}

	void use_weapon() const {
		m_weapon->use_weapon();
	}

	virtual void display() const = 0;

private:
	std::unique_ptr<WeaponBehavior> m_weapon;
};

class Queen : public Character {
public:
	void display() const override {
		print("I am a queen!");
	}
};

class King : public Character {
public:
	void display() const override {
		print("I am a king!");
	}
};

class Troll : public Character {
public:
	void display() const override {
		print("I am a troll!");
	}
};

class Knight : public Character {
public:
	void display() const override {
		print("I am knight!");
	}
};


// ---------------- Example ----------------
inline void strategy_1() {

	print("Queen");
	Queen queen_character;
	queen_character.display();
	queen_character.use_weapon();

	print("King");
	King king_character;
	king_character.display();
	king_character.use_weapon();

	print("Queen");
	queen_character.set_weapon(std::make_unique<SwordBehavior>());
	queen_character.use_weapon();

}
