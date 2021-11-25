cmake_minimum_required(VERSION 3.16)
project(Core6 VERSION 0.5.8 DESCRIPTION "basic game engine, edition 6")

set(CMAKE_CXX_STANDARD 20)

# find library dependency
if(WIN32)
    set(LIB_DIR libraries/win)
    set(SHRD_EXT dll)
else()
    set(LIB_DIR libraries/unix)
    set(SHRD_EXT so)
endif(WIN32)

# include SFML 2.5
set(SFML_DIR ${LIB_DIR}/SFML-2.5.1/lib/cmake/SFML/)
find_package(SFML 2.5 COMPONENTS graphics window system audio network REQUIRED)

# include Box2D
include_directories(${LIB_DIR}/Box2D/include)

# include MPL
include_directories(${LIB_DIR}/../MPL/include)

# include concurent
include_directories(${LIB_DIR}/../Concurrent/include)

# include gtest
include_directories(${LIB_DIR}/gtest/include)

# includes
include_directories(src)
include_directories(src/sample)

# add targets

add_library(Core6 SHARED src/Core6/base/listener/emitter.hpp src/Core6/base/listener/listener.hpp src/Core6/base/nonCopyable.hpp src/Core6/base/singleton.hpp src/Core6/base/nonMovable.hpp src/Core6/base/state/stateMachine.cpp src/Core6/base/state/stateMachine.hpp src/Core6/base/state/state.cpp src/Core6/base/state/state.hpp src/Core6/base/activable.cpp src/Core6/base/activable.hpp src/Core6/utils/storage.hpp src/Core6/utils/filepath.cpp src/Core6/utils/filepath.hpp src/Core6/utils/shuffledList.hpp src/Core6/ecs/config.hpp src/Core6/ecs/system.hpp src/Core6/ecs/entityComponentSystem.hpp src/Core6/ecs/componentManager.hpp src/Core6/ecs/entityFactory.hpp src/Core6/systems/renderer.cpp src/Core6/systems/renderer.hpp src/Core6/systems/resourceManager.cpp src/Core6/systems/resourceManager.hpp src/Core6/systems/inputHandler.cpp src/Core6/systems/inputHandler.hpp src/Core6/systems/soundboard.cpp src/Core6/systems/soundboard.hpp src/Core6/systems/console.cpp src/Core6/systems/console.hpp src/Core6/framework.hpp src/Core6/base/loggable.cpp src/Core6/base/loggable.hpp src/Core6/concurrent/concurrent.hpp src/Core6/application.hpp src/Core6/scene.hpp src/Core6/concurrent/job.cpp src/Core6/concurrent/job.hpp src/Core6/concurrent/jobPool.cpp src/Core6/concurrent/jobPool.hpp src/Core6/physicsConfig.hpp src/Core6/ecs/components.hpp src/Core6/framework.cpp src/Core6/gui/graphics/frame9.cpp src/Core6/gui/graphics/frame9.hpp src/Core6/base/lazy.hpp src/Core6/utils/functional.hpp src/Core6/animations/animation.hpp src/Core6/animations/parallelAnimation.cpp src/Core6/animations/parallelAnimation.hpp src/Core6/animations/animation.cpp src/Core6/animations/spriteAnimation.cpp src/Core6/animations/spriteAnimation.hpp src/Core6/animations/sequentialAnimation.cpp src/Core6/animations/sequentialAnimation.hpp src/Core6/animations/pathTransition.cpp src/Core6/animations/pathTransition.hpp src/Core6/animations/moveTransition.cpp src/Core6/animations/moveTransition.hpp src/Core6/ecs/entityBuilder.hpp src/Core6/ecs/components/entityState.hpp src/Core6/ecs/components/animatedSprite.cpp src/Core6/ecs/components/animatedSprite.hpp src/Core6/ecs/systems/drawSystem.hpp src/Core6/ecs/systems/drawSystem.hpp src/Core6/ecs/systems/syncPhysicsWithGraphics.hpp libraries/MPL/include/MPL/strip.hpp src/Core6/gui/graphics/widgetGraphics.cpp src/Core6/gui/graphics/widgetGraphics.hpp src/Core6/gui/widget.hpp src/Core6/gui/logic/widgetLogic.cpp src/Core6/gui/logic/widgetLogic.hpp src/Core6/base/listener/empty.hpp src/Core6/gui/systems/updateWidgetTree.hpp src/Core6/ecs/concepts.hpp src/Core6/gui/systems/drawWidget.hpp src/Core6/gui/graphics/empty.cpp src/Core6/gui/graphics/empty.hpp src/Core6/gui/graphics/frame.cpp src/Core6/gui/graphics/frame.hpp src/Core6/gui/graphics/image.cpp src/Core6/gui/graphics/image.hpp src/Core6/gui/logic/button.cpp src/Core6/gui/logic/button.hpp src/Core6/gui/systems/setWidgetParent.hpp)

add_executable(Core6debug src/sample/src/main.cpp src/sample/src/main.cpp src/sample/src/platformer.cpp src/sample/src/platformer.hpp src/sample/src/init.hpp src/sample/src/scenes/mainMenu.cpp src/sample/src/scenes/mainMenu.hpp src/sample/src/scenes/pause.cpp src/sample/src/scenes/pause.hpp src/sample/src/scenes/play.cpp src/sample/src/scenes/play.hpp src/sample/src/systems/ecsEventHandler.cpp src/sample/src/systems/ecsEventHandler.hpp)

add_executable(tests test/main.cpp test/base/listener/listener.hpp test/base/listener/emitter.hpp test/ecs/entityManager.hpp test/ecs/config.hpp test/ecs/componentManager.hpp test/ecs/ecsInit.hpp)
add_executable(CreateCore6lib tools/createLibrary.cpp)

set_target_properties(CreateCore6lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../tools/")
set_target_properties(Core6debug PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../src/sample/bin")

# compile options
if(WIN32)
    set(COMPILE_ARGS -Wall -Wextra)
else()
    set(COMPILE_ARGS -Wall -Wextra -fconcepts)
endif(WIN32)

target_compile_options(Core6 PRIVATE ${COMPILE_ARGS})

target_compile_options(CreateCore6lib PRIVATE ${COMPILE_ARGS})
target_compile_options(tests PRIVATE ${COMPILE_ARGS})

target_compile_options(Core6debug PRIVATE ${COMPILE_ARGS})

# link libraries
target_link_libraries(Core6 sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(Core6 stdc++fs)

target_link_libraries(Core6debug sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(Core6debug ${CMAKE_HOME_DIRECTORY}/src/sample/bin/libbox2d.${SHRD_EXT})
target_link_libraries(Core6debug ${CMAKE_HOME_DIRECTORY}/src/sample/bin/libCore6.${SHRD_EXT})

target_link_libraries(tests ${CMAKE_HOME_DIRECTORY}/cmake_files/libgtest.${SHRD_EXT})
target_link_libraries(tests sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(tests Core6)