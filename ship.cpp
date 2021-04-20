#include "ship.h"
#define endl << endl

void ship::assignBotCoords(int displace0, int displace1){
    start[0] = rand()%10 + 1;
    start[1] = rand()%10 + 1;
    end[0] = start[0] + displace0;
    end[1] = start[1] + displace1;
}

void ship::setBotShips(int shipAmount){
    int displaceCalc = 4 - shipAmount;
    for(int i = 0; i < shipAmount; i++){
        direction = rand()%4 + 1;
        switch(direction){
            case 1: // up
                shipDirection = "vertical";
                assignBotCoords(-1 * displaceCalc, 0);
                if(botShipCoordsChecker()){
                    i--;
                } else{
                    createBotShip();
                } 
                
                break;
            case 2: // down
                shipDirection = "vertical";
                assignBotCoords(displaceCalc, 0);
                if(botShipCoordsChecker()){
                    i--;
                } else{
                    createBotShip();
                }
                break;
            case 3: // left
                shipDirection = "horizontal";
                assignBotCoords(0, -1 * displaceCalc);
                if(botShipCoordsChecker()){
                    i--; 
                } else{
                    createBotShip();
                }
                break;
            case 4: // right
                shipDirection = "horizontal";
                assignBotCoords(0, displaceCalc);
                if(botShipCoordsChecker()){
                    i--;
                } else{
                    createBotShip();
                }
                break;
        }
    }
}

void ship::generateFields(){ // добавить цифры у сторон поля
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 13; j++){
            playerUI[i][j] = '#';
            botUI[i][j] = '#';
            shipBotUI[i][j] = '#';
            if(j > 0 && j < 11 && i > 0 && i < 11){
                playerUI[i][j] = ' ';
                botUI[i][j] = ' ';
                shipBotUI[i][j] = ' ';
            }
            if(j == 12){
                playerUI[i][j] = '\0';
                botUI[i][j] = '\0';
                shipBotUI[i][j] = '\0';
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
        cout << botUI[i];
        // cout << shipBotUI[i];
        // разкоментировать это ^ для того чтобы видеть поле бота
        cout endl;
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
            if(shipBotUI[start[0] + i][start[1] + j] == '*' || shipBotUI[end[0] + i][end[1] + j] == '*' || start[0] < 1 || start[0] > 10 || start[1] < 1 || start[1] > 10 || end[0] < 1 || end[0] > 10 || end[1] < 1 || end[1] > 10){
                return true;
            }
        }
    }
    return false;
}

void ship::generateBotCoords(){ // ограничение во время генераци карты бота (потом)
    for(int i = 4; i > 0; i--){
        setBotShips(i);
    }
}

void ship::createBotShip(){
    if(shipDirection == "horizontal"){ 
        shipLength = end[1] - start[1];
        int shipLength2 = abs(shipLength);
        if(botShips[shipLength2] > 0){
            if(shipLength >= 0) {
                for(int i = start[1]; i <= end[1]; i++){
                    shipBotUI[start[0]][i] = '*';
                } 
                botShips[shipLength]--;
            } else if(shipLength < 0) {
                for(int i = start[1]; i >= end[1]; i--){  
                    shipBotUI[start[0]][i] = '*';
                }
                botShips[-(shipLength)]--;
            }
        } else{
            cout << "Maximum amount of this type of ships reached. (bot, horiz)" endl;
        }
        
    }
    else if(shipDirection == "vertical"){
        shipLength = end[0] - start[0];
        int shipLength3 = abs(shipLength);
        if(botShips[shipLength3] > 0){
            if(shipLength >= 0) {
                for(int i = start[0]; i <= end[0]; i++){
                    shipBotUI[i][start[1]] = '*';
                }
                botShips[shipLength]--;
            } else if(shipLength < 0) {
                for(int i = start[0]; i >= end[0]; i--){
                    shipBotUI[i][start[1]] = '*';
                }
                botShips[-(shipLength)]--;
            }
        } else{
            cout << "Maximum amount of this type of ships reached. (bot), vertic" endl;
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
            cout << "Maximum amount of this type of ships reached. (user)" endl;
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
            cout << "Maximum amount of this type of ships reached. (user)" endl;
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

void ship::userMove(){
    int attackY, attackX;
    cout << "Enter the firing coordinates: " endl;
    cin >> attackY >> attackX;
    if(botUI[attackY][attackX] == '.' || botUI[attackY][attackX] == 'X'){
        cout << "You already fired in these coordiantes." endl;
        userMove();
        return;
    }
    if(shipBotUI[attackY][attackX] == '*'){
        if(shipBotUI[attackY - 1][attackX] == '*' || shipBotUI[attackY + 1][attackX] == '*' || shipBotUI[attackY][attackX + 1] == '*' || shipBotUI[attackY][attackX - 1] == '*'){
            cout << "It's a hit!" endl;
        } else{
            cout << "It's a kill!" endl;
        }
        userHitCounter++;
        botUI[attackY][attackX] = 'X';
        shipBotUI[attackY][attackX] = 'X';
    } else{
        cout << "It's a miss!" endl;
        botUI[attackY][attackX] = '.';
        shipBotUI[attackY][attackX] = '.';
    }
}

void ship::botMove(){
    int botAttackY, botAttackX;
    do{
        botAttackY = rand()%10 + 1;
        botAttackX = rand()%10 + 1;
    }
    while(playerUI[botAttackY][botAttackX] == '.' || playerUI[botAttackY][botAttackX] == 'X');
    cout << botAttackY << " " << botAttackX endl;
    if(playerUI[botAttackY][botAttackX] == '*'){
        botHitCounter++;
        cout << "The enemy hit you!" endl;
        playerUI[botAttackY][botAttackX] = 'X';
    } else{
        cout << "The enemy missed!" endl;
        playerUI[botAttackY][botAttackX] = '.';
    }
}

void ship::setUserShips(){      // 4 одинарных, 3 двойних, 2 тройных, 1 четверной
    char choice;                // 0 - одинарн., 1 - двойн., 2 - тройн., 3 - четверн.
    while(fieldStatusCheck()){ 
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

ship::ship(){ 
    srand(time(0));
    generateFields();
    setUserShips();
    printUI();    
    generateBotCoords();
    while(userHitCounter < 20 && botHitCounter < 20){
        printUI();
        userMove();
        botMove();
        printUI();
    }
    if(userHitCounter == 20){
        cout << "You Win!" endl;
    } else{
        cout << "Your enemy won." endl;
    }
}