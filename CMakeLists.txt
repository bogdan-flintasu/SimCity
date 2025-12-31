cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################
# external dependencies with FetchContent (optional)
# include(FetchContent)
#
# set(FETCHCONTENT_QUIET OFF)
# set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
#
# FetchContent_Declare(
#         SFML
#         GIT_REPOSITORY https://github.com/SFML/SFML.git
#         GIT_TAG        2.6.1
# )
# FetchContent_MakeAvailable(SFML)

###############################################################################
# external dependencies with find_package (recommended)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp

        # --- SFML UI ---
        src/ui/App.cpp
        src/ui/Button.cpp
        src/ui/TextInput.cpp

        # --- your sources ---
        Source/Oras.cpp
        Source/Zona.cpp
        Source/Strada.cpp
        Source/Proiect.cpp
        Source/CladirePublica.cpp
        Source/CladireRezidentiala.cpp
)

target_include_directories(${MAIN_EXECUTABLE_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/Headers
        ${CMAKE_SOURCE_DIR}/src
)

# Link SFML (works for typical SFML installs)
# Some installs expose SFML::graphics targets, others expose sfml-graphics libs.
if (TARGET SFML::graphics)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE SFML::graphics SFML::window SFML::system)
else()
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
endif()

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

# SFML assets (font)
copy_files(FILES assets/arial.ttf COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
