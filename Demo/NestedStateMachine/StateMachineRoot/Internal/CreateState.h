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
#ifndef __DemoNestedStateMachineRoot_CreateState_H__
#define __DemoNestedStateMachineRoot_CreateState_H__

#include "CStateMachine.h"

#include "EEventRoot.h"

#include "CData.h"

namespace DemoNestedStateMachineRoot {
   namespace Internal {
      //create state functions
      ILULibStateMachine::CCreateState CreateState1(CData* pData);
      ILULibStateMachine::CCreateState CreateState2(CData* pData);
      ILULibStateMachine::CCreateState CreateState3(CData* pData);
   }
};

#endif //__DemoNestedStateMachineRoot_CreateState_H__

