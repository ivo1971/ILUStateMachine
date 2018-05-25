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

#include "ChildCreateState.h"
#include "CChildState3.h"

namespace StateMachineChild {
   namespace Internal {
      void CChildState3::HandlerEvt3(const LibEvents::CEventType2Data* const pData)
      {
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] message [%3%]\n") % __FUNCTION__ % __LINE__ % pData->m_strMsg);
      }

      ILULibStateMachine::CCreateState CreateChildState3(CChildData* pData)
      {
         return ILULibStateMachine::TCreateState<CChildState3,CChildData>(pData);
      }
   };
};
   
