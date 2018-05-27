/** @file
 ** @brief The THandleEventTypeInfo template class declaration.
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
#ifndef __ILULibStateMachine_THandleEventTypeInfoImpl_H__
#define __ILULibStateMachine_THandleEventTypeInfoImpl_H__

#include "Logging.h"
#include "CStateChangeException.h"

namespace ILULibStateMachine {
   /** Constructor.
    **/
   template <class TEventData> 
   THandleEventTypeInfo<TEventData>::THandleEventTypeInfo(
      BFTypeHandler handler,   //< Event handler to be called.
      CCreateState createState //< Describes the state transition following this handler. 
      )
      : CHandleEventInfoBase()
      , m_TypeHandler(HandlerTypeCreateState(handler, createState))
   {
   }; 
   
   /** Call the handler.
    **
    ** @return a HandleResult instance indicating whether a handler was called or not and, when one was called, what the accompanying state transition is (CCreateState).
    **/
   template <class TEventData> 
   CHandleEventInfoBase::HandleResult THandleEventTypeInfo<TEventData>::Handle(
      const bool              bDefaultState, //< Indicator whether this function is called for the default state or the current state, logging only.
      SPEventBase             spEventBase,   //< Event descriptor.
      const TEventData* const pEventData     //< Data accompanying the event, will be provided to the handler.
      )
   {
      const char* const szType = bDefaultState ? "default-state" : "state";;
      
      CLogIndent logIndent;
      
      //call the type handler
      return CallHandler(
         boost::format("Calling %1% type handler\n") % szType,
         TYPESEL::get<0>(m_TypeHandler), 
         TYPESEL::get<1>(m_TypeHandler), 
         spEventBase, 
         pEventData, 
         szType
         );
   };

   /** Without further ado, call the handler and deal with exceptions.
    **
    ** @return a HandleResult instance indicating whether a handler was called or not and, when one was called, what the accompanying state transition is (CCreateState).
    **/
   template <class TEventData> 
   CHandleEventInfoBase::HandleResult THandleEventTypeInfo<TEventData>::CallHandler(
      boost::format&                                                                       fmt,         //< Logging accompanying the handler call.
      TYPESEL::function<void(SPEventBase spEventBase, const TEventData* const pEventData)> handler,     //< The handler to be called.
      CCreateState                                                                         createState, //< The CCreateState instance accompanying the handler. Will not be called but will be included in the return value. Can be overridden if a state-change exception was caught while calling the handler.
      SPEventBase                                                                          spEventBase, //< Event descriptor.
      const TEventData* const                                                              pEventData,  //< Data accompanying the event, will be provided to the handler.
      const char* const                                                                    szType       //< Indicator whether this function is called for the default state or the current state, logging only.
      )
   {
      try {
         LogNotice(fmt);
         {
            CLogIndent logIndent;
            handler(spEventBase, pEventData);
         }
         LogNotice(boost::format("Calling type hanlder done\n"));
      } catch(CStateChangeException& ex) {
         LogWarning(boost::format("State-change caught while calling %1% type handler: %2%\n") % szType % ex.what());
         createState = ex.GetCreateState();
      } catch(std::exception& ex) {
         LogErr(boost::format("Exception caught while calling %1% type handler: %2%\n") % szType % ex.what());
         createState = CCreateState(); //remain in this state
      } catch(...) {
         LogErr(boost::format("Exception caught while calling %1% type handler: %2%\n") % szType % "unknown");
         createState = CCreateState(); //remain in this state
      }
      return HandleResult(true, createState);
   } 
};

#endif //__ILULibStateMachine_THandleEventTypeInfoImpl_H__

