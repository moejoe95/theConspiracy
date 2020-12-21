cmake_minimum_required(VERSION 3.18)

project(theConspiracy)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(spdlog REQUIRED)
FIND_PACKAGE( Boost COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES 
    src/main.cpp 
    src/Game.cpp 
    src/Utils.cpp 
    src/SDLException.cpp 
    src/Room.cpp 
    src/Player.cpp 
    src/EventDispatcher 
    src/Entity.cpp
    src/Enemy.cpp
    src/Bullet.cpp
    src/CollisionManager.cpp)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# SDL
target_include_directories(${PROJECT_NAME} PRIVATE
    include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${})


target_compile_options(${PROJECT_NAME} PRIVATE )

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES} 
    ${SDL2IMAGE_LIBRARIES} 
    ${SDL2TTF_LIBRARIES} 
    ${OPENGL_LIBRARIES}
    nlohmann_json::nlohmann_json 
    spdlog::spdlog 
    ${Boost_LIBRARIES}
    )

