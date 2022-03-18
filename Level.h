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
    Level* nextLevel;
    Level* precLevel;

public:
    Level(int levelNumber){
        this->levelNumber = levelNumber;
        this->alreadyPassed = false;
        this->nextLevel = NULL;
        this->precLevel = NULL;
    }


};




#endif //PROGETTO_PROGRAMMAZIONE_LEVEL_H
