#******************************************************************************
#
# Makefile - Makefile for building this project.
#
# Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
#
#******************************************************************************

#******************************************************************************
#
# Modified by Zee Lv
# Nov 6, 2018
#
#******************************************************************************

#
# Defines project name
#
PROJ_NAME=

#
# Defines the part type that this project uses.
#
PART=TM4C123GH6PM

#
# The root directory for zEEware.
#
ROOT=../..

#
# Include the common make definitions.
#
include ${ROOT}/common.mk

#
# Where to find header files that do not live in the source directory.
#
IPATH += \
	${ROOT}/lib/common/inc    \

#
# The default rule
#
all: ${BUILDPATH}
all: ${BUILDPATH}/$(PROJ_NAME).elf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${BUILDPATH} ${wildcard *~}

#
# The rule to create the target directory.
#
${BUILDPATH}:
	@mkdir -p ${BUILDPATH}

#
# Rules for building the Project Zero Example.
#
${BUILDPATH}/$(PROJ_NAME).elf: main.o
${BUILDPATH}/$(PROJ_NAME).elf: ${ROOT}/lib/common/src/startup.o
${BUILDPATH}/$(PROJ_NAME).elf: ${ROOT}/lib/common/src/PLL.o
${BUILDPATH}/$(PROJ_NAME).elf: ${ROOT}/lib/libdriver.a
${BUILDPATH}/$(PROJ_NAME).elf: ${ROOT}/lib/tm4c123gxl.ld
SCATTERgcc_$(PROJ_NAME)=${ROOT}/lib/tm4c123gxl.ld
ENTRY_$(PROJ_NAME)=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${BUILDPATH}/*.d} __dummy__
endif
