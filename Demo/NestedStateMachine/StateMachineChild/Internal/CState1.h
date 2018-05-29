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
#ifndef __DemoNestedStateMachineChild_CState1_H__
#define __DemoNestedStateMachineChild_CState1_H__

#include "CStateEvtId.h"

#include "CEventChildData.h"

#include "CData.h"

namespace DemoNestedStateMachineChild {
   namespace Internal {
      class CState1 : public ILULibStateMachine::CStateEvtId {
         public:
                    CState1(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData);
                    ~CState1(void);

         public:
            void    HandlerEvt1(const DemoNestedStateMachineEvents::CEventChildData* const pEvtData);

         private:
                    CState1(const CState1& ref);
            CState1 operator=(const CState1& ref);

         private:
            CData*  m_pData;
      };
   };
};

#endif //__DemoNestedStateMachineChild_CState1_H__

