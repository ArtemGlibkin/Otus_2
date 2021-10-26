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
add_executable(allocator_test tests/AllocatorTest.cpp)

set_target_properties(allocator  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

target_include_directories(allocator
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(allocator allocator_lib)

target_include_directories(allocator_lib
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(allocator_test PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(allocator_test ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} Threads::Threads allocator_lib)

if(MSVC)
	target_compile_options(allocator_lib PRIVATE /MT)
	target_compile_options(allocator PRIVATE /MT)
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artem-glibkin@yandex.ru)

include(CPack)
enable_testing()

gtest_add_tests(TARGET allocator_test
				TEST_LIST Map Vector MyContainer
)