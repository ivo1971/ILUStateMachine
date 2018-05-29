/** @file
 ** @brief The CStateMachine declaration.
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
#ifndef __ILULibStateMachine_CStateMachine__H__
#define __ILULibStateMachine_CStateMachine__H__

#include "Types.h"

#include "CCreateState.h"
#include "CHandleEventInfoBase.h"
#include "CStateMachineData.h"
#include "TEventEvtId.h"
#include "CSPEventBaseSort.h"

namespace ILULibStateMachine {
   /** @brief This is the actual state machine engine,
    ** instantiated once per state machine.
    **
    ** The class takes ownership of the provided pStateMachineData: it will destruct it, can be nullptr (if no overall data is required)
    ** creates and owns the states
    **
    ** When a statemachine has completely finished, the m_pState can become nullptr.
    ** The state machine data will still be accessible.
    **
    ** It is possible to subclass CStateMachine in order to get selective access (e.g. processing result) in
    ** the state machine data via function calls (never give direct access to the data instance.
    **
    ** Do not use a shared_ptr of CStateMachineData but a raw pointer instead:
    ** - its ownership and life time are well defined and no cause of errors
    ** - there will be no instances of CStateMachineData itself, only of derived
    **   classes, which would result in easy shared_ptr mistakes with dramatic
    **   consequences
    **
    **/
   class CStateMachine : public TYPESEL::enable_shared_from_this<CStateMachine> {
      public:
         static TYPESEL::shared_ptr<CStateMachine> ConstructStateMachine(const char* szName, CCreateState createState,                                  CStateMachineData* const pStateMachineData = NULL);
         static TYPESEL::shared_ptr<CStateMachine> ConstructStateMachine(const char* szName, CCreateState createState, CCreateState createDefaultState, CStateMachineData* const pStateMachineData = NULL);
         virtual                                   ~CStateMachine(void);

      public:
         const std::string&                         GetName(void) const;
         bool                                       HasFinished(void) const;
         template <class TEventData> 
         void                                       EventTypeRegister(
            const bool                                                                bDefault   ,
            const std::string&                                                        strEventType,
            TYPESEL::function<void(SPEventBase spEventBase, const TEventData* const)> typeHandler,
            CCreateState                                                              createState   
            );
         template <class TEventData> 
         void                                       EventRegister(
            const bool                                       bDefault       ,
            TYPESEL::function<void(const TEventData* const)> unguaredHandler,
            CCreateState                                     createState    ,
            SPEventBase                                      spEventBase    
            );
         template <class TEventData> 
         bool                                       EventRegister(
            const bool                                       bDefault   ,
            TYPESEL::function<bool(const TEventData* const)> guard      ,
            TYPESEL::function<void(const TEventData* const)> handler    ,
            CCreateState                                     createState,
            SPEventBase                                      spEventBase    
            );
         template <class TEventData, class EvtId>                                                    
         bool                                       EventHandle(
            const TEventData* const pEventData,
            const EvtId             evtId     
            );
         template <class TEventData, class EvtId, class EvtSubId1>                                                    
         bool                                       EventHandle(
            const TEventData* const pEventData,
            const EvtId             evtId     ,
            const EvtSubId1         evtSubId1  
            );
         template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2>                                                    
         bool                                       EventHandle(
            const TEventData* const pEventData,
            const EvtId             evtId     ,
            const EvtSubId1         evtSubId1 , 
            const EvtSubId2         evtSubId2  
            );
         template <class TEventData, class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>                                                    
         bool                                       EventHandle(
            const TEventData* const pEventData,
            const EvtId             evtId     ,
            const EvtSubId1         evtSubId1 , 
            const EvtSubId2         evtSubId2 , 
            const EvtSubId3         evtSubId3      
            );
         template <class TEventData>                                                    
         bool                                       EventHandle(
            const TEventData* const pEventData,
            const SPEventBase       spEventBase
            );

      private:
         typedef std::pair<SPEventBase, SPHandleEventInfoBase>                  EventPair;       //< pair coupling an event ID to a handle-event-info instance
         typedef std::map<SPEventBase, SPHandleEventInfoBase, CSPEventBaseSort> EventMap;        //< map of event ID/handle-event-info pairs, do use custom sort because we do not want to sort pointer values
         typedef EventMap::iterator                                             EventMapIt;      //< iterator for the event map
         typedef EventMap::const_iterator                                       EventMapCIt;     //< const iterator for the event map
         typedef std::pair<std::string, SPHandleEventInfoBase>                  EventTypePair;   //< pair coupling an event ID to a handle-event-info instance
         typedef std::map<std::string, SPHandleEventInfoBase>                   EventTypeMap;    //< map of event ID/handle-event-info pairs, do use custom sort because we do not want to sort pointer values
         typedef EventTypeMap::iterator                                         EventTypeMapIt;  //< iterator for the event map
         typedef EventTypeMap::const_iterator                                   EventTypeMapCIt; //< const iterator for the event map
         
      private:
                                                 CStateMachine(const char* szName, CStateMachineData* const pStateMachineData);
                                                 CStateMachine(CStateMachine& ref); //defined, not implemented --> avoid copy
         CStateMachine                           operator=(CStateMachine& ref);     //defined, not implemented --> avoid copy
         void                                    SetInitialState(CCreateState& createState, CCreateState createDefaultState = CCreateState());
         void                                    ChangeState(const CCreateState& createState);
         EventMap&                               EventGetMap(const bool bDefault);
         const EventMap&                         EventGetMap(const bool bDefault) const;
         EventTypeMap&                           EventTypeGetMap(const bool bDefault);
         const EventTypeMap&                     EventTypeGetMap(const bool bDefault) const;
         void                                    EventUnregister(const bool bDefault);
         void                                    TraceAll(void) const;
         void                                    TraceHandlers(const bool bDefault) const;
         void                                    TraceTypeHandlers(const bool bDefault) const;
         std::string                             GetStateName(const bool bDefault = false) const; 
         template <class TEventData>                                                    
         bool                                    EventHandle(
            const bool              bDefault   ,
            const TEventData* const pEventData ,
            const SPEventBase       spEventBase
            );
         template <class TEventData>                                                    
         bool                                    EventTypeHandle(
            const bool              bDefault   ,
            const TEventData* const pEventData ,
            const SPEventBase       spEventBase
            );

      private:
         const std::string                       m_strName;             //< The state machine name, logging only.
         EventMap                                m_EventMapDefault;     //< Map of event handlers registered for the default state.
         EventMap                                m_EventMapState;       //< Map of event handlers registered for the current state. They precede the handlers for the default state.
         EventTypeMap                            m_EventTypeMapDefault; //< Map of event-type handlers registered for the default state.
         EventTypeMap                            m_EventTypeMapState;   //< Map of event-type handlers registered for the current state. They precede the handlers for the default state.
         CState*                                 m_pDefaultState;       //< Pointer to the default state. Owned and deleted by the state machine when it is destructed itself. Raw pointer since fine-grained control over life-time is required (on-exit/on-entry functions).
         CState*                                 m_pState;              //< Pointer to the current state. Created and deleted by the state machine during state transitions. Raw pointer since fine-grained control over life-time is required (on-exit/on-entry functions)
         CStateMachineData* const                m_pStateMachineData;   //< Pointer to the state machine data. Owned and deleted by the state machine when it is destructed itself. Raw pointer to avoid dynamic-casts to the type used inside the state classes of the actual state machine (which derives from CStateMachineData)
   };

   /** Define a shared pointer to CStateMachine.
    **/
   typedef TYPESEL::shared_ptr<CStateMachine>    SPStateMachine;

   /** Define a weak pointer to the CStateMachine.
    **/
   typedef TYPESEL::weak_ptr<CStateMachine>      WPStateMachine;
}

#define GUARD(et,cl,f)        TYPESEL::function<bool(const et* const)>(TYPESEL::bind(&cl::f, this, TYPESEL_PLACEHOLDERS_1))                                                          ///< Macro eases definition of a guard handler upon event registration. First parameter: event data type; second parameter: class; second parameter: class method.
#define HANDLER(et,cl,f)      TYPESEL::function<void(const et* const)>(TYPESEL::bind(&cl::f, this, TYPESEL_PLACEHOLDERS_1))                                                          ///< Macro eases definition of an event handler upon event registration. First parameter: event data type; second parameter: class; third parameter: class method.
#define HANDLER_NO_DATA(cl,f) TYPESEL::function<void(const CStateMachineData* const)>(TYPESEL::bind(&cl::f, this, TYPESEL_PLACEHOLDERS_1))                                           ///< Macro eases definition of an event handler upon event registration when the state machine has no accompanying data. First parameter: class; second parameter: class method.
#define HANDLER_TYPE(et,cl,f) TYPESEL::function<void(ILULibStateMachine::SPEventBase, const et* const)>(TYPESEL::bind(&cl::f, this, TYPESEL_PLACEHOLDERS_1, TYPESEL_PLACEHOLDERS_2)) ///<Macro eases definition of an event-type handler upon event registration. First parameter: event data type; second parameter: class; third parameter: class method.

//include the class template function definitions.
#include "CStateMachineImpl.h"

#endif //__ILULibStateMachine_CStateMachine__H__

