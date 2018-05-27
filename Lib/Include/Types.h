/** @file
 ** @brief Type declarations.
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
#ifndef __ILULibStateMachine_Types__H__
#define __ILULibStateMachine_Types__H__

#if __cplusplus < 201300
   /** C++14 not available
    **/
#  include "boost/bind.hpp"
#  include "boost/enable_shared_from_this.hpp"
#  include "boost/function.hpp"
#  include "boost/shared_ptr.hpp"
#  include "boost/tuple/tuple.hpp"
#  include "boost/weak_ptr.hpp"
/** No C++14 --> use boost 
 **/
#  define TYPESEL boost
/** Make using first bind placeholder transparant for C++14 or boost 
 **/
#  define TYPESEL_PLACEHOLDERS_1 _1
/** Make using second bind placeholder transparant for C++14 or boost 
 **/
#  define TYPESEL_PLACEHOLDERS_2 _2 
#else
   /** C++14 available
    **/
#  include <functional>
#  include <memory>
#  include <tuple>
/** No C++14 --> use it 
 **/
#  define TYPESEL std                                  
/** Make using first bind placeholder transparant for C++14 or boost 
 **/
#  define TYPESEL_PLACEHOLDERS_1 std::placeholders::_1
/** Make using second bind placeholder transparant for C++14 or boost
 **/
#  define TYPESEL_PLACEHOLDERS_2 std::placeholders::_2
#endif

#endif //__ILULibStateMachine_Types__H__

