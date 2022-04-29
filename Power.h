//
// Created by carol on 25/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_1_POWER_H
#define PROGETTO_PROGRAMMAZIONE_1_POWER_H

#endif //PROGETTO_PROGRAMMAZIONE_1_POWER_H

#include "Artifact.h"

class Power {
protected:
    int posX;
    int posY;
    char symbol;
    WINDOW *win;
    Power* next;
 public:
    Power(int posX, int posY, char symbol)
    {
        this->posX=posX;
        this->posY=posY;
        this->symbol=symbol;
    }


      Power* initializePower(Artifact* artifacts, Power* powers,WINDOW *win){
         int posYNew, posXNew;
         do{
         y = rand() % (getmaxy(win) - 2) +1;
         x=rand()%(getmaxx(win)-2) +1;
         }while(!checkPowerPosition(posXNew,posYNew,powers,artifacts);
        Power* tmp= new Power(posXNew,posYNew,'p');
         tmp->next=powers;
         return tmp;
     }
    bool checkPowerPosition(int posXPower, int posYPower, Power* powers, Artifact* artifacts){
        bool check=true;
        while(check&&a!=NULL){
            if(posX==artifacts->getx() && posY==artifacts->gety()){
                check=false;
            }
            artifacts=artifacts->next;

        }
        while (check && powers!=NULL)
        {
            if(posXPower==powers->posX && posYPower=powers->posY)
            {
                check=false;
            }
            powers=powers->next;
        }

        return check;
    }

    void printPower(){
        mvwddch(win, posY, posX, symbol);
        wrefresh(win);
    }

     char getsymbol const {
         return symbol;
     }
     int getPosX const{
         return posX;
     }
     int getPosY const{
         return posY;
     }

};