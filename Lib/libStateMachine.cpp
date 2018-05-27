/** @file
 ** @brief Library overall documentation.
 **
 ** ILUStateMachine is a library implementing a generic state machine engine.
 ** Copyright (C) 2018 Ivo Luyckx
 **
 ** This program is free software; you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License along
 ** with this program; if not, write to the Free Software Foundation, Inc.,
 ** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **
 **/

/** @brief This is the namespace that wraps the public interface of this library.
 **/
namespace ILULibStateMachine {
};

/** @mainpage ILULibStateMachine
 **
 ** This library has a state machine engine optimized to make implementing a state machine as easy and clean as possible.
 **
 ** \section intro_sec Introduction
 **
 ** It implements the following functionalities:
 ** - Each state is implemented as a cpp class;
 ** - A state machine:
 **   - Has one current state and a default state. The default state can register event handlers that kick-in when the current state does not have a registered handler for the event; 
 **   - Groups its data in a seperate class (not the state classes). There is exactly one instance from this class which is passed from state to state;
 ** - OnEntry and OnExit functions via the class constructor and destructor;
 ** - Dynamic event registration.
 **   Each event has an event ID, an event handler and a state transition (which can be 'stay in this state').
 **   Thus there is a clear overview and easy comparison against an UML state machine diagram;
 ** - Often there are state transitions that are not drawn in an UML diagram, for example error handling,
 **   because they make the diagram too complex.
 **   The engine uses a state-transition-exception to allow state transitions besides the normal was registered
 **   with the event handlers.
 **   These exceptions can be thrown both in handlers and in state constructors, they are not allowed in destructors 
 **   (which is standard C++ behaviour);
 ** - Type-events:
 **
 ** \subsection step1 Step 1: Opening the box
 **
 ** 
 **/

