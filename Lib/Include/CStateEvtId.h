/** @file
 ** @brief The CStateEvtId declaration.
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
#ifndef __ILULibStateMachine_CStateEvtId__H__
#define __ILULibStateMachine_CStateEvtId__H__

#include "CState.h"

#include "CStateMachine.h"

namespace ILULibStateMachine {
   /** @brief Base class to implement a state that is using TEventEvtId to identify events.
    **
    ** The state machine provide a generic mechanism to define events and register event handlers
    ** which uses TEventEvtId instances to identify an event.
    ** This class is the base class for states using TEventEvtId instances to identify an event.
    ** It provides event regisration functions.
    **
    ** SPStateMachineData is NOT a member as this would require casting CStateMachineDatat to the actual
    ** data class whenever it is used. Thus it is stored directly in the derived classes instead.
    **
    ** The order of the parameters in the register functions is extremely important. In order to avoid
    ** invalid template instantiation, the parameters setting the handlers and create state (present in
    ** all overloads) preceed the event identification parameters.
    **
    ** The implementation of the template functions is put in a seperate header file (included by this
    ** header) to keep the class declaration clean.
    **/
   class CStateEvtId : public CState {
      public:
                            CStateEvtId(const char* const szName, WPStateMachine wpStateMachine, const bool bDefault = false);
         virtual            ~CStateEvtId(void);

      protected:
         template <class TEventData>                                                    
         void EventTypeRegister(
            const std::string&                                                        strEventType,
            TYPESEL::function<void(SPEventBase spEventBase, const TEventData* const)> typeHandler,
            CCreateState                                                              createState   
            );
         template <class TEventData, class EvtId>                                                    
         void EventRegister(
            TYPESEL::function<void(const TEventData* const)> unguardedHandler,
            CCreateState                                     createState     ,
            const EvtId                                      evtId         
            );
         template <class TEventData, class EvtId, class EvtSubId1>                                                    
         void EventRegister(
            TYPESEL::function<void(const TEventData* const)> unguardedHandler,
            CCreateState                                     createState     ,
            const EvtId                                      evtId           ,
            const EvtSubId1                                  evtSubId1      
            );
         template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2>                                                    
         void EventRegister(
            TYPESEL::function<void(const TEventData* const)> unguardedHandler,
            CCreateState                                     createState     ,
            const EvtId                                      evtId           ,
            const EvtSubId1                                  evtSubId1       , 
            const EvtSubId2                                  evtSubId2      
            );
         template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>                                                    
         void EventRegister(
            TYPESEL::function<void(const TEventData* const)> unguardedHandler,
            CCreateState                                     createState     ,
            const EvtId                                      evtId           ,
            const EvtSubId1                                  evtSubId1       , 
            const EvtSubId2                                  evtSubId2       , 
            const EvtSubId3                                  evtSubId3      
            );
         template <class TEventData, class EvtId>                                                    
         void EventRegister(
            TYPESEL::function<bool(const TEventData* const)> guard           ,
            TYPESEL::function<void(const TEventData* const)> handler         ,
            CCreateState                                     createState     ,
            const EvtId                                      evtId      
            );
         template <class TEventData, class EvtId, class EvtSubId1>                                                    
         void EventRegister(
            TYPESEL::function<bool(const TEventData* const)> guard           ,
            TYPESEL::function<void(const TEventData* const)> handler         ,
            CCreateState                                     createState     ,
            const EvtId                                      evtId           ,
            const EvtSubId1                                  evtSubId1      
            );
         template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2>                                                    
         void EventRegister(
            TYPESEL::function<bool(const TEventData* const)> guard           ,
            TYPESEL::function<void(const TEventData* const)> handler         ,
            CCreateState                                     createState     ,
            const EvtId                                      evtId           ,
            const EvtSubId1                                  evtSubId1       , 
            const EvtSubId2                                  evtSubId2      
            );
         template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>                                                    
         void EventRegister(
            TYPESEL::function<bool(const TEventData* const)> guard           ,
            TYPESEL::function<void(const TEventData* const)> handler         ,
            CCreateState                                     createState     ,
            const EvtId                                      evtId           ,
            const EvtSubId1                                  evtSubId1       ,   
            const EvtSubId2                                  evtSubId2       , 
            const EvtSubId3                                  evtSubId3      
            );

      private:
         WPStateMachine     m_wpStateMachine; ///< Weak pointer to the state machine owning this state. Used to register event handlers in the state machine.
                                              //   It is private to avoid that subclasses are using this,
                                              //   all access to the CStateMachine owner should
                                              //   go via this base class.
                                              //   Because it is private, it can not be a member of the 
                                              //   CState base class.
   };
}

//include the class template function definitions.
#include "CStateEvtIdImpl.h"

#endif //__ILULibStateMachine_CStateEvtId__H__

