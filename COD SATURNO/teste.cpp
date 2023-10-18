#include "sculptor.cpp"

int main(){
    Sculptor teste(50, 50, 50);
    teste.setColor(0.1, 0.6, 0.1, 1);
    teste.putBox(0, 9, 0, 9, 0, 9);
    teste.cutBox(6, 9, 6, 9, 6, 9);
    teste.cutEllipsoid(0, 0, 0, 2, 5, 4);

    teste.putSphere(20, 7, 7, 7);
    teste.cutSphere(20, 18, 18, 13);

    teste.putEllipsoid(40, 7, 7, 10, 3, 5);

    teste.writeOFF("teste.off");
}