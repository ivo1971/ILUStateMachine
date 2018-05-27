/** @file
 ** @brief The CCreateStateFinished definition.
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
#include "Include/CCreateStateFinished.h"

namespace ILULibStateMachine {
   namespace {
      /** The actual create-state function that returns a pointer
       ** to the next state, NULL for the finished state.
       **/
      CState* CreateStateFinished(TYPESEL::weak_ptr<CStateMachine>)
      {
         return NULL;
      }
   };
   
   /** Default constructor.
    **
    ** No parameters required: the next state is known.
    **/
   CCreateStateFinished::CCreateStateFinished(void)
      : CCreateState(boost::function<CState*(TYPESEL::weak_ptr<CStateMachine> wpStateMachine)>(CreateStateFinished))
   {
   }

   /** Copy constructor.
    **/
   CCreateStateFinished::CCreateStateFinished(const CCreateStateFinished& ref)
      : CCreateState(ref)
   {
   }

   /** Copy operator.
    **/
   CCreateStateFinished& CCreateStateFinished::operator=(const CCreateStateFinished& ref)
   {
      if(this == &ref) return *this;
      CCreateState::operator=(ref);
      return *this;
   }
}

