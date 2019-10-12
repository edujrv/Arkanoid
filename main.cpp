#include <iostream>
#include <SFML/Graphics.hpp>
#include "Playerbar.h"
#include "Ball.h"

using namespace sf;

//Beginning of Main.
int main() {
    // Variables
    // Original ball size
    float ballSize = 28.7;
    // Original playerbar size
    float playerbarSize = 127.8;

    RenderWindow w(VideoMode::getDesktopMode(), "Breaking Bricks");  //Window Loading.


    //Initial Object Positions.
    //--->//Playerbar:
    float DesktopX = (float)VideoMode::getDesktopMode().width;
    float DesktopY = (float)VideoMode::getDesktopMode().height;

    float xPlayerbar= (DesktopX / 2) - (playerbarSize/2);
    float yPlayerbar = DesktopY - 200;

    //--->//Ball:

    float xBall = (w.getSize().x/2)-(ballSize/2);
    float yBall = yPlayerbar + 2;

    //Textures.
    Texture tPlayerbar;
    Texture tBall;
    Texture tScreenBackground;

    // Sprite screen background
    Sprite sScreenBackground;

    //Texture Loading.
    tPlayerbar.loadFromFile("imagenes/playerbar.png");
    tBall.loadFromFile("imagenes/ball.png");
    tScreenBackground.loadFromFile("imagenes/fondo.jpg");

    // Background sprite and full screen setting
    sScreenBackground.setTexture(tScreenBackground);
    sScreenBackground.setScale(((float)w.getSize().x / sScreenBackground.getTexture()->getSize().x), ((float)w.getSize().y / sScreenBackground.getTexture()->getSize().y));



    //Texture Assignment.
    Playerbar playerbar(xPlayerbar, yPlayerbar, &tPlayerbar);
    xBall = playerbar.xPlayerbar + (playerbar.getLongX(&tPlayerbar) / 2) - (ballSize / 2);
    yBall = yPlayerbar - playerbar.getLongY(&tPlayerbar);
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




                        //End If.

                    }//End While Event Action.

                    float longBar = playerbar.getLongX(&tPlayerbar);
                    float highBar = playerbar.getLongY(&tPlayerbar);
                    if (!ball.isDrew)
                    ball.moveBallWithPlayerbar(longBar, highBar, playerbar.xPlayerbar, yPlayerbar); // Start on the middle of the bar

                //Move Right.
                if(Keyboard::isKeyPressed(Keyboard::Right)) {
                    if (playerbar.xPlayerbar >= (float)VideoMode::getDesktopMode().width - 400) {

                    } else {
                    playerbar.mover('d');
                    }
                    if(!ball.isDrew){
                        ball.moveBallWithPlayerbar(longBar, highBar, playerbar.xPlayerbar, yPlayerbar);
                    }



                }

                //Move Left.
                if(Keyboard::isKeyPressed(Keyboard::Left)){
                    if (playerbar.xPlayerbar <= 0 + 400) {
                        std::cout<<playerbar.getLongX(&tPlayerbar)<<std::endl;
                    } else {
                        playerbar.mover('i');
                    }
                    if(!ball.isDrew){
                        ball.moveBallWithPlayerbar(longBar, highBar, playerbar.xPlayerbar, yPlayerbar);
                    }
                }

                //Set ball free
                if(Keyboard::isKeyPressed(Keyboard::Space)){
                   // playerbar.mover('i');
                    if(!ball.isDrew){
                        ball.isDrew = true;
                    }
                }
                if (ball.isDrew){
                    ball.move(longBar, highBar, playerbar.xPlayerbar, yPlayerbar);
                }





                //Refresh Screen.
                w.clear(Color(20, 20, 100, 150));

                //Object Illustration.
                w.draw(sScreenBackground);
                playerbar.dibujar(&w);
                ball.draw(&w);



                //Paste Objects in Window.
                w.display();

                              }//End While Windows Open.
    //Closing Program.
    return 0;


}