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
#ifndef __StateMachineRoot_CData__H__
#define __StateMachineRoot_CData__H__

#include "CStateMachine.h"

namespace StateMachineRoot {
   namespace Internal {
      /** This object holds the global data for this statemachine.
       ** Only 1 instance will be instantiated and provided to
       ** all state instances upon construction.
       ** The instance will be managed (destructed) by the state machine engine 
       ** when it is destructed itself.
       ** The instance is passed from one state to the other, with the next-state
       ** functionality. But states are not allowed to delete it, they just borrow it.
       **/
      class CData : public ILULibStateMachine::CStateMachineData {
         public:
                         CData(const unsigned int uiGlobVal);
                         ~CData(void);
            
         public:
            unsigned int m_uiGlobVal;
      };
   };
};

#endif //__StateMachineRoot_CData__H__

