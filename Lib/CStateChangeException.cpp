/** @file
 ** @brief The CStateChangeException definition.
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
#include "Include/CStateChangeException.h"

namespace ILULibStateMachine {
   /** Constructor.
    **/
   CStateChangeException::CStateChangeException(const std::string& whatArg, CCreateState createState)
      : std::runtime_error(whatArg)
      , m_CreateState(createState)
   {
   }

   /** Destructor.
    **
    ** Required because the base class sets 'throw' on its destructor.
    **/
   CStateChangeException::~CStateChangeException(void) throw()
   {
   }

   /** Get the CCreateState describing the requested state transition by the exception.
    **
    ** @return the CCreateState describing the requested state transition by the exception.
    **/
   CCreateState CStateChangeException::GetCreateState(void) const
   {
      return m_CreateState;
   }
};

