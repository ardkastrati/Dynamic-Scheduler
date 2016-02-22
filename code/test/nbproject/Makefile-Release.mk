#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=icc
CCC=mpic++
CXX=mpic++
FC=ifort
AS=as

# Macros
CND_PLATFORM=Intel-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include test-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/scheduler/FIFOTestCase.o \
	${OBJECTDIR}/scheduler/LIFOTestCase.o \
	${OBJECTDIR}/scheduler/LJFTestCase.o \
	${OBJECTDIR}/scheduler/SJFTestCase.o \
	${OBJECTDIR}/scheduler/SchedulerTestSuite.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/scheduler/FIFOTestCase.o: scheduler/FIFOTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/FIFOTestCase.o scheduler/FIFOTestCase.cpp

${OBJECTDIR}/scheduler/LIFOTestCase.o: scheduler/LIFOTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/LIFOTestCase.o scheduler/LIFOTestCase.cpp

${OBJECTDIR}/scheduler/LJFTestCase.o: scheduler/LJFTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/LJFTestCase.o scheduler/LJFTestCase.cpp

${OBJECTDIR}/scheduler/SJFTestCase.o: scheduler/SJFTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/SJFTestCase.o scheduler/SJFTestCase.cpp

${OBJECTDIR}/scheduler/SchedulerTestSuite.o: scheduler/SchedulerTestSuite.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/SchedulerTestSuite.o scheduler/SchedulerTestSuite.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
