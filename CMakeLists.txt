cmake_minimum_required(VERSION 3.10)

# set the project name
project(EDA)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
set(Boost_NO_WARN_NEW_VERSIONS 1)


find_package(Boost REQUIRED COMPONENTS random system thread filesystem chrono atomic date_time regex)
find_package(yaml CONFIG REQUIRED)
find_package(cpprestsdk CONFIG REQUIRED)
find_package(OpenSSL 1.0.0 REQUIRED)
# Test

find_package(etcd-cpp-api CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)


add_library(config_parser ./eda/core/config_parser.cpp)
target_include_directories(config_parser PUBLIC
    ${PROJECT_SOURCE_DIR}
)
target_link_libraries(config_parser yaml)


add_library(config ./eda/config/config.cpp)
target_include_directories(config PUBLIC
    ${PROJECT_SOURCE_DIR}
)
target_link_libraries(config
    config_parser
)


# add the executable
add_library(etcdop ./eda/etcd/etcd_op.cpp)
target_include_directories(etcdop PUBLIC
    ${PROJECT_SOURCE_DIR}
)
target_link_libraries(etcdop
    config
    etcd-cpp-api
    cpprestsdk::cpprest
    Boost::boost
    Boost::random
    Boost::system
    Boost::thread
    Boost::filesystem
    Boost::chrono
    Boost::atomic
    Boost::date_time
    Boost::regex
    OpenSSL::SSL
)


add_library(vfs ./eda/vfs/vfs.cpp)
target_include_directories(vfs PUBLIC
    ${PROJECT_SOURCE_DIR}
)
target_link_libraries(vfs 
    etcdop
)

add_executable(eda ${PROJECT_SOURCE_DIR}/eda/main.cpp)

target_link_libraries(eda 
    vfs
)


target_include_directories(eda PUBLIC
    ${PROJECT_SOURCE_DIR}
)



add_executable(testcase ${PROJECT_SOURCE_DIR}/eda/tests/tests.cpp)
target_link_libraries(testcase 
    PRIVATE Catch2::Catch2
    vfs
    config_parser
    config)
target_include_directories(testcase PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_compile_definitions(testcase
    PRIVATE
    TEST_ROOT="${PROJECT_SOURCE_DIR}/eda/tests"
)
