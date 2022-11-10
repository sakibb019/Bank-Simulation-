cmake_minimum_required(VERSION 3.0)
project(bankSimulation)

# Set compiler flags based on environment
if (MSVC)
    # Force to always compile with W4
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif ()
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_C_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -g")
endif ()

# Download and unpack googletest at configure time
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path dependencies automatically
# when using CMake 2.8.11 or later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

set(CMAKE_CXX_STANDARD 14)

set(SRC_MAIN_FILES
        src/Main.cpp)
set(SRC_DEMO_FILES
        src/Demo.cpp)
set(SRC_TEST_FILES
        test/TestRunner.cpp
        test/GradeAccumulator.cpp)

add_executable(bankSimulation ${SRC_MAIN_FILES})
target_include_directories(bankSimulation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(bankSimulationDemo ${SRC_DEMO_FILES})
target_include_directories(bankSimulationDemo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Now simply link against gtest or gtest_main as needed.
add_executable(bankSimulationTest ${SRC_TEST_FILES})
target_link_libraries(bankSimulationTest gtest_main)
target_include_directories(bankSimulationTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add custom commands that copy data input files to target working directories
add_custom_command(TARGET bankSimulation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/resource/mainData.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET bankSimulationDemo PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/resource/demoData.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET bankSimulationTest PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/resource/testData.txt ${CMAKE_CURRENT_BINARY_DIR})
