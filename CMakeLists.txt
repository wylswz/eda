cmake_minimum_required(VERSION 3.10)

# set the project name
project(EDA)
set(CMAKE_CXX_STANDARD 11)

find_library(CPPREST_LIB cpprest)
find_package(Boost REQUIRED COMPONENTS random system thread filesystem chrono atomic date_time regex)
find_package(OpenSSL 1.0.0 REQUIRED)
find_package(etcd-cpp-api)


add_library(config ./eda/config/config.cpp)
target_include_directories(config PUBLIC
    ${PROJECT_SOURCE_DIR}
)


# add the executable
add_library(etcdop ./eda/etcd/etcd_op.cpp)
target_include_directories(etcdop PUBLIC
    ${PROJECT_SOURCE_DIR}
)
target_link_libraries(etcdop
    config
    etcd-cpp-api
    ${CPPREST_LIB}
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
target_link_libraries(vfs etcdop)

add_executable(eda ${PROJECT_SOURCE_DIR}/eda/main.cpp)

target_link_libraries(eda 
    vfs
)


target_include_directories(eda PUBLIC
    ${PROJECT_SOURCE_DIR}
)
