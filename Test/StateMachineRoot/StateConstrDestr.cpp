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
 ** This file groups all state constructors and destructors of StateMachineRoot so that
 ** there is a clear overview of:
 ** - All event handlers (registered in state constructors);
 ** - All on-entry functions (called from state constructors);
 ** - All on-exit functions (called from state destructors).
 **
 **/
#include "CCreateStateFinished.h"
#include "CStateChangeException.h"
#include "TCreateState.h"

#include "StateMachineChild.h"

#include "CreateState.h"
#include "CState1.h"
#include "CState2.h"
#include "CState3.h"
#include "CState4.h"
#include "CStateDefault.h"

namespace StateMachineRoot {
   namespace Internal {
      /****************************************************************************************
       ** 
       ** CState1
       **
       ***************************************************************************************/
      CState1::CState1(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData)
         : ILULibStateMachine::CStateEvtId("state-1", wpStateMachine)
         , m_pData(pData)
      {
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
         //step 1: register event handlers

         EventRegister(HANDLER_EVT(CState1, HandlerEvt1),       ILULibStateMachine::CCreateState(), LibEvents::EEvent1);
         EventRegister(HANDLER_EVT(CState1, HandlerEvt2),       CreateState2(pData),                LibEvents::EEvent2);
         EventRegister(HANDLER_EVT(CState1, HandlerEvt5),       ILULibStateMachine::CCreateState(), LibEvents::EEvent5);
         EventRegister(HANDLER_EVT(CState1, HandlerEvt6),       ILULibStateMachine::CCreateState(), LibEvents::EEvent6);
         EventRegister(HANDLER_EVT(CState1, HandlerEvt7),       CreateState3(pData),                LibEvents::EEvent7);
         
         //step 2: call on-entry functions this state
      }
      
      CState1::~CState1(void)
      {
         //step 1: call on-exit functions this state
         
         //step 2: unregister event handlers
         //        --> EventMachine::CStateEventMachine
         
         //testing 1-2
         m_pData->m_uiGlobVal += 10;
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
      }

      /****************************************************************************************
       ** 
       ** CState2
       **
       ***************************************************************************************/
      CState2::CState2(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData)
         : ILULibStateMachine::CStateEvtId("state-2", wpStateMachine)
         , m_pData(pData)
         , m_uiGuardEvt1Cnt(0)
      {
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
         //step 1: register event handlers
         EventRegister(GUARD_EVT(CState2, GuardEvt1Never),       HANDLER_EVT(CState2, HandlerEvt1Never),       ILULibStateMachine::CCreateState(),         LibEvents::EEvent1);
         //EventRegister(GUARD_EVT(CState2, GuardEvt1SwitchState), HANDLER_EVT(CState2, HandlerEvt1SwitchState), CreateState1(pData),                        LibEvents::EEvent1);
         EventRegister(                                          HANDLER_EVT(CState2, HandlerEvt1Default),     ILULibStateMachine::CCreateState(),         LibEvents::EEvent1);
         EventRegister(                                          HANDLER_EVT(CState2, HandlerEvt2),            CreateState1(pData),                        LibEvents::EEvent2);
         EventRegister(                                          HANDLER_EVT(CState2, HandlerEvtAny),          ILULibStateMachine::CCreateState(),         LibEvents::EEvent3);
         EventRegister(                                          HANDLER_EVT(CState2, HandlerEvtAny),          ILULibStateMachine::CCreateStateFinished(), LibEvents::EEvent8);
         
         //step 2: call on-entry functions this state
      }
      
      CState2::~CState2(void)
      {
         //step 1: call on-exit functions this state
         
         //step 2: unregister event handlers
         //        --> EventMachine::CStateEventMachine
         
         //testing 1-2
         m_pData->m_uiGlobVal += 25;
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
      }

      /****************************************************************************************
       ** 
       ** CState3
       **
       ***************************************************************************************/
      CState3::CState3(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData)
         : ILULibStateMachine::CStateEvtId("state-3", wpStateMachine)
         , m_pData(pData)
      {
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
         //throw exception
         throw ILULibStateMachine::CStateChangeException("throw CStateChangeException", CreateState2(pData));
      }
      
      CState3::~CState3(void)
      {
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
      }

      /****************************************************************************************
       ** 
       ** CState4
       **
       ***************************************************************************************/
      CState4::CState4(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData)
         : ILULibStateMachine::CStateEvtId("state-4", wpStateMachine)
         , m_pData(pData)
         , m_spStateMachine(StateMachineChild::CreateStateMachine())
      {
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
         //step 1: register event handlers
         EventRegister(HANDLER_TYPE(LibEvents::CEventType2Data, CState4, HandleEventType2ToChild), ILULibStateMachine::CCreateState());

         //step 2: call on-entry functions this state
      }
      
      CState4::~CState4(void)
      {
         //step 1: call on-exit functions this state
         
         //step 2: unregister event handlers
         //        --> EventMachine::CStateEventMachine
         
         //testing 1-2
         m_pData->m_uiGlobVal += 25;
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
      }

      /****************************************************************************************
       ** 
       ** CStateDefault
       **
       ***************************************************************************************/
      CStateDefault::CStateDefault(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData)
         : ILULibStateMachine::CStateEvtId("default state", wpStateMachine, true)
         , m_pData(pData)
      {
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
         //step 1: register event handlers
         EventRegister(HANDLER_EVT(CStateDefault, HandlerEvt3), ILULibStateMachine::CCreateState(), LibEvents::EEvent3);
         EventRegister(HANDLER_EVT(CStateDefault, HandlerEvt9), CreateState4(pData),                LibEvents::EEvent9);
         
         //step 2: call on-entry functions this state
      }
      
      CStateDefault::~CStateDefault(void)
      {
         //step 1: call on-exit functions this state
         
         //step 2: unregister event handlers
         //        --> EventMachine::CStateEventMachine
         
         //testing 1-2
         ILULibStateMachine::LogInfo("[%s][%u] data [%u]\n", __FUNCTION__, __LINE__, m_pData->m_uiGlobVal);
      }      
   };      
};
   
