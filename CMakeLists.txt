cmake_minimum_required(VERSION 3.24)
project(ProdManageSys)

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
        COMMON_SOURCES
        src/product.cpp src/product.h
        src/auth.cpp src/auth.h
        src/menu.cpp src/menu.h
        src/terminal.cpp src/terminal.h
        src/dirty.cpp src/dirty.h
        src/ui.cpp src/ui.h
        src/utils.cpp src/utils.h
)

add_executable(ProdManageSys main.cpp ${COMMON_SOURCES})
target_link_libraries(ProdManageSys PRIVATE nlohmann_json::nlohmann_json)

add_executable(Tests test.cpp ${COMMON_SOURCES})
target_link_libraries(Tests PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

set_target_properties(ProdManageSys PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)