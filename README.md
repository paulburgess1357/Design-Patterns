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
