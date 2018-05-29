/** @file
 ** @brief The TEventEvtId template class defintions.
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
#ifndef __ILULibStateMachine_TEventEvtId_H__
#define __ILULibStateMachine_TEventEvtId_H__

#include "map"
#include "sstream"
#include "vector"

#include "CCreateState.h"
#include "CEventBase.h"
#include "EEvtSubNotSet.h"

namespace ILULibStateMachine {
   /** @brief This template class uniquely identifyies an event.
    **
    ** As this is a generic state machine library, no assumptions about the events have
    ** been made other than that they can be identified by at least an event ID (EvtId)
    ** and optionally up to 3 sub event ID's.
    **
    ** Because the sub event ID's are optional template parameters, this also allows
    ** to define an event class for events only having an event ID and no sub ID's.
    **
    ** It allows comparing an event occurence against registered events.
    **
    ** This class does not define anything about the data that comes with the event.
    ** It does have an szDataType string to allow logging a description of the data type
    ** going with this event. This is merely logging and servers no other comparison
    ** or identification purposes.
    **
    ** An event needs a unique template instance, thus having a unique set of template
    ** parameters.
    **/
   template <class EvtId, class EvtSubId1 = EEvtSubNotSet, class EvtSubId2 = EEvtSubNotSet, class EvtSubId3 = EEvtSubNotSet> class TEventEvtId : public CEventBase {
      public:
                                    TEventEvtId(const char* const szDataType, const EvtId evtId); 
                                    TEventEvtId(const char* const szDataType, const EvtId evtId, const EvtSubId1 evtSubId1);
                                    TEventEvtId(const char* const szDataType, const EvtId evtId, const EvtSubId1 evtSubId1, const EvtSubId2 evtSubId2); 
                                    TEventEvtId(const char* const szDataType, const EvtId evtId, const EvtSubId1 evtSubId1, const EvtSubId2 evtSubId2, const EvtSubId3 evtSubId3); 

      public:
         static std::string         IdTypeInit(void);
      
      private:
                                    TEventEvtId(const TEventEvtId& ref); 
         TEventEvtId&               operator=(const TEventEvtId& ref); //< not implemented due to const members
         virtual bool               CompareTypeIdIdentical(const CEventBase& ref) const;

      private:
         static std::string         IdInit(const EvtId evtId, const EvtSubId1 evtSubId1 = EvtSubId1(), const EvtSubId2 evtSubId2 = EvtSubId2(), const EvtSubId3 evtSubId3 = EvtSubId3());

      private:
         const EvtId                m_EvtId;
         const EvtSubId1            m_EvtSubId1;
         const EvtSubId2            m_EvtSubId2;
         const EvtSubId3            m_EvtSubId3;
   };
};

//include the class template function definitions.
#include "TEventEvtIdImpl.h"

#endif //__ILULibStateMachine_TEventEvtId_H__

