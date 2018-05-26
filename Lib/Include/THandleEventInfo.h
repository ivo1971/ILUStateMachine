/** @file
 ** @brief The THandleEventInfo template class defintions.
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
#ifndef __ILULibStateMachine_THandleEventInfo_H__
#define __ILULibStateMachine_THandleEventInfo_H__

#include "map"
#include "sstream"
#include "vector"

#include "boost/format.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/tuple/tuple.hpp"

#include "CCreateState.h"
#include "CHandleEventInfoBase.h"

namespace ILULibStateMachine {
   /** @brief Template class that allows storing and calling of event handlers for one specific event data
    ** type (TEventData).
    **
    ** The implementation of the template functions is put in a seperate header file (included by this
    ** header) to keep the class declaration clean.
    **/
   template <class TEventData> class THandleEventInfo : public CHandleEventInfoBase {
      public:
         typedef bool                                              FGuard(const TEventData* const pEventData);                     ///< Prototype of an event guard: depending on its return value the corresponding event handler is called.
	 typedef void                                              FHandler(const TEventData* const pEventData);                   ///< Prototype of an event handler: it is provided with the event data.
	 typedef boost::function<FGuard>                           BFGuard;                                                        ///< FGuard wrapped in a boost function, so the event guard can be a class method bound to a class instance.
         typedef boost::function<FHandler>                         BFHandler;                                                      ///< FHandler wrapped in a boost function, so the event handler can be a class method bound to a class instance.
         typedef boost::tuple<BFGuard, BFHandler, CCreateState>    GuardHandlerCreateState;                                        ///< Type that fully defines one event action: guard (optional), handler, state transition. This maps 1-on-1 to 1 arrow in a state machine schema.
         typedef std::vector<GuardHandlerCreateState>              GuardHandlerCreateStates;                                       ///< Container of event action descriptors.
         typedef typename GuardHandlerCreateStates::iterator       GuardHandlerCreateStatesIt;                                     ///< Iterator on the container of event action descriptors.
         typedef typename GuardHandlerCreateStates::const_iterator GuardHandlerCreateStatesCIt;                                    ///< Constant iterator on the container of event action descriptors.
        
      public:
                                  THandleEventInfo   (void);
                                  THandleEventInfo   (               BFHandler     handler, CCreateState createState);
                                  THandleEventInfo   (BFGuard guard, BFHandler     handler, CCreateState createState);

      public:
         void                     SetUnguardedHandler(               BFHandler handler, CCreateState createState);
         void                     AddGuardedHandler  (BFGuard guard, BFHandler handler, CCreateState createState);
         HandleResult             Handle             (const bool bDefaultState, const TEventData* const pEventData);
         
      private:
         HandleResult             CallHandler        (boost::format& fmt, boost::function<void(const TEventData* const pEventData)> handler, CCreateState createState, const TEventData* const pEventData, const char* const szType);

      private:

      protected:
         bool                     m_bUnguardedHandlerSet; ///< Indicates whether the unguared handler has been set or not.
         GuardHandlerCreateState  m_UnguardedHandler;     ///< Stores the unguarded event handler ([0,] per event).
         GuardHandlerCreateStates m_GuardHandlers;        ///< Stores a container of guarded event handlers. The guard conditions should be mutually exclusive (otherwise there is a bug in the state machine design, not in the code), but this is not checked in any way.
   };
};

//include the class template function definitions.
#include "THandleEventInfoImpl.h"

#endif //__ILULibStateMachine_THandleEventInfo_H__

