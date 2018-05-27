/** @file
 ** @brief The THandleEventTypeInfo template class defintions.
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
#ifndef __ILULibStateMachine_THandleEventTypeInfo_H__
#define __ILULibStateMachine_THandleEventTypeInfo_H__

#include "CCreateState.h"
#include "CHandleEventInfoBase.h"

namespace ILULibStateMachine {
   /** @brief Template class that allows storing and calling of event-type handlers for one specific event data
    ** type (TEventData).
    **
    ** Event-type handlers are only called when no more specific matching handlers are found.
    **
    ** The implementation of the template functions is put in a seperate header file (included by this
    ** header) to keep the class declaration clean.
    **/
   template <class TEventData> class THandleEventTypeInfo : public CHandleEventInfoBase {
      public:
         typedef void                                                FTypeHandler(SPEventBase spEventBase, const TEventData* const); ///< Prototype of a type-event handler: it is provided with the event identifier and the event data.
         typedef TYPESEL::function<FTypeHandler>                     BFTypeHandler;                                                  ///< FTypeHandler wrapped in a boost function, so the event handler can be a class method bound to a class instance.
         typedef TYPESEL::tuple<BFTypeHandler, CCreateState>         HandlerTypeCreateState;                                         ///< Completely describes on action: handler and state transition.
         
      public:
                                  THandleEventTypeInfo(BFTypeHandler handler, CCreateState createState);

      public:
         HandleResult             Handle(const bool bDefaultState, SPEventBase spEventBase, const TEventData* const pEventData);

      private:
         HandleResult             CallHandler(boost::format& fmt, TYPESEL::function<void(SPEventBase spEventBase, const TEventData* const pEventData)> handler, CCreateState createState, SPEventBase spEventBase, const TEventData* const pEventData, const char* const szType);

      private:
         HandlerTypeCreateState   m_TypeHandler; ///< Stores the action for this class: handler combined with state transition.
   };
};

//include the class template function definitions.
#include "THandleEventTypeInfoImpl.h"

#endif //__ILULibStateMachine_THandleEventTypeInfo_H__

