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
#ifndef __ILUStateMachine_EventType2__H__
#define __ILUStateMachine_EventType2__H__

#include "CCreateState.h"

namespace LibEvents {
   enum EEventType2 {
      EEventType2Event1 = 1,
      EEventType2Event2 = 2,
      EEventType2Event3 = 3,
   };

   class CEventType2Data {
      public:
         CEventType2Data(const std::string& strMsg)
            : m_strMsg(strMsg)
         {
         };

      public:
         std::string m_strMsg;
   };
};

#define HANDLER_EVTTYPE2(cl,f) HANDLER(LibEvents::CEventType2Data, cl,f)

#endif //__ILUStateMachine_EventType2__H__

