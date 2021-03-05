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

void ship::setUserShips(){ // 4 одинарных, 3 двойних, 2 тройных, 1 четверной
    int start[2], end[2], ships[4] = {4, 3, 2, 1}, shipLength; // 0 - одинарн., 1 - двойн., 2 - тройн., 3 - четверн.
    while(ships[0] != 0 || ships[1] != 0 || ships[2] != 0 || ships[3] != 0){
        printUI();
        cout << "Enter your coordinates for the beginning of the ship: " endl;
        cin >> start[0] >> start[1];
        // if(playerUI[start[0] - 1][start[1]] == '*' || playerUI[start[0] + 1][1] == '*' || playerUI[start[1] - 1][1] == '*' || playerUI[start[1] + 1][1] == '*' || playerUI[start[0] - 1][start[1] - 1] == '*' || playerUI[start[0] + 1][start[1] - 1] == '*' || playerUI[start[0] - 1][start[1] + 1] == '*' || playerUI[start[0] + 1][start[1] + 1] == '*'){
        //     cout << "Incorrect coordinates, ships can't be next to each other." endl;
        // }
        cout << "Enter your coordinates for the ending of the ship: " endl;
        cin >> end[0] >> end[1];
        // if(playerUI[end[0] - 1][end[1]] == '*' || playerUI[end[0] + 1][end[1]] == '*' || playerUI[end[0]][end[1] - 1] == '*' || playerUI[end[0]][end[1] + 1] == '*' || playerUI[end[0] - 1][end[1] - 1] == '*' || playerUI[end[0] + 1][end[1] - 1] == '*' || playerUI[end[0] - 1][end[1] + 1] == '*' || playerUI[end[0] + 1][end[1] + 1] == '*'){
        //     cout << "Incorrect coordinates, ships can't be next to each other." endl;
        // }
        // playerUI[start[0]][start[1]] = '*';
        if(end[1] - start[1] > 3 || end[0] - start[0] > 3){
            cout << "Incorrect size, should be less than 5." endl;
            continue;
        }
        if(start[0] == end[0]){ // добавить возможность изменить положение кораблей до битвы, добавить проверки.
            shipLength = end[1] - start[1];
            if(ships[shipLength] > 0){
                for(int i = start[1]; i <= end[1]; i++){
                    playerUI[start[0]][i] = '*';
                } 
                ships[shipLength]--;
            } else{
                cout << "Maximum amount of this type of ships reached." endl;
            }
            
        }
        else if(start[1] == end[1]){
            shipLength = end[0] - start[0];
            if(ships[shipLength] > 0){
                for(int i = start[0]; i <= end[0]; i++){
                    playerUI[i][start[1]] = '*';
                }
                ships[shipLength]--;
            } else{
                cout << "Maximum amount of this type of ships reached." endl;
            }
        } else{
            cout << "incorect coordinates. Ship shouldn't be diagonal" endl;
        }
    }
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


