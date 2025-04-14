cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

project(Asteroids)

if(WIN32)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()


find_package(raylib CONFIG REQUIRED)

if(WIN32)
    add_executable(Asteroids WIN32 src/main.cpp src/asteroids.h src/asteroids.cpp src/meteor.h src/meteor.cpp src/bullet.cpp src/bullet.h)
else()
    add_executable(Asteroids src/main.cpp src/asteroids.h src/asteroids.cpp src/meteor.h src/meteor.cpp src/bullet.cpp src/bullet.h)
endif()

target_link_libraries(Asteroids PRIVATE raylib)

# cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/Programs/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_MANIFEST_MODE=ON
# cmake.exe --build build 