
#ifndef ARKANOID_PLAYERBAR_H
#define ARKANOID_PLAYERBAR_H
#include <SFML/Graphics.hpp>

using namespace sf;

//Class Playerbar Statement.
class Playerbar{
    //Private Variables.
        private:
            float highPLayerbar;
            float yPlayerbar;    //NOTE: Remains fixed.
            float velPlayerbar; //Playerbar Velocity.
            char direccion;     // Address in Which the Playerbar Moves. d: Right; i: Left.
            Sprite sPlayerbar;      // Playerbar Sprite.
            float longPlayerbar;            //Playerbar Length.

    //Public Variables.
        public:
            float xPlayerbar;
            Playerbar(float xPlayerbar, float yPlayerbar, Texture *texturaPlayerbar); //Builder
            ~Playerbar();                                                           //Destroyer.
            float mover(char direccion);
            float getLongX(Texture *texturaPlayerbar);                              //Returns the size in x of the Player
            void dibujar(RenderWindow *w);
            float getLongY(Texture *texturaPlayerbar);

};//End Playerbar Class.


#endif //ARKANOID_PLAYERBAR_H