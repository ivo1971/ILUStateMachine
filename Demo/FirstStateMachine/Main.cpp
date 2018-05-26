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
//statemachine includes
#include "CStateEvtId.h"
#include "CStateMachineData.h"
#include "Logging.h"
#include "TCreateStateNoData.h"

//make using the library easy
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

/****************************************************************************************
 ** 
 ** First state
 **
 ** This state has 1 event handler. The event ID is an integer (value 1). It calls the
 ** registered handler and then switches to the second state.
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
		  HANDLER_NO_DATA(CState1, HandlerEvt1), //< the event handler
		  CreateState2(),                        //< the state transition: switch to state-2 when the handler returns
		  1                                      //< the event ID (type integer)
		  );
    LogInfo(boost::format("[%1%][%2%] [%3%] created\n") % __FUNCTION__ % __LINE__ % GetName());
  }
  
  ~CState1(void)
  {
    LogInfo(boost::format("[%1%][%2%] [%3%] destructed\n") % __FUNCTION__ % __LINE__ % GetName());
  }
  
public:
  void HandlerEvt1(const CStateMachineData*)
  {
    LogInfo(boost::format("[%1%][%2%] [%3%] handle first event\n") % __FUNCTION__ % __LINE__ % GetName());
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
    LogInfo(boost::format("[%1%][%2%] [%3%] created\n") % __FUNCTION__ % __LINE__ % GetName());
  }
  
  ~CState2(void)
  {
    LogInfo(boost::format("[%1%][%2%] [%3%] destructed\n") % __FUNCTION__ % __LINE__ % GetName());
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
 **
 ***************************************************************************************/
int main (void)
{
   LogInfo(boost::format("[%1%][%2%] first-statemachine demo in\n") % __FUNCTION__ % __LINE__);

   //create a local scope so that the state machine is
   //destructed when it has handled the event
   {
     //create the state machine
     SPStateMachine spStateMachine = CreateStateMachine();

     //handle event
     spStateMachine->EventHandle((CStateMachineData*)NULL, 1);
   }
   
   LogInfo(boost::format("[%1%][%2%] first-statemachine demo out\n") % __FUNCTION__ % __LINE__);
   return 0;
}

