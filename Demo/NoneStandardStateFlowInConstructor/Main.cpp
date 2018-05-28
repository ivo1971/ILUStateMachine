/** @file
 ** @brief 1-file state machine demo
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
//include the statemachine library and make using it easy
#include "StateMachine.h"
using namespace ILULibStateMachine;

/****************************************************************************************
 ** 
 ** State create function declarations.
 ** These are used during event registration to define the next state after the handler
 ** returned.
 **
 ***************************************************************************************/
CCreateState CreateState1(void);
CCreateState CreateState2(void);
CCreateState CreateState3(void);

/****************************************************************************************
 ** 
 ** First state
 **
 ** This state has 1 event handler. The event ID is an integer (value 1). 
 ** In the registration of this handler, the standard flow is to switch to the second
 ** state.
 ** But the handler throws a state-change-exception to switch to the third state.
 **
 ***************************************************************************************/
/** Class definition of state-1
 **/
class CState1 : public ILULibStateMachine::CStateEvtId {
public:
   CState1(WPStateMachine wpStateMachine)
      : CStateEvtId("state-1", wpStateMachine)
   {
      //register event handlers
      EventRegister(
                    HANDLER(int, CState1, HandlerEvt1), //< the event handler
                    CreateState2(),                     //< the state transition: switch to state-2 when the handler returns
                    1                                   //< the event ID (type integer)
                    );
      LogInfo("[%s][%u] [%s] created\n", __FUNCTION__, __LINE__, GetName().c_str());
   }
   
   ~CState1(void)
   {
      LogInfo("[%s][%u] [%s] destructed\n", __FUNCTION__, __LINE__, GetName().c_str());
   }
   
public:
   void HandlerEvt1(const int* const pEvtData)
   {
      LogInfo("[%s][%u] [%s] handle event with data [%d]\n", __FUNCTION__, __LINE__, GetName().c_str(), *pEvtData);
   }
};

/** State transition function for state-1
 **/
CCreateState CreateState1(void)
{
   return TCreateStateNoData<CState1>();
}

/****************************************************************************************
 ** 
 ** Second state.
 **
 ** This state has no event handlers.
 **
 ***************************************************************************************/
/** Class definition of state-2
 **/
class CState2 : public ILULibStateMachine::CStateEvtId {
public:
   CState2(WPStateMachine wpStateMachine)
      : CStateEvtId("state-2", wpStateMachine)
   {
      //no event handlers
      LogInfo("[%s][%u] [%s] created\n", __FUNCTION__, __LINE__, GetName().c_str());
      throw CStateChangeException("none-standard state change", CreateState3());
   }
   
   ~CState2(void)
   {
      LogInfo("[%s][%u] [%s] destructed\n", __FUNCTION__, __LINE__, GetName().c_str());
   }
};

/** State transition function for state-2
 **/
CCreateState CreateState2(void)
{
   return TCreateStateNoData<CState2>();
}

/****************************************************************************************
 ** 
 ** Thirth state.
 **
 ** This state has no event handlers.
 **
 ***************************************************************************************/
/** Class definition of state-3
 **/
class CState3 : public ILULibStateMachine::CStateEvtId {
public:
   CState3(WPStateMachine wpStateMachine)
      : CStateEvtId("state-3", wpStateMachine)
   {
      //no event handlers
      LogInfo("[%s][%u] [%s] created\n", __FUNCTION__, __LINE__, GetName().c_str());
   }
   
   ~CState3(void)
   {
      LogInfo("[%s][%u] [%s] destructed\n", __FUNCTION__, __LINE__, GetName().c_str());
   }
};

/** State transition function for state-3
 **/
CCreateState CreateState3(void)
{
   return TCreateStateNoData<CState3>();
}

/****************************************************************************************
 ** 
 ** State machine.
 **
 ***************************************************************************************/
/** Function returning the state machine.
 **/
SPStateMachine CreateStateMachine(void)
{
   return CStateMachine::ConstructStateMachine(
                                               "state-machine", //< name used for logging
                                               CreateState1()   //< used by the state machine to create the initial state
                                               );
}

/****************************************************************************************
 ** 
 ** This is the main function.
 ** It instantiates the state machine and
 ** sends 1 event to it. 
 ** The event handler registration shows a state transition
 ** to state-2.
 ** However the constructor of state-2 throws and exception.
 ** So the state machine changes to state-3 (as defined in the
 ** state-change exception).
 **
 ***************************************************************************************/
int main (void)
{
   LogInfo("[%s][%u] none-standard-state-flow-in-constructor demo in\n", __FUNCTION__, __LINE__);
   
   //create a local scope so that the state machine is
   //destructed when it has handled the event
   {
      //create the state machine
      LogInfo("[%s][%u] create state machine\n", __FUNCTION__, __LINE__);
      SPStateMachine spStateMachine = CreateStateMachine();
      
      //handle event
      //(local scoping event data)
      LogInfo("[%s][%u] send first event\n", __FUNCTION__, __LINE__);
      {
         int iEvtData = 5;
         spStateMachine->EventHandle(&iEvtData, 1);
      }

      //finished sending events
      LogInfo("[%s][%u] sending events done\n", __FUNCTION__, __LINE__);
   }
   
   LogInfo("[%s][%u] none-standard-state-flow-in-constructor demo demo out\n", __FUNCTION__, __LINE__);
   return 0;
}

