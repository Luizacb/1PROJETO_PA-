#include "sculptor.cpp"
#include <math.h>

void putRing(Sculptor* arte, int xcenter, int ycenter, int zcenter, int radius, int thickness){
    for (int x = xcenter - radius; x < xcenter + radius; x++){
        for (int z = ycenter - radius; z < zcenter + radius; z++){
            if ((pow(radius - thickness, 2) <= pow(x - xcenter, 2) + pow(z - zcenter, 2)) && (pow(x - xcenter, 2) + pow(z - zcenter, 2) < pow(radius, 2))){
                (*arte).putVoxel(x, ycenter, z);
            }
        }
    }
}

void buildSaturn(Sculptor* arte, int x, int y, int z){
    (*arte).setColor(0.5, 0.3, 0, 1);
    (*arte).putSphere(x, y, z, 42);
    (*arte).cutSphere(x, y, z, 40);

    (*arte).setColor(0.8, 0.55, 0, 1);
    putRing(arte, x, y, z, 99, 10);
    
    (*arte).setColor(0.5, 0.3, 0, 1);
    putRing(arte, x, y, z, 85, 4);
    
    (*arte).setColor(0.8, 0.55, 0, 1);
    putRing(arte, x, y, z, 77, 5);

    (*arte).setColor(0.5, 0.3, 0, 1);
    putRing(arte, x, y, z, 72, 4);
    putRing(arte, x, y, z, 66, 2);
    
    (*arte).setColor(0.8, 0.55, 0, 1);
    putRing(arte, x, y, z, 64, 5);
}

void addStars(Sculptor* arte, int tamx, int tamy, int tamz, int n){
    int x, y, z;
    for (int i = 0; i < n; i++){
        x = tamx*((float) rand() / RAND_MAX);
        y = tamy*((float) rand() / RAND_MAX);
        z = tamz*((float) rand() / RAND_MAX);
        (*arte).setColor(1, 1, 1, 1);
        (*arte).putVoxel(x, y, 0);
        (*arte).putVoxel(0, y, z);
        (*arte).putVoxel(x, 0, z);
    }
}

int main(){

    Sculptor arte(400, 400, 400);
    buildSaturn(&arte, 100, 100, 100);
    addStars(&arte, 200, 200, 200, 100);

    arte.writeOFF("saturno.off");

}