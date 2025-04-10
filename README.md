**Creational Patterns:** Deal with object creation mechanisms, aiming to create objects in a manner suitable to the situation.

- **Factory**: _The Factory Pattern provides a way to encapsulate the object creation logic_
- **Abstract Factory**: _Provides an interface for creating families of related or dependent objects without specifying their concrete classes._
- **Builder**: _Separates the construction of a complex object from its representation, allowing the same construction process to create various representations._
- **Factory Method**: _Defines an interface for creating an object but allows subclasses to alter the type of objects that will be created._
- **Prototype**: _Creates new objects by copying an existing object, known as the prototype._
- **Singleton**: _Ensures a class has only one instance and provides a global point of access to it._
- **Lazy Initialization**: _Delays the creation of an object, the calculation of a value, or some other expensive process until the first time it is needed._
- **Object Pool**: _Avoids expensive acquisition and release of resources by recycling objects that are no longer in use._
- **Multiton**: _Extends the Singleton pattern to allow multiple instances, each identified by a unique key._


**Structural Patterns:** Concern class and object composition, using inheritance to compose interfaces and define ways to compose objects to obtain new functionality.

- **Object Adapter**: _The Object Adapter Pattern allows for an interface of one class to be adapted to a different interface of another class_
- **Class Adapter**: _The Class Adapter Pattern allows one class to adapt the interface of another class through inheritance._
- **Bridge**: _Decouples an abstraction from its implementation so that the two can vary independently._
- **Composite**: _Composes objects into tree structures to represent part-whole hierarchies, allowing clients to treat individual objects and compositions uniformly._
- **Decorator**: _Dynamically adds responsibilities to objects._
- **Facade**: _Provides a simplified interface to a complex subsystem._
- **Flyweight**: _Reduces the cost of creating and manipulating a large number of similar objects._
- **Proxy**: _Provides a surrogate or placeholder for another object to control access to it._
- **Dependency Injection**: _Injects dependencies into a class instead of hardcoding them, improving testability and flexibility._
- **Front Controller**: _Centralizes request handling by channeling all requests through a single handler, commonly used in web applications to manage navigation and authorization._
- **Fluent Interface**: _A pattern where method calls are chained together in a readable and expressive way. Typically, methods return *this._


**Behavioral Patterns:** Concerned with algorithms and the assignment of responsibilities between objects.

- **Chain of Responsibility**: _Delegates commands to a chain of processing objects._
- **Pipeline**: _The Pipeline pattern is a specific case of the Chain of Responsibility pattern where a series of processing steps (or functions) are applied to a piece of data sequentially._
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


**Concurrency Patterns:**

- **Active Object**: _Decouples method execution from method invocation to simplify multithreading._
- **Guarded Suspension**: _Suspends execution until a condition is met, used in concurrency scenarios._
- **Monitor Object**: _Encapsulates access to an object that can be accessed by multiple threads, ensuring mutual exclusion and synchronization._
- **Thread Pool**: _Manages a collection of threads to perform tasks, ensuring that threads are reused efficiently._
- **Read-Write Lock**: _The Read-Write Lock pattern allows multiple threads to read shared data concurrently while providing exclusive access for a thread when writing data._
- **Producer-Consumer**: _The Producer-Consumer design pattern solves problems related to shared data access by ensuring proper synchronization between producer and consumer threads._
- **Thread-Specific Storage**: _The Thread-Specific Storage (TSS) design pattern is used when you need to store data that is unique to each thread._
- **Future**: _The Future design pattern simplifies working with asynchronous programming by allowing you to get the result of an operation that may not be complete yet._


**Architectural Patterns:**

- **Event Sourcing**: _Stores the state of a system as a sequence of events rather than the current state._
- **CQRS (Command Query Responsibility Segregation)**: _Segregates the responsibilities of command (writing data) and query (reading data) to improve scalability and performance._
- **Microservices Architecture**: _Architecting a system as a collection of loosely coupled services._
- **Layered Pattern**: _Separates the system into layers such as presentation, business, data access, and service layers to promote separation of concerns._
- **Service Mesh**: _Used to manage microservices communication in a more structured way, often used in conjunction with microservices architectures._
- **Serverless Architecture**: _A cloud-native architecture style where the server management is abstracted away, and you only focus on the application logic._
- **Entity Component System (ECS)**: _An architectural pattern that decouples data (components) from behavior (systems),
 * improving flexibility and performance in complex applications such as game engines._


**User Interface Patterns:**

- **Model-View-Controller (MVC)**: _Separates the concerns of data (model), user interface (view), and interaction logic (controller)._
- **Model-View-ViewModel (MVVM)**: _An extension of MVC, used primarily in applications with data-binding like WPF or Xamarin._
- **Presenter-First (or MVP)**: _Used in UI design where the "Presenter" acts as the middleman between the model and the view._


**Cloud and Distributed Systems Patterns:**

- **Circuit Breaker**: _Prevents a system from repeatedly attempting to execute an operation that's likely to fail, improving system resilience._
- **API Gateway**: _Acts as a single entry point for multiple microservices, often used in microservices architectures._
- **Event-Driven Architecture**: _Systems that are driven by events, where components react to the occurrence of events._


**Data Management Patterns:**

- **Lazy Load**: _Defers loading an object until it's actually needed, commonly used in databases and object-relational mapping (ORM) systems._
- **Repository Pattern**: _Encapsulates the logic for accessing data sources and abstracts it from the rest of the application._
- **Data Mapper**: _Separates the in-memory objects from the database schema, allowing the objects to remain unaware of the database's structure._
- **Unit of Work**: _Manages a set of operations on a data source, ensuring that all operations are completed successfully before committing them as a single transaction._
- **Cache-Aside**: _A pattern where the application code loads data from the cache if available, or loads it from the database if it is not present, and then stores it back in the cache for future access._


**Security Patterns:**

- **Access Control List (ACL)**: _Defines permissions for various users or groups for accessing resources in the system._
- **Token-Based Authentication**: _Uses tokens (like JWT) for authenticating users without maintaining server-side sessions._
- **OAuth**: _A popular pattern for delegated access to resources, typically used in scenarios where a client application needs to access data on behalf of a user._
- **Permission-based Access Control (PBAC)**: _A pattern for defining permission rules based on a user’s role, ensuring secure access to system resources._


**Domain-Driven Design (DDD) Patterns:**

- **Aggregate**: _Represents a group of related objects that are treated as a unit for data changes._
- **Domain Event**: _An event that signifies a state change in the domain, often used in CQRS._
- **Value Object**: _An object that represents a concept in the domain that has no identity and is immutable._
