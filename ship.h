#include <iostream>
#include <math.h>

using namespace std;
class ship{
    char playerUI[12][13];
    char botUI[12][13]; 
    int start[2], end[2];
    int ships[4] = {4, 3, 2, 1};
    bool askCoordinates();
    void generateFields();
    void createShip();
    void deleteShip();
    void printUI();
    void setUserShips();
    void askMove();
    void makeMove();
    public:
    ship();

};