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

#include "Logging.h"
#include "THandleEventInfo.h"
#include "THandleEventTypeInfo.h"

namespace ILULibStateMachine {
   /** Register an event-type handler.
    **/
   template <class TEventData> 
   void CStateMachine::EventTypeRegister(
      const bool                                                                bDefault,     //< When true: register this handler in the default event-type map (default state); when false: register this handler for the current state.
      const std::string&                                                        strEventType, //< String representation of the event type.
      TYPESEL::function<void(SPEventBase spEventBase, const TEventData* const)> typeHandler,  //< The handler to be registered.
      CCreateState                                                              createState   //< The state transition accompanying this event-type.
      )
   {
      try {
         EventTypeMap& map = EventTypeGetMap(bDefault);
         const EventTypeMapIt it = map.find(strEventType);
         if(map.end() == it) {
            LogDebug("Register type event handler for [%s] from [%s]\n",
                     strEventType.c_str(),
                     (bDefault ? "default" : "state")
                     );
            map.insert(EventTypePair(strEventType, SPHandleEventInfoBase(new THandleEventTypeInfo<TEventData>(typeHandler, createState))));
         } else {
            //event already in the map
            LogErr("Register type event handler for [%s] from [%s] failed: already registered\n",
                   strEventType.c_str(),
                   (bDefault ? "default" : "state")
                   );
         }
      } catch(std::exception& ex) {
         LogErr("Event type handler registration failed for [%s]: %s\n",
                strEventType.c_str(),
                ex.what()
                );
      } catch(...) {
         LogErr("Event type handler registration failed for [%s]: %s\n",
                strEventType.c_str(),
                "unknown"
                );
      }
   }

   /** Register an unguarded event handler.
    **/
   template <class TEventData> 
   void CStateMachine::EventRegister(
      const bool                                       bDefault,         //< When true: register this handler in the default event-type map (default state); when false: register this handler for the current state.
      TYPESEL::function<void(const TEventData* const)> unguardedHandler, //< The handler to be registered.
      CCreateState                                     createState,      //< The state transition accompanying this event-type.
      SPEventBase                                      spEventBase       //< The complete event identification that triggers this handler.
      )
   {
      try {
         EventMap& map = EventGetMap(bDefault);
         const EventMapIt it = map.find(spEventBase);
         if(map.end() == it) {
            LogDebug("Register unguarded event handler for [%s] from [%s]\n",
                     spEventBase->GetId().c_str(),
                     (bDefault ? "default" : "state")
                     );
            map.insert(EventPair(spEventBase, SPHandleEventInfoBase(new THandleEventInfo<TEventData>(unguardedHandler, createState))));
         } else {
            //event already in the map
            //--> set the default handler
            //    (will throw when the default handler has already been set)
            LogDebug("Set unguarded event handler for [%s] from [%s]\n",
                     spEventBase->GetId().c_str(),
                     (bDefault ? "default" : "state")
                     );
            THandleEventInfo<TEventData>* pHandleEventInfo = dynamic_cast<THandleEventInfo<TEventData>*>(it->second.get());
            if(NULL == pHandleEventInfo) {
               //serious error in the implementation: mismatch in registration
               throw std::runtime_error("IMPLEMENTATION ERROR: registration mismatch found in unguarded event handler");
            }
            pHandleEventInfo->SetUnguardedHandler(unguardedHandler, createState);
         }
      } catch(std::exception& ex) {
         LogErr("Event default handler registration failed for [%s]: %s\n",
                spEventBase->GetId().c_str(),
                ex.what()
                );
      } catch(...) {
         LogErr("Event default handler registration failed for [%s]: %s\n",
                spEventBase->GetId().c_str(),
                "unknown"
                );
      }
   }

   /** Register a guarded event handler.
    **/
   template <class TEventData> 
   bool CStateMachine::EventRegister(
      const bool                                       bDefault,    //< When true: register this handler in the default event-type map (default state); when false: register this handler for the current state.
      TYPESEL::function<bool(const TEventData* const)> guard,       //< The guard called before the handler. When the guard returns true, the handler is called; when the guard returns false the handler is not called.
      TYPESEL::function<void(const TEventData* const)> handler,     //< The handler to be registered.
      CCreateState                                     createState, //< The state transition accompanying this event-type.
      SPEventBase                                      spEventBase  //< The complete event identification that triggers this handler.
      )
   {
      try {
         EventMap& map = EventGetMap(bDefault);
         const EventMapIt it = map.find(spEventBase);
         if(map.end() == it) {
            //event with the specified ID not yet in the map
            //--> add it with a guarded handler
            LogDebug("Register event guard/handler combo for [%s] from [%s]\n",
                     spEventBase->GetId().c_str(),
                     (bDefault ? "default" : "state")
                     );
            map.insert(EventPair(spEventBase, SPHandleEventInfoBase(new THandleEventInfo<TEventData>(guard, handler, createState))));
         } else {
            //event already in the map
            //--> add a guarded handler
            LogDebug("Add event guard/handler combo for [%s] from [%s]\n",
                     spEventBase->GetId().c_str(),
                     (bDefault ? "default" : "state")
                     );
            THandleEventInfo<TEventData>* pHandleEventInfo = dynamic_cast<THandleEventInfo<TEventData>*>(it->second.get());
            if(NULL == pHandleEventInfo) {
               //serious error in the implementation: mismatch in registration
               throw std::runtime_error("IMPLEMENTATION ERROR: registration mismatch found in guarded event handler");
            }
            pHandleEventInfo->AddGuardedHandler(guard, handler, createState);
         }
         return true;
      } catch(std::exception& ex) {
         LogErr("Event guard/handler combo registration failed for [%s]: %s\n",
                spEventBase->GetId().c_str(),
                ex.what()
                );
         return false;
      } catch(...) {
         LogErr("Event guard/handler combo registration failed for [%s]: %s\n",
                spEventBase->GetId().c_str(),
                "unknown"
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
      return EventHandle(pEventData, SPEventBase(new TEventEvtId<EvtId>(typeid(TEventData), evtId)));
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
      return EventHandle(pEventData, SPEventBase(new TEventEvtId<EvtId, EvtSubId1>(typeid(TEventData), evtId, evtSubId1)));
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
      return EventHandle(pEventData, SPEventBase(new TEventEvtId<EvtId, EvtSubId1, EvtSubId2>(typeid(TEventData), evtId, evtSubId1, evtSubId2)));
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
      return EventHandle(pEventData, SPEventBase(new TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>(typeid(TEventData), evtId, evtSubId1, evtSubId2, evtSubId3)));
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
      //store the current state name as the current state can change and the logging
      //should keep the original state name for the handling loggings
      const std::string strCurrentState(GetStateName());
      
      CLogIndent logIndent;
      LogNotice("Statemachine [%s] state [%s] handling event [%s] type [%s] in\n",
                m_strName.c_str(),
                strCurrentState.c_str(),
                spEventBase->GetId().c_str(),
                spEventBase->GetDataType().c_str()
                );
      
      //try the state event map
      if(EventHandle(false, pEventData, spEventBase)) {
         //event handled
         LogNotice("Statemachine [%s] state [%s] handling event [%s] by current state done\n",
                   m_strName.c_str(),
                   strCurrentState.c_str(),
                   spEventBase->GetId().c_str()
                   );
         return HasFinished();
      }
      
      //try the default event map
      if(EventHandle(true, pEventData, spEventBase)) {
         //event handled
         LogNotice("Statemachine [%s] state [%s] handling event [%s] by default state done\n",
                   m_strName.c_str(),
                   strCurrentState.c_str(),
                   spEventBase->GetId().c_str()
            );
         return HasFinished();
      }

      //try the state type map
      if(EventTypeHandle(false, pEventData, spEventBase)) {
         //event handled
         LogNotice("Statemachine [%s] state [%s] handling event type [%s] by current state done\n",
                   m_strName.c_str(),
                   strCurrentState.c_str(),
                   spEventBase->GetDataType().c_str()
            );
         return HasFinished();
      }
      
      //try the default type map
      if(EventTypeHandle(true, pEventData, spEventBase)) {
         //event handled
         LogNotice("Statemachine [%s] state [%s] handling event type [%s] by default state done\n",
                   m_strName.c_str(),
                   strCurrentState.c_str(),
                   spEventBase->GetDataType().c_str()
                   );
         return HasFinished();
      }
      
      LogNotice("Statemachine [%s] state [%s] handling event [%s] looking for handler failed: no matching registered handler --> event ignored\n",
                m_strName.c_str(),
                strCurrentState.c_str(),
                spEventBase->GetId().c_str()
                );
      TraceAll();
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
      LogDebug("Statemachine [%s] state [%s] handling event [%s] looking for [%s] handler (%lu registered ID's)\n",
               m_strName.c_str(),
               GetStateName().c_str(),
               spEventBase->GetId().c_str(),
               (bDefault ? "default" : "state"),
               (long unsigned int)map.size()
               );
      const EventMapIt it  = map.find(spEventBase);
      if(map.end() == it) {
         return false;
      }

      //handler found --> get info to call it
      THandleEventInfo<TEventData>* pHandleEventInfo = dynamic_cast<THandleEventInfo<TEventData>*>(it->second.get());
      if(NULL == pHandleEventInfo) {
         //serious error in the implementation: mismatch in registration
         LogErr("Statemachine [%s] state [%s] handling event [%s] looking for [%s] handler found handler with invalid type\n",
                m_strName.c_str(),
                GetStateName().c_str(),
                spEventBase->GetId().c_str(),
                (bDefault ? "default" : "state")
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
      LogDebug("Statemachine [%s] state [%s] handling event type [%s] in [%s] (%lu registered ID's)\n",
               m_strName.c_str(),
               GetStateName().c_str(),
               spEventBase->GetIdType().c_str(),
               (bDefault ? "default" : "state"),
               (long unsigned int)map.size()
               );
      const EventTypeMapIt it = map.find(spEventBase->GetIdType());
      if(map.end() == it) {
         return false;
      }

      //handler found --> get info to call it
      THandleEventTypeInfo<TEventData>* pHandleEventTypeInfo = dynamic_cast<THandleEventTypeInfo<TEventData>*>(it->second.get());
      if(NULL == pHandleEventTypeInfo) {
         //serious error in the implementation: mismatch in registration
         LogErr("Statemachine [%s] state [%s] handling event type [%s] in [%s] found type handler with type\n",
                  m_strName.c_str(),
                  GetStateName().c_str(),
                  spEventBase->GetIdType().c_str(),
                  (bDefault ? "default" : "state")
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

