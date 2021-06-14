cmake_minimum_required(VERSION 3.17)
project(Core6 VERSION 0.3.3 DESCRIPTION "basic game engine, edition 6")

set(CMAKE_CXX_STANDARD 20)

# find library dependency
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

# find gtest
include_directories(${LIB_DIR}/gtest/include)

# includes
include_directories(src)
include_directories(src/tests)

# add targets

add_library(Core6base SHARED src/Core6/base/listener/emitter.hpp src/Core6/base/listener/listener.hpp src/Core6/base/nonCopyable.hpp src/Core6/base/singleton.hpp src/Core6/base/nonMovable.hpp src/Core6/base/interfaces/builder.hpp src/Core6/base/state/stateMachine.cpp src/Core6/base/state/stateMachine.hpp src/Core6/base/state/state.cpp src/Core6/base/state/state.hpp src/Core6/base/interfaces/activable.cpp src/Core6/base/interfaces/activable.hpp src/Core6/base/state/stateEvent.cpp src/Core6/base/state/stateEvent.hpp src/Core6/base/interfaces/factory.hpp)
add_executable(tests test/main.cpp test/listener.hpp test/emitter.hpp)

# compile options
target_compile_options(Core6base PRIVATE -Wall -O3 -Wextra)
target_compile_options(tests PRIVATE -Wall -O3 -Wextra)

# link libraries
target_link_libraries(tests ${CMAKE_HOME_DIRECTORY}/cmake_files/libgtest.${SHRD_EXT})
target_link_libraries(tests ${CMAKE_HOME_DIRECTORY}/cmake_files/libCore6base.${SHRD_EXT})


# @@@@@ OLD @@@@@ #

# add execs
add_library(Core6 SHARED src/Core6_old/utils/path.cpp src/Core6_old/utils/gizmo.cpp src/Core6_old/utils/gizmo.hpp src/Core6_old/utils/group.cpp src/Core6_old/utils/group.hpp src/Core6_old/signal/signal.cpp src/Core6_old/signal/signal.hpp src/Core6_old/signal/listener.cpp src/Core6_old/signal/listener.hpp src/Core6_old/systems/inputHandler.cpp src/Core6_old/systems/inputHandler.hpp src/Core6_old/utils/singleton.cpp src/Core6_old/utils/nonCopyable.cpp src/Core6_old/framework.cpp src/Core6_old/framework.hpp src/Core6_old/utils/commonFunctions.cpp src/Core6_old/systems/console.cpp src/Core6_old/systems/console.hpp src/Core6_old/signal/message.cpp src/Core6_old/signal/message.hpp src/Core6_old/scene.cpp src/Core6_old/scene.hpp src/Core6_old/systems/renderer.cpp src/Core6_old/systems/renderer.hpp src/Core6_old/systems/resourceManager.cpp src/Core6_old/systems/resourceManager.hpp src/Core6_old/camera.cpp src/Core6_old/camera.hpp src/Core6_old/state/finiteStateMachine.cpp src/Core6_old/state/finiteStateMachine.hpp src/Core6_old/state/finiteState.cpp src/Core6_old/state/finiteState.hpp src/Core6_old/application.cpp src/Core6_old/threading/concurent.cpp src/Core6_old/utils/storage.cpp src/Core6_old/plugin/plugin.cpp src/Core6_old/plugin/plugin.hpp src/Core6_old/plugin/entryPoint.cpp src/Core6_old/plugin/entryPoint.hpp src/Core6_old/plugin/package.cpp src/Core6_old/plugin/package.hpp src/Core6_old/state/finiteStateEvent.cpp src/Core6_old/state/finiteStateEvent.hpp src/Core6_old/agent/ecsConfig.cpp src/Core6_old/agent/ecsConfig.hpp src/Core6_old/agent/ecs/componentStorage.cpp src/Core6_old/agent/ecs/componentStorage.hpp src/Core6_old/agent/ecs/signatureStorage.cpp src/Core6_old/agent/ecs/signatureStorage.hpp src/Core6_old/agent/agent.cpp src/Core6_old/agent/agent.hpp src/Core6_old/agent/agentGroup.cpp src/Core6_old/agent/agentGroup.hpp src/Core6_old/agent/system.cpp src/Core6_old/agent/system.hpp src/Core6_old/agent/components.hpp src/Core6_old/agent/factory.cpp src/Core6_old/agent/factory.hpp src/Core6_old/agent/ecs/systemStorage.cpp src/Core6_old/agent/ecs/systemStorage.hpp src/Core6_old/utils/lazyClass.cpp src/Core6_old/utils/lazyClass.hpp src/Core6_old/config.cpp src/Core6_old/config.hpp src/Core6_old/systems/soundboard.cpp src/Core6_old/systems/soundboard.hpp src/Core6_old/plugin/extensionable.cpp src/Core6_old/plugin/extensionable.hpp src/Core6_old/physicsConfig.cpp src/Core6_old/physicsConfig.hpp src/Core6_old/widgets/widgetAssetPack.cpp src/Core6_old/widgets/widgetAssetPack.hpp src/Core6_old/widgets/factories.cpp src/Core6_old/widgets/factories.hpp src/Core6_old/widgets/misc/frame9.cpp src/Core6_old/widgets/misc/frame9.hpp src/Core6_old/widgets/components/graphic.cpp src/Core6_old/widgets/components/graphic.hpp src/Core6_old/widgets/components/label.cpp src/Core6_old/widgets/components/label.hpp src/Core6_old/widgets/systems/label.cpp src/Core6_old/widgets/systems/label.hpp)
add_executable(CreateCore6lib tools/createLibrary.cpp)
add_library(Core6debugLib SHARED src/tests/src/game.cpp src/tests/src/game.hpp src/tests/src/init.hpp src/tests/src/objects/rectComponent.cpp src/tests/src/objects/rectComponent.hpp src/tests/src/init.cpp)
add_executable(Core6debug src/tests/src/main.cpp)
add_library(Core6plugin SHARED src/tests/plugin/plugin.cpp src/tests/plugin/plugin.hpp)
add_library(Core6plugin2 SHARED src/tests/plugin/pluginConflict.cpp src/tests/plugin/pluginConflict.hpp)

# target properties
set_target_properties(CreateCore6lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../tools/")
set_target_properties(Core6debug PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../tests/bin/")

# compile options
target_compile_options(Core6 PRIVATE -Wall -O3 -Wextra)
target_compile_options(CreateCore6lib PRIVATE -Wall -O3 -Wextra)
target_compile_options(Core6debugLib PRIVATE -Wall -O3 -Wextra)
target_compile_options(Core6debug PRIVATE -Wall -O3 -Wextra)
target_compile_options(Core6plugin PRIVATE -Wall -O3 -Wextra)
target_compile_options(Core6plugin2 PRIVATE -Wall -O3 -Wextra)

# link libraries
target_link_libraries(Core6 sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(Core6 ${CMAKE_HOME_DIRECTORY}/tests/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6 stdc++fs)

target_link_libraries(Core6debugLib sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(Core6debugLib ${CMAKE_HOME_DIRECTORY}/tests/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6debugLib ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6.${SHRD_EXT})

target_link_libraries(Core6plugin sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(Core6plugin ${CMAKE_HOME_DIRECTORY}/tests/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6plugin ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6.${SHRD_EXT})
target_link_libraries(Core6plugin ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6debugLib.${SHRD_EXT})

target_link_libraries(Core6plugin2 sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(Core6plugin2 ${CMAKE_HOME_DIRECTORY}/tests/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6plugin2 ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6.${SHRD_EXT})
target_link_libraries(Core6plugin2 ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6debugLib.${SHRD_EXT})

target_link_libraries(Core6debug sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(Core6debug ${CMAKE_HOME_DIRECTORY}/tests/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6debug ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6.${SHRD_EXT})
target_link_libraries(Core6debug ${CMAKE_HOME_DIRECTORY}/tests/bin/libCore6debugLib.${SHRD_EXT})

