cmake_minimum_required( VERSION 2.6 )

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/.cmake/Modules)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_USE_RELATIVE_PATHS TRUE)

project(cpGUI-project)

## add_subdirectory(doc build/doc)
add_subdirectory(src build/src)
add_subdirectory(samples build/samples)
