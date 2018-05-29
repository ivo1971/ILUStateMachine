/** @file
 ** @brief The THandleEventInfo template function defintions.
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
#ifndef __ILULibStateMachine_THandleEventInfoImpl_H__
#define __ILULibStateMachine_THandleEventInfoImpl_H__

#include "Logging.h"
#include "CStateChangeException.h"

namespace ILULibStateMachine {
   /** Constructs an instance without handlers.
    **/
   template <class TEventData> 
   THandleEventInfo<TEventData>::THandleEventInfo(void)
      : CHandleEventInfoBase()
      , m_bUnguardedHandlerSet(false)
      , m_UnguardedHandler()
      , m_GuardHandlers()
   {
   }; 

   /** Constructor setting the unguarded handler.
    **/
   template <class TEventData> 
   THandleEventInfo<TEventData>::THandleEventInfo(
      BFHandler    handler,    //< The handler to be called.
      CCreateState createState //< Describes the state state transition once the handler has been called.
      )
      : CHandleEventInfoBase()
      , m_bUnguardedHandlerSet(true)
      , m_UnguardedHandler(GuardHandlerCreateState(0, handler, createState))
      , m_GuardHandlers()
   {
   }; 
   
   /** Constructor configuring 1 guarded handler and no unguarded handler.
    **/
   template <class TEventData> 
   THandleEventInfo<TEventData>::THandleEventInfo(
      BFGuard      guard,      //< The guard to be called before the handler itself is called. When the guard returns false, the handler will not be called (no event match). 
      BFHandler    handler,    //< The handler to be called.
      CCreateState createState //< Describes the state state transition once the handler has been called.
      )
      : CHandleEventInfoBase()
      , m_bUnguardedHandlerSet(false)
      , m_UnguardedHandler()
      , m_GuardHandlers()
   {
      m_GuardHandlers.push_back(GuardHandlerCreateState(guard, handler, createState));
   }; 

   /** Set the unguarded handler.
    **
    ** Will throw an exception when the unguarded handler has already been set before (e.g. constructor).
    **/
   template <class TEventData> 
   void THandleEventInfo<TEventData>::SetUnguardedHandler(
      BFHandler    handler,    //< The handler to be called.
      CCreateState createState //< Describes the state state transition once the handler has been called.
      )
   {
      if(m_bUnguardedHandlerSet) {
         throw std::runtime_error("Unguarded handler already set");
      }
      m_bUnguardedHandlerSet = true;
      m_UnguardedHandler     = GuardHandlerCreateState(0, handler, createState);
   };
   
   /** Add a guarded handler.
    **/
   template <class TEventData> 
   void THandleEventInfo<TEventData>::AddGuardedHandler(
      BFGuard      guard,      //< The guard to be called before the handler itself is called. When the guard returns false, the handler will not be called (no event match). 
      BFHandler    handler,    //< The handler to be called.
      CCreateState createState //< Describes the state state transition once the handler has been called.
      )
   {
      m_GuardHandlers.push_back(GuardHandlerCreateState(guard, handler, createState));
   };
   
   /** Try to find an event handler.
    **
    ** The function will start by looking for a guarded handler with its guard function returning true.
    ** When none is found, it will call the unguarded handler.
    **
    ** @return a HandleResult instance indicating whether a handler was called or not and, when one was called, what the accompanying state transition is (CCreateState).
    **/
   template <class TEventData> 
   CHandleEventInfoBase::HandleResult THandleEventInfo<TEventData>::Handle(
      const bool              bDefaultState, //< Indicator whether this function is called for the default state or the current state, logging only.
      const TEventData* const pEventData     //< Data accompanying the event, will be provided to the handler.
      )
   {
      const char* const szType = bDefaultState ? "default-state" : "state";;
      
      CLogIndent logIndent;
      
      //first try find a guarded handler
      LogDebug("Trying [%lu] %s guard's\n", (long unsigned int)m_GuardHandlers.size(), szType);
      {
         unsigned int uiGuardNbr = 1; //1-based: logging only
         for(GuardHandlerCreateStatesCIt cit = m_GuardHandlers.begin() ; m_GuardHandlers.end() != cit ; ++cit, ++uiGuardNbr) {
            LogDebug("Trying %s guard [%u/%lu]\n", szType, uiGuardNbr, (long unsigned int)m_GuardHandlers.size());
            bool bGuardPassed = false;
            try {
               CLogIndent logIndentGuard; //indent logging while calling the guard
               bGuardPassed = TYPESEL::get<0>(*cit)(pEventData);
            } catch(std::exception& ex) {
               LogErr("Exception while calling %s guard [%u/%lu]: %s\n", szType, uiGuardNbr, (long unsigned int)m_GuardHandlers.size(), ex.what());
            } catch(...) {
               LogErr("Exception while calling %s guard [%u/%lu]: %s\n", szType, uiGuardNbr, (long unsigned int)m_GuardHandlers.size(), "unknown");
            }
            if(bGuardPassed) {
               //guard returns true
               //--> call the handler
               std::stringstream ss;
               ss << "Passed " << szType << " guard [" << uiGuardNbr << "/" << (long unsigned int)m_GuardHandlers.size() << "] --> calling accompanying " << szType << " handler\n";
               return CallHandler(
                                  ss.str(),
                                  TYPESEL::get<1>(*cit), 
                                  TYPESEL::get<2>(*cit), 
                                  pEventData, 
                                  szType
                                  );
            }
         }
      }
      if(0 != m_GuardHandlers.size()) {
         LogDebug("No matching %s guard\n", szType);
      }
      
      //no guarded handler found
      //--> check default handler
      if(!m_bUnguardedHandlerSet) {
         LogDebug("No %s unguarded handler\n", szType);
         return HandleResult(false, CCreateState());
      }
      
      //call the default handler
      std::stringstream ss;
      ss << "Calling " << szType << " unguarded handler\n";
      return CallHandler(
                         ss.str(),
                         TYPESEL::get<1>(m_UnguardedHandler), 
                         TYPESEL::get<2>(m_UnguardedHandler), 
                         pEventData, 
                         szType
                         );
   };

   /** Without further ado, call the handler and deal with exceptions.
    **
    ** @return a HandleResult instance indicating whether a handler was called or not and, when one was called, what the accompanying state transition is (CCreateState).
    **/
   template <class TEventData> 
   CHandleEventInfoBase::HandleResult THandleEventInfo<TEventData>::CallHandler(
      const std::string&                                          strMsg,      //< Logging accompanying the handler call.
      TYPESEL::function<void(const TEventData* const pEventData)> handler,     //< The handler to be called.
      CCreateState                                                createState, //< The CCreateState instance accompanying the handler. Will not be called but will be included in the return value. Can be overridden if a state-change exception was caught while calling the handler.
      const TEventData* const                                     pEventData,  //< Data accompanying the event, will be provided to the handler.
      const char* const                                           szType       //< Indicator whether this function is called for the default state or the current state, logging only.
      )
   {
      try {
         LogNotice("%s", strMsg.c_str());
         {
            CLogIndent logIndent;
            handler(pEventData);
         }
         LogNotice("Calling handler done\n");
      } catch(CStateChangeException& ex) {
         LogWarning("State-change caught while calling %s handler: %s\n", szType, ex.what());
         createState = ex.GetCreateState();
      } catch(std::exception& ex) {
         LogErr("Exception caught while calling %s handler: %s\n", szType, ex.what());
         createState = CCreateState(); //remain in this state
      } catch(...) {
         LogErr("Exception caught while calling %s handler: %s\n", szType, "unknown");
         createState = CCreateState(); //remain in this state
      }
      return HandleResult(true, createState);
   } 
};

#endif //__ILULibStateMachine_THandleEventInfoImpl_H__

