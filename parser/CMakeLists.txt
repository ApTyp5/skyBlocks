cmake_minimum_required(VERSION 3.14)
project(parser)

set(AnalyzersFiles
        Analyzers/BaseAnalyzer.cpp Analyzers/BaseAnalyzer.h
        Analyzers/ClikeAnalyzer.cpp Analyzers/ClikeAnalyzer.h)
set(FiguresFiles
        Figures/AbstractFigure.cpp Figures/AbstractFigure.h
        Figures/Arrow.cpp Figures/Arrow.h
        Figures/BegEnd.cpp Figures/BegEnd.h
        Figures/BorderedRect.cpp Figures/BorderedRect.h
        Figures/DoubleMeasureFigure.cpp Figures/DoubleMeasureFigure.h
        Figures/Hrombus.cpp Figures/Hrombus.h
        Figures/Line.cpp Figures/Line.h
        Figures/OneMeasureFigure.cpp Figures/OneMeasureFigure.h
        Figures/Rectangle.cpp Figures/Rectangle.h)
set(PrimitiveFiles
        Primitives/AbstractPrimitive.cpp Primitives/AbstractPrimitive.h
        Primitives/Cycle.cpp Primitives/Cycle.h
        Primitives/Follow.cpp Primitives/Follow.h
        Primitives/Fork.cpp Primitives/Fork.h
        Primitives/SubScheme.cpp Primitives/SubScheme.h)
set(SchedulerFiles
        Schedulers/AbstractScheduler.cpp Schedulers/AbstractScheduler.h
        Schedulers/GostScheduler.cpp Schedulers/GostScheduler.h
        )
set(ParserFiles
        Parser.cpp Parser.h)
set(MockFiles
        Mocks/MockAnalyzer.h
        Mocks/MockScheduler.h
        )
set(AllFiles ${ParserFiles} ${SchedulerFiles}
        ${PrimitivesFiles} ${FigureFiles} ${AnalyzersFiles}
        ${MockFiles})


find_package(GTest REQUIRED)

include_directories(test_parser ${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_library(${PROJECT_NAME} SHARED ${AllFiles})

add_executable(test_parser test.cpp)
target_link_libraries(test_parser ${PROJECT_NAME} -lgtest -lgmock pthread)
