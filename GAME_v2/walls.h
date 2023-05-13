#ifndef WALLS_H
#define WALLS_H

#include "board.h"

class Walls :public Board

{    int  width, hieght;


public:
     Walls();
     Walls( int w , int h , QPixmap qpixmap);

};

#endif // WALLS_H
