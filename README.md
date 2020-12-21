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
