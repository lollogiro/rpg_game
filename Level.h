//
// Created by lollo on 17/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_LEVEL_H
#define PROGETTO_PROGRAMMAZIONE_LEVEL_H


class Level {
public:
    int levelNumber;
    //Enemy* enemies;
    //Artifact* artifacts;
    //Power* powers;
    bool alreadyPassed;
    WINDOW* win;
    Level* nextLevel;
    Level* precLevel;

public:
    Level(int levelNumber, WINDOW* win){
        this->levelNumber = levelNumber;
        this->alreadyPassed = false;
        this->win = win;
        this->nextLevel = NULL;
        this->precLevel = NULL;
    }

    void printDoor(char* doorString){
        int startPosition = ((getmaxx(win)-2)/2)-2;
        int endPosition = ((getmaxx(win)-2)/2)+3;
        for (int i = startPosition; i <= endPosition; ++i) {
            mvwaddch(win, 0, i, doorString[i-startPosition]);
        }
    }

};




#endif //PROGETTO_PROGRAMMAZIONE_LEVEL_H
