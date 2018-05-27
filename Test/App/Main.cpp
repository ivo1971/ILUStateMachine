/** @file
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
#include "Logging.h"

//generated by autotools
#include "config.h"

//test includes
#include "Events.h"
#include "EventType2.h"
#include "StateMachineRoot.h"

namespace {
   using namespace ILULibStateMachine;

   void TestRun(void)
   {
      //create state machine
      LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
      SPStateMachine spStateMachine(StateMachineRoot::CreateStateMachine(88));
      LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);

      //fake events
      //these would actually be incoming events (e.g. messages, timers, ...)
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(12);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent1);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(34);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent3);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(66);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent2);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(34);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent3);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(-1);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent1);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(-2);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent1);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(-3);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent1);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(0);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent4);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(1);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent5);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(2);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent5);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(1);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent6);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(2);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent6);
      }
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(2);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent2);
      }

      //event resulting in a constructor exception
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(2);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent7);
      }

      //event 9: default handler changing state to state-4 --> start child state machine
      {
         //event to switch root state machine to state 4
         {
            LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
            LibEvents::CEventData eventData(1);
            spStateMachine->EventHandle(&eventData, LibEvents::EEvent9);
         }

         //send events to the child
         {
            LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
            LibEvents::CEventType2Data eventData("event 1");
            spStateMachine->EventHandle(&eventData, LibEvents::EEventType2Event1);
         }
         {
            LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
            LibEvents::CEventType2Data eventData("event 2");
            spStateMachine->EventHandle(&eventData, LibEvents::EEventType2Event2);
         }
         {
            LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
            LibEvents::CEventType2Data eventData("event 3");
            spStateMachine->EventHandle(&eventData, LibEvents::EEventType2Event3);
         }
      }

      //state 2 --> finished state
      {
         LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         LibEvents::CEventData eventData(99);
         spStateMachine->EventHandle(&eventData, LibEvents::EEvent8);
      }

      //finished sending events
      LogInfo("[%s][%u] finished sending events\n", __FUNCTION__, __LINE__);
   }
};

int main (void)
{
   LogInfo("[%s][%u] %s self-test in\n", __FUNCTION__, __LINE__, PACKAGE_STRING);
   EnableSerialLogDebug();
   
   //state machine test
   TestRun();

   LogInfo("[%s][%u] %s self-test out\n", __FUNCTION__, __LINE__, PACKAGE_STRING);
   return 0;
}

