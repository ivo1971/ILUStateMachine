##
## ILUStateMachine is a library implementing a generic state machine engine.
## Copyright (C) 2018 Ivo Luyckx
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program; if not, write to the Free Software Foundation, Inc.,
## 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
##
##initialisation
AC_PREREQ([2.60])
AC_INIT([ILUStateMachine], [1.0.0], [ivo@nomail.com], [https://github.com/ivo1971/ILUStateMachine])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

##utils to be available (compilers, linkers ...)
AM_PROG_AR
AC_PROG_CC
AC_PROG_CXX

##script internal variables
cpp_standard_used="default"
using_boost="no"
using_abi_demangle="no"

##required to build shared libraries,
##has to be after _PROG_
LT_INIT

##suggested when running autoreconf --install
AC_CONFIG_MACRO_DIRS([m4])

##generate a 'config.h' file containing configuration defines
AC_CONFIG_HEADERS([config.h])

##use short output while building
AM_SILENT_RULES([yes])

##set cppflags in a way they can be used in all makefiles
CXXFLAGS="-W -Wall -Wextra -Wpointer-arith -Wformat-security -Werror -Wswitch-default -Wshadow -ffor-scope -Woverloaded-virtual -Wcast-qual"

##set library flags in a way they can be used in all makefiles
EXTRA_LDFLAGS="-version-info 1:0:0"
AC_SUBST(EXTRA_LDFLAGS)

##store current flags so the can be temporarily changed for running a test
##and restoring them afterwards
saved_cflags="$CFLAGS"
saved_cxxflags="$CXXFLAGS"
saved_ldflags="$LDFLAGS"

##run the following tests with the C++ compiler
AC_LANG_PUSH([C++])

##check C++14
CXXFLAGS="-Werror -std=c++14"
AC_MSG_CHECKING([whether CXX supports -std=c++14])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
   [])],
   [AC_MSG_RESULT([yes]); saved_cxxflags="$saved_cxxflags -std=c++14";cpp_standard_used="C++14"],
   [AC_MSG_RESULT([no])])
CXXFLAGS="$saved_cxxflags"

##check for the availability of boost
##if no C++14
if test "x${cpp_standard_used}" = "xC++14"; then
   AC_MSG_NOTICE([boost not required, using C++14])
else
   CXXFLAGS=""
   if test "x${prefix}" != "xNONE"; then
      CXXFLAGS="${CXXFLAGS} -I${prefix}/include"
   fi
   AC_MSG_CHECKING([whether boost library is available])
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
       [[
          #include "boost/bind.hpp"
          #include "boost/enable_shared_from_this.hpp"
          #include "boost/function.hpp"
          #include "boost/shared_ptr.hpp"
          #include "boost/tuple/tuple.hpp"
          #include "boost/weak_ptr.hpp"
       ]])],
       AC_MSG_RESULT([yes]);saved_cxxflags="${saved_cxxflags} ${CXXFLAGS}";using_boost="yes",
       AC_MSG_ERROR([no])
       )
   CXXFLAGS="$saved_cxxflags"
   ##at this point either boost or C++14 is available
   ##otherwise the script has exited
fi

##check if compiler supports 'abi::__cxa_demangle' to beautify typeid output
AC_MSG_CHECKING([whether compiler supports 'abi::__cxa_demangle'])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
    [[
      #include <typeinfo>
      #include <cxxabi.h>
      
      void Demangle(void)
      {
            int status = 0;
            abi::__cxa_demangle(typeid(int).name(), 0, 0, &status);
      }
    ]])],
    AC_MSG_RESULT([yes]);saved_cxxflags="${saved_cxxflags} -DABI_DEMANGLE";using_abi_demangle="yes",
    AC_MSG_RESULT([no])
    )
CXXFLAGS="$saved_cxxflags"

##can optionally use doxygen to generate library documentation
##source: https://chris-miceli.blogspot.be/2011/01/integrating-doxygen-with-autotools.html
AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi
AM_CONDITIONAL([HAVE_DOXYGEN],
[test -n "$DOXYGEN"])AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([docs/Doxyfile])])

##makefiles to be generated
##(alphabetic order, Makefile.ac dictates the make order)
AC_OUTPUT([
   Makefile
   docs/Makefile
   Lib/Makefile
   Test/App/Makefile
   Test/Makefile
   Test/StateMachineChild/Makefile
   Test/StateMachineRoot/Makefile
   Demo/Makefile
   Demo/DefaultState/Makefile
   Demo/FirstStateMachine/Makefile
   Demo/FirstStateMachineWithData/Makefile
   Demo/GuardedHandlers/Makefile
   Demo/NoneStandardStateFlowInConstructor/Makefile
   Demo/NoneStandardStateFlowInHandler/Makefile
   ])

echo \
"----------------------------------------------------------------

${PACKAGE_NAME} Version ${PACKAGE_VERSION}

Current compiler options:
   CC:                                  ${CC}
   CXX:                                 ${CXX}
   LD:                                  ${LD}
   Default CFLAGS:                      ${CFLAGS}
   Default CXXFLAGS:                    ${CXXFLAGS}

Features configured in ${PACKAGE_NAME}:
   C++ standard used:                   ${cpp_standard_used}
   Boost:                               ${using_boost}
   ABI demangle:                        ${using_abi_demangle}

----------------------------------------------------------------"
