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
 ** Event enums.
 **
 ***************************************************************************************/
enum EEventsType1 {
   EEventsType1Id1 = 1,
   EEventsType1Id2 = 2,
   EEventsType1Id3 = 3
};

enum EEventsType2 {
   EEventsType2Id1 = 1,
   EEventsType2Id2 = 2,
   EEventsType2Id3 = 3
};

/****************************************************************************************
 ** 
 ** State create function declarations.
 ** These are used during event registration to define the next state after the handler
 ** returned.
 **
 ***************************************************************************************/
CCreateState CreateState1(void);

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
      /** register event handlers
       ** (all handlers use CCreateState() --> no state change)
       **/
      //handlers for event ID 1
      EventRegister(GUARD(int, CState1, GuardEvt1Data5),  HANDLER(int, CState1, HandlerEvt1Data5),           CCreateState(), EEventsType1Id1); //guarded handler
      EventRegister(GUARD(int, CState1, GuardEvt1Data10), HANDLER(int, CState1, HandlerEvt1Data10),          CCreateState(), EEventsType1Id1); //guarded handler
      //handlers for event ID 2
      EventRegister(GUARD(int, CState1, GuardEvt2Data5),  HANDLER(int, CState1, HandlerEvt2Data5),           CCreateState(), EEventsType1Id2); //guarded handler
      EventRegister(GUARD(int, CState1, GuardEvt2Data10), HANDLER(int, CState1, HandlerEvt2Data10),          CCreateState(), EEventsType1Id2); //guarded handler
      EventRegister(                                      HANDLER(int, CState1, HandlerEvt2),                CCreateState(), EEventsType1Id2); //unguarded handler (catch-all if none of the guards match for event ID 2)
      //handlers for event type EEventsType1
      EventTypeRegister(TEventEvtId<EEventsType1>::IdTypeInit().c_str(), HANDLER_TYPE(int, CState1, HandleEvtEEventsType1), CCreateState()); //type handler for 'EEventsType1' (catch-all if none of the other guarded and unguarded handlers for this type match)
      LogInfo("[%s][%u] [%s] created\n", __FUNCTION__, __LINE__, GetName().c_str());
   }
   
   ~CState1(void)
   {
      LogInfo("[%s][%u] [%s] destructed\n", __FUNCTION__, __LINE__, GetName().c_str());
   }
   
public:
   bool GuardEvt1Data5(const int* const pEvtData)
   {
      const bool bHandle = 5 == *pEvtData;
      LogInfo("Guard event with data [%d]: %s\n", *pEvtData, bHandle ? "match" : "mismatch");
      return bHandle;
   }
   
   bool GuardEvt1Data10(const int* const pEvtData)
   {
      const bool bHandle = 10 == *pEvtData;
      LogInfo("Guard event with data [%d]: %s\n", *pEvtData, bHandle ? "match" : "mismatch");
      return bHandle;
   }
   
   void HandlerEvt1Data5(const int* const)
   {
      LogInfo("[%s][%u] guarded handler EVT 1 data 5\n", __FUNCTION__, __LINE__);
   }

   void HandlerEvt1Data10(const int* const)
   {
      LogInfo("[%s][%u] guarded handler EVT 1 data 10\n", __FUNCTION__, __LINE__);
   }

   bool GuardEvt2Data5(const int* const pEvtData)
   {
      const bool bHandle = 5 == *pEvtData;
      LogInfo("Guard event with data [%d]: %s\n", *pEvtData, bHandle ? "match" : "mismatch");
      return bHandle;
   }
   
   bool GuardEvt2Data10(const int* const pEvtData)
   {
      const bool bHandle = 10 == *pEvtData;
      LogInfo("Guard event with data [%d]: %s\n", *pEvtData, bHandle ? "match" : "mismatch");
      return bHandle;
   }
   
   void HandlerEvt2Data5(const int* const)
   {
      LogInfo("[%s][%u] guarded handler EVT 2 data 5\n", __FUNCTION__, __LINE__);
   }

   void HandlerEvt2Data10(const int* const)
   {
      LogInfo("[%s][%u] guarded handler EVT 2 data 10\n", __FUNCTION__, __LINE__);
   }

   void HandlerEvt2(const int* const)
   {
      LogInfo("[%s][%u] unguarded handler EVT 2\n", __FUNCTION__, __LINE__);
   }

   void HandleEvtEEventsType1(SPEventBase spEvent, const int* const)
   {
      LogInfo("[%s][%u] unguarded handler EVT ID [%s]\n", __FUNCTION__, __LINE__, spEvent->GetId().c_str());
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
 ** sends several events to it that invoke the guarded,
 ** unguarded and type handlers.
 **
 ***************************************************************************************/
int main (void)
{
   EnableSerialLogDebug();
   LogInfo("[%s][%u] guarded-handlers demo in\n", __FUNCTION__, __LINE__);
   
   //create a local scope so that the state machine is
   //destructed when it has handled the event
   {
      //create the state machine
      LogInfo("[%s][%u] create state machine\n", __FUNCTION__, __LINE__);
      SPStateMachine spStateMachine = CreateStateMachine();
      
      //handle event
      //(local scoping event data)
      {
         const EEventsType1 evtId    = EEventsType1Id1;
         const int          iEvtData = 5;
         LogInfo("[%s][%u] send event [%d] with data [%d] --> invoke guarded HandlerEvt1Data5\n", __FUNCTION__, __LINE__, evtId, iEvtData);
         spStateMachine->EventHandle(&iEvtData, evtId);
      }

      //handle event
      //(local scoping event data)
      {
         const EEventsType1 evtId    = EEventsType1Id2;
         const int          iEvtData = 10;
         LogInfo("[%s][%u] send event [%d] with data [%d] --> invoke guarded HandlerEvt1Data10\n", __FUNCTION__, __LINE__, evtId, iEvtData);
         spStateMachine->EventHandle(&iEvtData, evtId);
      }

      //handle event
      //(local scoping event data)
      {
         const EEventsType1 evtId    = EEventsType1Id2;
         const int          iEvtData = 15;
         LogInfo("[%s][%u] send event [%d] with data [%d] --> invoke unguarded HandleEvt2\n", __FUNCTION__, __LINE__, evtId, iEvtData);
         spStateMachine->EventHandle(&iEvtData, evtId);
      }

      //handle event
      //(local scoping event data)
      {
         const EEventsType1 evtId    = EEventsType1Id3;
         const int          iEvtData = 5;
         LogInfo("[%s][%u] send event [%d] with data [%d] --> invoke type HandleEvtEEventsType1\n", __FUNCTION__, __LINE__, evtId, iEvtData);
         spStateMachine->EventHandle(&iEvtData, evtId);
      }

      //handle event
      //(local scoping event data)
      {
         const EEventsType2 evtId    = EEventsType2Id2;
         const int          iEvtData = 5;
         LogInfo("[%s][%u] send EEvents event [%u] with data [%d] --> unhandled\n", __FUNCTION__, __LINE__, evtId, iEvtData);
         spStateMachine->EventHandle(&iEvtData, evtId);
      }
      //finished sending events
      LogInfo("[%s][%u] sending events done\n", __FUNCTION__, __LINE__);
   }
   
   LogInfo("[%s][%u] guarded-handlers demo out\n", __FUNCTION__, __LINE__);
   return 0;
}

