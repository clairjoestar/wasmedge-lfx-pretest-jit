cmake_minimum_required(VERSION 3.16)
project(LLVMFunctionLister)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_executable(list_functions list_functions.cpp)

target_include_directories(list_functions PRIVATE ${LLVM_INCLUDE_DIRS})

llvm_map_components_to_libnames(llvm_libs core support irreader)
message(STATUS "${llvm_libs}")
target_link_libraries(list_functions ${llvm_libs})

set_target_properties(list_functions PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)