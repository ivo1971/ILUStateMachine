/** @file
 ** @brief The CStateChangeException declaration.
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
#ifndef __ILULibStateMachine_CStateChangeException_H__
#define __ILULibStateMachine_CStateChangeException_H__

#include "stdexcept"

#include "../Include/CCreateState.h"

namespace ILULibStateMachine {
   /** @brief When the state machine catches an exception of this type while executing an event handler
    ** or while constructing a new state, it will switch to the state created by calling the
    ** CCreateState instance in the caught exception.
    **
    ** This class allows breaking the normal flow as dictated by the registered event handlers.
    **/
   class CStateChangeException : public std::runtime_error {
      public:
                      CStateChangeException(const std::string& whatArg, CCreateState createState);
                      ~CStateChangeException(void) throw();

      public:
         CCreateState GetCreateState(void) const;

      private:
         CCreateState m_CreateState; //< The state machine will use this instance to change the current state when it catches this exception.
   };
};

#endif //__ILULibStateMachine_CStateChangeException_H__

