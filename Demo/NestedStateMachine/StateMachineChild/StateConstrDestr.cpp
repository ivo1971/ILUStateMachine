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

#include "CreateState.h"
#include "CState1.h"
#include "CState2.h"
#include "CState3.h"

namespace DemoNestedStateMachineChild {
   namespace Internal {
      /****************************************************************************************
       ** 
       ** CState1
       **
       ***************************************************************************************/
      CState1::CState1(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData)
         : ILULibStateMachine::CStateEvtId("child-state-1", wpStateMachine)
         , m_pData(pData)
      {
         ILULibStateMachine::LogInfo("%s '%s'\n", GetName().c_str(), __FUNCTION__);

         EventRegister(HANDLER(DemoNestedStateMachineEvents::CEventChildData, CState1, HandlerEvt1), CreateState2(pData), DemoNestedStateMachineEvents::EEventChild1);
      }
      
      CState1::~CState1(void)
      {
         ILULibStateMachine::LogInfo("%s '%s'\n", GetName().c_str(), __FUNCTION__);
      }

      /****************************************************************************************
       ** 
       ** CState2
       **
       ***************************************************************************************/
      CState2::CState2(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData)
         : ILULibStateMachine::CStateEvtId("child-state-2", wpStateMachine)
         , m_pData(pData)
      {
         ILULibStateMachine::LogInfo("%s '%s'\n", GetName().c_str(), __FUNCTION__);

         EventRegister(HANDLER(DemoNestedStateMachineEvents::CEventChildData, CState2, HandlerEvt2), CreateState3(pData), DemoNestedStateMachineEvents::EEventChild2);
      }
      
      CState2::~CState2(void)
      {
         ILULibStateMachine::LogInfo("%s '%s'\n", GetName().c_str(), __FUNCTION__);
      }

      /****************************************************************************************
       ** 
       ** CState3
       **
       ***************************************************************************************/
      CState3::CState3(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData)
         : ILULibStateMachine::CStateEvtId("child-state-3", wpStateMachine)
         , m_pData(pData)
      {
         ILULibStateMachine::LogInfo("%s '%s'\n", GetName().c_str(), __FUNCTION__);

         EventRegister(HANDLER(DemoNestedStateMachineEvents::CEventChildData, CState3, HandlerEvt3), ILULibStateMachine::CCreateStateFinished(), DemoNestedStateMachineEvents::EEventChild3);
      }
      
      CState3::~CState3(void)
      {
         ILULibStateMachine::LogInfo("%s '%s'\n", GetName().c_str(), __FUNCTION__);
      }
   };      
};
   
