# ------------------------------------------------------------------------------
#
# Cepheus Character Generator, a character generator for the Cepheus Engine
# and derived RPG systems.
#
# Copyright (C) 2019 Michael N. Henry <mike.henry@mikehenry.se>
#
# This file is part of Cepheus Character Generator.
#
# Cepheus Character Generator is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or (at your
# option) any later version.
#
# Cepheus Character Generator is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# See the GNU General Public License for more details. You should have received
# a copy of the GNU General Public License along with Cepheus Character
# Generator. If not, see <http://www.gnu.org/licenses/>.
#
# ------------------------------------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    career.cc \
    careerdialog.cc \
    careermodel.cc \
    die.cc \
    main.cc \
    stats.cc \
    workspace.cc

HEADERS += \
    career.hh \
    careerdialog.hh \
    careermodel.hh \
    die.hh \
    stats.hh \
    workspace.hh

FORMS += \
    careerdialog.ui \
    workspace.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
