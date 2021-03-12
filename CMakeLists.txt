cmake_minimum_required(VERSION 3.17)
project(Core6 VERSION 0.1.10 DESCRIPTION "basic game engine, edition 6")

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(LIB_DIR libraries/win)
    set(SHRD_EXT dll)
else()
    set(LIB_DIR libraries/unix)
    set(SHRD_EXT so)
endif(WIN32)

# find SFML 2.5
set(SFML_DIR ${LIB_DIR}/SFML-2.5.1/lib/cmake/SFML/)
find_package(SFML 2.5 COMPONENTS graphics window system audio network REQUIRED)

# find Box2D
include_directories(${LIB_DIR}/Box2D/include)

# find MPL
include_directories(${LIB_DIR}/../MPL/include)

# includes
include_directories(src)
include_directories(tests)

# add execs
add_library(Core6 SHARED src/Core6/utils/path.cpp src/Core6/utils/gizmo.cpp src/Core6/utils/gizmo.hpp src/Core6/utils/group.cpp src/Core6/utils/group.hpp src/Core6/signal/signal.cpp src/Core6/signal/signal.hpp src/Core6/signal/listener.cpp src/Core6/signal/listener.hpp src/Core6/systems/inputHandler.cpp src/Core6/systems/inputHandler.hpp src/Core6/utils/singleton.cpp src/Core6/utils/nonCopyable.cpp src/Core6/framework.cpp src/Core6/framework.hpp src/Core6/utils/commonFunctions.cpp src/Core6/systems/console.cpp src/Core6/systems/console.hpp src/Core6/signal/message.cpp src/Core6/signal/message.hpp src/Core6/scene.cpp src/Core6/scene.hpp src/Core6/systems/renderer.cpp src/Core6/systems/renderer.hpp src/Core6/systems/resourceManager.cpp src/Core6/systems/resourceManager.hpp src/Core6/camera.cpp src/Core6/camera.hpp src/Core6/state/finiteStateMachine.cpp src/Core6/state/finiteStateMachine.hpp src/Core6/state/finiteState.cpp src/Core6/state/finiteState.hpp src/Core6/application.cpp src/Core6/threading/concurent.cpp src/Core6/utils/storage.cpp src/Core6/plugin/plugin.cpp src/Core6/plugin/plugin.hpp src/Core6/plugin/entryPoint.cpp src/Core6/plugin/entryPoint.hpp src/Core6/plugin/extensionable.cpp src/Core6/plugin/extensionable.hpp src/Core6/plugin/package.cpp src/Core6/plugin/package.hpp src/Core6/state/finiteStateEvent.cpp src/Core6/state/finiteStateEvent.hpp src/Core6/agent/ecsConfig.cpp src/Core6/agent/ecsConfig.hpp src/Core6/agent/ecs/componentStorage.cpp src/Core6/agent/ecs/componentStorage.hpp src/Core6/agent/ecs/signatureStorage.cpp src/Core6/agent/ecs/signatureStorage.hpp src/Core6/agent/agent.cpp src/Core6/agent/agent.hpp src/Core6/agent/agentGroup.cpp src/Core6/agent/agentGroup.hpp src/Core6/agent/system.cpp src/Core6/agent/system.hpp src/Core6/agent/components/components.hpp)
add_executable(CreateCore6lib tools/createLibrary.cpp)
add_library(Core6debugLib SHARED tests/src/game.cpp tests/src/game.hpp)
add_executable(Core6debug tests/src/main.cpp)
add_library(Core6plugin SHARED tests/plugin/plugin.cpp tests/plugin/plugin.hpp)
# target properties
set_target_properties(CreateCore6lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../tools/")
set_target_properties(Core6debug PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../tests/bin/")
#set_target_properties(Core6 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../Core6/bin/")
#set_target_properties(Core6debugLib PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../tests/bin")
#set_target_properties(Core6plugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../tests/mods")

# compile options
target_compile_options(Core6 PRIVATE -Wall -O3 -Wextra)
target_compile_options(CreateCore6lib PRIVATE -Wall -O3 -Wextra)
target_compile_options(Core6debugLib PRIVATE -Wall -O3 -Wextra)
target_compile_options(Core6debug PRIVATE -Wall -O3 -Wextra)
target_compile_options(Core6plugin PRIVATE -Wall -O3 -Wextra)

# link libraries
target_link_libraries(Core6 sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
#target_link_libraries(Core6 ${LIB_DIR}/Box2D/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6 stdc++fs)

target_link_libraries(Core6debugLib sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
#target_link_libraries(Core6debugLib ${LIB_DIR}/Box2D/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6debugLib ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6.${SHRD_EXT})

target_link_libraries(Core6plugin sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
#target_link_libraries(Core6plugin ${LIB_DIR}/Box2D/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6plugin ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6.${SHRD_EXT})
target_link_libraries(Core6plugin ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6debugLib.${SHRD_EXT})

target_link_libraries(Core6debug sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
#target_link_libraries(Core6debug ${LIB_DIR}/Box2D/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6debug ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6.${SHRD_EXT})
target_link_libraries(Core6debug ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6debugLib.${SHRD_EXT})

