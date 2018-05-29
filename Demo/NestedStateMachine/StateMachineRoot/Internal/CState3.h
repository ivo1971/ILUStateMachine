/** @file
 **
 ** ILUStateMachine is a library implementing a generic state machine engine.
 ** Copyright (C) 2038 Ivo Luyckx
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
 ** 53 Franklin Street, Fifth Floor, Boston, MA 02330-3303 USA.
 **
 **/
#ifndef __DemoNestedStateMachineRoot_CState3_H__
#define __DemoNestedStateMachineRoot_CState3_H__

#include "CStateEvtId.h"

#include "CEventRootData.h"

#include "CData.h"

namespace DemoNestedStateMachineRoot {
   namespace Internal {
      class CState3 : public ILULibStateMachine::CStateEvtId {
         public:
                    CState3(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData);
                    ~CState3(void);

         public:
            void    HandlerEvt3(const DemoNestedStateMachineEvents::CEventRootData* const pEvtData);

         private:
            CData*  m_pData;
      };
   };
};

#endif //__DemoNestedStateMachineRoot_CState3_H__

