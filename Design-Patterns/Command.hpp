#pragma once
#include "Print.hpp"

// Concept From: Head First Design Patterns
// Example in C++ written by: Paul Burgess

// The command pattern encapsulates a request as an object.  The invoker is
// passed a command object.  The command object has one method (execute).  The
// command object contains a receiver that has knowledge on what it needs to
// E.g. Remote::press_button() -> CommandObject::execute() -> Receiver::turn_on()

// Definitions
// Client: Responsible for creating a Command and setting its receiver.  In the example below, the 'main()' function is the receiver.
// Invoker: Holds a command and asks that command to carry out a request by calling its execute() function.
// Receiver: Knows how to perform the work needed to carry out the request.
// Command Interface: Declared for all commands.  This function asks the receiver to perform an action (e.g. turn_on()).
// Command: Defines a binding between an action and a receiver.  The invoker makes a request by calling execute().
//          The ConcreteCommand carries it out by calling one or more actions on the Receiver.



// ------------ Receivers -------------
// Receivers "receive" the command request and have the knowledge on how to
// perform the request
class Light {
public:
	void turn_on() const {
		print("Turning light on");
	}
};

class GarageDoor {
public:
	void open() const {
		print("Garage door opening");
	}
	void close() const {
		print("Garage door closing");
	}
};


// ---------- Command Interface ----------
class Command {

public:
	virtual ~Command() = default;
	virtual void execute() const = 0;

};


// -------------- Commands --------------
// Create a command and pass the receiver to it
class LightOnCommand : public Command {
public:
	LightOnCommand(const Light& light)
		:m_light{ light } {
	}
	void execute() const override {
		m_light.turn_on();
	}
private:
	Light m_light;
};

class GarageDoorOpenCommand : public Command {
public:
	GarageDoorOpenCommand(const GarageDoor& garage_door)
		:m_garage_door{ garage_door } {
	}
	void execute() const override {
		m_garage_door.open();
	}
private:
	GarageDoor m_garage_door;
};


// ------------ Invoker ------------
// The object that runs the command (e.g. press button)
class RemoteControl {
public:
	RemoteControl()
		:m_command_slot{ nullptr } {
	}
	void set_command(Command* command) {
		m_command_slot = command;
	}
	void press_button() const {
		m_command_slot->execute();
	}
private:
	Command* m_command_slot;
};

// ------------- Client -------------
int main() {

	// Invoker
	// The remote control will eventually contain an object that it will call
	// to execute the request.  The remote control does not know anything about
	// how the request is executed.  It just knows how to call something that
	// knows what to do.
	RemoteControl remote_control;

	// Receiver (Knows how to execute the request)
	const Light light_object;

	// Command object (contains the receiver)
	Command* command = new LightOnCommand{ light_object };

	// Pass the command object to the invoker.  The invoker will call
	// the interface method 'execute'.  This will call the receivers functions
	// (in this case turn_on()).
	remote_control.set_command(command);
	remote_control.press_button();

	// Testing garage
	const GarageDoor garage_door_object;
	Command* another_command = new GarageDoorOpenCommand{ garage_door_object };
	remote_control.set_command(another_command);
	remote_control.press_button();

	delete command;
	delete another_command;
}