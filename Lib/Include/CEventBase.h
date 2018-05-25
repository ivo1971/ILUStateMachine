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
#ifndef __ILULibStateMachine_CEventBase_H__
#define __ILULibStateMachine_CEventBase_H__

#include "boost/shared_ptr.hpp"

namespace ILULibStateMachine {
   /** @brief Virtual base class used by the state machine engine to store event handlers in a map.
    ** 
    ** This class is the event key in the map, thus it has to be strictly ordered
    ** (operator<). This is accomplished by starting the comparison with the type id
    ** and using them as the primary key. Only when these match the 'CompareTypeIdIdentical'
    ** function is called to compare 2 instances of the same type.
    **/
   class CEventBase {
      public:
         virtual                    ~CEventBase(void);

      public:
         bool                       operator<(const CEventBase& ref) const;
         virtual const std::string& GetId(void) const;
         virtual const std::string& GetDataType(void) const;

      protected:
                                    CEventBase(const std::string& strId, const char* const szDataType);

      private:
                                    CEventBase(const CEventBase& ref);
         CEventBase&                operator=(const CEventBase& ref);
         virtual bool               CompareTypeIdIdentical(const CEventBase& ref) const = 0;

      private:
         const std::string          m_strId;
         const std::string          m_strDataType;

   };

   typedef boost::shared_ptr<CEventBase> SPEventBase; ///< shared pointer around the CEventBase class.
};

#endif //__ILULibStateMachine_CEventBase_H__

