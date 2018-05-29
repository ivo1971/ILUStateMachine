/** @file
 ** @brief The TEventEvtId template class declaration.
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
#ifndef __ILULibStateMachine_TEventEvtIdImpl_H__
#define __ILULibStateMachine_TEventEvtIdImpl_H__

#include <cxxabi.h>
#include <iomanip>

namespace ILULibStateMachine {
   /** Constructor.
    **/
   template <class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>
   TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>::TEventEvtId(
      const std::type_info& typeinfo,   //< Typeinfo describing the data type belonging to this event, logging only.
      const EvtId           evtId       //< Event ID.
      ) 
      : CEventBase(IdInit(evtId), IdTypeInit(), Demangle(typeinfo))
      , m_EvtId(evtId)
      , m_EvtSubId1()
      , m_EvtSubId2()
      , m_EvtSubId3()
   {
   }

   /** Constructor.
    **/
   template <class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>
   TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>::TEventEvtId(
      const std::type_info& typeinfo,   //< Typeinfo describing the data type belonging to this event, logging only.
      const EvtId           evtId,      //< Event ID.
      const EvtSubId1       evtSubId1   //< First event sub-ID.
      ) 
      : CEventBase(IdInit(evtId, evtSubId1), IdTypeInit(), Demangle(typeinfo))
      , m_EvtId(evtId)
      , m_EvtSubId1(evtSubId1)
      , m_EvtSubId2()
      , m_EvtSubId3()
   {
   }

   /** Constructor.
    **/
   template <class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>
   TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>::TEventEvtId(
      const std::type_info& typeinfo,   //< Typeinfo describing the data type belonging to this event, logging only.
      const EvtId           evtId,      //< Event ID.
      const EvtSubId1       evtSubId1,  //< First event sub-ID.
      const EvtSubId2       evtSubId2   //< Second event sub-ID.
      ) 
      : CEventBase(IdInit(evtId, evtSubId1, evtSubId2), IdTypeInit(), Demangle(typeinfo))
      , m_EvtId(evtId)
      , m_EvtSubId1(evtSubId1)
      , m_EvtSubId2(evtSubId2)
      , m_EvtSubId3()
   {
   }

   /** Constructor.
    **/
   template <class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>
   TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>::TEventEvtId(
      const std::type_info& typeinfo,   //< Typeinfo describing the data type belonging to this event, logging only.
      const EvtId           evtId,      //< Event ID.
      const EvtSubId1       evtSubId1,  //< First event sub-ID.
      const EvtSubId2       evtSubId2,  //< Second event sub-ID.
      const EvtSubId3       evtSubId3   //< Third event sub-ID.   
      ) 
      : CEventBase(IdInit(evtId, evtSubId1, evtSubId2, evtSubId3), IdTypeInit(), Demangle(typeinfo))
      , m_EvtId(evtId)
      , m_EvtSubId1(evtSubId1)
      , m_EvtSubId2(evtSubId2)
      , m_EvtSubId3(evtSubId3)
   {
   }

   /** Compare function called by the base class once it has determined that the reference instance has
    ** the same type as this.
    **/
   template <class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>
   bool TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>::CompareTypeIdIdentical(
      const CEventBase& ref //< Reference against which this will be compared. Pre-condition: type is identical to this (or an exception will be thrown).
      ) const
   {
      const TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>& refEvtId = dynamic_cast<const TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>&>(ref);
      if(this->m_EvtId != refEvtId.m_EvtId) {
         return this->m_EvtId < refEvtId.m_EvtId;
      }
      if(this->m_EvtSubId1 != refEvtId.m_EvtSubId1) {
         return this->m_EvtSubId1 < refEvtId.m_EvtSubId1;
      }
      if(this->m_EvtSubId2 != refEvtId.m_EvtSubId2) {
         return this->m_EvtSubId2 < refEvtId.m_EvtSubId2;
      }
      return this->m_EvtSubId3 < refEvtId.m_EvtSubId3;
   }

   /** Demangle the typename when the compiler supports it.
    **/
   template <class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>
   std::string TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>::Demangle(const std::type_info& typeinfo)
   {
#ifdef ABI_DEMANGLE
      int status = 0;
      char* const szDemangled = abi::__cxa_demangle(typeinfo.name(), 0, 0, &status);
      const std::string strDemangled(NULL != szDemangled ? szDemangled : typeinfo.name());
      free(szDemangled);
      return strDemangled;
#else
      return typeinfo.name();
#endif      
   }

   /** Generate an identifier string that describes this event.
    **/
   template <class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>
   std::string TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>::IdInit(
      const EvtId       evtId,      //< Event ID.
      const EvtSubId1   evtSubId1,  //< First event sub-ID.
      const EvtSubId2   evtSubId2,  //< Second event sub-ID.
      const EvtSubId3   evtSubId3   //< Third event sub-ID.   
      )
   {
      std::stringstream ss;
      ss << std::uppercase << std::hex;
      ss << "0x" << std::setfill('0') << std::setw(4) << evtId;
      if(typeid(EvtSubId1) != typeid(EEvtSubNotSet)) {
         ss << "-0x" << std::setfill('0') << std::setw(4) << evtSubId1;
         if(typeid(EvtSubId2) != typeid(EEvtSubNotSet)) {
            ss << "-0x" << std::setfill('0') << std::setw(4) << evtSubId2;
            if(typeid(EvtSubId3) != typeid(EEvtSubNotSet)) {
               ss << "-0x" << std::setfill('0') << std::setw(4) << evtSubId3;
            }
         }
      }
      return ss.str();
   }

   /** Generate an identifier string that describes this event ID.
    **/
   template <class EvtId, class EvtSubId1, class EvtSubId2, class EvtSubId3>
   std::string TEventEvtId<EvtId, EvtSubId1, EvtSubId2, EvtSubId3>::IdTypeInit(void)
   {
      std::stringstream ss;
      ss << Demangle(typeid(EvtId));
      if(typeid(EvtSubId1) != typeid(EEvtSubNotSet)) {
         ss << "-" << Demangle(typeid(EvtSubId1));
         if(typeid(EvtSubId2) != typeid(EEvtSubNotSet)) {
            ss << "-" << Demangle(typeid(EvtSubId2));
            if(typeid(EvtSubId3) != typeid(EEvtSubNotSet)) {
               ss << "-" << Demangle(typeid(EvtSubId3));
            }
         }
      }
      return ss.str();
   }
};

#endif //__ILULibStateMachine_TEventEvtIdImpl_H__

