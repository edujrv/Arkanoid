#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Playerbar.h"
#include "Ball.h"
#include "Menu.h"
#include "Textos.h"

using namespace sf;

//Beginning of Main.
int main() {
    // Variables
    char menu='V';

    // Windows Resolutions.
   unsigned int windowHeight= 720;
   unsigned int windowWidth= 1080;


    float ballSize = 28.7;  // Original ball size
    float playerbarSize = 127.8;    // Original playerbar size

    //Scoreboard Settings.
    int vidas = 3;
    char resetPosition = 'F'; //Setea la playerbar en el centro cuando la pelota cae por el vacio.

    //Texts
    Font * retroFont = new Font();
    retroFont->loadFromFile("fuentes/Retro.ttf");
    Textos gameOver("GAME OVER",retroFont,60, ((int)windowWidth / 2) - 100 , ((int)windowHeight / 2) - 150);
    Textos tryAgain("Press space to try again",retroFont,30, ((int)windowWidth / 2) - 120, ((int)windowHeight / 2) - 80);
    Textos quit("Press esc to quit",retroFont,30, ((int)windowWidth / 2) - 75, ((int)windowHeight / 2) - 40);
    Textos lifes("LIFES: ",retroFont,40, 0, 0);
    Textos numLifes("3",retroFont,40, 100, 0);



    //Window Loading.
    RenderWindow w(VideoMode(windowWidth,windowHeight), "Breaking Bricks");

    //Menu.
    Menu menuprincipal(w.getSize().x, w.getSize().y);

    //Initial Object Positions.
    //--->//Playerbar:
    float desktopX = (float)windowWidth;
    float desktopY = (float)windowHeight;

    float xPlayerbar= (desktopX / 2) - (playerbarSize / 2);
    float yPlayerbar = desktopY - 100;

    //--->//Ball:

    float xBall = (w.getSize().x/2)-(ballSize/2);
    float yBall = yPlayerbar + 2;



    //Buffers.
    SoundBuffer bufferGolpe;
    SoundBuffer bufferRebote;
    SoundBuffer bufferBye;

    //Sounds.
    Sound soundGolpe;
    if(!bufferGolpe.loadFromFile("audios/Golpe.wav")){
        std::cout<<"No se pudo cargar el sonido"<<std::endl;
    }
    Sound soundRebote;
    if(!bufferRebote.loadFromFile("audios/Rebote.wav")){
        std::cout<<"No se pudo cargar el sonido"<<std::endl;
    }
    Sound soundBye;
    if(!bufferBye.loadFromFile("audios/Bye.wav")){
        std::cout<<"No se pudo cargar el sonido"<<std::endl;
    }

    //Music.
    Music music;
    if(!music.openFromFile("audios/Tetrismusic.wav")){
        std::cout<<"No se pudo cargar la musica"<<std::endl;
    }

    bool missed = false; //Para musica triste
    Music sadMusic;
    if(!sadMusic.openFromFile("audios/Sadmusic.wav")){
        std::cout<<"No se pudo cargar la musica"<<std::endl;
    }

    Music menuMusic;
    if(!menuMusic.openFromFile("audios/Boquita.wav")){
        std::cout<<"No se pudo cargar la musica"<<std::endl;
    }

    //Music Loading.
    music.setVolume(10);
    music.setLoop(true);

    sadMusic.setVolume(60);
    sadMusic.setLoop(true);

    menuMusic.setVolume(20);
    menuMusic.play();
    menuMusic.setLoop(true);

    //Sounds Assignment.
    soundGolpe.setBuffer(bufferGolpe);
    soundRebote.setBuffer(bufferRebote);
    soundBye.setBuffer(bufferBye);

    //Textures.
    Texture tPlayerbar;
    Texture tBall;
    Texture tScreenBackground;
    Texture tMenuBackground;

    // Sprite screen background
    Sprite sScreenBackground;
    Sprite sMenuBackground;

    //Texture Loading.
    tPlayerbar.loadFromFile("imagenes/playerbar.png");
    tBall.loadFromFile("imagenes/ball.png");
    tScreenBackground.loadFromFile("imagenes/fondo.jpg");
    tMenuBackground.loadFromFile("imagenes/fondomenu.jpg");

    // Background sprite and full screen setting
    sScreenBackground.setTexture(tScreenBackground);
    sScreenBackground.setScale(((float)w.getSize().x / sScreenBackground.getTexture()->getSize().x), ((float)w.getSize().y / sScreenBackground.getTexture()->getSize().y));

    sMenuBackground.setTexture(tMenuBackground);
    sMenuBackground.setScale(((float)w.getSize().x / sMenuBackground.getTexture()->getSize().x), ((float)w.getSize().y / sMenuBackground.getTexture()->getSize().y));

    //Texture Assignment.
    Playerbar playerbar(xPlayerbar, yPlayerbar, &tPlayerbar);
    xBall = playerbar.xPlayerbar + (playerbar.getLongX(&tPlayerbar) / 2) - (ballSize / 2);
    yBall = yPlayerbar - playerbar.getLongY(&tPlayerbar);
    Ball ball(xBall, yBall, &tBall);

    //Performance Settings.
    w.setFramerateLimit(30);

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
                                music.stop();
                                menuMusic.stop();
                                sadMusic.stop();
                                soundBye.play();
                                sleep(seconds(1.5));
                                w.close();
                            }//End If.
                            if(menu=='V'){
                                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                                    menuprincipal.moveUp();
                                }
                                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                                    menuprincipal.moveDown();
                                }
                                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                                    switch (menuprincipal.getSelectedItemIndex()){
                                        case 0:
                                            menuMusic.stop();
                                            music.play();
                                            menu='F';
                                            break;
                                        case 1:
                                            menuMusic.stop();
                                            soundBye.play();
                                            sleep(seconds(1.5));
                                            w.close();
                                            break;
                                    }

                                }
                            }

                    }//End While Event Action.

                    if(menu=='F'){
                if(vidas == 0 && !missed){ //Si las vidas son iguales a 0 aparece un cartel de perdiste y la musica triste.
                    music.stop();
                    sadMusic.play();
                    missed=true;
                }

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

                        // Para el turbo
                        if (Keyboard::isKeyPressed(Keyboard::T)) {

                            w.setFramerateLimit(120);
                        }else{

                            w.setFramerateLimit(30);
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
                                soundRebote.play();
                                ball.isDrew = true;
                            }
                        }
                        if (ball.isDrew) {
                            ball.move(longBar, highBar, playerbar.xPlayerbar, yPlayerbar, desktopY, desktopX, ballSize,  &vidas,
                                      &resetPosition);
                            if (resetPosition == 'V') {
                                soundGolpe.play();
                                playerbar.centrar(desktopX, playerbarSize);
                                resetPosition = 'F';
                            }

                        }

                    }//Fin if si vidas > 0.

                //Refresh Screen.
                w.clear(Color(20, 20, 100, 150));

                    if(menu=='F'){

                //Asignacion de la cantidad de vidas actuales.
                switch (vidas) {
                    case 1:{
                        numLifes.setMessage("1");
                        break;
                    }
                    case 2:{
                        numLifes.setMessage("2");
                        break;
                    }
                    case 3:{
                        numLifes.setMessage("3");
                        break;
                    }
                    default:{
                        numLifes.setMessage("0");
                        break;
                    }
                }

            }

                //Object Illustration.
                w.draw(sScreenBackground);
                playerbar.dibujar(&w);
                ball.draw(&w);

                lifes.draw(&w);
                numLifes.draw(&w);


                if(vidas == 0){ //Si las vidas son iguales a 0 aparece un cartel de perdiste.
                   gameOver.draw(&w);
                    tryAgain.draw(&w);
                    quit.draw(&w);

                    if (Keyboard::isKeyPressed(Keyboard::Space)){
                        vidas = 3;
                        sadMusic.stop();
                        missed=false;
                        music.play();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape)){
                        sadMusic.stop();
                        soundBye.play();
                        sleep(seconds(1.5));
                        w.close();
                    }

                }
                    }//Fin menu
                    else{
                        w.draw(sMenuBackground);
                        menuprincipal.draw(w);
                    }
                //Paste Objects in Window.
                w.display();

                              }//End While Windows Open.
    //Closing Program.
    return 0;


}
