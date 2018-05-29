# ILUStateMachine demo applications
This directory contains a number of small 1-file demo applications that illustrate the usage of libStateMachine.
This document describes them from the easiest application to the more advanced applications.


### FirstStateMachine
This application is called 'FirstStateMachine' since it is the first one you should take a look at.
The state machine has 2 states: state-1 and state-2. 
The state machine starts in state-1.
state-1 has 1 event handler which results in a state transition to state-2 when it triggers.
The event type is a plain integer and the event handlers are called without event data.
> Note: it is assumed that this will not happen wih real-world events. 
> Hence the event handler prototypes still have 1 parameter.

### FirstStateMachineWithData
This application builds on the previous one. It has the following changes:

* The event handlers are now called **with** event data (a plain integer). This data is logged in the event handlers;
* state-2 also has an event handler. The handler specifies that the event will **not** result in a state transition. 

### NoneStandardStateFlowInHandler
The event registrations always define the next state when the event is handled. This next state can be:

* An actual state - in which case the current state instance will be destructed and a new state instance will be instantiated;
* An indication to remain in the same state (*CCreateState()*);
* An indication to set the next state to *NULL* (meaning the state machine has finished).

So the registered event handlers define a **normal** flow.
Often state machines also have a special flow, for example when something goes wrong.

If a handlers wants to jump out of the **normal** flow, it throws a state-change exception (*CStateChangeException*). The exception defines the next state.

The demo application throws a state-change exception when the event handler in state-1 is called. In stead of transitioning to state-2, a state transition to state-3 is made.

### NoneStandardStateFlowInConstructor
This application is identical to the previous one except for the location of the state-change exception.
It is thrown from the constructor of state-2 instead of from the event handler in state-1.
As a result, the state machine engine will catch the exception after it has destructed state-1 while it is constructing state-2.
This again triggers a state transition to state-3.

### DefaultState
This application has a state machine with 2 states:

* state-1, as the previous state machines;
* A default state. The default state is constructed when the state machine itself is constructed, it is destructed when the state machine is destructed (*thus independent of state transitions*).

A default state can register handlers. These handlers will only be called when the current state itself does not have a matching handler for the event.

The default state handlers can even be called when the state machine has finished (*current state is NULL*).

The default state handlers can also result in state transitions, both by the event handler registrations and state-change exceptions from its handlers.

### GuardedHandlers
This state machine introduces guarded event handlers, where all previous applications have unguarded event handlers only.

A guarded handler registers 2 functions, next to the state transition of course:

1. The guard;
1. The event handler.

Nothing special about the event handler, once called it behaves in exactly the same way as the unguarded event handlers.
But before calling the handler the state machine engine first calls the guard. The guard returns a boolean value indicating whether there is a match (*true*) and the event handler has to be called or a mismatch (*false*) and the event handler should not be called.
Since the guards are also called with the event data as parameter, this allows registering different **normal** event flows for the same event based upon the event data (or other criteria *, e.g. the number of times an event occured*).

Each event ID can have multiple guarded event handlers but only 1 (or zero) unguarded handlers. When an unguarded handler is registered, it is called when there are no guarded handlers or when all the guards return false.

Next to the guarded and unguarded handlers, a state can also register a handler for an event type. 
This handler is only called when both the current state and the default state have no matching event handlers.
Both the *normal* states and the *default* can register type handlers for event types. The ones in the *normal* state are checked first. Only when there is no match the ones in the *default* state are tried. 

**In any case, maximum 1 handler will be called for each event in 1 state machine.**

### NestedStateMachine
This demo application is the most advanced one. It has 2 state machines in 1 application: the root state machine and the child state machine.
It is no longer a one-file application. Instead it is higly structured to illustrate the modular nature of the state machine engine:

1. Events;
1. StateMachineChild;
1. StateMachineRoot;
1. App.

##### Events
The events module contains event ID definitions, 1 for the root state machine and 1 for the child state machine.
Each event type (*EEventX*) has its own dedicated data class (*CEventXData*).
The link between event type and data class is **not** made in this module, it will be made upon registration of event handlers and when sending events.

##### StateMachineChild
A module containing the complete child state machine implementation. Its interface boils down to 1 function which creates the child state machine and returns a shared pointer to it.

The child state machine has 3 states:
1. child-state-1: has 1 event registration which will trigger a transition to child-state-2;
1. child-state-2: has 1 event registration which will trigger a transition to child-state-3;
1. child-state-3: has 1 event registration which will trigger a transition to the NULL state which means the state machine has finished.

##### StateMachineRoot
A module containing the complete root state machine implementation. Its interface boils down to 1 function which creates the root state machine and returns a shared pointer to it.

The root state machine has 3 states:
1. root-state-1: has 1 event registration which will trigger a transition to root-state-2;
1. root-state-2:
   ** constructs the child state machine when this state is constructed;
   ** has 1 event-type registration for child state machine events. The handler will forward all events to the child state machine as long as the child state machine is not finished;
   ** when the child state machine finished as the result of handling an event, this will trigger a transition to root-state-3;
1. root-state-3: has 1 event registration which will trigger no state transition.

##### App
The application that gluess all modules together.
It creates the root state machine (by calling its one interface function) and sends events to it.

