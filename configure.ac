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

##required to build shared libraries,
##has to be after _PROG_
LT_INIT

##suggested when running autoreconf --install
AC_CONFIG_MACRO_DIRS([m4])

##generate a 'config.h' file containing configuration defines
AC_CONFIG_HEADERS([config.h])

##set cppflags in a way they can be used in all makefiles
EXTRA_CPPFLAGS="-I${prefix}/include -W -Wall -Wextra -Wpointer-arith -Wformat-security -Werror -Wswitch-default -Wshadow -ffor-scope -Woverloaded-virtual -Wcast-qual"
AC_SUBST(EXTRA_CPPFLAGS)

##use short output while building
AM_SILENT_RULES([yes])

##set library flags in a way they can be used in all makefiles
EXTRA_LDFLAGS="-version-info 1:0:0"
AC_SUBST(EXTRA_LDFLAGS)

##requires boost
##AX_BOOST_BASE([1.67], [], AC_MSG_ERROR([Could not find Boost]))
##AX_BOOST_SYSTEM
##AX_BOOST_FILESYSTEM

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
   ])

##TODO:
##- doxygen beschrijving main page uitbreiden
##- alle gebruikte comando's ergens documenteren --> ik heb een cloud hosted prive wiki nodig!!!
##- build and run demo application: shows 1 or 2 very simple state machines, to get started
##- build and run test application: test all features
##- test cross-compilation builds
##- test builds from relative dir, not from root
##- use C++14 compiler when it is available instead of boost
##- check for boost installation if no C++14 available
##- dist packate test
##- add dist tests: are all include files exported ...
##

