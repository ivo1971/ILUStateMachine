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
CCreateState CreateState1      (void);
CCreateState CreateStateDefault(void);

/****************************************************************************************
 ** 
 ** First state
 **
 ** This state has 1 event handler. The event ID is an integer (value 1).
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
                    CCreateState(),                     //< the state transition: stay in this state
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
 ** Default state
 **
 ** This state has 1 event handler. The event ID is an integer (value 2).
 **
 ***************************************************************************************/
/** Class definition of state-default
 **/
class CStateDefault : public ILULibStateMachine::CStateEvtId {
public:
   CStateDefault(WPStateMachine wpStateMachine)
      : CStateEvtId("state-default", wpStateMachine, true /* default state */)
   {
      //register event handlers
      EventRegister(
                    HANDLER(int, CStateDefault, HandlerEvt2), //< the event handler
                    CCreateState(),                           //< the state transition: stay in this state
                    2                                         //< the event ID (type integer)
                    );
      LogInfo("[%s][%u] [%s] created\n", __FUNCTION__, __LINE__, GetName().c_str());
   }
   
   ~CStateDefault(void)
   {
      LogInfo("[%s][%u] [%s] destructed\n", __FUNCTION__, __LINE__, GetName().c_str());
   }
   
public:
   void HandlerEvt2(const int* const pEvtData)
   {
      LogInfo("[%s][%u] [%s] handle event with data [%d]\n", __FUNCTION__, __LINE__, GetName().c_str(), *pEvtData);
   }
};

/** State transition function for state-1
 **/
CCreateState CreateStateDefault(void)
{
   return TCreateStateNoData<CStateDefault>();
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
                                               "state-machine",       //< name used for logging
                                               CreateState1(),        //< used by the state machine to create the initial state
                                               CreateStateDefault()   //< used by the state machine to create the initial state
                                               );
}

/****************************************************************************************
 ** 
 ** This is the main function.
 ** It instantiates the state machine with a current state and
 ** a default state.
 **
 ***************************************************************************************/
int main (void)
{
   //EnableSerialLogDebug();
   LogInfo("[%s][%u] default-state demo in\n", __FUNCTION__, __LINE__);
   
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

      //handle event
      //(local scoping event data)
      LogInfo("[%s][%u] send second event\n", __FUNCTION__, __LINE__);
      {
         int iEvtData = 10;
         spStateMachine->EventHandle(&iEvtData, 2);
      }

      //handle event
      //(local scoping event data)
      LogInfo("[%s][%u] send third event\n", __FUNCTION__, __LINE__);
      {
         int iEvtData = 15;
         spStateMachine->EventHandle(&iEvtData, 3);
      }

      //finished sending events
      LogInfo("[%s][%u] sending events done\n", __FUNCTION__, __LINE__);
   }
   
   LogInfo("[%s][%u] default-state demo out\n", __FUNCTION__, __LINE__);
   return 0;
}

