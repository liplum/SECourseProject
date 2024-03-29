cmake_minimum_required(VERSION 3.24)
project(SECourseProject)

set(CMAKE_CXX_STANDARD 23)

# Include the FetchContent module
include(FetchContent)

# Fetch and configure nlohmann/json
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2  # Specify the desired version or commit hash
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.3.2 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(
        SHARED_SOURCES
        shared/dirty.cpp shared/dirty.h
        shared/auth.h
        shared/menu.cpp shared/menu.h
        shared/model.h
        shared/terminal.h
        shared/utils.cpp shared/utils.h
)

# Product management
set(
        PROD_MGMT_SOURCES
        prod-mgmt/src/auth.cpp prod-mgmt/src/auth.h
        prod-mgmt/src/models.cpp prod-mgmt/src/models.h
        prod-mgmt/src/terminal.cpp prod-mgmt/src/terminal.h
        prod-mgmt/src/ui.cpp prod-mgmt/src/ui.h
)

add_library(ProdMgmtLib ${SHARED_SOURCES} ${PROD_MGMT_SOURCES})
target_link_libraries(ProdMgmtLib PUBLIC nlohmann_json::nlohmann_json)

add_executable(ProdMgmt prod-mgmt/main.cpp)
target_link_libraries(ProdMgmt PRIVATE ProdMgmtLib)

add_executable(ProdMgmtTests prod-mgmt/test.cpp)
target_link_libraries(ProdMgmtTests PRIVATE ProdMgmtLib Catch2::Catch2WithMain)

set_target_properties(ProdMgmt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Library management

set(
        LIBRARY_MGMT_SOURCES
        library-mgmt/src/auth.cpp library-mgmt/src/auth.h
        library-mgmt/src/models.cpp library-mgmt/src/models.h
        library-mgmt/src/terminal.cpp library-mgmt/src/terminal.h
)

add_library(LibaryMgmtLib ${SHARED_SOURCES} ${LIBRARY_MGMT_SOURCES})
target_link_libraries(LibaryMgmtLib PUBLIC nlohmann_json::nlohmann_json)

add_executable(LibaryMgmt library-mgmt/main.cpp)
target_link_libraries(LibaryMgmt PRIVATE LibaryMgmtLib)

set_target_properties(LibaryMgmt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
