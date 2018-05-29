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
#include "CStateChangeException.h"
#include "TCreateState.h"

#include "StateMachineChild.h"

#include "CreateState.h"
#include "CState2.h"

namespace DemoNestedStateMachineRoot {
   namespace Internal {
      void CState2::HandlerEvtTypeChild(ILULibStateMachine::SPEventBase spEventBase, const DemoNestedStateMachineEvents::CEventChildData* const pEvtData)
      {
         ILULibStateMachine::LogInfo("%s %s forwarding event to child\n", GetName().c_str(), __FUNCTION__);
         if(!m_spStateMachineChild->EventHandle(pEvtData, spEventBase)) {
            ILULibStateMachine::LogInfo("%s %s child not finished\n", GetName().c_str(), __FUNCTION__);
            return;
         }
         ILULibStateMachine::LogInfo("%s %s child finished --> to root state 3\n", GetName().c_str(), __FUNCTION__);
         throw ILULibStateMachine::CStateChangeException("state change to root state 3", CreateState3(m_pData));
      }

      ILULibStateMachine::CCreateState CreateState2(CData* pData)
      {
         return ILULibStateMachine::TCreateState<CState2,CData>(pData);
      }
   };
};
   
