#include <iostream>
#include <SFML/Graphics.hpp>
#include "Playerbar.h"
#include "Ball.h"

using namespace sf;

//Beginning of Main.
int main() {
    // Variables

    // Windows Resolutions.
    unsigned int windowHeight= 900u;
    unsigned int windowWidth= 1600u;

    // Original ball size
    float ballSize = 28.7;
    // Original playerbar size
    float playerbarSize = 127.8;

    //Scoreboard Settings.
    int vidas= 3;
    char resetPosition = 'F'; //Setea la playerbar en el centro cuando la pelota cae por el vacio.

    //Window Loading.
    RenderWindow w(VideoMode(windowWidth,windowHeight), "Breaking Bricks");

    //Initial Object Positions.
    //--->//Playerbar:
    float desktopX = (float)windowWidth;
    float desktopY = (float)windowHeight;

    float xPlayerbar= (desktopX / 2) - (playerbarSize / 2);
    float yPlayerbar = desktopY - 100;

    //--->//Ball:

    float xBall = (w.getSize().x/2)-(ballSize/2);
    float yBall = yPlayerbar + 2;

    //Font Print on Windows Declaration.
    Font * fuenteRetro;
    fuenteRetro= new Font();

    //Text Print on Windows Declaration.
    Text * txtVidas;
    txtVidas=new Text();
    Text * numVidas;
    numVidas=new Text();
    Text * txtPerdiste;
    txtPerdiste=new Text();

    //Font Assignment.
    fuenteRetro->loadFromFile("Retro.ttf");

    //Text Configuration.
    txtVidas->setFont(*fuenteRetro);
    txtVidas->setString("VIDAS");
    txtVidas->setPosition(0,0);
    txtVidas->setColor(Color::Red);
    txtVidas->setCharacterSize(20);

    numVidas->setFont(*fuenteRetro);
    numVidas->setPosition(50,0);
    numVidas->setColor(Color::Red);
    numVidas->setCharacterSize(20);

    txtPerdiste->setString("PERDISTE");
    txtPerdiste->setFont(*fuenteRetro);
    txtPerdiste->setColor(Color::Red);
    txtPerdiste->setCharacterSize(60);
    txtPerdiste->setPosition(desktopX/2,desktopY/2);
    txtPerdiste->setOrigin(txtPerdiste->getGlobalBounds().width/2, txtPerdiste->getGlobalBounds().height/2);

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
                            }//End If.

                    }//End While Event Action.

                    if(vidas > 0) {//Comienzo if si la vidas son mayores a 0 podes jugar.

                        float longBar = playerbar.getLongX(&tPlayerbar);
                        float highBar = playerbar.getLongY(&tPlayerbar);
                        if (!ball.isDrew)
                            ball.moveBallWithPlayerbar(longBar, highBar, playerbar.xPlayerbar,
                                                       yPlayerbar); // Start on the middle of the bar

                        //Move Right.
                        if (Keyboard::isKeyPressed(Keyboard::Right)) {
                            if (playerbar.xPlayerbar >= (float) desktopX - (longBar * 0.2)) {
                                std::cout << "Limite derecho de la pantalla alcanzado" << std::endl;
                            } else {
                                playerbar.mover('d');
                            }
                            if (!ball.isDrew) {
                                ball.moveBallWithPlayerbar(longBar, highBar, playerbar.xPlayerbar, yPlayerbar);
                            }
                        }

                        //Move Left.
                        if (Keyboard::isKeyPressed(Keyboard::Left)) {
                            if (playerbar.xPlayerbar <= 0) {
                                std::cout << "Limite izquierdo de la pantalla alcanzado" << std::endl;
                            } else {
                                playerbar.mover('i');
                            }
                            if (!ball.isDrew) {
                                ball.moveBallWithPlayerbar(longBar, highBar, playerbar.xPlayerbar, yPlayerbar);
                            }
                        }

                        //Set ball free
                        if (Keyboard::isKeyPressed(Keyboard::Space)) {
                            // playerbar.mover('i');
                            if (!ball.isDrew) {
                                ball.isDrew = true;
                            }
                        }
                        if (ball.isDrew) {
                            ball.move(longBar, highBar, playerbar.xPlayerbar, yPlayerbar, desktopY, &vidas,
                                      &resetPosition);

                            if (resetPosition == 'V') {
                                playerbar.centrar(desktopX, playerbarSize);
                                resetPosition = 'F';
                            }

                        }

                    }//Fin if si vidas > 0.

                //Refresh Screen.
                w.clear(Color(20, 20, 100, 150));

                //Asignacion de la cantidad de vidas actuales.
                numVidas->setString(std::to_string(vidas));

                //Object Illustration.
                w.draw(sScreenBackground);
                playerbar.dibujar(&w);
                ball.draw(&w);
                w.draw(*numVidas);
                w.draw(*txtVidas);

                if(vidas == 0){ //Si las vidas son iguales a 0 aparece un cartel de perdiste.
                    w.draw(*txtPerdiste);
                }

                //Paste Objects in Window.
                w.display();

                              }//End While Windows Open.
    //Closing Program.
    return 0;


}