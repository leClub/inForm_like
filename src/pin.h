#ifndef PIN_H
#define PIN_H

#include "ofMain.h"

class Pin
{
    public:
        void init(int _x, int _y);
        void update(int _z);
        void draw();

        int x;
        int y;
        int z;
};

#endif // PIN_H
