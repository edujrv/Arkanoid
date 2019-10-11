#include "Ball.h"

//Builder.
Ball::Ball(float xBall, float yBall, Texture *texturaBall) {

    sBall.setTexture(*texturaBall);   //Sprite Loading.
    sBall.setScale(0.7,0.7);  //Object Size.

    //Initial Variables.
    this->xBall = xBall;
    this->yBall = yBall;
    velBall = 30;
    radioBall = 0;
    direccion = ' ';
    isDrew = false; // QUIERO CAMBIAR ESTE NOMBRE POR isPlaying o isAlive PERO NO ME DEJA EL CLION ASIQUE BUENO. ESTA VARIABLE QUIERE DECIR QUE SI LA PELOTA ESTA REBOTANDO POR LA PANTALLA O ESTA PEGADA A LA RAQUETA O MUERTA.
}//End Builder.



// moveBallWithPlayerbar
void Ball::moveBallWithPlayerbar(float  longBar, float  highBar, float xBar, float yBar) {

    float scale;
    scale = (float) (longBar * 0.2);
    xBall = xBar + (scale / 2);
    yBall = yBar - highBar;

}//End moveBallWithPlayerbar.



//Dibujar.
void Ball::draw(RenderWindow *w) {

    sBall.setPosition(xBall, yBall);     //Spray Position.
    w->draw(sBall);       //Drawing.

}//End Dibujar.




//getRadio.
float Ball::getRadio(Texture *texturaBall) {
    radioBall = texturaBall->getSize().x;
    return radioBall;
}
//End getRadio.




void Ball::move() {
    if (isDrew){

        if(direccion){
            sBall.setPosition(xBall,yBall);
            yBall -= 5;

            // DEFAULT CONDITION
            if (yBall <= 0){
                direccion = false;
            }

            /*
             * INSERTAR CONDICION DE COLISIONES
             * */
        }else {
            sBall.setPosition(xBall,yBall);
            yBall += 5;

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







//Destroyer.
Ball::~Ball() = default;
//End Destroyer.