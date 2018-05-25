/** @file
 ** @brief The CState definition. 
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
#include "Include/CState.h"

namespace ILULibStateMachine {
   /** Constructor.
    **/
   CState::CState(
      const char* const szName,  ///< State name, used for logging only.
      const bool        bDefault ///< Indicates whether this state is the state machine's default state (true) or not (false).
      )
      : m_bDefault(bDefault)
      , m_strName(szName)
   {
   }

   /** Destructor to make this a virtual class.
    **/
   CState::~CState(void)
   {
   };

   /** Get the state name.
    **
    ** @return the state name.
    **/
   const std::string& CState::GetName(void) const
   {
      return m_strName;
   }
}

