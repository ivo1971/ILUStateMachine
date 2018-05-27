/** @file
 ** @brief The CState declaration.
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
#ifndef __ILULibStateMachine_CState__H__
#define __ILULibStateMachine_CState__H__

#include <string>

namespace ILULibStateMachine {
   /** @brief Base class for all states in a state machine.
    **
    ** Used by the state machine engine to keep track of the current and the default state.
    **
    ** The FCreateState function returns a pointer to a state instance.
    **
    ** SPStateMachineData is NOT a member as this would require casting CStateMachineData to the actual
    ** data class whenever it is used. Thus it is stored directly in the derived state classes instead.
    **/
   class CState {
      public:
                            CState(const char* const szName, const bool bDefault = false);
         virtual            ~CState(void);

      public:
         const std::string& GetName(void) const;

      protected:
         const bool         m_bDefault; ///< Indicates whether this state is the state machine's default state (true) or not (false).

      private:
         const std::string  m_strName;  ///< State name, used for logging only.
   };
}

#endif //__ILULibStateMachine_CState__H__

