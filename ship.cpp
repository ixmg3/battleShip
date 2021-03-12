#include "ship.h"
#define endl << endl

void ship::generateFields(){ // добавить цифры у сторон поля
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 13; j++){
            playerUI[i][j] = '#';
            botUI[i][j] = '#';
            if(j > 0 && j < 11 && i > 0 && i < 11){
                playerUI[i][j] = ' ';
                botUI[i][j] = ' ';
            }
            if(j == 12){
                playerUI[i][j] = '\0';
                botUI[i][j] = '\0';
            }
        }
    }
}

void ship::printUI(){
    for(int i = 0; i < 12; i++){
        cout << playerUI[i] << "\t \t" << botUI[i] endl;
    }
}

void ship::setShipDirection() {
    if(start[0] == end[0]) {
        shipDirectin = "horizontal";
    }
    shipDirectin = "vertical";
}

bool ship::askCoordinates(char choice) {
    cout << "Enter your coordinates for the beginning of the ship: " endl;
    cin >> start[0] >> start[1];
    cout << "Enter your coordinates for the ending of the ship: " endl;
    cin >> end[0] >> end[1];

    if(end[1] - start[1] > 3 || end[0] - start[0] > 3){
        cout << "Incorrect size, should be less than 5." endl;
        return false;
    }

    if(start[0] != end[0] && start[1] != end[1]) {
        cout << "Incorect coordinates. Ship shouldn't be diagonal" endl;
        return false;
    }

    setShipDirection();

    if(choice == 'P') {
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if(playerUI[start[0] + i][start[1] + j] == '*' || playerUI[end[0] + i][end[1] + j] == '*'){
                    cout << "Incorrect coordinates, ships can't be next to each other." endl;
                    return false;
                }
            }
        }
    } else {
        if(shipDirectin == "horizontal") {
            for(int i = start[1]; i <= end[1]; i++) {
                if(playerUI[start[0]][i] != '*') {
                    cout << "Incorrect coordinates, there is no ships!" endl;
                    return false;
                }
            }
        } else if(shipDirectin == "vertical") {
            for(int i = start[0]; i <= end[0]; i++) {
                if(playerUI[i][start[1]] != '*') {
                    cout << "Incorrect coordinates, there is no ships!" endl;
                    return false;
                }
            }
        }
    }
    
    return true;
}

void ship::createShip(){
    if(shipDirectin == "horizontal"){ // добавить возможность изменить положение кораблей до битвы, почему то ставятся рядом, но не ставятся вдали друг от друга. 
        shipLength = end[1] - start[1];
        if(ships[shipLength] > 0){
            if(shipLength >= 0) {
                for(int i = start[1]; i <= end[1]; i++){
                    playerUI[start[0]][i] = '*';
                } 
                ships[shipLength]--;
            } else if(shipLength < 0) {
                for(int i = start[1]; i >= end[1]; i--){  
                    playerUI[start[0]][i] = '*';
                }
                ships[abs(shipLength)]--;
            }
        } else{
            cout << "Maximum amount of this type of ships reached." endl;
        }
        
    }
    else if(shipDirectin == "vertical"){
        shipLength = end[0] - start[0];
        if(ships[shipLength] > 0){
            if(shipLength >= 0) {
                for(int i = start[0]; i <= end[0]; i++){
                    playerUI[i][start[1]] = '*';
                }
                ships[shipLength]--;
            } else if(shipLength < 0) {
                for(int i = start[0]; i >= end[0]; i--){
                    playerUI[i][start[1]] = '*';
                }
                ships[shipLength]--;
            }
        } else{
            cout << "Maximum amount of this type of ships reached." endl;
        }
    }
}

void ship::deleteShip(){

}

void ship::setUserShips(){      // 4 одинарных, 3 двойних, 2 тройных, 1 четверной
    char choice;                // 0 - одинарн., 1 - двойн., 2 - тройн., 3 - четверн.
    while(ships[0] != 0 || ships[1] != 0 || ships[2] != 0 || ships[3] != 0){
        printUI();
        cout << "What do you want to do? Place a ship (P), Delete a ship (D)." endl;
        cin >> choice;
        
        if(choice == 'P'){
            if(!askCoordinates(choice)) {
                continue;
            }
            createShip();
        } 
        else if(choice == 'D'){
            if(!askCoordinates(choice)) {
                continue;
            }
            deleteShip();
        } else{
            cout << "Only two choices available. Place a ship (P), Delete a ship (D)." endl;
        }
    }
}

void ship::askMove(){

}

void ship::makeMove(){

}

ship::ship(){
    generateFields();
    setUserShips();
    printUI();    
}


