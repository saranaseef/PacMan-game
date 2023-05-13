#ifndef GROUND_H
#define GROUND_H

#include <board.h>
class Ground  : public Board

{
    int  width, hieght;

public:
    Ground(int , int , QPixmap);
    Ground();
};

#endif // GROUND_H
