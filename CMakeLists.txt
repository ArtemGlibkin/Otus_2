cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(allocator VERSION ${PROJECT_VESRION})

configure_file(include/version.h.in include/version.h)

add_executable(allocator src/main.cpp)
add_library(allocator_lib STATIC src/MyAllocator.cpp)
#add_executable(ip_filter_test tests/IPV4PoolTest.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(allocator
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(allocator allocator_lib)

target_include_directories(allocator_lib
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#target_include_directories(ip_filter_test PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(ip_filter_test ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} Threads::Threads ip_filter_lib)

if(MSVC)
	target_compile_options(allocator_lib PRIVATE /MT)
	target_compile_options(allocator PRIVATE /MT)
endif()

