/** @file
 ** @brief The internal TFLog template  declaration.
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
#ifndef __ILULibStateMachine_TLog_H__
#define __ILULibStateMachine_TLog_H__

#include <stdexcept>

#include "Logging.h"

namespace ILULibStateMachine {
   namespace Internal {
      /** @brief Template class to wrap a logging, increase indentation and decrease indentation function.
       **
       ** The class allows detection whether a function has been set or not.
       **/
      template <class FUNC>
      class TFLog {
         public:
            /** Constructor without embedding a function.
             **/
            TFLog(void)
               : m_bSet(false)
               , m_Func()
            {
            }

            /** Constructor with embedding a function.
             **/
            TFLog(FUNC func)
               : m_bSet(true)
               , m_Func(func)
            {
            }
            
            /** Copy constructor
             **/
            TFLog(const TFLog& ref)
               : m_bSet(ref.m_bSet)
               , m_Func(ref.m_Func)
            {
            }

            /** Copy operator.
             **/
            TFLog& operator=(const TFLog& ref)
            {
               if(this == &ref) return *this;
               m_bSet = ref.m_bSet;
               m_Func = ref.m_Func;
               return *this;
            }

         public:
            /** Check wether a function has been embedded or not.
             **
             ** @return true when a function is embedded; false otherwise.
             **/
            bool IsSet(void) const
            {
               return m_bSet;
            }
            
            /** Get the embedded function.
             **
             ** @return the embedded function
             **/
            FUNC Get(void) const
            {
               if(!IsSet()) {
                  throw std::runtime_error("TFLog: no embedded function set");
               }
               return m_Func;
            }
            
         private:
            bool   m_bSet;
            FUNC   m_Func;
      };

      typedef TFLog<FLog>      CFLog;      ///< Define a warapper class for logging functions.
      typedef TFLog<FIndent>   CFIndent;   ///< Define a wrapper class for increase indentation functions.
      typedef TFLog<FUnindent> CFUnindent; ///< Define a wrapper class for decrease indentation functions.
   };
};

#endif //__ILULibStateMachine_TLog_H__

