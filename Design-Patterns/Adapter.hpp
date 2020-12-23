#pragma once
#include "Print.hpp"

// Concept From: Head First Design Patterns
// Example in C++ written by: Paul Burgess

// The adapter pattern is used as a way to "translate" from one interface
// to another.


// ---------- Class Interface ----------
// This is what you need to adapt "TO".  
class DuckClass{
public:
	virtual ~DuckClass() = default;
	virtual void quack() const = 0;
	virtual void fly() const = 0;
};

// The fluffy duck as no problem working with the Duck interface
class FluffyDuckClass : public DuckClass{
public:
	void quack() const override{
		print("Fluffy Duck Quacking!");
	}
	void fly() const override{
		print("Its so FLUFFY!!! (That fluffy duck flying!)");
	}	
};

// ---------- Class Interface ----------
// This interface is for Turkeys.  However, as we will see,
// our function at the bottom expects a Duck! (This is what
// we will create an adapter for).

// The Turkey is the "adaptee".
class TurkeyClass{
public:
	virtual ~TurkeyClass() = default;
	virtual void gobble() = 0;
	virtual void fly() = 0;
};

class CookedThanksgivingTurkeyClass : public TurkeyClass{
	void gobble() override{
		print("Did you just hear something in the oven?!");
	}
	void fly() override{
		print("Turkey flying away!!");
	}	
};

// ---------- Adapter ----------
class TurkeyToDuckAdapterClass : public DuckClass{
public:
	TurkeyToDuckAdapterClass(TurkeyClass* turkey)
		:m_turkey{ turkey }{		
	}

	void quack() const override{
		m_turkey->gobble();
	}

	void fly() const override{
		m_turkey->fly();
	}
		
private:
	TurkeyClass* m_turkey;
};


// ---------- Duck Test ---------
// This function (the "client") is meant for ducks.  However, for our purposes
// we need to feed it a turkey.  For example, if you have existing
// code and you get a new vender that your code does not work with.
// You may have to create an adapter (like we did above).
inline void test_duck(DuckClass* duck){
	duck->fly();
	duck->quack();
}

inline void adapter_1(){

	DuckClass* fluffy_duck = new FluffyDuckClass;

	TurkeyClass* yummy_turkey = new CookedThanksgivingTurkeyClass;
	DuckClass* converted_yummy_turkey = new TurkeyToDuckAdapterClass{yummy_turkey};

	test_duck(fluffy_duck);
	test_duck(converted_yummy_turkey);
	
	delete fluffy_duck;
	delete yummy_turkey;	
}