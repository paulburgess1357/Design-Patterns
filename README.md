# Design Patterns
Simple C++ Design Pattern Examples

### Strategy
The strategy patten allows behavior to be changed at runtime.  It defines a set of algorithms that can be used interchangeably.  For example, paying for a meal can be considered a strategy.  There are various options for paying for a meal (credit card, cash, check, etc.).  These methods ("algorithms") can all be used to pay for a meal and be used interchangeably.  When used as a strategy patten, each payment option would be encapsulated and easily "swapped" with another payment method.  The result is still the same, in that the meal is paid.

Examples:
  - Link1
  - Link2

### Observer
The observer patten defines a one-to-many relationship.  When the "one" (subject) object changes state, the "many" (dependents/observers) are notified of the state change and update automatically.  The subject maintains a list of its observers without tightly coupling the relationship.  For example, say you are interested in the score of a particular football game.  You could hit refresh over and over to get the updated score.  Other users like yourself could do the same thing.  However, that would be inefficient, as most of the time there will not be a change in score.  Alternatively, you could "register" yourself with a particular score tracking service.  Other users could do the same.  When the score changes, the score service (subject) will notify its dependents (observers - you and other users) of the change.  You and the other users can then decide independently what you want to do with that information.

Examples:
  - Link1
  - Link2

### Decorator
The decorator patten allows the user to dynamically add new functionality to an existing object.  It provides a flexible alternative to the inheritance structure and allows functionality to be easily extended.  You can think of the decorator patten as a “wrapper” pattern.  You take existing objects and “wrap” them with new classes that contain the desired behavior.  Both the “wrapper” classes and “original” object classes share the same interface.  This ensures that any downstream functions/classes will not be affected by the wrapped class.

For example, say you own a coffee shop.  Some customers may want sprinklers, some may want whipped cream, and some may want both.  You can take the base coffee class and “wrap” the object with the desired ingredient variations.  You provide the customers with the objects: Coffee, Sprinkles { Coffee }, WhippedCream { Coffee }, Sprinkles{ WhippedCream { Coffee } }, etc.  These objects all share the same interface (say “DeliciousCaffeineDrink”), so any downstream functionality will continue to operate.  This can be done for any number of ingredient combinations.  You have extended the coffee variations by adding new classes that share a common interface.

Examples:
  - Link1
  
### Creational Patterns
  
#### Abstract Factory
The abstract factory pattern provides an interface for creating related objects.  Subclass factories are used to create and instantiate the related products.   Adding a new group of related products is done simply by creating a new subclass factory.  The products produced by the subclass factories share a common interface by their “type”.  

For example, say you have an abstract “car parts” factory.  Subclass factories could be “sports car parts” and “off-road car parts”.  Each factory would create an engine and wheels (sports car engine, sports car wheels, off-road car engine, off-road car wheels).  These products would share a common interface.  The engine products would all share the “engine” interface.  The wheel products would all share the “wheel” interface.  The downstream code remains unaltered because it only cares about the interface type implemented by the actual product (wheels->turn(); engine->rev(); etc.).

Example:
  - Link1

#### Factory Method
The factory method creates a common interface for object creation.  The superclass (“Parent Factory”) contains the method for object creation but delegates the “type” of object being created to its subclasses (Think of them as “mini” factories that produce one product type).  The subclass factories are designed to create specific product types (via the ‘new’ method).  The products that are created from the factories all share a common interface.  This allows any downstream processing to remain unaltered.  

Example:
  - Link1

### Singleton
The singleton pattern is used when you want to have a single instance of a class across the entire program.  This is typically done by making the constructor of the class private.  A public static function will create a new class object or return the existing object.

Example:
  - Link1
  
### Command
The command pattern is a behavioral design pattern.  Objects (“receivers”) contain all of the necessary information to perform specific tasks (e.g. turn_on_light()).  These objects are contained in a command object with a simple execute() function (The execute function calls the light function from above).  An invoker holds all of the commands and is responsible for initiating the execute call.

For example, say you have a programmable remote (“invoker”).  You have a class that turns on the tv (“receiver”).  Since the remote can only be programmed with commands, you create a command object.  The command object is constructed and holds the tv class and logic.  This command object is placed with the associated remote button.  The calls look like this:  
  - remote.push_button()
    - command->execute()
	  - tv.turn_on()

This allows for any number of commands/logic to be programmed with the remote.  The logic is encapsulated within the receivers.  The invoker has no knowledge on how the action is performed.  All it knows is that it can call "execute()".  The command object holding the receiver will delegate the call to the receiver.

Example:
  - Link1

### Adapter
The adapter pattern is used to translate from one interface to another.  A great real world example is the use of outlet converters.  When you travel from the US to another country, you need an “adapter” to connect your electronics.  The plug from your laptop (aka “client”) uses the “adapter” to connect to the wall outlet (“adaptee”).  The client (plug) knows nothing about the adaptee (outlet).  As far as the client is concerned, it is connected to the correct interface.  The client and adaptee are completely decoupled. 

Example:
  - Link1

### Facade
The façade pattern provides a simplified interface to a set of interfaces and classes in a subsystem.  The goal of the façade pattern is to make the system easier to use.  This is done through composition.  For example, say you needed to ship a product.  You would have to open the box, package the product, close the box, tape it shut, label it, and send it to the post office.  Those are a lot of tasks to do each time.  The façade pattern would take all of those tasks and roll it up into a simple function: ship_product().  Each of those functions may belong to separate classes.  If that’s the case, the façade pattern class will hold each of those classes internally and call their methods.  In short, the façade pattern is a class that is a composition of other classes.  It simplifies complex calls.  If more specialized functionality is needed, the client still has access to each individual class/function (outside the façade pattern).

### Principle of Least Knowledge ("Law of Demeter")
The principle of least knowledge reduces interactions between objects.  It helps us create designs that have a limited number of coupled classes.  When a system is built on too many coupled classes, it becomes fragile and difficult to maintain.  In short, the following guidelines should be used when calling methods within a class:
  -	Use methods in the object itself
  -	Use methods from objects passed in as parameters
  - Use methods from any objects that are created or instantiated
  -	Use methods from any public/protected/private components

The above guidelines mean you cannot use methods from an object you get back from another call.  For example, this would be incorrect:
```
// Concept From: Head First Design Patterns

// Bad
float get_driving_time(){
	Thermometer thermometer = station.get_thermometer();
	return thermometer.get_temp();
}

// Good
float get_temp(){
	return station.get_temp();
}
```

In the good example from above, we have added a method to the station class.  This reduces the number of classes that we are depend on.

Example:
  - Link1
