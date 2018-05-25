/** @file
 ** @brief The CCreateState definition.
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
#include "Include/CCreateState.h"

namespace ILULibStateMachine {
   /** Default constructor: no valid state create function set.
    **/
   CCreateState::CCreateState(void)
      : m_bValid(false)
      , m_fCreateState()
   {
   }

   /** Copy constructor.
    **/
   CCreateState::CCreateState(
      const CCreateState& ref ///< Instance to be copied.
      )
      : m_bValid(ref.m_bValid)
      , m_fCreateState(ref.m_fCreateState)
   {
   }

   /** Constructor setting a state create function.
    **/
   CCreateState::CCreateState(
      FCreateState fCreateState ///< Create state function to be embedded.
      )
      : m_bValid(true)
      , m_fCreateState(fCreateState)
   {
   }

   /** Destructor.
    **/
   CCreateState::~CCreateState(void)
   {
   }

   /** Copy operator.
    **/
   CCreateState& CCreateState::operator=(
      const CCreateState& ref ///< Instance to be copied.
      )
   {
      if(this == &ref) return *this;
      m_bValid       = ref.m_bValid;
      m_fCreateState = ref.m_fCreateState;
      return *this;
   }

   /** Check whether the embedded create state function is valid.
    **
    ** @return true when the embedded create state function is valid and can be called.
    **/
   bool CCreateState::IsValid(void) const
   {
      return m_bValid;
   }

   /** Get a reference to the embedded create state function.
    **
    ** @return a reference to the embedded create state function.
    **/
   const FCreateState& CCreateState::Get(void) const
   {
      return m_fCreateState;
   }
}

