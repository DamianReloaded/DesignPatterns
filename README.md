# DesignPatterns
c++ implementation of design patterns

**Creational Patterns:** Deal with object creation mechanisms, aiming to create objects in a manner suitable to the situation.

- Abstract Factory: Provides an interface for creating families of related or dependent objects without specifying their concrete classes.
- Builder: Separates the construction of a complex object from its representation, allowing the same construction process to create various representations.
- Factory Method: Defines an interface for creating an object but allows subclasses to alter the type of objects that will be created.
- Prototype: Creates new objects by copying an existing object, known as the prototype.
- Singleton: Ensures a class has only one instance and provides a global point of access to it.
- Lazy Initialization: Delays the creation of an object, the calculation of a value, or some other expensive process until the first time it is needed.
- Object Pool: Avoids expensive acquisition and release of resources by recycling objects that are no longer in use.
- Multiton: Extends the Singleton pattern to allow multiple instances, each identified by a unique key.

**Structural Patterns:** Concern class and object composition, using inheritance to compose interfaces and define ways to compose objects to obtain new functionality.

- Adapter: Allows classes with incompatible interfaces to work together by wrapping its own interface around that of an already existing class.
- Bridge: Decouples an abstraction from its implementation so that the two can vary independently.
- Composite: Composes objects into tree structures to represent part-whole hierarchies, allowing clients to treat individual objects and compositions uniformly.
- Decorator: Dynamically adds responsibilities to objects.
- Facade: Provides a simplified interface to a complex subsystem.
- Flyweight: Reduces the cost of creating and manipulating a large number of similar objects.
- Proxy: Provides a surrogate or placeholder for another object to control access to it.
- Dependency Injection: Injects dependencies into a class instead of hardcoding them, improving testability and flexibility.
- Front Controller: Centralizes request handling by channeling all requests through a single handler, commonly used in web applications to manage navigation and authorization.

**Behavioral Patterns:** Concerned with algorithms and the assignment of responsibilities between objects.

- Chain of Responsibility: Delegates commands to a chain of processing objects.
- Command: Encapsulates a request as an object, thereby allowing for parameterization of clients with queues, requests, or operations.
- Interpreter: Implements a specialized language.
- Iterator: Provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.
- Mediator: Defines an object that encapsulates how a set of objects interact.
- Memento: Provides the ability to restore an object to its previous state (undo).
- Observer: Defines a one-to-many dependency between objects where a state change in one object results in all its dependents being notified and updated automatically.
- State: Allows an object to alter its behavior when its internal state changes.
- Strategy: Defines a family of algorithms, encapsulates each one, and makes them interchangeable.
- Template Method: Defines the skeleton of an algorithm in an operation, deferring some steps to subclasses.
- Visitor: Represents an operation to be performed on the elements of an object structure, allowing for a new operation to be defined without changing the classes of the elements on which it operates.
- Null Object: Avoids null references by providing a default object.
- Servant: Defines common functionality for a group of classes.
- Specification: Recombinable business logic in a Boolean fashion.
- Blackboard: Utilizes a common knowledge base, the "blackboard," where different subsystems contribute information to solve a problem collaboratively.


