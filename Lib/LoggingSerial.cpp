/** @file
 ** @brief The internal serial logging functions definition.
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
#include <iostream>

#include "Internal/LoggingSerial.h"

namespace ILULibStateMachine {
   namespace Internal {
      //source: https://en.wikipedia.org/wiki/ANSI_escape_code#graphics
      const std::string strColorReset  ("\033[0m"       ); ///< Constant string resetting stdio.
      const std::string strColorFgBlack("\033[30m"      ); ///< Constant string setting the stdio foreground color to black.
      const std::string strColorFgRed  ("\033[31m"      ); ///< Constant string setting the stdio foreground color to red.
      const std::string strColorFgGreen("\033[32m"      ); ///< Constant string setting the stdio foreground color to green.
      const std::string strColorFgBlue ("\033[34m"      ); ///< Constant string setting the stdio foreground color to blue.
      const std::string strColorFgWhite("\033[37m"      ); ///< Constant string setting the stdio foreground color to white.
      const std::string strColorFgGray ("\033[38;5;242m"); ///< Constant string setting the stdio foreground color to gray (any value in [232,255] is a tone of gray).

      /** Get/set function taking care of indentation.
       **
       ** @return a string containing the current indentation.
       **/
      std::string HandleIndent(
         bool bGetOnly,  //< When true the indentation is not changed, the function only returns a string containing the current indentation. When false the indentation is incremented or decremented.
         bool bIncrement //< When bGetOnly is false: increment or decrement the indentation according to this parameter.
         )
      {
         static       std::string strIndent;
         static const std::string strIncrement("   ");
         static const size_t      incrementLength(strIncrement.length());
         if(bGetOnly) {
            return strIndent;
         }
         if(bIncrement) {
            strIndent += strIncrement;
            return strIndent;
         }
         const size_t indentLength = strIndent.length();
         if(incrementLength <= indentLength)  {
            strIndent = strIndent.substr(0, indentLength - incrementLength);
         }
         return strIndent;
      }

      /** Log the string to the console in the defined debug color.
       **/
      void SerialLogDebug(
         const std::string& strLog //< String that will be logged.
         )
      {
         std::cout << strColorFgGray  << HandleIndent() << strLog << strColorReset;
      }
      
      /** Log the string to the console in the defined info color.
       **/
      void SerialLogInfo(
         const std::string& strLog //< String that will be logged.
         )
      {
         std::cout << strColorReset << HandleIndent() << strLog;
      }
      
      /** Log the string to the console in the defined notice color.
       **/
      void SerialLogNotice(
         const std::string& strLog //< String that will be logged.
         )
      {
         std::cout << strColorReset << HandleIndent() << strLog;
      }
      
      /** Log the string to the console in the defined warninging color.
       **/
      void SerialLogWarning(
         const std::string& strLog //< String that will be logged.
         )
      {
         std::cout << strColorFgBlue  << HandleIndent() << strLog << strColorReset;
      }
      
      /** Log the string to the console in the defined error color.
       **/
      void SerialLogErr(
         const std::string& strLog //< String that will be logged.
         )
      {
         std::cerr << strColorFgRed   << HandleIndent() << strLog << strColorReset;
      }

      /** Increment the logging indentation.
       **/
      void SerialLogIndent(void)
      {
         HandleIndent(false, true);
      }
      
      /** Decrement the logging indentation.
       **/
      void SerialLogUnindent(void)
      {
         HandleIndent(false, false);
      }
   };
};

