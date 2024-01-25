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
        prod-mgmt/src/product.cpp prod-mgmt/src/product.h
        prod-mgmt/src/auth.cpp prod-mgmt/src/auth.h
        prod-mgmt/src/menu.cpp prod-mgmt/src/menu.h
        prod-mgmt/src/terminal.cpp prod-mgmt/src/terminal.h
        prod-mgmt/src/dirty.cpp prod-mgmt/src/dirty.h
        prod-mgmt/src/ui.cpp prod-mgmt/src/ui.h
        prod-mgmt/src/utils.cpp prod-mgmt/src/utils.h
)

add_executable(ProdManageSys prod-mgmt/main.cpp ${COMMON_SOURCES})
target_link_libraries(ProdManageSys PRIVATE nlohmann_json::nlohmann_json)

add_executable(ProdManageSysTests prod-mgmt/test.cpp ${COMMON_SOURCES})
target_link_libraries(ProdManageSysTests PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(ProdManageSysTests PRIVATE Catch2::Catch2WithMain)

set_target_properties(ProdManageSys PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)