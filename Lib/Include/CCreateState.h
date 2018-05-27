/** @file
 ** @brief The CCreateState declaration.
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
#ifndef __ILULibStateMachine_CCreateState__H__
#define __ILULibStateMachine_CCreateState__H__

//when using a C++14 compatible compiler,
//boost can be replaced by std.
#include "boost/function.hpp"

#include "CState.h"
#include "Types.h"

namespace ILULibStateMachine {
   //forward declarations
   //(avoiding recursive includes)
   class CStateMachine;

   /** Prototype of function to create a new state
    ** this cannot be a mere typedef since states can require
    ** constructor parameters. Boost bind can then be used to return
    ** an FCreateState with only the statemachine weak pointer 
    ** (parameters provided in the bind call) and keep this 
    ** transparent for the state machine engine.
    ** A parameter which is often required is the global state 
    ** machine data (CStateMachineData). It cannot be a parameter 
    ** of the FCreateState function to avoid a dynamic cast.
    **/
   typedef boost::function<CState*(TYPESEL::weak_ptr<CStateMachine> wpStateMachine)> FCreateState;

   /** @brief Wrapper of a create-state function so it is possible to check that the function is valid or not. 
    **
    ** A boost::function cannot be checked for validity.
    ** Nevertheless, event handler definitions not requireing 
    ** a state change have to be able to indicate this.
    ** Thus the CCreateState wraps the FCreateState together
    ** with a valid-flag.
    ** An alternative would have been a std::pair.
    **/
   class CCreateState {
      public:
                             CCreateState(void);
                             CCreateState(const CCreateState& ref);
                             CCreateState(FCreateState fCreateState);         
         virtual             ~CCreateState(void);
         CCreateState&       operator=(const CCreateState& ref);

      public:
         bool                IsValid(void) const;
         const FCreateState& Get(void) const;

      private:
         bool                m_bValid;       //< When true the FCreateFunction is valid and can be called.
         FCreateState        m_fCreateState; //< When called this function creates a new state in the state machine.
   };
}

#endif //__ILULibStateMachine_CCreateState__H__

