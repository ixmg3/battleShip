#include <iostream>
#include <math.h>

using namespace std;
class ship{
    char playerUI[12][13];
    char botUI[12][13]; 
    void generateFields();
    void printUI();
    void setUserShips();
    void askMove();
    void makeMove();
    public:
    ship();

};