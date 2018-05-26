/** @file
 ** @brief The internal logging functions definition.
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
#include "Internal/LoggingInternal.h"
#include "Internal/LoggingSerial.h"

namespace ILULibStateMachine {
   namespace {
     void LogNone(const std::string&)
      {
      }
   };

   namespace Internal {
      /** Get/set the registered debug loggings callback function.
       **
       ** When CFLog indicates it has an embedded funtion, the registered function
       ** is updated.
       ** In any case the registered function is returned.
       **/
      FLog RegisterLogDebug(
         CFLog log //< Wraps an embedded logging callback function.
         )
      {
         static FLog s_FLog(LogNone);
         if(log.IsSet()) {
            s_FLog = log.Get();
         }
         return s_FLog;
      }

      /** Get/set the registered info loggings callback function.
       **
       ** When CFLog indicates it has an embedded funtion, the registered function
       ** is updated.
       ** In any case the registered function is returned.
       **/
      FLog RegisterLogInfo(
         CFLog log //< Wraps an embedded logging callback function.
         )
      {
         static FLog s_FLog(SerialLogInfo);
         if(log.IsSet()) {
            s_FLog = log.Get();
         }
         return s_FLog;
      }

      /** Get/set the registered notice loggings callback function.
       **
       ** When CFLog indicates it has an embedded funtion, the registered function
       ** is updated.
       ** In any case the registered function is returned.
       **/
      FLog RegisterLogNotice(
         CFLog log //< Wraps an embedded logging callback function.
         )
      {
         static FLog s_FLog(SerialLogNotice);
         if(log.IsSet()) {
            s_FLog = log.Get();
         }
         return s_FLog;
      }

      /** Get/set the registered warninging loggings callback function.
       **
       ** When CFLog indicates it has an embedded funtion, the registered function
       ** is updated.
       ** In any case the registered function is returned.
       **/
      FLog RegisterLogWarning(
         CFLog log //< Wraps an embedded logging callback function.
         )
      {
         static FLog s_FLog(SerialLogWarning);
         if(log.IsSet()) {
            s_FLog = log.Get();
         }
         return s_FLog;
      }

      /** Get/set the registered error loggings callback function.
       **
       ** When CFLog indicates it has an embedded funtion, the registered function
       ** is updated.
       ** In any case the registered function is returned.
       **/
      FLog RegisterLogErr(
         CFLog log //< Wraps an embedded logging callback function.
         )
      {
         static FLog s_FLog(SerialLogErr);
         if(log.IsSet()) {
            s_FLog = log.Get();
         }
         return s_FLog;
      }

      /** Get/set the registered increase indentation function.
       **
       ** When CFIndent indicates it has an embedded funtion, the registered function
       ** is updated.
       ** In any case the registered function is returned.
       **/
      FIndent RegisterLogIndent(
         CFIndent indent //< Wraps an embedded increase indentation logging callback function.
         )
      {
         static FIndent s_FIndent(SerialLogIndent);
         if(indent.IsSet()) {
            s_FIndent = indent.Get();
         }
         return s_FIndent;
      }

      /** Get/set the registered decrease indentation function.
       **
       ** When CFIndent indicates it has an embedded funtion, the registered function
       ** is updated.
       ** In any case the registered function is returned.
       **/
      FUnindent RegisterLogUnindent(
         CFUnindent unindent //< Wraps an embedded increase indentation logging callback function.
         )
      {
         static FUnindent s_FUnindent(SerialLogUnindent);
         if(unindent.IsSet()) {
            s_FUnindent = unindent.Get();
         }
         return s_FUnindent;
      }
   };
};

