//
// Created by carol on 15/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_1_ARTIFACT_H
#define PROGETTO_PROGRAMMAZIONE_1_ARTIFACT_H


class Artifact {
protected:
    int lifepoint;
    int x;
    int y;
public:
    Artifact(int x, int y, int lifepoint){
        this->x=x;
        this->y=y;
        this->lifepoint=lifepoint;
        WINDOW *min;
    }
    void printarifact(){
        printf("a");
    }
int control()
{

}


};


#endif //PROGETTO_PROGRAMMAZIONE_1_ARTIFACT_H
