/** @file
 ** @brief The internal logging functions declaration.
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
 ** These functions are called by the logging functions.
 ** The extra layer is used to encapsulate the way the registered
 ** functions are stored.
 **/
#ifndef __ILULibStateMachine_LoggingInternal_H__
#define __ILULibStateMachine_LoggingInternal_H__

#include "Internal/TLog.h"

namespace ILULibStateMachine {
   namespace Internal {
      FLog      RegisterLogDebug   (CFLog      log      = CFLog()     );
      FLog      RegisterLogInfo    (CFLog      log      = CFLog()     );
      FLog      RegisterLogNotice  (CFLog      log      = CFLog()     );
      FLog      RegisterLogWarning (CFLog      log      = CFLog()     );
      FLog      RegisterLogErr     (CFLog      log      = CFLog()     );
      FIndent   RegisterLogIndent  (CFIndent   indent   = CFIndent()  );
      FUnindent RegisterLogUnindent(CFUnindent unindent = CFUnindent());
   };
};

#endif //__ILULibStateMachine_LoggingInternal_H__

