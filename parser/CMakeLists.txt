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
set(AnalyzersFiles ${PrimitiveFiles} Analyzer/AAnalyzeFactory.h Analyzer/AAnalyzer.h Analyzer/IndentAnalyze/IndentAnalyzer.cpp Analyzer/IndentAnalyze/IndentAnalyzer.h Analyzer/AConstraintor.h Analyzer/IndentAnalyze/IndentConstraintor.cpp Analyzer/IndentAnalyze/IndentConstraintor.h Analyzer/AnalyzeFactoryType.h Analyzer/AnalyzeFactoryCreator.h Analyzer/IndentAnalyze/IndentAnalyzeFactory.h Analyzer/IndentAnalyze/Tools/Liner.cpp Analyzer/IndentAnalyze/Tools/Liner.h Analyzer/IndentAnalyze/Tools/Utils.h Analyzer/IndentAnalyze/Tools/States.h Analyzer/IndentAnalyze/Tools/Memory.cpp Analyzer/IndentAnalyze/Tools/Memory.h Analyzer/IndentAnalyze/Alphabet/BaseAlphabet.h Analyzer/IndentAnalyze/Alphabet/PythonLikeAlphabet.h Analyzer/AccumulateErrors.h)
set(SchedulerFiles ${FigureFiles} Scheduler/SchedulerType.h Scheduler/SchedulerCreator.h Scheduler/AScheduler.h Scheduler/CommonScheduler.cpp Scheduler/CommonScheduler.h)
set(MockFiles Mocks/MockScheduler.h Mocks/MockAnalyzeFactory.h Mocks/MockParser.cpp Mocks/MockParser.h)
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
        Mocks/MockScheduler.h)


find_package(GTest REQUIRED)
include_directories(test_parser ${GTEST_INCLUDE_DIRS})
add_library(${PROJECT_NAME} SHARED ${AllFiles})

enable_testing()

add_executable(parserTest parserTest.cpp ptrVector.h)
target_link_libraries(parserTest ${PROJECT_NAME} -lgtest -lgmock pthread)

add_test(parser_testing parserTest)