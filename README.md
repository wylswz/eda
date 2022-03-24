# Dependencies

## Boost, ssl
```
apt-get install libboost-all-dev libssl-dev
```

## protobuf


## GRPC

```
apt-get install libgrpc-dev \
        libgrpc++-dev \
        libprotobuf-dev \
        protobuf-compiler-grpc
```


## C++ rest SDK

```sh
 git clone https://github.com/microsoft/cpprestsdk.git
 cd cpprestsdk
 mkdir build && cd build
 cmake .. -DCPPREST_EXCLUDE_WEBSOCKETS=ON
 make -j && make install
```

## CPP etcd v3
```sh
git clone https://github.com/etcd-cpp-apiv3/etcd-cpp-apiv3.git
cd etcd-cpp-apiv3
mkdir build && cd build
cmake ..
make -j && make install
```


# Build project

```
$ mkdir target && cd target
$ cmake .. && cmake --build .
```
