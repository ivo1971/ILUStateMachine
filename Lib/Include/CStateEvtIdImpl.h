/** @file 
 ** @brief The CStateEvtId template function defintions.
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
#ifndef __ILULibStateMachine_CStateImpl__H__
#define __ILULibStateMachine_CStateImpl__H__

namespace ILULibStateMachine {
   /** Register a handler that catches all events with event data type TEventData when
    ** no other more specific handler has been registered.
    **
    ** This can for example be used to forward all events of a certain type from a
    ** a parent to a child state machine without the parent being aware of all specific
    ** events of that type that can occur. The parant only has to be aware of the event
    ** type to forward them.
    **
    ** The parent has to be at least aware of the event type to avoid dynamic casts on
    ** the event data (which is also the reason for this being a template function).
    **/
   template <class TEventData>                                                    
   void CStateEvtId::EventRegister(
      boost::function<void(SPEventBase spEventBase, const TEventData* const)> typeHandler,  //< The event handler to be called when an event with TEventData occurs and there is no more specific (event ID aware) handler found.
      CCreateState                                                            createState   //< Describes the state transition following this handler. 
      )
   {
      SPStateMachine spStateMachine = m_wpStateMachine.lock();
      if(!spStateMachine) {
         return;
      }
      spStateMachine->EventRegister(m_bDefault, typeHandler, createState);
   }

   /** Register an unguarded handler (handler called without checking a guard first) when an event
    ** matching the specified ID occurs.
    ** 
    ** This is a kind of 'default' handler, called when no guarded handler is found that matches the event
    ** and for which the guard passes.
    **/
   template <class TEventData, class EvtId>                                                    
   void CStateEvtId::EventRegister(
      boost::function<void(const TEventData* const)> unguardedHandler, //< Event handler to be called.
      CCreateState                                   createState,      //< Describes the state transition following this handler. 
      const EvtId                                    evtId             //< Event ID as defined by TEventEvtId.
      )
   {
      SPStateMachine spStateMachine = m_wpStateMachine.lock();
      if(!spStateMachine) {
         return;
      }
      spStateMachine->EventRegister(m_bDefault, unguardedHandler, createState, SPEventBase(new TEventEvtId<EvtId>(typeid(TEventData).name(), evtId)));
   }

   /** Register an unguarded handler (handler called without checking a guard first) when an event
    ** matching the specified ID occurs.
    ** 
    ** This is a kind of 'default' handler, called when no guarded handler is found that matches the event
    ** and for which the guard passes.
    **/
   template <class TEventData, class EvtId, class EvtSubId1>                                                    
   void CStateEvtId::EventRegister(
      boost::function<void(const TEventData* const)> unguardedHandler, //< Event handler to be called.
      CCreateState                                   createState,      //< Describes the state transition following this handler. 
      const EvtId                                    evtId,            //< Event ID as defined by TEventEvtId.
      const EvtSubId1                                evtSubId1         //< First event sub-ID as defined by TEventEvtId.
      )
   {
      SPStateMachine spStateMachine = m_wpStateMachine.lock();
      if(!spStateMachine) {
         return;
      }
      spStateMachine->EventRegister(m_bDefault, unguardedHandler, createState, SPEventBase(new TEventEvtId<EvtId, EvtSubId1>(typeid(TEventData).name(), evtId, evtSubId1)));
   }
   
   /** Register an unguarded handler (handler called without checking a guard first) when an event
    ** matching the specified ID occurs.
    ** 
    ** This is a kind of 'default' handler, called when no guarded handler is found that matches the event
    ** and for which the guard passes.
    **/
   template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2>                                                    
   void CStateEvtId::EventRegister(
      boost::function<void(const TEventData* const)> unguardedHandler, //< Event handler to be called.
      CCreateState                                   createState,      //< Describes the state transition following this handler. 
      const EvtId                                    evtId,            //< Event ID as defined by TEventEvtId.
      const EvtSubId1                                evtSubId1,        //< First event sub-ID as defined by TEventEvtId.
      const EvtSubId2                                evtSubId2         //< Second event sub-ID as defined by TEventEvtId.
      )
   {
      SPStateMachine spStateMachine = m_wpStateMachine.lock();
      if(!spStateMachine) {
         return;
      }
      spStateMachine->EventRegister(m_bDefault, unguardedHandler, createState, SPEventBase(new TEventEvtId<EvtId, EvtSubId1, EvtSubId2>(typeid(TEventData).name(), evtId, evtSubId1, evtSubId2)));
   }
   
   /** Register an unguarded handler (handler called without checking a guard first) when an event
    ** matching the specified ID occurs.
    ** 
    ** This is a kind of 'default' handler, called when no guarded handler is found that matches the event
    ** and for which the guard passes.
    **/
   template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>                                                    
   void CStateEvtId::EventRegister(
      boost::function<void(const TEventData* const)> unguardedHandler, //< Event handler to be called.
      CCreateState                                   createState,      //< Describes the state transition following this handler. 
      const EvtId                                    evtId,            //< Event ID as defined by TEventEvtId.
      const EvtSubId1                                evtSubId1,        //< First event sub-ID as defined by TEventEvtId.
      const EvtSubId2                                evtSubId2,        //< Second event sub-ID as defined by TEventEvtId.
      const EvtSubId3                                evtSubId3         //< Third event sub-ID as defined by TEventEvtId.      
      )
   {
      SPStateMachine spStateMachine = m_wpStateMachine.lock();
      if(!spStateMachine) {
         return;
      }
      spStateMachine->EventRegister(m_bDefault, unguardedHandler, createState, SPEventBase(new TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>(typeid(TEventData).name(), evtId, evtSubId1, evtSubId2, evtSubId3)));
   }
   
   /** Register a guarded handler (handler called with checking a guard first) when an event
    ** matching the specified ID occurs.
    **
    ** If the guard returns false, the actual handler is not called and the event is unhandled by this registration.
    **/
   template <class TEventData, class EvtId>                                                    
   void CStateEvtId::EventRegister(
      boost::function<bool(const TEventData* const)> guard,        //< Guard called before the event handler. When the guard returns true the handler will be called; when the guard returns false the handler will not be called.
      boost::function<void(const TEventData* const)> handler,      //< Event handler to be called.
      CCreateState                                   createState,  //< Describes the state transition following this handler. 
      const EvtId                                    evtId         //< Event ID as defined by TEventEvtId.
      )
   {
      SPStateMachine spStateMachine = m_wpStateMachine.lock();
      if(!spStateMachine) {
         return;
      }
      spStateMachine->EventRegister(m_bDefault, guard, handler, createState, SPEventBase(new TEventEvtId<EvtId>(typeid(TEventData).name(), evtId)));
   }

   /** Register a guarded handler (handler called with checking a guard first) when an event
    ** matching the specified ID occurs.
    **
    ** If the guard returns false, the actual handler is not called and the event is unhandled by this registration.
    **/
   template <class TEventData, class EvtId, class EvtSubId1>                                                    
   void CStateEvtId::EventRegister(
      boost::function<bool(const TEventData* const)> guard,        //< Guard called before the event handler. When the guard returns true the handler will be called; when the guard returns false the handler will not be called.
      boost::function<void(const TEventData* const)> handler,      //< Event handler to be called.
      CCreateState                                   createState,  //< Describes the state transition following this handler. 
      const EvtId                                    evtId,        //< Event ID as defined by TEventEvtId.
      const EvtSubId1                                evtSubId1     //< First event sub-ID as defined by TEventEvtId.
      )
   {
      SPStateMachine spStateMachine = m_wpStateMachine.lock();
      if(!spStateMachine) {
         return;
      }
      spStateMachine->EventRegister(m_bDefault, guard, handler, createState, SPEventBase(new TEventEvtId<EvtId, EvtSubId1>(typeid(TEventData).name(), evtId, evtSubId1)));
   }
   
   /** Register a guarded handler (handler called with checking a guard first) when an event
    ** matching the specified ID occurs.
    **
    ** If the guard returns false, the actual handler is not called and the event is unhandled by this registration.
    **/
   template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2>                                                    
   void CStateEvtId::EventRegister(
      boost::function<bool(const TEventData* const)> guard,        //< Guard called before the event handler. When the guard returns true the handler will be called; when the guard returns false the handler will not be called.
      boost::function<void(const TEventData* const)> handler,      //< Event handler to be called.
      CCreateState                                   createState,  //< Describes the state transition following this handler. 
      const EvtId                                    evtId,        //< Event ID as defined by TEventEvtId.
      const EvtSubId1                                evtSubId1,    //< First event sub-ID as defined by TEventEvtId.
      const EvtSubId2                                evtSubId2     //< Second event sub-ID as defined by TEventEvtId.
      )
   {
      SPStateMachine spStateMachine = m_wpStateMachine.lock();
      if(!spStateMachine) {
         return;
      }
      spStateMachine->EventRegister(m_bDefault, guard, handler, createState, SPEventBase(new TEventEvtId<EvtId, EvtSubId1, EvtSubId2>(typeid(TEventData).name(), evtId, evtSubId1, evtSubId2)));
   }
   
   /** Register a guarded handler (handler called with checking a guard first) when an event
    ** matching the specified ID occurs.
    **
    ** If the guard returns false, the actual handler is not called and the event is unhandled by this registration.
    **/
   template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>                                                    
   void CStateEvtId::EventRegister(
      boost::function<bool(const TEventData* const)> guard,        //< Guard called before the event handler. When the guard returns true the handler will be called; when the guard returns false the handler will not be called.
      boost::function<void(const TEventData* const)> handler,      //< Event handler to be called.
      CCreateState                                   createState,  //< Describes the state transition following this handler. 
      const EvtId                                    evtId,        //< Event ID as defined by TEventEvtId.
      const EvtSubId1                                evtSubId1,    //< First event sub-ID as defined by TEventEvtId.
      const EvtSubId2                                evtSubId2,    //< Second event sub-ID as defined by TEventEvtId.
      const EvtSubId3                                evtSubId3     //< Third event sub-ID as defined by TEventEvtId.      
      )
   {
      SPStateMachine spStateMachine = m_wpStateMachine.lock();
      if(!spStateMachine) {
         return;
      }
      spStateMachine->EventRegister(m_bDefault, guard, handler, createState, SPEventBase(new TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>(typeid(TEventData).name(), evtId, evtSubId1, evtSubId2, evtSubId3)));
   }
}

#endif //__ILULibStateMachine_CStateImpl__H__

