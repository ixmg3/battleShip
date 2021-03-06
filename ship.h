#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
class ship{
    char playerUI[12][13];
    char botUI[12][13];
    char shipBotUI[12][13]; 
    int start[2], end[2];
    int ships[4] = {4, 3, 2, 1};
    int botShips[4] = {4, 3, 2, 1};
    string shipDirection = "horizontal";
    int shipLength, userHitCounter = 0, botHitCounter = 0, direction;

    void assignBotCoords(int displace0, int displace1);
    void setBotShips(int shipAmount);
    void setShipDirection();
    bool askCoordinates(char choice);
    void generateFields();
    bool botShipCoordsChecker();
    void generateBotCoords();
    void createBotShip();
    void createShip();
    void deleteShip();
    void printUI();
    void setUserShips();
    void userMove();
    void botMove();
    bool fieldStatusCheck();
    public:
    ship();

};