project (DesignPatterns)
cmake_minimum_required (VERSION 2.6)

if (WIN32)
else (WIN32)
  add_definitions(-O3 -std=gnu++11)
endif (WIN32)

add_executable(1 1_strategy/strategy_test.cpp 1_strategy/strategy.cpp 1_strategy/strategy.h)
add_executable(2 2_observer/observer.cpp)
add_executable(3 3_decorator/decorator.cpp)
add_executable(4 4_factory/factory.cpp)
add_executable(5 5_singleton/singleton.cpp)
add_executable(6 6_command/command.cpp)
add_executable(7 7_adapter/adapter.cpp)
add_executable(8 8_templateMethod/templateMethod.cpp)
add_executable(9it 9_itComp/iteratorMain.cpp)
add_executable(9comp 9_itComp/component.cpp 9_itComp/Iterator.h 9_itComp/Iterator.cpp 9_itComp/Menu.h 9_itComp/Menu.cpp 9_itComp/Waitress.h 9_itComp/Waitress.cpp)
add_executable(A A_state/State.cpp A_state/GumballMachine.cpp A_state/main.cpp A_state/State.h A_state/GumballMachine.h)
