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
#include "Include/CStateChangeException.h"
#include "Include/CState.h"
#include "Include/CStateMachine.h"
#include "Include/Logging.h"

namespace ILULibStateMachine {
   /** Factory function to instantiate a state machine without a default state.
    ** 
    ** This factory function and the private state machine constructors ensure
    ** that the state machines are instantiated correctly:
    ** - first create an instance;
    ** - then set the initial state of the state machine.
    ** This is required becuase CCreateState takes a weak pointer to the state machine.
    **
    ** @return a shared pointer to the instantiated state machine.
    **/
   boost::shared_ptr<CStateMachine> CStateMachine::ConstructStateMachine(
      const char* szName,                        //< State machine name, logging only.
      CCreateState createState,                  //< Class to create the initial state.
      CStateMachineData* const pStateMachineData //< Pointer to the state machine data belonging to this state machine. The state machine takes ownership and deletes the instance when the state machine itself is destructed.
      )
   {
      boost::shared_ptr<CStateMachine> sp(new CStateMachine(szName, pStateMachineData));
      sp->SetInitialState(createState);
      return sp;
   }

   /** Factory function to instantiate a state machine with a default state.
    ** 
    ** This factory function and the private state machine constructors ensure
    ** that the state machines are instantiated correctly:
    ** - first create an instance;
    ** - then set the initial state of the state machine.
    ** This is required becuase CCreateState takes a weak pointer to the state machine.
    **
    ** @return a shared pointer to the instantiated state machine.
    **/
   boost::shared_ptr<CStateMachine> CStateMachine::ConstructStateMachine(
      const char* szName,                        //< State machine name, logging only.
      CCreateState createState,                  //< Class to create the initial state.
      CCreateState createDefaultState,           //< Class to create the default state.
      CStateMachineData* const pStateMachineData //< Pointer to the state machine data belonging to this state machine. The state machine takes ownership and deletes the instance when the state machine itself is destructed.
      )
   {
      boost::shared_ptr<CStateMachine> sp(new CStateMachine(szName, pStateMachineData));
      sp->SetInitialState(createState, createDefaultState);
      return sp;
   }

   /** Destructor.
    **/
   CStateMachine::~CStateMachine(void)
   {
      //unregister state handlers
      EventUnregister(true);
      EventUnregister(false);

      //delete in reverse order
      delete m_pState;
      delete m_pDefaultState;
      delete m_pStateMachineData;
   }

   /** Get the state machine name.
    **
    ** @return the state machine name.
    **/
   const std::string& CStateMachine::GetName(void) const
   {
      return m_strName;
   }

   /** Indicates whether the state machine has finished (state is null) or not.
    **
    ** @return true: when the state machine has finished (state is null); false when the state machine still has a valid state (not null), meaning it has not finished.
    **/
   bool CStateMachine::HasFinished(void) const
   {
      return NULL == m_pState;
   }

   /** Constructor.
    **/
   CStateMachine::CStateMachine(
      const char* szName,                        //< State machine name, logging only.
      CStateMachineData* const pStateMachineData //< Pointer to the state machine data belonging to this state machine. The state machine takes ownership and deletes the instance when the state machine itself is destructed.
      )
      : m_strName            (szName           )
      , m_EventMapDefault    (                 )
      , m_EventMapState      (                 )
      , m_EventTypeMapDefault(                 )
      , m_EventTypeMapState  (                 )
      , m_pDefaultState      (NULL             )
      , m_pState             (NULL             )
      , m_pStateMachineData  (pStateMachineData)
   {
   }

   /** Set the initial state of the state machine.
    **
    ** This function is required becuase CCreateState takes a weak pointer to the state machine
    ** as a parameter. Such a weak pointer does not yet exist in the constructor, hence the
    ** initial state (and default) state have to be set later (from the factory function).
    ** 
    ** It can set the intial state and the default state at the same time.
    **/
   void CStateMachine::SetInitialState(
      CCreateState& createState,       //< Class to create the initial state.
      CCreateState  createDefaultState //< Class to create the default state. Cannot be a reference due to the default value.
      )
   {
      if(createDefaultState.IsValid()) {
         m_pDefaultState = createDefaultState.Get()(WPStateMachine(shared_from_this()));
      }
      m_pState = createState.Get()(WPStateMachine(shared_from_this()));
   }

   /** Take all actions required to change the current state of the state machine.
    **
    ** This includes desctructing the current state (and unregistering all its event
    ** handlers) and constructing the new state.
    **/
   void CStateMachine::ChangeState(
      const CCreateState& createState //< Class that describes the next state to be created. Class can describe that no new state has to be created, in which case the state machine remains in the same state.
      )
   {
      //step 1: check if a state change is required
      if(!createState.IsValid()) {
         //nope, no state change requested
         return;
      }
      //yes, state change requested

      //step 2: unregister state handlers
      EventUnregister(false);

      //step 3: delete existing state
      {
         const std::string strStateName(GetStateName(false));
         LogDebug(boost::format("State-change destructing state [%1%]\n") % strStateName);
         {
            CLogIndent logIndent;
            delete m_pState;
         }
         LogDebug(boost::format("State-change destructing state [%1%] done\n") % strStateName);
         m_pState = NULL;
      }

      //step 4: create the new state
      //        store the new state
      //        when a 'CStateChangeException' occures, propagate to creating the next state
      for(CCreateState createStateLoop = createState.Get() ; createStateLoop.IsValid() ; /* createStateLoop changed inside the loop */) {
         try {
            CCreateState createStateTmp = createStateLoop;
            createStateLoop = CCreateState(); //make invalid (break loop)
            LogDebug(boost::format("State-change constructing new state\n"));
            {
               CLogIndent logIndent;
               m_pState = createStateTmp.Get()(WPStateMachine(shared_from_this()));
            }
            LogDebug(boost::format("State-change constructing new state [%1%] done\n") % GetStateName(false));
         } catch(CStateChangeException& ex) {
            LogWarning(boost::format("Caught state-change-exception while creating new state --> create next state: %1%\n") % ex.what());
            createStateLoop = ex.GetCreateState();
         } catch(std::exception& ex) {
            LogErr(boost::format("Caught exeption while creating new state --> setting null-state (state machine finished): %1%\n") % ex.what());
            m_pState = NULL;
         } catch(...) {
            LogErr(boost::format("Caught exeption while creating new state --> setting null-state (state machine finished): %1%\n") % "unknown");
            m_pState = NULL;
         }
      }
   }

   /** Get a reference to the event map for the current or default state.
    **/
   CStateMachine::EventMap& CStateMachine::EventGetMap(
      const bool bDefault //< When true get a reference to the default map; when false get a reference to the current map.
      )
   {
      return bDefault ? m_EventMapDefault : m_EventMapState;
   }

   /** Get a const reference to the event map for the current or default state.
    **/
   const CStateMachine::EventMap& CStateMachine::EventGetMap(
      const bool bDefault //< When true get a reference to the default map; when false get a reference to the current map.
      ) const
   {
      return bDefault ? m_EventMapDefault : m_EventMapState;
   }

   /** Get a reference to the event-type map for the current or default state.
    **/
   CStateMachine::EventTypeMap& CStateMachine::EventTypeGetMap(
      const bool bDefault //< When true get a reference to the default map; when false get a reference to the current map.
      )
   {
      return bDefault ? m_EventTypeMapDefault : m_EventTypeMapState;
   }

   /** Get a const reference to the event-type map for the current or default state.
    **/
   const CStateMachine::EventTypeMap& CStateMachine::EventTypeGetMap(
      const bool bDefault //< When true get a reference to the default map; when false get a reference to the current map.
      ) const
   {
      return bDefault ? m_EventTypeMapDefault : m_EventTypeMapState;
   }

   /** Unregister all events for the current or default state.
    **/
   void CStateMachine::EventUnregister(
      const bool bDefault //< When true unregister handlers belonging to the default state; when false unregister handlers belonging to the current state.
      )
   {
      EventMap& map = EventGetMap(bDefault);
      map.clear();
   }

   /** Trace all event handlers registered for the default or current state.
    **/
   void CStateMachine::TraceHandlers(
      const bool bDefault //< When true trace handlers belonging to the default state; when false trace handlers belonging to the current state.
      ) const
   {
      CLogIndent logIndent1;
      const EventMap& map = EventGetMap(bDefault);
      LogDebug(boost::format("%1% event handlers (%2%):\n") % GetStateName(bDefault) % map.size());
      {
         CLogIndent logIndent2;
         for(EventMapCIt cit = map.begin() ; map.end() != cit ; ++cit) {
            LogDebug(boost::format("%1% (%2%)\n") % cit->first->GetId() % cit->first->GetDataType());
         }
      }
   }

   /** Trace all event type handlers registered for the default or current state.
    **/
   void CStateMachine::TraceTypeHandlers(
      const bool bDefault //< When true trace handlers belonging to the default state; when false trace handlers belonging to the current state.
      ) const
   {
      CLogIndent logIndent1;
      const EventTypeMap& map = EventTypeGetMap(bDefault);
      LogDebug(boost::format("%1% event type handlers (%2%):\n") % GetStateName(bDefault) % map.size());
      {
         CLogIndent logIndent2;
         for(EventTypeMapCIt cit = map.begin() ; map.end() != cit ; ++cit) {
            LogDebug(boost::format("%1%\n") % cit->first);
         }
      }
   }

   /** Get the name of the default or current state.
    **
    ** The function handles state machines without a default state.
    ** The function handles state machines that have finished (no current state).
    **/
   std::string CStateMachine::GetStateName(
      const bool bDefault //< When true get the name of the default state; when false get the name of the current state.
      ) const
   {
      if(bDefault) {
         if(NULL == m_pDefaultState) {
            return "no default state";
         }
         return m_pDefaultState->GetName();
      }
      if(NULL == m_pState) {
         return "no current state";
      }
      return m_pState->GetName();
   }
}

