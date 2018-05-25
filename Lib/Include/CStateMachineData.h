/** @file
 ** @brief The CStateMachineData declaration.
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
#ifndef __ILULibStateMachine_CStateMachineData__H__
#define __ILULibStateMachine_CStateMachineData__H__

#include "boost/shared_ptr.hpp"

namespace ILULibStateMachine {
   /** @brief Base class to hold all data belonging to one state machine.
    **
    ** Each state machine data class (1 per state machine)
    ** derives from this class.
    ** The base class is required to keep a reference in CStateMachine
    ** and clean it up upon destruction
    **/
   class CStateMachineData {
      public:
         virtual ~CStateMachineData(void);
   };
}

#endif //__ILULibStateMachine_CStateMachineData__H__

