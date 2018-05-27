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
#include "CCreateStateFinished.h"
#include "CStateChangeException.h"
#include "TCreateState.h"

#include "ChildCreateState.h"
#include "CChildState1.h"
#include "CChildState2.h"
#include "CChildState3.h"

namespace StateMachineChild {
   namespace Internal {
      /****************************************************************************************
       ** 
       ** CChildState1
       **
       ***************************************************************************************/
      CChildState1::CChildState1(ILULibStateMachine::WPStateMachine wpStateMachine, CChildData* pData)
         : ILULibStateMachine::CStateEvtId("child state-1", wpStateMachine)
         , m_pData(pData)
      {
         ILULibStateMachine::LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         //step 1: register event handlers
         EventRegister(HANDLER_EVTTYPE2(CChildState1, HandlerEvt1), CreateChildState2(pData), LibEvents::EEventType2Event1);
         
         //step 2: call on-entry functions this state
      }
      
      CChildState1::~CChildState1(void)
      {
         //step 1: call on-exit functions this state
         
         //step 2: unregister event handlers
         //        --> EventMachine::CStateEventMachine
         ILULibStateMachine::LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
      }

      /****************************************************************************************
       ** 
       ** CChildState2
       **
       ***************************************************************************************/
      CChildState2::CChildState2(ILULibStateMachine::WPStateMachine wpStateMachine, CChildData* pData)
         : ILULibStateMachine::CStateEvtId("child state-2", wpStateMachine)
         , m_pData(pData)
      {
         ILULibStateMachine::LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         //step 1: register event handlers
         EventRegister(HANDLER_EVTTYPE2(CChildState2, HandlerEvt2), CreateChildState3(pData), LibEvents::EEventType2Event2);
         
         //step 2: call on-entry functions this state
      }
      
      CChildState2::~CChildState2(void)
      {
         //step 1: call on-exit functions this state
         
         //step 2: unregister event handlers
         //        --> EventMachine::CStateEventMachine
         ILULibStateMachine::LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
      }

      /****************************************************************************************
       ** 
       ** CChildState3
       **
       ***************************************************************************************/
      CChildState3::CChildState3(ILULibStateMachine::WPStateMachine wpStateMachine, CChildData* pData)
         : ILULibStateMachine::CStateEvtId("child state-3", wpStateMachine)
         , m_pData(pData)
      {
         ILULibStateMachine::LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
         //step 1: register event handlers
         EventRegister(HANDLER_EVTTYPE2(CChildState3, HandlerEvt3), ILULibStateMachine::CCreateStateFinished(), LibEvents::EEventType2Event3);
         
         //step 2: call on-entry functions this state
      }
      
      CChildState3::~CChildState3(void)
      {
         //step 1: call on-exit functions this state
         
         //step 2: unregister event handlers
         //        --> EventMachine::CStateEventMachine
         ILULibStateMachine::LogInfo("[%s][%u]\n", __FUNCTION__, __LINE__);
      }
   };      
};
   
