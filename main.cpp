#include <iostream>
#include <SFML/Graphics.hpp>
#include "Playerbar.h"
#include "Ball.h"

using namespace sf;

//Beginning of Main.
int main() {
    //Variables.

    //Main Windows Dimensions.
    unsigned int windowHigh=1366u; //1920u (valores felipe)
    unsigned int windowWidth=768u; //1080u (valores felipe)

    //Window Loading.
    RenderWindow w(VideoMode::getDesktopMode(), "Breaking Bricks");


    //Initial Object Positions.
    //--->//Playerbar:
    int xPlayerbar= (w.getSize().x/2)-60.0, yPlayerbar= 1300 / 2;//-120   1800 (valores felipe)
    //--->//Ball:
    int xBall= xPlayerbar+50.0, yBall= 1240 / 2;//+50   1750 (valores felipe)

    //Textures.
    Texture tPlayerbar;
    Texture tBall;
    Texture tScreenBackground;

    // Sprite screen background
    Sprite sScreenBackground;

    //Texture Loading.
    tPlayerbar.loadFromFile("playerbar.png");
    tBall.loadFromFile("ball.png");
    tScreenBackground.loadFromFile("screen background.jpg");

    // Background sprite and full screen setting
    sScreenBackground.setTexture(tScreenBackground);
    sScreenBackground.setScale(((float)w.getSize().x / sScreenBackground.getTexture()->getSize().x), ((float)w.getSize().y / sScreenBackground.getTexture()->getSize().y));

    //Texture Assignment.
    Playerbar playerbar(xPlayerbar, yPlayerbar, &tPlayerbar);
    Ball ball(xBall, yBall, &tBall);

    //Performance Settings.
    w.setFramerateLimit(120);

    //Windows Open.
        //Beginning While.
            while (w.isOpen()){
                //Event Statement:
                Event e;

                //Event Action.
                    //Beginning While.
                    while(w.pollEvent(e)){

                        //Beginning If.

                            //Close Window.
                            if(e.type==Event::Closed) {
                                w.close();
                            }

                            //Move Right.
                            if(Keyboard::isKeyPressed(Keyboard::Right)){
                                    playerbar.mover('d');
                                }

                            //Move Left.
                            if(Keyboard::isKeyPressed(Keyboard::Left)){
                            playerbar.mover('i');
                                }

                            // Move ball together with racket
                            if(!Keyboard::isKeyPressed(Keyboard::Space)){
                                //Move Right.
                                if(Keyboard::isKeyPressed(Keyboard::Right)){
                                    ball.moverBall('d',xPlayerbar);
                                }
                                //Move Left.
                                if(Keyboard::isKeyPressed(Keyboard::Left)){
                                    ball.moverBall('i',xPlayerbar);
                                }
                            }

                        //End If.

                    }//End While Event Action.

                //Refresh Screen.
                w.clear(Color(20, 20, 100, 150));

                //Object Illustration.
                w.draw(sScreenBackground);
                playerbar.dibujar(&w);
                ball.dibujar(&w);



                //Paste Objects in Window.
                w.display();

                              }//End While Windows Open.
    //Closing Program.
    return 0;


}