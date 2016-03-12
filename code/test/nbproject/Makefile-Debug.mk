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
CC=gcc
CCC=mpic++
CXX=mpic++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include test-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/database/DatabaseHandlerTestCase.o \
	${OBJECTDIR}/database/DatabaseTestSuite.o \
	${OBJECTDIR}/datamining/grid/ArrayHandlerTestCase.o \
	${OBJECTDIR}/datamining/grid/DataStorageTestCase.o \
	${OBJECTDIR}/datamining/grid/GridDataMiningTestCase.o \
	${OBJECTDIR}/datamining/grid/GridDataMiningTestSuite.o \
	${OBJECTDIR}/datamining/grid/GridLibraryTestCase.o \
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
LDLIBSOPTIONS=../bin/libscheduler.a /usr/lib/libcppunit.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test: ../bin/libscheduler.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test: /usr/lib/libcppunit.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	mpic++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/database/DatabaseHandlerTestCase.o: database/DatabaseHandlerTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/database
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/database/DatabaseHandlerTestCase.o database/DatabaseHandlerTestCase.cpp

${OBJECTDIR}/database/DatabaseTestSuite.o: database/DatabaseTestSuite.cpp 
	${MKDIR} -p ${OBJECTDIR}/database
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/database/DatabaseTestSuite.o database/DatabaseTestSuite.cpp

${OBJECTDIR}/datamining/grid/ArrayHandlerTestCase.o: datamining/grid/ArrayHandlerTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/datamining/grid
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/datamining/grid/ArrayHandlerTestCase.o datamining/grid/ArrayHandlerTestCase.cpp

${OBJECTDIR}/datamining/grid/DataStorageTestCase.o: datamining/grid/DataStorageTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/datamining/grid
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/datamining/grid/DataStorageTestCase.o datamining/grid/DataStorageTestCase.cpp

${OBJECTDIR}/datamining/grid/GridDataMiningTestCase.o: datamining/grid/GridDataMiningTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/datamining/grid
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/datamining/grid/GridDataMiningTestCase.o datamining/grid/GridDataMiningTestCase.cpp

${OBJECTDIR}/datamining/grid/GridDataMiningTestSuite.o: datamining/grid/GridDataMiningTestSuite.cpp 
	${MKDIR} -p ${OBJECTDIR}/datamining/grid
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/datamining/grid/GridDataMiningTestSuite.o datamining/grid/GridDataMiningTestSuite.cpp

${OBJECTDIR}/datamining/grid/GridLibraryTestCase.o: datamining/grid/GridLibraryTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/datamining/grid
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/datamining/grid/GridLibraryTestCase.o datamining/grid/GridLibraryTestCase.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/scheduler/FIFOTestCase.o: scheduler/FIFOTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/FIFOTestCase.o scheduler/FIFOTestCase.cpp

${OBJECTDIR}/scheduler/LIFOTestCase.o: scheduler/LIFOTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/LIFOTestCase.o scheduler/LIFOTestCase.cpp

${OBJECTDIR}/scheduler/LJFTestCase.o: scheduler/LJFTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/LJFTestCase.o scheduler/LJFTestCase.cpp

${OBJECTDIR}/scheduler/SJFTestCase.o: scheduler/SJFTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/SJFTestCase.o scheduler/SJFTestCase.cpp

${OBJECTDIR}/scheduler/SchedulerTestSuite.o: scheduler/SchedulerTestSuite.cpp 
	${MKDIR} -p ${OBJECTDIR}/scheduler
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/cppunit -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/scheduler/SchedulerTestSuite.o scheduler/SchedulerTestSuite.cpp

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
