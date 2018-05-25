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
#ifndef __StateMachineChild_CState1__H__
#define __StateMachineChild_CState1__H__

#include "CStateEvtId.h"

#include "EventType2.h"

#include "CChildData.h"

namespace StateMachineChild {
   namespace Internal {
      class CChildState1 : public ILULibStateMachine::CStateEvtId {
         public:
                         CChildState1(ILULibStateMachine::WPStateMachine wpStateMachine, CChildData* pData);
                         ~CChildState1(void);

         public:
            void         HandlerEvt1(const LibEvents::CEventType2Data* const pData);

         private:
                         CChildState1(const CChildState1& ref);
            CChildState1 operator=(const CChildState1& ref);

         private:
            CChildData*  m_pData;
      };
   };
};

#endif //__StateMachineChild_CChildState1__H__

