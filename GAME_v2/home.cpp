#include "home.h"

Home::Home()
{

}
Home::Home(int w , int h , QPixmap qpixmap) : Board  (qpixmap)
{
    width = w;
    hieght = h;
}
