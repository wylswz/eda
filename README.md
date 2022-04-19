# Dependencies

## libyaml

```
$ apt install libyaml-dev
```

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

## Catch 2 testing framework

```sh
$ git clone https://github.com/catchorg/Catch2.git
$ cd Catch2
$ cmake -Bbuild -H. -DBUILD_TESTING=OFF
$ sudo cmake --build build/ --target install
```


# Build project

## Build executable

Currently nothing is implemented in executable, but you can still build it

```
$ mkdir target && cd target
$ cmake .. && cmake --build .
```

## Test
```
$ mkdir target && cd target
$ cmake..
$ make testcase
$ ./testcase
```

