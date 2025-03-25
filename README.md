**Creational Patterns:** Deal with object creation mechanisms, aiming to create objects in a manner suitable to the situation.

- **Abstract Factory**: _Provides an interface for creating families of related or dependent objects without specifying their concrete classes._
- **Builder**: _Separates the construction of a complex object from its representation, allowing the same construction process to create various representations._
- **Factory Method**: _Defines an interface for creating an object but allows subclasses to alter the type of objects that will be created._
- **Prototype**: _Creates new objects by copying an existing object, known as the prototype._
- **Singleton**: _Ensures a class has only one instance and provides a global point of access to it._
- **Lazy Initialization**: _Delays the creation of an object, the calculation of a value, or some other expensive process until the first time it is needed._
- **Object Pool**: _Avoids expensive acquisition and release of resources by recycling objects that are no longer in use._
- **Multiton**: _Extends the Singleton pattern to allow multiple instances, each identified by a unique key._

**Structural Patterns:** Concern class and object composition, using inheritance to compose interfaces and define ways to compose objects to obtain new functionality.

- **Adapter**: _Allows classes with incompatible interfaces to work together by wrapping its own interface around that of an already existing class._
- **Bridge**: _Decouples an abstraction from its implementation so that the two can vary independently._
- **Composite**: _Composes objects into tree structures to represent part-whole hierarchies, allowing clients to treat individual objects and compositions uniformly._
- **Decorator**: _Dynamically adds responsibilities to objects._
- **Facade**: _Provides a simplified interface to a complex subsystem._
- **Flyweight**: _Reduces the cost of creating and manipulating a large number of similar objects._
- **Proxy**: _Provides a surrogate or placeholder for another object to control access to it._
- **Dependency Injection**: _Injects dependencies into a class instead of hardcoding them, improving testability and flexibility._
- **Front Controller**: _Centralizes request handling by channeling all requests through a single handler, commonly used in web applications to manage navigation and authorization._

**Behavioral Patterns:** Concerned with algorithms and the assignment of responsibilities between objects.

- **Chain of Responsibility**: _Delegates commands to a chain of processing objects._
- **Command**: _Encapsulates a request as an object, thereby allowing for parameterization of clients with queues, requests, or operations._
- **Interpreter**: _Implements a specialized language._
- **Iterator**: _Provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation._
- **Mediator**: _Defines an object that encapsulates how a set of objects interact._
- **Memento**: _Provides the ability to restore an object to its previous state (undo)._
- **Observer**: _Defines a one-to-many dependency between objects where a state change in one object results in all its dependents being notified and updated automatically._
- **State**: _Allows an object to alter its behavior when its internal state changes._
- **Strategy**: _Defines a family of algorithms, encapsulates each one, and makes them interchangeable._
- **Template Method**: _Defines the skeleton of an algorithm in an operation, deferring some steps to subclasses._
- **Visitor**: _Represents an operation to be performed on the elements of an object structure, allowing for a new operation to be defined without changing the classes of the elements on which it operates._
- **Null Object**: _Avoids null references by providing a default object._
- **Servant**: _Defines common functionality for a group of classes._
- **Specification**: _Recombinable business logic in a Boolean fashion._
- **Blackboard**: _Utilizes a common knowledge base, the "blackboard," where different subsystems contribute information to solve a problem collaboratively._
