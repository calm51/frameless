
cmake_minimum_required(VERSION 3.5)

project(frameless VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB FRAMELESS_PROJECT_SOURCES
    "./src/*.h"
    "./src/*.cpp"
    "./src/*.ui"
    "./src/*/*.h"
    "./src/*/*.cpp"
    "./src/*/*.ui"
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

add_definitions(-DI_AM_LIBRARY)
add_library(frameless SHARED ${FRAMELESS_PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if (WIN32)
    message("CMAKE_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID}")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND python "${CMAKE_SOURCE_DIR}/script/package.py" win32msvc) # PRE_BUILD | PRE_LINK| POST_BUILD
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND python "${CMAKE_SOURCE_DIR}/script/package.py" win32mingw) # PRE_BUILD | PRE_LINK| POST_BUILD
    endif ()
    set_target_properties(frameless PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    )

elseif (ANDROID)
    ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND python3 "${CMAKE_SOURCE_DIR}/script/package.py" android)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS AndroidExtras)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS AndroidExtras)
    target_link_libraries(frameless PRIVATE Qt${QT_VERSION_MAJOR}::AndroidExtras)
    set(ANDROID_ABI armeabi-v7a)
    set(ANDROID_NATIVE_API_LEVEL 21)
    #    set_target_properties(frameless PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/android-build/libs/armeabi-v7a")

elseif (UNIX AND NOT APPLE AND NOT WIN32 AND NOT ANDROID)
    ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND python3 "${CMAKE_SOURCE_DIR}/script/package.py" linux64)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS X11Extras)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS X11Extras)
    target_link_libraries(frameless PRIVATE Qt${QT_VERSION_MAJOR}::X11Extras Qt${QT_VERSION_MAJOR}::CorePrivate)

endif()

add_definitions(-D_HAS_STD_BYTE=0)

#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/test/framelessdemo)


