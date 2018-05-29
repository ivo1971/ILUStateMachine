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
#include "CData.h"
#include "CreateState.h"
#include "StateMachineChild.h"

//StateMachineChild common implementation
namespace DemoNestedStateMachineChild {
   ILULibStateMachine::SPStateMachine CreateStateMachine(void)
   {
      //create single CData instance
      Internal::CData* pData = new Internal::CData();

      //create & return state machine
      return ILULibStateMachine::CStateMachine::ConstructStateMachine(
         "state-machine-child",         //< name used for logging
         Internal::CreateState1(pData), //< used to create the initial state
         pData                          //< CStateMachine takes ownership of the data pointer
         );
   }
};

