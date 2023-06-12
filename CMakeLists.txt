cmake_minimum_required(VERSION 3.24)
project(ProdManageSys)

set(CMAKE_CXX_STANDARD 23)

# Include the FetchContent module
include(FetchContent)

# Define the target name for nlohmann/json
set(JSON_LIBRARY_TARGET_NAME nlohmann_json)

# Fetch and configure nlohmann/json
FetchContent_Declare(
        ${JSON_LIBRARY_TARGET_NAME}
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2  # Specify the desired version or commit hash
)
FetchContent_MakeAvailable(${JSON_LIBRARY_TARGET_NAME})

add_executable(ProdManageSys main.cpp product.cpp product.h auth.cpp auth.h menu.cpp menu.h terminal.cpp terminal.h dirty.cpp dirty.h)

target_link_libraries(ProdManageSys PRIVATE nlohmann_json::nlohmann_json)
