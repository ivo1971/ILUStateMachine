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
#include "TCreateState.h"

#include "CreateState.h"
#include "CState2.h"

namespace StateMachineRoot {
   namespace Internal {
      bool CState2::GuardEvt1Never(void)
      {
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState2 glob data [%3%]\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal);
         return false;
      }
      bool CState2::GuardEvt1SwitchState(void)
      {
         ++m_uiGuardEvt1Cnt;
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState2 glob data [%3%] guard cnt [%4%] --> [%5%]\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal % m_uiGuardEvt1Cnt % (2 < m_uiGuardEvt1Cnt));
         return 2 < m_uiGuardEvt1Cnt;
      }

      void CState2::HandlerEvt1Never(const LibEvents::CEventData* const pData)
      {
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState2 glob data [%3%] state data [%4%]\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal % pData->m_iVal);
      }
      
      void CState2::HandlerEvt1SwitchState(const LibEvents::CEventData* const pData)
      {
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState2 glob data [%3%] state data [%4%]\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal % pData->m_iVal);
      }

      void CState2::HandlerEvt1Default(const LibEvents::CEventData* const pData)
      {
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState2 glob data [%3%] state data [%4%]\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal % pData->m_iVal);
      }

      void CState2::HandlerEvt2(const LibEvents::CEventData* const pData)
      {
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState2 glob data [%3%] state data [%4%]\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal % pData->m_iVal);
      }
      
      void CState2::HandlerEvtAny(const LibEvents::CEventData* const pData)
      {
         ILULibStateMachine::LogInfo(boost::format("[%1%][%2%] CState2 glob data [%3%] state data [%4%]\n") % __FUNCTION__ % __LINE__ % m_pData->m_uiGlobVal % pData->m_iVal);
      }
      
      ILULibStateMachine::CCreateState CreateState2(CData* pData)
      {
         return ILULibStateMachine::TCreateState<CState2,CData>(pData);
      }
   };
};

