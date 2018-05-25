/** @file
 ** @brief The internal serial logging functions declaration.
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
 ** These functions are initially registered in the logging
 ** interface to provide logging to the console (stdout and
 ** stderr). 
 ** The logging interface allows registering other
 ** application specific functions in case these defaults
 ** are not sufficient.
 **/
#ifndef __ILULibStateMachine_LoggingSerial_H__
#define __ILULibStateMachine_LoggingSerial_H__

#include <string>

namespace ILULibStateMachine {
   namespace Internal {
      std::string HandleIndent     (bool bGet = true, bool bIncrement = true);
      void        SerialLogDebug   (const std::string& strLog);
      void        SerialLogInfo    (const std::string& strLog);
      void        SerialLogNotice  (const std::string& strLog);
      void        SerialLogWarning (const std::string& strLog);
      void        SerialLogErr     (const std::string& strLog);
      void        SerialLogIndent  (void);
      void        SerialLogUnindent(void);
   };
};

#endif //__ILULibStateMachine_LoggingSerial_H__

