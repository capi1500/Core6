cmake_minimum_required(VERSION 3.17)
project(Core6 VERSION 0.1.0 DESCRIPTION "basic game engine, edition 6")

set(CMAKE_CXX_STANDARD 17)

# find SFML 2.5
if(WIN32)
    set(SFML_DIR libraries/SFML-2.5.1/lib/cmake/SFML/)
endif(WIN32)

find_package(SFML 2.5 COMPONENTS graphics window system audio network REQUIRED)

# find Box2D
include_directories(libraries/Box2D/include)

# includes
include_directories(src)
include_directories(tests)

# add execs
add_library(Core6 SHARED src/Core6/utils/path.cpp src/Core6/utils/gizmo.cpp src/Core6/utils/gizmo.hpp src/Core6/utils/group.cpp src/Core6/utils/group.hpp src/Core6/agent/agent.cpp src/Core6/agent/agent.hpp src/Core6/agent/graphicComponent.cpp src/Core6/agent/graphicComponent.hpp src/Core6/agent/audioComponent.cpp src/Core6/agent/audioComponent.hpp src/Core6/agent/inputComponent.cpp src/Core6/agent/inputComponent.hpp src/Core6/agent/logicComponent.cpp src/Core6/agent/logicComponent.hpp src/Core6/signal/signal.cpp src/Core6/signal/signal.hpp src/Core6/signal/listener.cpp src/Core6/signal/listener.hpp src/Core6/systems/inputHandler.cpp src/Core6/systems/inputHandler.hpp src/Core6/utils/singleton.cpp src/Core6/utils/nonCopyable.cpp src/Core6/framework.cpp src/Core6/framework.hpp src/Core6/utils/commonFunctions.cpp src/Core6/systems/console.cpp src/Core6/systems/console.hpp src/Core6/signal/message.cpp src/Core6/signal/message.hpp src/Core6/scene.cpp src/Core6/scene.hpp src/Core6/systems/renderer.cpp src/Core6/systems/renderer.hpp src/Core6/systems/assetManager.cpp src/Core6/systems/assetManager.hpp src/Core6/systems/loader.cpp src/Core6/systems/loader.hpp src/Core6/camera.cpp src/Core6/camera.hpp src/Core6/state/finiteStateMachine.cpp src/Core6/state/finiteStateMachine.hpp src/Core6/state/finiteState.cpp src/Core6/state/finiteState.hpp src/Core6/systems/audioManager.cpp src/Core6/systems/audioManager.hpp src/Core6/signal/core_signal/coreSignal.cpp src/Core6/signal/core_signal/coreSignal.hpp src/Core6/agent/factory.cpp src/Core6/agent/factory.hpp src/Core6/application/application.cpp src/Core6/application/bundle.cpp src/Core6/threading/concurent.cpp src/Core6/utils/storage.cpp)
add_executable(CreateCore6lib createLibrary.cpp)
add_executable(Core6debug tests/main.cpp)

# target properties
set_target_properties(CreateCore6lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")

# compile options
target_compile_options(Core6 PRIVATE -Wall)

# link libraries
target_link_libraries(Core6 sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(Core6 ${CMAKE_HOME_DIRECTORY}/libraries/Box2D/bin/libbox2d.dll)
target_link_libraries(Core6 stdc++fs)

target_link_libraries(Core6debug sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(Core6debug ${CMAKE_HOME_DIRECTORY}/libraries/Box2D/bin/libbox2d.dll)
target_link_libraries(Core6debug ${CMAKE_HOME_DIRECTORY}/Core6/bin/libCore6.dll)