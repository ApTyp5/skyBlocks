cmake_minimum_required(VERSION 3.14)
project(parser)

set(CMAKE_CXX_STANDARD 11)


set(Stubs Stubs/Stubs.h)
set(Errors Errors/ParseError.h)
set(JsonFormer
        JsonFormer/JsonFormer.h JsonFormer/JsonFormer.cpp
        )
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
        Scheduler/Figure/FContinue.h Scheduler/Figure/FContinue.cpp
        Scheduler/Figure/FigureTypes.h
        Scheduler/Figure/FigureCreator.h
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
set(AnalyzersFiles ${PrimitiveFiles}
        Analyzer/AAnalyzeFactory.h
        Analyzer/AAnalyzer.h
        Analyzer/IndentAnalyze/IndentAnalyzer.cpp Analyzer/IndentAnalyze/IndentAnalyzer.h
        Analyzer/AConstraintor.h
        Analyzer/IndentAnalyze/IndentConstraintor.cpp Analyzer/IndentAnalyze/IndentConstraintor.h
        Analyzer/AnalyzeFactoryType.h
        Analyzer/AnalyzeFactoryCreator.h
        Analyzer/IndentAnalyze/IndentAnalyzeFactory.h
        Analyzer/IndentAnalyze/Tools/IndentAnalyzerUtils.h
        Analyzer/IndentAnalyze/Tools/States.h
        Analyzer/IndentAnalyze/Tools/Memory.cpp Analyzer/IndentAnalyze/Tools/Memory.h
        Analyzer/IndentAnalyze/Alphabet/BaseAlphabet.h
        Analyzer/IndentAnalyze/Alphabet/PythonLikeAlphabet.h
        Analyzer/AccumulateErrors.h
        )
set(ToolFiles
        Tools/Liner.cpp Tools/Liner.h
        Tools/SizedLiner.cpp Tools/SizedLiner.h
        Tools/Meta.h
        )
set(SchedulerFiles
        ${FigureFiles}
        Scheduler/SchedulerType.h
        Scheduler/SchedulerCreator.h
        Scheduler/AScheduler.h
        Scheduler/EmborderScheduler/EmborderScheduler.cpp Scheduler/EmborderScheduler/EmborderScheduler.h
        Scheduler/Figure/FContinue.h Scheduler/Figure/FContinue.cpp
        Scheduler/Figure/Primitives/Point.h
        Scheduler/Figure/Primitives/Rect.h
        )
set(MockFiles
        Mocks/MockScheduler.h
        Mocks/MockAnalyzeFactory.h
        Mocks/MockParser.cpp
        Mocks/MockParser.h
        )
set(ParserFiles
        Parser.h Parser.cpp
        Tools/ptrVector.h
        )
set(TestFiles
        Fixtures/FIndentPythonLikeAnalyzer.h
        Fixtures/FEmborderScheduler.h
        )
set(AllFiles
        ${Stubs}
        ${Errors}
        ${JsonFormer}
        ${ToolFiles}
        ${AnalyzersFiles}
        ${SchedulerFiles}
        ${ParserFiles}
        ${TestFiles}
        )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_library(${PROJECT_NAME} SHARED ${AllFiles})

add_executable(parserTest tests/parserTest.cpp)
target_link_libraries(parserTest ${PROJECT_NAME} -lgtest -lgmock pthread)

add_executable(analyzerTest tests/analyzerTest.cpp)
target_link_libraries(analyzerTest ${PROJECT_NAME} -lgtest -lgmock pthread)

add_executable(schedulerTest tests/schedulerTest.cpp)
target_link_libraries(schedulerTest ${PROJECT_NAME} -lgtest -lgmock pthread)

add_executable(parserToolsTest tests/parserToolsTest.cpp)
target_link_libraries(parserToolsTest ${PROJECT_NAME} -lgtest -lgmock pthread)

add_executable(constraintorTest tests/constraintorTest.cpp)
target_link_libraries(constraintorTest ${PROJECT_NAME} -lgtest -lgmock pthread)

add_executable(main main.cpp)
target_link_libraries(main ${PROJECT_NAME} -lgtest -lgmock pthread)

enable_testing()
add_test(ParserTest parserTest)
add_test(ParserToolsTest parserToolsTest)
add_test(AnalyzerTest analyzerTest)
add_test(ConstraintorTest constraintorTest)
add_test(SchedulerTest schedulerTest)