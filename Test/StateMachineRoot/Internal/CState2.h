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
#ifndef __StateMachineRoot_CState2__H__
#define __StateMachineRoot_CState2__H__

#include "CStateEvtId.h"

#include "Events.h"

#include "CData.h"

namespace StateMachineRoot {
   namespace Internal {
      class CState2 : public ILULibStateMachine::CStateEvtId {
         public:
                                               CState2(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData);
                                               ~CState2(void);

         public:
            bool                               GuardEvt1Never(void);
            void                               HandlerEvt1Never(const LibEvents::CEventData* const pData);
            bool                               GuardEvt1SwitchState(void);
            void                               HandlerEvt1SwitchState(const LibEvents::CEventData* const pData);
            void                               HandlerEvt1Default(const LibEvents::CEventData* const pData);
            void                               HandlerEvt2(const LibEvents::CEventData* const pData);
            void                               HandlerEvtAny(const LibEvents::CEventData* const pData);
            
         private:
                                               CState2(const CState2& ref);
            CState2                            operator=(const CState2& ref);

         private:
            CData*                             m_pData;
            unsigned int                       m_uiGuardEvt1Cnt;
      };
   };
};

#endif //__StateMachineRoot_CState2__H__

