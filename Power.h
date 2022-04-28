//
// Created by carol on 25/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_1_POWER_H
#define PROGETTO_PROGRAMMAZIONE_1_POWER_H

#endif //PROGETTO_PROGRAMMAZIONE_1_POWER_H

#include "Artifact.h"

class Power {
protected:
    int x;
    int y;
    char symbol;
    window *window;
    Power* next;
 public:
    Power(int x, int y, char symbol)
    {
        this->x=x;
        this->y=y;
        this->symbol=symbol;
    }


      Power* initializePower(Artifact* artifacts, Power* powers){
         int y, x;
         do{
         y = rand() % (getmaxy(window) - 2) +1;
         x=rand()%(getmaxx(window)-2) +1;
         }while(!checkPowerPosition(x,y,powers,artifacts);
        Power* tmp= new Power(x,y,'p');
         tmp->next=powers;
         return tmp;
     }
    bool checkPowerPosition(int x, int y, Power* p, Artifact* a){
        bool check=true;
        while(check&&a!=NULL){
            if(x==a->getx() && y==a->gety()){
                check=false;
            }
            a=a->next;

        }
        while (check && p!=NULL)
        {
            if(x==p->x x=p->x)
            {
                check=false;
            }
            p=p->next;
        }

        return check;
    }

    void printPower(){
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

};