cmake_minimum_required(VERSION 3.3)
project(code)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/database/DatabaseServer.cpp
    src/database/DatabaseServer.h
    src/datamining/grid/GirdPredictor.cpp
    src/datamining/grid/GridCreator.cpp
    src/datamining/grid/GridCreator.h
    src/datamining/grid/GridDataMining.cpp
    src/datamining/grid/GridDataMining.h
    src/datamining/grid/GridPredictor.h
    src/datamining/DataMining.h
    src/scheduler/AbstractScheduler.cpp
    src/scheduler/AbstractScheduler.h
    src/scheduler/FIFO.cpp
    src/scheduler/FIFO.h
    src/scheduler/LIFO.cpp
    src/scheduler/LIFO.h
    src/scheduler/LJF.cpp
    src/scheduler/LJF.h
    src/scheduler/Master.cpp
    src/scheduler/Master.h
    src/scheduler/MpiWinLIFO.cpp
    src/scheduler/MpiWinLIFO.h
        src/scheduler/SchedulingStrategyEvaluator.cpp
        src/scheduler/SchedulingStrategyEvaluator.h
    src/scheduler/SchedulingStrategy.h
    src/scheduler/SJF.cpp
    src/scheduler/SJF.h
    src/scheduler/TaskStealingScheduler.cpp
    src/scheduler/TaskStealingScheduler.h
    src/worker/AbstractWorker.cpp
    src/worker/AbstractWorker.h
    src/worker/Worker.cpp
    src/worker/Worker.h
    src/worker/WorkerProxy.cpp
    src/worker/WorkerProxy.h
    src/Const.h
    src/easylogging++.h
        src/Executor.cpp
        src/Executor.h
    src/Main.cpp
    src/ScientificCode.cpp
    src/ScientificCode.h
    src/Types.h
    Makefile src/scheduler/MpiWinSchedulingStrategy.h src/worker/WorkerExecutor.cpp src/worker/WorkerExecutor.h src/worker/TaskStealingWorker.cpp src/worker/TaskStealingWorker.h src/worker/WorkerForwarder.h src/worker/WorkerForwarder.cpp src/datamining/DummyDataMining.cpp src/datamining/DummyDataMining.h src/util/CommandLineParser.cpp src/util/CommandLineParser.h src/scheduler/DesignEnum.h src/scheduler/SchedulingStrategyEnum.h src/util/TimeUtility.cpp src/util/TimeUtility.h)

add_executable(code ${SOURCE_FILES})
