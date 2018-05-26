/** @file
 ** @brief The logging functions declaration.
 **
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
 ** The logging functions can be used to create a logging of different levels
 ** (debug, info, news, warninging and error).
 ** They can also be used to indent the logging.
 **
 ** The default behaviour of the logging functions is to use console output
 ** (stdout and stderr).
 ** LogDebug is disabled by default, it can be enabled by calling 'EnableSerialLogDebug'.
 ** However by registering other logging functions this behaviour can be 
 ** changed as required by the application using this library.
 **
 ** Log levels according to http://man7.org/linux/man-pages/man2/syslog.2.html
 **
 **/
#ifndef __ILULibStateMachine_Logging_H__
#define __ILULibStateMachine_Logging_H__

#include "string"

#include "boost/format.hpp"
#include "boost/function.hpp"

#include "CLogIndent.h"

namespace ILULibStateMachine {
   typedef boost::function<void(const std::string& log)> FLog;      ///< Prototype of a logging function that can be registered.
   typedef boost::function<void(void)>                   FIndent;   ///< Prototype of a function that increases the logging indentation that can be registered.
   typedef boost::function<void(void)>                   FUnindent; ///< Prototype of a function that decreases the logging indentation that can be registered.

   //logging administration functions
   void RegisterLogDebug     (FLog log);
   void RegisterLogInfo      (FLog log);
   void RegisterLogNotice    (FLog log);
   void RegisterLogWarning   (FLog log);
   void RegisterLogErr       (FLog log);
   void RegisterLogIndent    (FIndent indent);
   void RegisterLogUnindent  (FUnindent unindent);
   void UnRegisterLogDebug   (void);
   void UnRegisterLogInfo    (void);
   void UnRegisterLogNotice  (void);
   void UnRegisterLogWarning (void);
   void UnRegisterLogErr     (void);
   void UnRegisterLogIndent  (void);
   void UnRegisterLogUnindent(void);
   void EnableSerialLogDebug (void);
   
   //logging functions
   void LogDebug             (const boost::format& log);
   void LogInfo              (const boost::format& log);
   void LogNotice            (const boost::format& log);
   void LogWarning           (const boost::format& log);
   void LogErr               (const boost::format& log);
   void LogIndent            (void);
   void LogUnindent          (void);
};

#endif //__ILULibStateMachine_Logging_H__

