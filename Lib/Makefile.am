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
libstatemachine_includedir = $(includedir)/ILUStateMachine

lib_LTLIBRARIES = libstatemachine.la
libstatemachine_la_SOURCES = \
	CCreateState.cpp \
	CCreateStateFinished.cpp \
	CEventBase.cpp \
	CHandleEventInfoBase.cpp \
	CSPEventBaseSort.cpp \
	CStateChangeException.cpp \
	CState.cpp \
	CStateEvtId.cpp \
	CStateMachine.cpp \
	CStateMachineData.cpp \
	CLogIndent.cpp \
	Logging.cpp \
	LoggingInternal.cpp \
	LoggingSerial.cpp \
	libStateMachine.cpp
libstatemachine_include_HEADERS = \
	Include/CCreateStateFinished.h \
	Include/CCreateState.h \
	Include/CEventBase.h \
	Include/CHandleEventInfoBase.h \
	Include/CLogIndent.h \
	Include/CSPEventBaseSort.h \
	Include/CStateChangeException.h \
	Include/CStateEvtId.h \
	Include/CStateEvtIdImpl.h \
	Include/CState.h \
	Include/CStateMachineData.h \
	Include/CStateMachine.h \
	Include/CStateMachineImpl.h \
	Include/EEvtSubNotSet.h \
	Include/Logging.h \
	Include/TCreateState.h \
	Include/TEventEvtId.h \
	Include/TEventEvtIdImpl.h \
	Include/THandleEventInfo.h \
	Include/THandleEventInfoImpl.h \
	Include/THandleEventTypeInfo.h \
	Include/THandleEventTypeInfoImpl.h

AM_CPPFLAGS = $(EXTRA_CPPFLAGS) -IInclude
AM_LDFLAGS = $(EXTRA_LDFLAGS)

