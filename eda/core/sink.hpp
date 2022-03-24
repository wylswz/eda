#include<iostream>

using namespace std;

template<typename T>
class Sink {
public:
    virtual void Emit(T const & t);
};


template<typename T>
class Stdout_Sink : public Sink<T> {

public:
void Emit(T const & t) {
    cout<< t << endl;
}
};