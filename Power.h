//
// Created by carol on 25/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_1_POWER_H
#define PROGETTO_PROGRAMMAZIONE_1_POWER_H

#endif //PROGETTO_PROGRAMMAZIONE_1_POWER_H

class Power {
protected:
    int x;
    int y;
    char symbol;
    window *window;
 public:
    Power(int x, int y, char symbol)
    {
        this->x=x;
        this->y=y;
        this->symbol=symbol;
    }


      Power initializePower(Power* powers, Artifact artifact){
         int y, x;
         do{
         y = rand() % (getmaxy(window) - 2) +1;
         x=rand()%(getmaxx(window)-2) +1;
         }while(x!=artifact.getx()&&y!=artifact.gety)

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