//
// Created by carol on 15/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_1_ARTIFACT_H
#define PROGETTO_PROGRAMMAZIONE_1_ARTIFACT_H


class Artifact {
protected:
    char symbol;
    int lifepoint;
    int x;
    int y;
public:
    Artifact(int x, int y, int lifepoint, char symbol){
        strcpy(this->symbol,symbol);
        this->x=x;
        this->y=y;
        this->lifepoint=lifepoint;
        WINDOW *win;
    }
    void printarifact(){
        mvwddch(win ,y, x, symbol);
        wrefresh(win);
    }
int control()
{

}
 char getsymbol const {
        return symbol;
    }
int getx const{
    return x;
}
 int gety const{
     return y
 }
  int getlifepoint const{
      return lifepoint;
  }

};


#endif //PROGETTO_PROGRAMMAZIONE_1_ARTIFACT_H
