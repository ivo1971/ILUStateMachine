/** @file
 ** @brief The CStateMachine template function defintions.
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
#ifndef __ILULibStateMachine_CStateMachineImpl__H__
#define __ILULibStateMachine_CStateMachineImpl__H__

#include "stdexcept"

#include "boost/format.hpp"

#include "../Include/Logging.h"
#include "../Include/THandleEventInfo.h"
#include "../Include/THandleEventTypeInfo.h"

namespace ILULibStateMachine {
   /** Register an event-type handler.
    **/
   template <class TEventData> 
   void CStateMachine::EventRegister(
      const bool                                                              bDefault,    //< When true: register this handler in the default event-type map (default state); when false: register this handler for the current state.
      boost::function<void(SPEventBase spEventBase, const TEventData* const)> typeHandler, //< The handler to be registered.
      CCreateState                                                            createState  //< The state transition accompanying this event-type.
      )
   {
      try {
         const std::string typeName(typeid(TEventData).name());
         EventTypeMap& map = EventTypeGetMap(bDefault);
         const EventTypeMapIt it = map.find(typeName);
         if(map.end() == it) {
            LogDebug(boost::format("[%1%][%2%] register type event handler for [%3%] from [%4%]\n")
                     % __FUNCTION__
                     % __LINE__
                     % typeName.c_str()
                     % (bDefault ? "default" : "state")
               );
            map.insert(EventTypePair(typeName, SPHandleEventInfoBase(new THandleEventTypeInfo<TEventData>(typeHandler, createState))));
         } else {
            //event already in the map
            LogErr(boost::format("[%1%][%2%] register type event handler for [%3%] from [%4%] failed: already registered\n")
                   % __FUNCTION__
                   % __LINE__
                   % typeName.c_str()
                   % (bDefault ? "default" : "state")
               );
         }
      } catch(std::exception& ex) {
         LogErr(boost::format("Event type handler registration failed for [%1%]: %2%\n")
                % typeid(TEventData).name()
                % ex.what()
            );
      } catch(...) {
         LogErr(boost::format("Event type handler registration failed for [%1%]: %2%\n")
                % typeid(TEventData).name()
                % "unknown"
            );
      }
   }

   /** Register an unguarded event handler.
    **/
   template <class TEventData> 
   void CStateMachine::EventRegister(
      const bool                                     bDefault,         //< When true: register this handler in the default event-type map (default state); when false: register this handler for the current state.
      boost::function<void(const TEventData* const)> unguardedHandler, //< The handler to be registered.
      CCreateState                                   createState,      //< The state transition accompanying this event-type.
      SPEventBase                                    spEventBase       //< The complete event identification that triggers this handler.
      )
   {
      try {
         EventMap& map = EventGetMap(bDefault);
         const EventMapIt it = map.find(spEventBase);
         if(map.end() == it) {
            LogDebug(boost::format("[%1%][%2%] register default event handler for [%3%] from [%4%]\n")
                     % __FUNCTION__
                     % __LINE__
                     % spEventBase->GetId()
                     % (bDefault ? "default" : "state")
               );
            map.insert(EventPair(spEventBase, SPHandleEventInfoBase(new THandleEventInfo<TEventData>(unguardedHandler, createState))));
         } else {
            //event already in the map
            //--> set the default handler
            //    (will throw when the default handler has already been set)
            LogDebug(boost::format("[%1%][%2%] set default event handler for [%3%] from [%4%]\n")
                     % __FUNCTION__
                     % __LINE__
                     % spEventBase->GetId()
                     % (bDefault ? "default" : "state")
               );
            THandleEventInfo<TEventData>* pHandleEventInfo = dynamic_cast<THandleEventInfo<TEventData>*>(it->second.get());
            if(NULL == pHandleEventInfo) {
               //serious error in the implementation: mismatch in registration
               throw std::runtime_error((boost::format("[%1%][%2%]") % __FUNCTION__ % __LINE__).str()); //TODO
            }
            pHandleEventInfo->SetUnguardedHandler(unguardedHandler, createState);
         }
      } catch(std::exception& ex) {
         LogErr(boost::format("Event default handler registration failed for [%1%]: %2%\n")
                % spEventBase->GetId()
                % ex.what()
            );
      } catch(...) {
         LogErr(boost::format("Event default handler registration failed for [%1%]: %2%\n")
                % spEventBase->GetId()
                % "unknown"
            );
      }
   }

   /** Register a guarded event handler.
    **/
   template <class TEventData> 
   bool CStateMachine::EventRegister(
      const bool                                     bDefault,    //< When true: register this handler in the default event-type map (default state); when false: register this handler for the current state.
      boost::function<bool(void)>                    guard,       //< The guard called before the handler. When the guard returns true, the handler is called; when the guard returns false the handler is not called.
      boost::function<void(const TEventData* const)> handler,     //< The handler to be registered.
      CCreateState                                   createState, //< The state transition accompanying this event-type.
      SPEventBase                                    spEventBase  //< The complete event identification that triggers this handler.
      )
   {
      try {
         EventMap& map = EventGetMap(bDefault);
         const EventMapIt it = map.find(spEventBase);
         if(map.end() == it) {
            //event with the specified ID not yet in the map
            //--> add it with a guarded handler
            LogDebug(boost::format("[%1%][%2%] register event guard/handler combo for [%3%] from [%4%]\n")
                     % __FUNCTION__
                     % __LINE__
                     % spEventBase->GetId()
                     % (bDefault ? "default" : "state")
               );
            map.insert(EventPair(spEventBase, SPHandleEventInfoBase(new THandleEventInfo<TEventData>(guard, handler, createState))));
         } else {
            //event already in the map
            //--> add a guarded handler
            LogDebug(boost::format("[%1%][%2%] add event guard/handler combo for [%3%] from [%4%]\n")
                     % __FUNCTION__
                     % __LINE__
                     % spEventBase->GetId()
                     % (bDefault ? "default" : "state")
               );
            THandleEventInfo<TEventData>* pHandleEventInfo = dynamic_cast<THandleEventInfo<TEventData>*>(it->second.get());
            if(NULL == pHandleEventInfo) {
               //serious error in the implementation: mismatch in registration
               throw std::runtime_error((boost::format("[%1%][%2%]") % __FUNCTION__ % __LINE__).str()); //TODO
            }
            pHandleEventInfo->AddGuardedHandler(guard, handler, createState);
         }
         return true;
      } catch(std::exception& ex) {
         LogErr(boost::format("Event guard/handler combo registration failed for [%1%]: %2%\n")
                % spEventBase->GetId()
                % ex.what()
            );
         return false;
      } catch(...) {
         LogErr(boost::format("Event guard/handler combo registration failed for [%1%]: %2%\n")
                % spEventBase->GetId()
                % "unknown"
            );
         return false;
      }
   }

   /** Event handler, called when an event has to be fed into the state machine.
    **
    ** Constructs a SPEventBase instance based on the provided event parameters
    ** and calls the common handler with this instance.
    **/
   template <class TEventData, class EvtId>                                                    
   bool CStateMachine::EventHandle(
      const TEventData* const pEventData, //< The event data belonging to the event.
      const EvtId             evtId       //< Event ID as defined by TEventEvtId.
      )
   {
      return EventHandle(pEventData, SPEventBase(new TEventEvtId<EvtId>(typeid(TEventData).name(), evtId)));
   }

   /** Event handler, called when an event has to be fed into the state machine.
    **
    ** Constructs a SPEventBase instance based on the provided event parameters
    ** and calls the common handler with this instance.
    **/
   template <class TEventData, class EvtId, class EvtSubId1>                                                    
   bool CStateMachine::EventHandle(
      const TEventData* const pEventData, //< The event data belonging to the event.
      const EvtId             evtId,      //< Event ID as defined by TEventEvtId.
      const EvtSubId1         evtSubId1   //< First event sub-ID as defined by TEventEvtId.
      )
   {
      return EventHandle(pEventData, SPEventBase(new TEventEvtId<EvtId, EvtSubId1>(typeid(TEventData).name(), evtId, evtSubId1)));
   }
   
   /** Event handler, called when an event has to be fed into the state machine.
    **
    ** Constructs a SPEventBase instance based on the provided event parameters
    ** and calls the common handler with this instance.
    **/
   template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2>                                                    
   bool CStateMachine::EventHandle(
      const TEventData* const pEventData, //< The event data belonging to the event.
      const EvtId             evtId,      //< Event ID as defined by TEventEvtId.
      const EvtSubId1         evtSubId1,  //< First event sub-ID as defined by TEventEvtId.
      const EvtSubId2         evtSubId2   //< Second event sub-ID as defined by TEventEvtId.
      )
   {
      return EventHandle(pEventData, SPEventBase(new TEventEvtId<EvtId, EvtSubId1, EvtSubId2>(typeid(TEventData).name(), evtId, evtSubId1, evtSubId2)));
   }
   
   /** Event handler, called when an event has to be fed into the state machine.
    **
    ** Constructs a SPEventBase instance based on the provided event parameters
    ** and calls the common handler with this instance.
    **/
   template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>                                                    
   bool CStateMachine::EventHandle(
      const TEventData* const pEventData, //< The event data belonging to the event.
      const EvtId             evtId,      //< Event ID as defined by TEventEvtId.
      const EvtSubId1         evtSubId1,  //< First event sub-ID as defined by TEventEvtId.
      const EvtSubId2         evtSubId2,  //< Second event sub-ID as defined by TEventEvtId.
      const EvtSubId3         evtSubId3   //< Third event sub-ID as defined by TEventEvtId.   
      )
   {
      return EventHandle(pEventData, SPEventBase(new TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>(typeid(TEventData).name(), evtId, evtSubId1, evtSubId2, evtSubId3)));
   }

   /** Event handler, called when an event has to be fed into the state machine.
    **
    ** This function dictates the order in which the event is checked against registered event handlers
    ** - current state event handlers;
    ** - default state event handlers;
    ** - current state event-type handlers;
    ** - default state event-type handlers.
    ** Depending on the match, the appropriate handler is called.
    **
    ** When no match is found, the function traces all registered handlers.
    **
    ** @return true: when the state machine has finished (current state is null); false when the state machine still has a valid state (not null), meaning it has not finished
    **/
   template <class TEventData>                                                    
   bool CStateMachine::EventHandle(
      const TEventData* const pEventData, //< The event data belonging to the event.
      const SPEventBase       spEventBase //< Class instance describing the event in all detail (1 class instance instead of seperate parameters).
      )
   {
      CLogIndent logIndent;
      LogNotice(boost::format("Statemachine [%1%] state [%2%] handling event [%3%] type [%4%] in\n")
              % m_strName
              % GetStateName()
              % spEventBase->GetId()
              % spEventBase->GetDataType()
         );
      
      //try the state event map
      if(EventHandle(false, pEventData, spEventBase)) {
         //event handled
         LogNotice(boost::format("Statemachine [%1%] state [%2%] handling event [%3%] by current state done\n")
                 % m_strName
                 % GetStateName()
                 % spEventBase->GetId()
            );
         return HasFinished();
      }
      
      //try the default event map
      if(EventHandle(true, pEventData, spEventBase)) {
         //event handled
         LogNotice(boost::format("Statemachine [%1%] state [%2%] handling event [%3%] by default state done\n")
                 % m_strName
                 % GetStateName()
                 % spEventBase->GetId()
            );
         return HasFinished();
      }

      //try the state type map
      if(EventTypeHandle(false, pEventData, spEventBase)) {
         //event handled
         LogNotice(boost::format("Statemachine [%1%] state [%2%] handling event type [%3%] by current state done\n")
                 % m_strName
                 % GetStateName()
                 % spEventBase->GetDataType()
            );
         return HasFinished();
      }
      
      //try the default type map
      if(EventTypeHandle(true, pEventData, spEventBase)) {
         //event handled
         LogNotice(boost::format("Statemachine [%1%] state [%2%] handling event type [%3%] by default state done\n")
                 % m_strName
                 % GetStateName()
                 % spEventBase->GetDataType()
            );
         return HasFinished();
      }
      
      LogNotice(boost::format("Statemachine [%1%] state [%2%] handling event [%3%] looking for handler failed: no registered handler\n")
              % m_strName
              % GetStateName()
              % spEventBase->GetId()
         );
      LogNotice(boost::format("Statemachine [%1%] state [%2%] handling event [%3%] with data type [%4%] registered handlers:\n")
              % m_strName
              % GetStateName()
              % spEventBase->GetId()
              % spEventBase->GetDataType()
         );
      TraceHandlers(false);
      TraceHandlers(true);
      TraceTypeHandlers(false);
      TraceTypeHandlers(true);
      return HasFinished();
   }

   /** Internal event handler.
    **
    ** The state machine calls this function to find an event match (not an event-type)
    ** match and call the handler if a match is found.
    **
    ** @return true: when the event has been handled (false otherwise).
    **/
   template <class TEventData>                                                    
   bool CStateMachine::EventHandle(
      const bool              bDefault,   //< Use the current state (false) or the default state (true) to find a matching registered event.
      const TEventData* const pEventData, //< The event data belonging to the event.
      const SPEventBase       spEventBase //< Class instance describing the event in all detail (1 class instance instead of seperate parameters).
      )
   {
      //find handler
      EventMap&        map = EventGetMap(bDefault);
      LogDebug(boost::format("Statemachine [%1%] state [%2%] handling event [%3%] looking for [%4%] handler (%5% registered ID's)\n")
               % m_strName
               % GetStateName()
               % spEventBase->GetId()
               % (bDefault ? "default" : "state")
               % map.size()
         );
      const EventMapIt it  = map.find(spEventBase);
      if(map.end() == it) {
         return false;
      }

      //handler found --> get info to call it
      THandleEventInfo<TEventData>* pHandleEventInfo = dynamic_cast<THandleEventInfo<TEventData>*>(it->second.get());
      if(NULL == pHandleEventInfo) {
         //serious error in the implementation: mismatch in registration
         LogErr(boost::format("Statemachine [%1%] state [%2%] handling event [%3%] looking for [%4%] handler found handler with invalid type\n")
                % m_strName
                % GetStateName()
                % spEventBase->GetId()
                % (bDefault ? "default" : "state")
            );
         return false;
      }
      
      //call handler
      CHandleEventInfoBase::HandleResult result(pHandleEventInfo->Handle(bDefault, pEventData));
      if(!result.first) {
         //no handler found
         return false;
      }
      
      //state change if requested by handler
      ChangeState(result.second);
      
      //event handled
      return true;
   }

   /** Internal event handler.
    **
    ** The state machine calls this function to find an event-type (not an event)
    ** match and call the handler if a match is found.
    **
    ** @return true: when the event has been handled (false otherwise).
    **/
   template <class TEventData>                                                    
   bool CStateMachine::EventTypeHandle(
      const bool              bDefault,   //< Use the current state (false) or the default state (true) to find a matching registered event.
      const TEventData* const pEventData, //< The event data belonging to the event.
      const SPEventBase       spEventBase //< Class instance describing the event in all detail (1 class instance instead of seperate parameters).
      )
   {
      //find handler
      EventTypeMap& map = EventTypeGetMap(bDefault);
      LogDebug(boost::format("Statemachine [%1%] state [%2%] handling event [%3%] looking for [%4%] type handler (%5% registered ID's)\n")
               % m_strName
               % GetStateName()
               % spEventBase->GetId()
               % (bDefault ? "default" : "state")
               % map.size()
         );
      const EventTypeMapIt it = map.find(spEventBase->GetDataType());
      if(map.end() == it) {
         return false;
      }

      //handler found --> get info to call it
      THandleEventTypeInfo<TEventData>* pHandleEventTypeInfo = dynamic_cast<THandleEventTypeInfo<TEventData>*>(it->second.get());
      if(NULL == pHandleEventTypeInfo) {
         //serious error in the implementation: mismatch in registration
         LogErr(boost::format("Statemachine [%1%] state [%2%] handling event [%3%] looking for [%4%] handler found type handler with invalid type\n")
                % m_strName
                % GetStateName()
                % spEventBase->GetId()
                % (bDefault ? "default" : "state")
            );
         return false;
      }
      
      //call handler
      CHandleEventInfoBase::HandleResult result(pHandleEventTypeInfo->Handle(bDefault, spEventBase, pEventData));
      if(!result.first) {
         //no handler found
         return false;
      }
      
      //state change if requested by handler
      ChangeState(result.second);
      
      //event handled
      return true;
   }
};
   
#endif //__ILULibStateMachine_CStateMachineImpl__H__

