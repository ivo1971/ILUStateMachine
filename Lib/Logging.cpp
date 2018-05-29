/** @file
 ** @brief The logging functions definition.
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
#include <stdarg.h>
#include <stdio.h>

#include "Include/Logging.h"
#include "Internal/LoggingInternal.h"
#include "Internal/LoggingSerial.h"
#include "Internal/TLog.h"

#define MSG_BUF_SIZE     (256) ///< set the buffer size for loggings (larger ones will be truncated)

/** @brief There are 5 log functions with the same body except for 1 parameter.
 ** This macro avoids copying those bodies.
 **
 ** TODO: investigate how this can be accomplished with a template.
 **/
#define LOGXXX(REG_FUNC) \
  FLog     flog               (REG_FUNC()); \
  char     szMsg[MSG_BUF_SIZE]; \
  va_list  ap                 ; \
  va_start(ap, szFormat); \
  vsnprintf(szMsg, sizeof(szMsg), szFormat, ap); \
  va_end(ap); \
  flog(szMsg);

namespace ILULibStateMachine {
   //use the libraries internal functions (not a part of the interface)
   using namespace Internal;

   /** Function to be called to register a debug loggings callback function.
    **/
   void RegisterLogDebug(
      FLog log //< Function to be called for debug loggings.
      )
   {
      RegisterLogDebug(CFLog(log));
   }
   
   /** Function to be called to register an info loggings callback function.
    **/
   void RegisterLogInfo(
      FLog log //< Function to be called for info loggings.
      )
   {
      RegisterLogInfo(CFLog(log));
   }
   
   /** Function to be called to register a notice loggings callback function.
    **/
   void RegisterLogNotice(
      FLog log //< Function to be called for notice loggings.
      )
   {
      RegisterLogNotice(CFLog(log));
   }
   
   /** Function to be called to register a warninging loggings callback function.
    **/
   void RegisterLogWarning(
      FLog log //< Function to be called for warninging loggings.
      )
   {
      RegisterLogWarning(CFLog(log));
   }
   
   /** Function to be called to register an error loggings callback function.
    **/
   void RegisterLogErr(
      FLog log //< Function to be called for error loggings.
      )
   {
      RegisterLogErr(CFLog(log));
   }
   
   /** Register a function to be called to increase logging indentation.
    **/
   void RegisterLogIndent(
      FIndent indent //< Function to be called to increase logging indentation.
      )
   {
      RegisterLogIndent(CFIndent(indent));
   }

   /** Register a function to be called to decrease logging indentation.
    **/
   void RegisterLogUnindent(
      FUnindent unindent //< Function to be called to decrease logging indentation.
      )
   {
      RegisterLogUnindent(CFUnindent(unindent));
   }

   /** Unregister the debug logging function currently
    ** registered.
    **
    ** The library will start using the default console logging again.
    **/
   void UnRegisterLogDebug(void)
   {
      RegisterLogDebug(CFLog(SerialLogDebug));
   }
   
   /** Unregister the info logging function currently
    ** registered.
    **
    ** The library will start using the default console logging again.
    **/
   void UnRegisterLogInfo(void)
   {
      RegisterLogInfo(CFLog(SerialLogInfo));
   }
   
   /** Unregister the info logging function currently
    ** registered.
    **
    ** The library will start using the default console logging again.
    **/
   void UnRegisterLogNotice(void)
   {
      RegisterLogNotice(CFLog(SerialLogNotice));
   }
   
   /** Unregister the warninging logging function currently
    ** registered.
    **
    ** The library will start using the default console logging again.
    **/
   void UnRegisterLogWarning(void)
   {
      RegisterLogWarning(CFLog(SerialLogWarning));
   }
   
   /** Unregister the error logging function currently
    ** registered.
    **
    ** The library will start using the default console logging again.
    **/
   void UnRegisterLogErr(void)
   {
      RegisterLogErr(CFLog(SerialLogErr));
   }

   /** Unregister the indentation increase function.
    **/
   void UnRegisterLogIndent(void)
   {
      RegisterLogIndent(CFIndent(SerialLogIndent));
   }
   
   /** Unregister the indentation decrease function.
    **/
   void UnRegisterLogUnindent(void)
   {
      RegisterLogUnindent(CFUnindent(SerialLogUnindent));
   }

   /** Register the standard serial debug logging function.
    **/
   void EnableSerialLogDebug (void)
   {
      RegisterLogDebug(CFLog(SerialLogDebug));
   }

   /** Generate a debug logging.
    **/
   void LogDebug(
                 const char* const szFormat, //< Format describing the message to be logged.
                 ...                         //< Format arguments
      )
   {
      LOGXXX(RegisterLogDebug);
   }

   /** Generate a info logging.
    **/
   void LogInfo(
                const char* const szFormat, //< Format describing the message to be logged.
                ...                         //< Format arguments
      )
   {
      LOGXXX(RegisterLogInfo);
   }

   /** Generate a notice logging.
    **/
   void LogNotice(
                  const char* const szFormat, //< Format describing the message to be logged.
                  ...                         //< Format arguments
      )
   {
      LOGXXX(RegisterLogNotice);
   }

   /** Generate a warninging logging.
    **/
   void LogWarning(
                   const char* const szFormat, //< Format describing the message to be logged.
                   ...                         //< Format arguments
                   )
   {
      LOGXXX(RegisterLogWarning);
   }

   /** Generate an error logging.
    **/
   void LogErr(
               const char* const szFormat, //< Format describing the message to be logged.
               ...                         //< Format arguments
      )
   {
      LOGXXX(RegisterLogErr);
   }

   /** Request to increase the logging indentation.
    **/
   void LogIndent(void)
   {
      FIndent findent = RegisterLogIndent();
      findent();
   }

   /** Request to decrease the logging indentation.
    **/
   void LogUnindent(void)
   {
      FIndent findent = RegisterLogUnindent();
      findent();
   }
};

