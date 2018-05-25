/** @file
 ** @brief The CEventBase declaration.
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
#include "Include/CEventBase.h"

namespace ILULibStateMachine {
   /** Protected constructor.
    **/
   CEventBase::CEventBase(
      const std::string& strId,    //< Textual description of the event, used in logging only.
      const char* const szDataType //< Textual description of the data class belonging to this event.
      )
      : m_strId(strId)
      , m_strDataType(szDataType)
   {
   }

   /** Destructor.
    **
    ** Required to make this a virtual class.
    **/
   CEventBase::~CEventBase(void)
   {
   }

   /**
    ** This class is the event key in the map, thus it has to be strictly ordered
    ** (operator<). This is accomplished by starting the comparison with the type id
    ** and using them as the primary key. Only when these match the 'CompareTypeIdIdentical'
    ** function is called to compare 2 instances of the same type.
    **/
   bool CEventBase::operator<(
      const CEventBase& ref //< Instance to be compared to this.
      ) const
   {
      if(typeid(*this) != typeid(ref)) {
         return typeid(*this).name() < typeid(ref).name();
      }
      return CompareTypeIdIdentical(ref);
   }

   /** Get the textual description of the event.
    **
    ** @return the textual description of the event.
    **/
   const std::string& CEventBase::GetId(void) const
   {
      return m_strId;
   }

   /** Get the textual description of the data class belonging to this event.
    **
    ** @return the textual description of the data class belonging to this event.
    **/
   const std::string& CEventBase::GetDataType(void) const
   {
      return m_strDataType;
   }
};

