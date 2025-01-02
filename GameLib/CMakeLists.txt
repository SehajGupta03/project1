project(GameLib)

set(SOURCE_FILES pch.h
        MainFrame.cpp
        MainFrame.h
        Game.cpp
        Game.h
        GameView.cpp
        GameView.h
        Product.cpp
        Product.h
        ids.h
        Gate.cpp
        Gate.h
        Scoreboard.cpp
        Scoreboard.h
        Beam.cpp
        Beam.h
        Item.h
        Item.cpp
        Conveyor.cpp
        Conveyor.h
        Sparty.cpp
        Sparty.h
        Sensor.cpp
        Sensor.h
        Pin.cpp
        Pin.h
        OrGate.cpp
        OrGate.h
        Pin.h
        Score.cpp
        Score.h
        NotGate.h
        NotGate.cpp
        AndGate.cpp
        AndGate.h
        DflipFlop.cpp
        DflipFlop.h
        SRFlipFlop.cpp
        SRFlipFlop.h
        ItemVisitor.cpp
        ItemVisitor.h
        PropertyBox.cpp
        PropertyBox.h
        ProductVisitor.cpp
        ProductVisitor.h
        NandGate.cpp
        NandGate.h
        SpartyVisitor.cpp
        SpartyVisitor.h
        PropertyBoxVisitor.cpp
        PropertyBoxVisitor.h
        SensorVisitor.cpp
        SensorVisitor.h
		DependencyGraph.cpp
		DependencyGraph.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

add_definitions(-D_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)