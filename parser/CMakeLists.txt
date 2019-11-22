cmake_minimum_required(VERSION 3.14)
project(parser)

set(CMAKE_CXX_STANDARD 11)


set(Stubs Stubs/Stubs.h)
set(Error Error/Error.h)
set(JsonFormer
        JsonFormer/JsonFormer.h JsonFormer/JsonFormer.cpp)
set(FigureFiles
        Scheduler/Figure/AFigure.h
        Scheduler/Figure/SingleMeasureFigure.h
        Scheduler/Figure/FLine.h
        Scheduler/Figure/FArrorw.h
        Scheduler/Figure/DoubleMeasureFigure.h
        Scheduler/Figure/FBegEnd.h
        Scheduler/Figure/FFollow.h
        Scheduler/Figure/FFork.h
        Scheduler/Figure/FFunc.h
        Scheduler/Figure/FBegCycle.h
        Scheduler/Figure/FEndCycle.h
        )
set(PrimitiveFiles
        Analyzer/Primitive/APrimitive.h
        Analyzer/Primitive/PFollow.h
        Analyzer/Primitive/PFunc.h
        Analyzer/Primitive/ComplexPrimitive.h
        Analyzer/Primitive/PAlgorithm.h
        Analyzer/Primitive/PFork.h
        Analyzer/Primitive/PCycle.h
        )
set(AnalyzersFiles ${PrimitiveFiles})
set(SchedulerFiles ${FigureFiles} Scheduler/SchedulerType.h Scheduler/SchedulerCreator.h Scheduler/AScheduler.h Scheduler/CommonScheduler.cpp Scheduler/CommonScheduler.h)
set(MockFiles)
set(ParserFiles
        Parser.h Parser.cpp
        ptrVector.h
        )

set(AllFiles
        ${Stubs}
        ${Error}
        ${JsonFormer}
        ${AnalyzersFiles}
        ${SchedulerFiles}
        ${ParserFiles}
        ${MockFiles}
        )


find_package(GTest REQUIRED)
include_directories(test_parser ${GTEST_INCLUDE_DIRS})
add_library(${PROJECT_NAME} SHARED ${AllFiles})

add_executable(test_parser test.cpp ptrVector.h)
target_link_libraries(test_parser ${PROJECT_NAME} -lgtest -lgmock pthread)
