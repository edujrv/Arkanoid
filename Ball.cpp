#include "Ball.h"

//Builder.
Ball::Ball(float xBall, float yBall, Texture *texturaBall) {

    sBall.setTexture(*texturaBall);   //Sprite Loading.
    sBall.setScale(0.7,0.7);  //Object Size.
    tBall = *texturaBall;

    //Initial Variables.
    this->xBall = xBall;
    this->yBall = yBall;
    velBall = 30;
    radioBall = 0;
    direccion = ' ';
    isDrew = false; // QUIERO CAMBIAR ESTE NOMBRE POR isPlaying o isAlive PERO NO ME DEJA EL CLION ASI QUE BUENO. ESTA VARIABLE QUIERE DECIR QUE SI LA PELOTA ESTA REBOTANDO POR LA PANTALLA O ESTA PEGADA A LA RAQUETA O MUERTA.

}//End Builder.



// moveBallWithPlayerbar
void Ball::moveBallWithPlayerbar(float  longBar, float  highBar, float xBar, float yBar) {

    float scale;
    scale = (float) (longBar * 0.2);
    xBall = xBar + (scale / 2) - ((Ball::getRadio(&tBall) * 0.7) / 2);
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




void Ball::move(float yButton) {
    if (isDrew){

        if(direccion){

            yBall -= 5;
            sBall.setPosition(xBall,yBall);

            // DEFAULT CONDITION
            if (yBall <= 0){
                direccion = false;
            }

            /*
             * INSERTAR CONDICION DE COLISIONES
             * */
        }else {

            yBall += 5;
            sBall.setPosition(xBall,yBall);

            //CONDICION DEFAULT
             if (yBall >= yButton){
                 direccion = true;
             }
            /*
             * INSERTAR CONDICION DE COLISIONES
             * */
        }
    }

}







//Destroyer.
Ball::~Ball() = default;
//End Destroyer.