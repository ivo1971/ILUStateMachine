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
if HAVE_DOXYGEN
directory_out = $(top_srcdir)/docs/out/
directory_man = $(directory_out)/man/man3/
directory_htm = $(directory_out)/html
archive_htm   = $(directory_out)/ILULibStateMachineDocHtml.tar.bz2

dist_man_MANS = $(directory_man)/ILULibStateMachine.3
$(directory_man)/ILULibStateMachine.3: doxyfile.stamp

dist_doc_DATA = $(archive_htm)
$(archive_htm): doxyfile.stamp
	tar -cjf $(archive_htm) -C $(directory_htm) .

doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(directory_out)
	rm -f doxyfile.stamp
endif 

