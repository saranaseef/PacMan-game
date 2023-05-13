#ifndef HOME_H
#define HOME_H

#include <board.h>
class Home:public Board
{
public:
    int  width, hieght;
    Home();
    Home(int w , int h , QPixmap qpixmap);
};

#endif // HOME_H
