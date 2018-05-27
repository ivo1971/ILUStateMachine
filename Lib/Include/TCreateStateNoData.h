/** @file
 ** @brief The TCreateState template function defintions.
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
#ifndef __ILULibStateMachine_TCreateStateNoData__H__
#define __ILULibStateMachine_TCreateStateNoData__H__

#include "CCreateState.h"
#include "CStateMachine.h"
#include "Types.h"

namespace ILULibStateMachine {
   /** @brief Templates to ease implementation of the state creation functions.
    **
    ** The templates assume a simple state class type that has 1 parameter:
    ** - a weak pointer to the state machine the class belongs to.
    ** It can only be used by state machines having no data.
    **/
   template<class CStateType> CState* TCreateStateInstanceNoData(WPStateMachine wpStateMachine)
   {
      return new CStateType(wpStateMachine);
   }
   
   /** Wrapper template around TCreateStateInstance that binds
    ** the state create function as expected by the state machine
    ** CCreateState.
    **/
   template<class CStateType> CCreateState TCreateStateNoData(void)
   {
     return CCreateState(TCreateStateInstanceNoData<CStateType>);
   }
}

#endif //__ILULibStateMachine_TCreateStateNoData__H__

