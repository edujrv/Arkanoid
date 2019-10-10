#include "Ball.h"

//Builder.
Ball::Ball(float xBall, float yBall, Texture *texturaBall) {
    //Sprite Loading.
    sBall.setTexture(*texturaBall);
    //Object Size.
    sBall.setScale(0.7,0.7);

    //Initial Variables.
    this->xBall = xBall;
    this->yBall = yBall;
    velBall = 30;
    radioBall = 0;
    direccion = ' ';
}//End Builder.

//Dibujar.
void Ball::dibujar(RenderWindow *w) {
    //Spray Position.
    sBall.setPosition(xBall, yBall);
    //Drawing.
    w->draw(sBall);

}//End Dibujar.

//getLongX.
float Ball::getLongX(Texture *texturaBall) {
    radioBall = texturaBall->getSize().x;
    return radioBall;
}
//End getLongX.

// Mover
float Ball::moverBall(char direccion,float xPlayerbar) {
    //Actions for d and i.
    this->direccion = direccion;
    if (direccion == 'd'){
        xBall += xPlayerbar/21;
    }else if (direccion == 'i') {
        xBall -= xPlayerbar/21;
    }//End ElseIf.
    //Returns new playerbar position.
    return xBall;
}//End Mover.


void Ball::drawBall(RenderWindow *w) {
    if (isDrew){

        if(direccion){
            sBall.setPosition(xBall,yBall);
            yBall -= 5;
            w->draw(sBall);
                // CONDICION DEFAULT
                if (yBall <= 0){
                    direccion = false;
                }

            /*
             * INSERTAR CONDICION DE COLISIONES
             * */
        }else {
            sBall.setPosition(xBall,yBall);
            yBall += 5;
            w->draw(sBall);
            //CONDICION DEFAULT
           /* if (yBall <= VideoMode::getDesktopMode().height - 100.0){
                direccion = false;
            }*/
            /*
             * INSERTAR CONDICION DE COLISIONES
             * */
        }
    }

}








//End isBallDrawn.





//Destroyer.
Ball::~Ball() = default;
//End Destroyer.