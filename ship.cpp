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

bool ship::askCoordinates() {
    cout << "Enter your coordinates for the beginning of the ship: " endl;
    cin >> start[0] >> start[1];
    cout << "Enter your coordinates for the ending of the ship: " endl;
    cin >> end[0] >> end[1];

    if(end[1] - start[1] > 3 || end[0] - start[0] > 3){
        cout << "Incorrect size, should be less than 5." endl;
        return false;
    }

    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(playerUI[start[0] + i][start[1] + j] == '*' || playerUI[end[0] + i][end[1] + j] == '*'){
                cout << "Incorrect coordinates, ships can't be next to each other." endl;
                return false;
            }
        }
    }

    if(start[0] != end[0] && start[1] != end[1]) {
        cout << "Incorect coordinates. Ship shouldn't be diagonal" endl;
        return false;
    }
    
    return true;
}

void ship::createShip(){
    int shipLength;
    if(start[0] == end[0]){ // добавить возможность изменить положение кораблей до битвы, почему то ставятся рядом, но не ставятся вдали друг от друга. 
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
    else if(start[1] == end[1]){
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

void ship::setUserShips(){ // 4 одинарных, 3 двойних, 2 тройных, 1 четверной
     // 0 - одинарн., 1 - двойн., 2 - тройн., 3 - четверн.
    char confirmation, choice;
    while(ships[0] != 0 || ships[1] != 0 || ships[2] != 0 || ships[3] != 0){
        printUI();
        cout << "What do you want to do? Place a ship (P), Delete a ship (D)." endl;
        cin >> choice;
        
        if(choice == 'P'){
            if(!askCoordinates()) {
                continue;
            }
            createShip();
        } 
        else if(choice == 'D'){
            if(!askCoordinates()) {
                continue;
            }
            deleteShip();
        } else{
            cout << "Only two choices available. Place a ship (P), Delete a ship (D)." endl;
        }
        

        // if(start[0] == end[0]){ // добавить возможность изменить положение кораблей до битвы, почему то ставятся рядом, но не ставятся вдали друг от друга. 
        //     shipLength = end[1] - start[1];
        //     if(ships[shipLength] > 0){
        //         if(shipLength >= 0) {
        //             for(int i = start[1]; i <= end[1]; i++){
        //                 playerUI[start[0]][i] = '*';
        //             } 
        //             ships[shipLength]--;
        //         } else if(shipLength < 0) {
        //             for(int i = start[1]; i >= end[1]; i--){  
        //                 playerUI[start[0]][i] = '*';
        //             }
        //             ships[abs(shipLength)]--;
        //         }
        //     } else{
        //         cout << "Maximum amount of this type of ships reached." endl;
        //     }
            
        // }
        // else if(start[1] == end[1]){
        //     shipLength = end[0] - start[0];
        //     if(ships[shipLength] > 0){
        //         if(shipLength >= 0) {
        //             for(int i = start[0]; i <= end[0]; i++){
        //                 playerUI[i][start[1]] = '*';
        //             }
        //             ships[shipLength]--;
        //         } else if(shipLength < 0) {
        //             for(int i = start[0]; i >= end[0]; i--){
        //                 playerUI[i][start[1]] = '*';
        //             }
        //             ships[shipLength]--;
        //         }
        //     } else{
        //         cout << "Maximum amount of this type of ships reached." endl;
        //     }
        // }
    }

    // printUI();
    // cout << "This is your final board, are you sure? (Y/N)" endl;
    // cin >> confirmation;
    // if(confirmation == 'Y'){
    //     cout << "Then let the battle begin!" endl;
    // }
    // else if(confirmation == 'N'){ // не удаляет корабль
    //     cout << "Enter the beginning coordinates of the ship you want to change: " endl;
    //     cin >> start[0] >> start[1];
    //     cout << "Enter the ending coordinates of the ship you want to change: " endl;
    //     cin >> end[0] >> end[1];
    //     if(start[0] == end[0]){
    //         shipLength = end[1] - start[1];
    //         // if(ships[shipLength] > 0){
    //             if(shipLength >= 0) {
    //                 for(int i = start[1]; i <= end[1]; i++){
    //                     if(playerUI[start[0]][i] == '*'){
    //                         cout << "if 1 passed" endl;
    //                         playerUI[start[0]][i] == ' ';
    //                         cout << "if finished" endl;
    //                     }
    //                 } 
    //                 ships[shipLength]++;
    //             } else if(shipLength < 0) {
    //                 for(int i = start[1]; i >= end[1]; i--){  
    //                     if(playerUI[start[0]][i] == '*'){
    //                         cout << "if 2 passed" endl;
    //                         playerUI[start[0]][i] = ' ';
    //                     }
    //                 }
    //                 ships[abs(shipLength)]++;
    //             }   else{
    //                     cout << "No ship found in set coordinates." endl;
    //                 } 
    //         // }
            
    //     }
    //     else if(start[1] == end[1]){
    //         shipLength = end[0] - start[0];
    //         // if(ships[shipLength] > 0){
    //             if(shipLength >= 0) {
    //                 for(int i = start[0]; i <= end[0]; i++){
    //                     if(playerUI[i][start[1]] == '*'){
    //                         cout << "if 3 passed" endl;
    //                         playerUI[i][start[1]] = ' ';
    //                     }
    //                 }
    //                 ships[shipLength]++;
    //             } else if(shipLength < 0) {
    //                 for(int i = start[0]; i >= end[0]; i--){
    //                     if(playerUI[i][start[1]] == '*'){
    //                         cout << "if 4 passed" endl;
    //                         playerUI[i][start[1]] = ' ';
    //                     }
    //                 }
    //                 ships[shipLength]++;
    //             }   else{
    //                     cout << "No ship found in set coordinates" endl;
    //                 }
    //         // } 
    //     } else{
    //         cout << "incorect coordinates. Ship shouldn't be diagonal" endl;
    //     }
    // }
    // else{
    //     cout << "Y or N!!!" endl;
    // }
}

void ship::askMove(){

}

void ship::makeMove(){

}

ship::ship(){
    generateFields();
    printUI();
    setUserShips();
    printUI();
    
// cout << botUI[3] << " "; // <- на основе этого переделать printUI
    
}


