#include "pin.h"

void Pin::init(int _x, int _y){
    x = _x;
    y = _y;
    z = 0;
}

void Pin::update(int _z){
    z = _z;
}

void Pin::draw(){
}
