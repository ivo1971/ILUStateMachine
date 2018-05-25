/** @file
 ** @brief The CLogIndent declaration.
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
#ifndef __ILULibStateMachine_CLogIndent_H__
#define __ILULibStateMachine_CLogIndent_H__

namespace ILULibStateMachine {
   /** @brief Help class to indent/unindent logging in the presence of exceptions and early returns.
    **
    ** When an instance is constructed: indentation is increased 1 level.
    ** When an instance is destructed: indentation is decreased 1 level.
    **/
   class CLogIndent {
      public:
         CLogIndent(void);
         ~CLogIndent(void);
   };
};

#endif //__ILULibStateMachine_CLogIndent_H__

