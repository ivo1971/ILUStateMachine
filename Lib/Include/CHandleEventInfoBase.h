/** @file
 ** @brief The CHandleEventInfoBase declaration.
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
#ifndef __ILULibStateMachine_CHandleEventInfoBase_H__
#define __ILULibStateMachine_CHandleEventInfoBase_H__

#include <map>

#include "../Include/CCreateState.h"

namespace ILULibStateMachine {
   /** @brief Base class used to store all event handling information for 1 event.
    **
    ** It is required by the state machine engine to store handlers for
    ** events with different data types in the same map.
    **/
   class CHandleEventInfoBase {
      public:
         typedef std::pair<bool, CCreateState> HandleResult; ///< Return multiple values from the event handler function, without using parameters.

      public:
                 CHandleEventInfoBase(void);
         virtual ~CHandleEventInfoBase(void);
   };
   
   typedef boost::shared_ptr<CHandleEventInfoBase> SPHandleEventInfoBase; ///< Shared pointer to a CHandleEventInfoBase instance.
};

#endif //__ILULibStateMachine_CHandleEventInfoBase_H__

