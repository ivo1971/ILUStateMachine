# ILUStateMachine demo applications
This directory contains a number of small 1-file demo applications that illustrate the usage of libStateMachine.
This document describes them from the easiest application to the more advanced applications.


###FirstStateMachine
This application is called 'FirstStateMachine' since it is the first one you should take a look at.

The state machine has 2 states: state-1 and state-2. 

The state machine starts in state-1.

state-1 has 1 event handler which results in a state transition to state-2 when it triggers.

The event type is a plain integer.

The event handlers are called without event data.
> Note: it is assumed that this will not happen wih real-world events. 
> Hence the event handler prototypes still have 1 parameter.

###FirstStateMachineWithData
This application builds on the previous one. It has the following changes:

* The event handlers are now called **with** event data (a plain integer). This data is logged in the event handlers;
* state-2 also has an event handler. The handler specifies that the event will **not** result in a state transition. 

###NoneStandardStateFlowInHandler
The event registrations always define the next state when the event is handled. This next state can be:

* an actual state - in which case the current state instance will be destructed and a new state instance will be instantiated;
* an indication to remain in the same state (*CCreateState()*);
* an indication to set the next state to *NULL* (meaning the state machine has finished).

So the registered event handlers define a **normal** flow.
Often state machines also have a special flow, for example when something goes wrong.

If a handlers wants to jump out of the **normal** flow, it throws a state-change exception (*CStateChangeException*). The exception defines the next state.

The demo application throws a state-change exception when the event handler in state-1 is called. In stead of transitioning to state-2, a state transition to state-3 is made.

###NoneStandardStateFlowInConstructor
This application is identical to the previous one except for the location of the state-change exception.
It is thrown from the constructor of state-2 instead of from the event handler in state-1.
As a result, the state machine engine will catch the exception after it has destructed state-1 while it is constructing state-2.
This again triggers a state transition to state-3.

###DefaultState
This application has a state machine with 2 states:

* state-1, as the previous state machines;
* a default state. The default state is constructed when the state machine itself is constructed, it is destructed when the state machine is destructed (*thus independent of state transitions*).

A default state can register handlers. These handlers will only be called when the current state itself does not have a matching handler for the event.

The default state handlers can even be called when the state machine has finished (*current state is NULL*).

The default state handlers can also result in state transitions, both by the event handler registrations and state-change exceptions from its handlers.

###GuardedHandlers
This state machine introduces guarded event handlers, where all previous applications have unguarded event handlers only.

A guarded handler registers 2 functions, next to the state transition of course:

1. The guard;
2. The event handler.

Nothing special about the event handler, once called it behaves in exactly the same way as the unguarded event handlers.
But before calling the handler the state machine engine first calls the guard. The guard returns a boolean value indicating whether there is a match (true) and the event handler has to be called or false when there is a mismatch and the event handler should not be called.
Since the guards are also called with the event data as parameter, this allows registering different **normal** event flows for the same event based upon the event data (or other criteria *, e.g. the number of times an event occured*).

Each event ID can have multiple guarded event handlers but only 1 (or zero) unguarded handlers. When an unguarded handler is registered, it is called when there are no guarded handlers or when all the guards return false.

Next to the guarded and unguarded handlers, a state can also register a handler for an event type. 
This handler is only called when both the current state and the default state have no matching event handlers.
Both the *normal* states and the *default* can register type handlers for event types. The ones in the *normal* state are checked first. Only when there is no match the ones in the *default* state are tried. 

**In any case, maximum 1 handler will be called for each event in 1 state machine.**

