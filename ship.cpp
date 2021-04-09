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
    cout << "   12345678910\t \t   12345678910" endl;
    for(int i = 0; i < 12; i++){
        cout << i;
        if(i < 10){
            cout << " ";
        }
        cout << playerUI[i] << "\t \t" << i;
        if(i < 10){
            cout << " ";
        }
        cout << botUI[i] endl;
        // cout << i << playerUI[i] << "\t \t" << i << botUI[i] endl;
    }
}

void ship::setShipDirection() {
    if(start[0] == end[0]) {
        shipDirection = "horizontal";
        return;
    }
    shipDirection = "vertical";
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
    } else if(choice == 'D'){ 
        if(shipDirection == "horizontal") {
            for(int i = start[1]; i <= end[1]; i++) {
                if(playerUI[start[0] + 1][i] == '*' || playerUI[start[0] - 1][i] == '*'){
                    cout << "Can't delete a part of the ship" endl;
                    return false;
                }
                if(playerUI[start[0]][i] != '*') {
                    cout << "Incorrect coordinates, there is no ships!" endl;
                    return false;
                }
            }
        } else if(shipDirection == "vertical") {
            for(int i = start[0]; i <= end[0]; i++) {
                if(playerUI[i][start[1] + 1] == '*' || playerUI[i][start[1] - 1] == '*'){
                    cout << "Can't delete a part of the ship asd" endl;
                    return false;
                }
                if(playerUI[i][start[1]] != '*') {
                    cout << "Incorrect coordinates, there is no ships!" endl;
                    return false;
                }
            }
        }
    }
    
    return true;
}

bool ship::botShipCoordsChecker(){
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(botUI[start[0] + i][start[1] + j] == '*' || botUI[end[0] + i][end[1] + j] == '*' || start[0] < 1 || start[0] > 10 || start[1] < 1 || start[1] > 10 || end[0] < 1 || end[0] > 10 || end[1] < 1 || end[1] > 10){
                cout << "worked" endl;
                return true;
            }
        }
    }
    return false;
}

void ship::generateBotCoords(){
    int direction, shipType;

    
    
    for(int i = 0; i < 4; i++){
        cout << i endl;
        start[0] = rand()%10 + 1;
        start[1] = rand()%10 + 1;
        end[0] = start[0];
        end[1] = start[1];
        if(botShipCoordsChecker()){
            i--;
            cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 1" endl; 
        } else{
            createBotShip();
        }
        printUI();
    }
    
    for(int i = 0; i < 3; i++){
        direction = rand()%5 + 1;
        switch(direction){
            case 1: // up
                shipDirection = "vertical";
                start[0] = rand()%10 + 1;
                start[1] = rand()%10 + 1;
                end[0] = start[0] - 1;
                end[1] = start[1];
                if(botShipCoordsChecker()){
                    i--;
                    cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 2" endl; 
                } else{
                    createBotShip();
                }
                break;
            case 2: // down
                shipDirection = "vertical";
                start[0] = rand()%10 + 1;
                start[1] = rand()%10 + 1;
                end[0] = start[0] + 1;
                end[1] = start[1];
                if(botShipCoordsChecker()){
                    i--;
                    cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 2" endl; 
                } else{
                    createBotShip();
                }
                break;
            case 3: // left
                shipDirection = "horizontal";
                start[0] = rand()%10 + 1;
                start[1] = rand()%10 + 1;
                end[0] = start[0];
                end[1] = start[1] - 1;
                if(botShipCoordsChecker()){
                    i--;
                    cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 2" endl; 
                } else{
                    createBotShip();
                }
                break;
            case 4: // right
                shipDirection = "horizontal";
                start[0] = rand()%10 + 1;
                start[1] = rand()%10 + 1;
                end[0] = start[0];
                end[1] = start[1] + 1;
                if(botShipCoordsChecker()){
                    i--;
                    cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 2" endl; 
                } else{
                    createBotShip();
                }
                break;
        }
        printUI();
    }
    
    for(int i = 0; i < 2; i++){
        direction = rand()%5 + 1;
        switch(direction){
            case 1: // up
                shipDirection = "vertical";
                start[0] = rand()%10 + 1;
                start[1] = rand()%10 + 1;
                end[0] = start[0] - 2;
                end[1] = start[1];
                if(botShipCoordsChecker()){
                    i--;
                    cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 3" endl; 
                } else{
                    createBotShip();
                }
                break;
            case 2: // down
                shipDirection = "vertical";
                start[0] = rand()%10 + 1;
                start[1] = rand()%10 + 1;
                end[0] = start[0] + 2;
                end[1] = start[1];
                if(botShipCoordsChecker()){
                    i--;
                    cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 3" endl; 
                } else{
                    createBotShip();
                }
                break;
            case 3: // left
                shipDirection = "horizontal";
                start[0] = rand()%10 + 1;
                start[1] = rand()%10 + 1;
                end[0] = start[0];
                end[1] = start[1] - 2;
                if(botShipCoordsChecker()){
                    i--;
                    cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 3" endl; 
                } else{
                    createBotShip();
                }
                break;
            case 4: // right
                shipDirection = "horizontal";
                start[0] = rand()%10 + 1;
                start[1] = rand()%10 + 1;
                end[0] = start[0];
                end[1] = start[1] + 2;
                if(botShipCoordsChecker()){
                    i--;
                    cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 3" endl; 
                } else{
                    createBotShip();
                }
                break;
        }
        printUI();
    }
    
    direction = rand()%5 + 1;
    for(int i = 0; i < 1; i++){
    switch(direction){
        case 1: // up
            shipDirection = "vertical";
            start[0] = rand()%10 + 1;
            start[1] = rand()%10 + 1;
            end[0] = start[0] - 3;
            end[1] = start[1];
            if(botShipCoordsChecker()){
                i--;
                cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 4" endl; 
            } else{
                createBotShip();
            }
            break;
        case 2: // down
            shipDirection = "vertical";
            start[0] = rand()%10 + 1;
            start[1] = rand()%10 + 1;
            end[0] = start[0] + 3;
            end[1] = start[1];
            if(botShipCoordsChecker()){
                i--;
                cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 4" endl; 
            } else{
                createBotShip();
            }
            break;
        case 3: // left
            shipDirection = "horizontal";
            start[0] = rand()%10 + 1;
            start[1] = rand()%10 + 1;
            end[0] = start[0];
            end[1] = start[1] - 3;
            if(botShipCoordsChecker()){
                i--;
                cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 4" endl; 
            } else{
                createBotShip();
            }
            break;
        case 4: // right
            shipDirection = "horizontal";
            start[0] = rand()%10 + 1;
            start[1] = rand()%10 + 1;
            end[0] = start[0];
            end[1] = start[1] + 3;
            if(botShipCoordsChecker()){
                i--;
                cout << "Coords: " << start[0] << " " << start[1] << " " << end[0] << " " << end[1] endl << "Ship type: 4" endl; 
            } else{
                createBotShip();
            }
            break;
    }
    printUI();
    }
    
    
}
void ship::createBotShip(){
    if(shipDirection == "horizontal"){ 
        shipLength = end[1] - start[1];
        if(botShips[shipLength] > 0){
            if(shipLength >= 0) {
                for(int i = start[1]; i <= end[1]; i++){
                    botUI[start[0]][i] = '*';
                } 
                botShips[shipLength]--;
            } else if(shipLength < 0) {
                for(int i = start[1]; i >= end[1]; i--){  
                    botUI[start[0]][i] = '*';
                }
                botShips[abs(shipLength)]--;
            }
        } else{
            cout << "Maximum amount of this type of ships reached." endl;
        }
        
    }
    else if(shipDirection == "vertical"){
        shipLength = end[0] - start[0];
        if(botShips[shipLength] > 0){
            if(shipLength >= 0) {
                for(int i = start[0]; i <= end[0]; i++){
                    botUI[i][start[1]] = '*';
                }
                botShips[shipLength]--;
            } else if(shipLength < 0) {
                for(int i = start[0]; i >= end[0]; i--){
                    botUI[i][start[1]] = '*';
                }
                botShips[shipLength]--;
            }
        } else{
            cout << "Maximum amount of this type of ships reached." endl;
        }
    }
}

void ship::createShip(){
    if(shipDirection == "horizontal"){ 
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
    else if(shipDirection == "vertical"){
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
    if(shipDirection == "horizontal"){ 
        shipLength = end[1] - start[1];
        if(ships[shipLength] < 4 - shipLength){
            if(shipLength >= 0) {
                for(int i = start[1]; i <= end[1]; i++){
                    playerUI[start[0]][i] = ' ';
                } 
                ships[shipLength]++;
            } else if(shipLength < 0) {
                for(int i = start[1]; i >= end[1]; i--){  
                    playerUI[start[0]][i] = ' ';
                }
                ships[abs(shipLength)]++;
            }
        } else{
            cout << "No ships of that type on the board." endl;
        }
        
    }
    else if(shipDirection == "vertical"){
        shipLength = end[0] - start[0];
        if(ships[shipLength] < 4 - shipLength){
            if(shipLength >= 0) {
                for(int i = start[0]; i <= end[0]; i++){
                    playerUI[i][start[1]] = ' ';
                }
                ships[shipLength]++;
            } else if(shipLength < 0) {
                for(int i = start[0]; i >= end[0]; i--){
                    playerUI[i][start[1]] = ' ';
                }
                ships[shipLength]++;
            }
        } else{
            cout << "No ships of that type on the board." endl;
        }
    }
}

bool ship::fieldStatusCheck(){
    char status;
    if(!(ships[0] != 0 || ships[1] != 0 || ships[2] != 0 || ships[3] != 0)){
        printUI();
        cout << "Is this your final field? (Y/N)" endl;
        cin >> status;
        if(status == 'Y'){
            return false;
        } 
    }
    return true;
}

void ship::setUserShips(){      // 4 одинарных, 3 двойних, 2 тройных, 1 четверной
    char choice;                // 0 - одинарн., 1 - двойн., 2 - тройн., 3 - четверн.
    while(fieldStatusCheck()){ // добавить подтверждение к завершению расстановки
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
    srand(time(0));
    generateFields();
    // setUserShips();
    printUI();    
    generateBotCoords();
    for(int i = 0; i < 4; i++){
        cout << botShips[i] << " ";
    }
    cout endl;
}


