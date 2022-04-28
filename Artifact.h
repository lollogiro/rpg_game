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
        this->symbol=symbol;
        this->x=x;
        this->y=y;
        this->lifepoint=lifepoint;
    }


    Artifact* initializeArtifact(Artifact* artifacts){
        int y, x;
        do {
            y = rand() % (getmaxy(window) - 2) + 1;
            x = rand() % (getmaxx(window) - 2) + 1;
        }while(!checkArtifactPosition(x,y,artifacts);
        Artifact* tmp= new Artifact(x,y,'a');
        tmp->next= artifacts;
        return tmp;
    }

    bool checkArtifactPosition(int x, int y, Artifact* a){
        bool check=true;
        while(check && a!NULL){
            if(x==a->x && y==a->y){
                check=false;
            }
            a=a->next;

        }
        return check;
    }

    void printArtifact(){
        mvwddch(window ,y, x, symbol);
        wrefresh(window);
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
