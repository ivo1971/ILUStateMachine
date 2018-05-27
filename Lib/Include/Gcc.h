/** @file
 ** @brief Extra gcc definitions.
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
#ifndef __ILULibStateMachine_Gcc_H__
#define __ILULibStateMachine_Gcc_H__

#if __GNUC__ >= 3
# ifndef __printf
#  define __printf(x)  __attribute__ ((format (printf, x+1, x+2))) ///< Make using the printf format check easier
# endif
#else
#  define __printf(x)                                              ///< Compiler does not support printf
#endif

#endif //#ifndef __ILULibStateMachine_Gcc_H__

