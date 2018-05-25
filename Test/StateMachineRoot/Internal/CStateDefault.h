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
#ifndef __StateMachineRoot_CStateDefault__H__
#define __StateMachineRoot_CStateDefault__H__

#include "CStateEvtId.h"

#include "Events.h"

#include "CData.h"

namespace StateMachineRoot {
   namespace Internal {
      class CStateDefault : public ILULibStateMachine::CStateEvtId {
         public:
                          CStateDefault(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData);
            virtual       ~CStateDefault(void);

         public:
            void          HandlerEvt3(const LibEvents::CEventData* const pData);
            void          HandlerEvt9(const LibEvents::CEventData* const pData);
            
         private:
                          CStateDefault(const CStateDefault& ref);
            CStateDefault operator=(const CStateDefault& ref);

         private:
            CData*        m_pData;
      };
   };
};

#endif //__StateMachineRoot_CStateDefault__H__

