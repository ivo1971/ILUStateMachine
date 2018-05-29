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

#include "CEventChildData.h"
#include "CEventRootData.h"
#include "EEventChild.h"
#include "EEventRoot.h"

#include "StateMachineRoot.h"

/****************************************************************************************
 ** 
 ** This is the main function of the nested-statemachine demo.
 **
 ***************************************************************************************/
int main (void)
{
   LogInfo("[%s][%u] nested-statemachine demo in\n", __FUNCTION__, __LINE__);
   
   //create a local scope so that the state machine is
   //destructed when it has handled the event
   {
      //create the state machine
      LogInfo("[%s][%u] create root state machine\n", __FUNCTION__, __LINE__);
      SPStateMachine spStateMachine = DemoNestedStateMachineRoot::CreateStateMachine();

      //send child-state-machine event
      //this is unhandled in root state 1
      {
         const DemoNestedStateMachineEvents::EEventChild     eventId  (DemoNestedStateMachineEvents::EEventChild1);
         const DemoNestedStateMachineEvents::CEventChildData eventData("child event 1");
         LogInfo("[%s][%u] send child-state-machine event ID [%u] with data [%s]\n", __FUNCTION__, __LINE__, eventId, eventData.Get().c_str());
         spStateMachine->EventHandle(&eventData, eventId);
      }
      
      //send root-state-machine event
      //this will result in a root-state-machine state change from state 1 to state 2
      {
         const DemoNestedStateMachineEvents::EEventRoot     eventId  (DemoNestedStateMachineEvents::EEventRoot1);
         const DemoNestedStateMachineEvents::CEventRootData eventData(1);
         LogInfo("[%s][%u] send root-state-machine event ID [%u] with data [%d]\n", __FUNCTION__, __LINE__, eventId, eventData.Get());
         spStateMachine->EventHandle(&eventData, eventId);
      }

      //send child-state-machine event
      //this will be forwarded by the root-state-machine in state 2 to the child-state-machine
      {
         const DemoNestedStateMachineEvents::EEventChild     eventId  (DemoNestedStateMachineEvents::EEventChild1);
         const DemoNestedStateMachineEvents::CEventChildData eventData("child event 1");
         LogInfo("[%s][%u] send child-state-machine event ID [%u] with data [%s]\n", __FUNCTION__, __LINE__, eventId, eventData.Get().c_str());
         spStateMachine->EventHandle(&eventData, eventId);
      }
      
      //send child-state-machine event
      //this will be forwarded by the root-state-machine in state 2 to the child-state-machine
      {
         const DemoNestedStateMachineEvents::EEventChild     eventId  (DemoNestedStateMachineEvents::EEventChild2);
         const DemoNestedStateMachineEvents::CEventChildData eventData("child event 2");
         LogInfo("[%s][%u] send child-state-machine event ID [%u] with data [%s]\n", __FUNCTION__, __LINE__, eventId, eventData.Get().c_str());
         spStateMachine->EventHandle(&eventData, eventId);
      }
      
      //send child-state-machine event
      //this will be forwarded by the root-state-machine in state 2 to the child-state-machine
      //this will also finish the child-state-machine, which will trigger a state transition to state 3 in the root-state-machine
      {
         const DemoNestedStateMachineEvents::EEventChild     eventId  (DemoNestedStateMachineEvents::EEventChild3);
         const DemoNestedStateMachineEvents::CEventChildData eventData("child event 3");
         LogInfo("[%s][%u] send child-state-machine event ID [%u] with data [%s]\n", __FUNCTION__, __LINE__, eventId, eventData.Get().c_str());
         spStateMachine->EventHandle(&eventData, eventId);
      }
      
      //send root-state-machine event
      //the root-state-machine will handle it but will stay in the same state
      {
         const DemoNestedStateMachineEvents::EEventRoot     eventId  (DemoNestedStateMachineEvents::EEventRoot3);
         const DemoNestedStateMachineEvents::CEventRootData eventData(3);
         LogInfo("[%s][%u] send root-state-machine event ID [%u] with data [%d]\n", __FUNCTION__, __LINE__, eventId, eventData.Get());
         spStateMachine->EventHandle(&eventData, eventId);
      }

      //finished sending events
      LogInfo("[%s][%u] sending events done, root state machine %s finished\n", __FUNCTION__, __LINE__, spStateMachine->HasFinished() ? "has" : "not");
   }
   
   LogInfo("[%s][%u] nested-statemachine demo out\n", __FUNCTION__, __LINE__);
   return 0;
}

