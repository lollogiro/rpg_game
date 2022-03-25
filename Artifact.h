//
// Created by carol on 15/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_1_ARTIFACT_H
#define PROGETTO_PROGRAMMAZIONE_1_ARTIFACT_H

#include <curses.h>
#include <stdlib.h>

class Artifact {
protected:
    char symbol;
    int lifepoint;
    int x;
    int y;
    window *window;
    Artifact* next;

public:
    Artifact(int x, int y, int lifepoint, char symbol){
        this->symbol,symbol);
        this->x=x;
        this->y=y;
        this->lifepoint=lifepoint;
    }
    void printArtifact(){
        mvwddch(window ,y, x, symbol);
        wrefresh(window);
    }

    Artifact initializeArtifact(Artifact* artifacts){
        int y, x;

        y = rand() % (getmaxy(window) - 2) +1;
        x=rand()%(getmaxx(window)-2) +1;

    }


 char getsymbol const {
        return symbol;
    }
int getx const{
    return x;
}
 int gety const{
     return y;
 }
  int getlifepoint const{
      return lifepoint;
  }

};


#endif //PROGETTO_PROGRAMMAZIONE_1_ARTIFACT_H
