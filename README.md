# ILUStateMachine
   ILUStateMachine is a library implementing a generic state machine engine. It is optimized to make implementing a state machine as easy and clean as possible. It is not optimized for binary size.

   > Copyright (C) 2018 Ivo Luyckx
   > License:GPL V2

   > Doxygen html documentation is generated while building the library.
   > This documentation describes the interface and usage of the library.

   ### Repository layout
   The main structur of this repository has to following directories:
   * Lib: the state machine library;
   * [Demo](https://github.com/ivo1971/ILUStateMachine/blob/master/Demo/README.md): demos that illustrate how the library can be used, both the most basic usage and advanced usage;
   * Test: applications used to unit-test the library;
   * doc: generating library doxygen documentation during a build.

   ### State machine engine features
   The engine has the following features:
   * Each state is a separate class, which allows giving each state is own data. There is no mandatory relation between the states, they do not have to derive from the same base class (*although this is possible if some common functionality is required);
   * When the state machine enters a state, it calls its constructor, which allows on-entry fuctionality;
   * When the state machine leaves a state, it calls its destructor, which allows on-exit fuctionality;
   * Next to the states a state machine can have a data class. One instance of this class will be constructed and will be provided to all state constructors. This allows:
      * the persist data between states;
      * enforces the data to be separated from the state implementations;
   * When a state is constructed, it registers event handlers applicable in that state. They are automatically unregistered when the state machine leaves the state;
   * Events have types. The type defines how an event can be identified. In the most basic form the identifier can be an integer or an enum. A type definition is always implemented as a C++ class; 
   * The engine has a template class that allows identifying events with 1 ID (*mandatory*) and up to 3 sub ID's (*optional*). For example a message can have a message category as ID and number (*or enum*) as sub ID; 
   * For each event that a state has to handle, an event handler has to be registered (state constructor). The map to the arrows in an UML state machine diagram;
   * An event registration has the following parts (some optional):
      * event identifier;
      * event guard (*optional*) to be called before the handler is called. The handler will only be called if the guard approves this (*returns true*);
      * event handler to be called, which is a member function of the state class. The event handler will be called with 1 parameter, the event data. This data gives more information about the event that occured, for example the message content;
      * state transition to be executed after the handler returns:
        * definition of the next state;
        * stay in the current state;
        * the state machine has finished: current state is destructed, no new state is constructed.
   * One event identifier can have multiple registrations:
      * [0,n] guarded handlers: the guards should be mutually exclusive although the engine has no way of checking this. If the guards are not mutually exclusive it cannot be predicted which one will be called for a certain event;
      * [0,1] unguarded handler: if all guards reject the event or if there are no guards, the unguarded handler will be called if it has been registered;
      * [0,1] event type hander: this handler does not match 1 event but all events of the same type (*thus the same C++ class defining the event). The type handler is only called if there is no prior match in the more specific handlers.
        The type handler makes it easy to forward all events of a certain type to a nested state machine;
   * Each state machine can have 1 default state (*its implementation is identical to the other state implementations: a class with a constructor and a destructor*). The default state:
      * is instantiated when the state machine is created and destructed when the state machine is destructed. Once created it cannot be changed;
      * can register event handlers as any other state. When an event occurs the engine will try to find a matching handler in the following order:
         * current state guarded handlers;
         * current state unguarded handler;
         * default state guarded handlers;
         * default state unguarded handlers;
         * current state type handler;
         * default state type handler;
   * In any case maximum one event handler will be called per event;
   * Calling a handler in the default state can result in a state transition;
   * State transitions are registered together with the events. This allows easily comparing the registered events with their handlers and state transitions against the UML state machine diagram. This becomes even easier when all state constructors and destructors for one state machine are grouped in one file. *It would even be possible to generat this file automatically starting from an UML diagram altough this has not been implemented*;
   * Since the handler registrations with event guards also register a state transition, arrows having a guard can be matched onto one handler registration;
   * An UML state machine diagram rarely shows all possible transitions. Often error transitions are not shown to avoid bloating the diagram. These transitions often reflect a state flow that occures in exceptional circumstances, for example a message response returning an error instead of the expected successful result. There are 2 ways to deal with this:
      * a guard is registered that checks for the error situation and deals with it. In that case the registration defines the state transition;
      * it is also possible to throw a state-transition-exception. This will result in the engine breaking the normal registered flow and have a state transition as dictated by the exception. This can be usefull when a processing error occures while handling the event that was not easily predicatable from inspecting the event data;
   * A state-transition-exception can also be thrown in a state constructor, **before** the state registers event handlers. This will result in an immediate and unconditional transition to the state dictated in the exception;
   * The state machine uses templates to implement event registration functions and event handlers. This prevents dynamic casting of event data and event ID's (*in type event handlers*).

   Take a look at the [demo's](https://github.com/ivo1971/ILUStateMachine/blob/master/Demo/README.md) to get a view on an actual state machine implementation. All demo's illustrate one feature.
  
