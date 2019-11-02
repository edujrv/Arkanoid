//LIBRARIES:
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Playerbar.h"
#include "Ball.h"
#include "Menu.h"
#include "Textos.h"
#include "Vidas.h"
#include "Stack.h"
#include "Ladrillo.h"
#include "LinkedList.h"
#include <string>

void crearLadrillos(LinkedList <Ladrillo*> &bricks);
void mostrarLadrillos(LinkedList <Ladrillo*> &bricks, RenderWindow *w);
//  //  //  //  //  //  //  //  //  //  //

//TERMINOLOGY:
using namespace sf;
//  //  //  //  //  //  //  //  //  //  //


//BEGINNING OF MAIN:
int main() {
    LinkedList<Ladrillo*> ladrillos;

    crearLadrillos(ladrillos);
    // VARIABLES:

       //*  WINDOW:
         //-   RESOLUTIONS:
            unsigned int windowHeight= 782;
            unsigned int windowWidth= 1368;
            /*
             * windowHeight:    Alto de la pantalla. -> Original del fondo |1152|.
             * windowWidth:     Ancho de la pantalla. ->Original del fondo |2048|o|1368|.
             * */
         //-   LOADING:
            RenderWindow w(VideoMode(windowWidth,windowHeight), "Chimuelo Bricks");
         //-   PERFORMANCE:
            w.setFramerateLimit(40);
            char resetPosition = 'F';
            char colisiono = 'F';
            /*
             * resetPosition: Si esta es verdadera, la barra del usuario se dibujara en el centro de la pantalla.
             * colisiono: Si es verdadera signufica que la pelota colisiono con algo.
             */

       //*  MENU:
         //-   LOADING:
            Menu menuPrincipal(&w);
         //-   PROPERTIES:
            char menu='V';
            /*
             * Mientras este en verdadero, el usuario se mantendrá en el menú.
             */

       //*  STACKS:
         //-   LOADING:
            Stack<int> stackFullHeart;
            Stack<int> stackEmptyHeart;
            /*
             * stackFullHeart:  Esta pila contiente la cantidad de corazones llenos.
             * stackEmptyHeart: Esta pila contiente la cantidad de corazones vacíos.
             */

       //*  LIFES:
         //-   LOADING:
            int vidas = 3;
         //-   STACK CHARGING:
            for(int i=0;i<3;i++){
                stackFullHeart.push(1);
             }//END FOR.
         //-   PROPERTIES:
            char perdidaVida='F';
            /*
             * Cuando esta se vuelva verdadera, significara que el usuario perdió una vida.
             */

       //*  TEXTS:
         //-   FONT LOADING:
            Font * retroFont = new Font();
            retroFont->loadFromFile("fuentes/Retro.ttf");
         //-   TEXTS LOADING:
            Textos gameOver("GAME OVER",retroFont,60, ((int)windowWidth / 2) - 100 , ((int)windowHeight / 2) - 150);
            Textos tryAgain("Press space to try again",retroFont,30, ((int)windowWidth / 2) - 120, ((int)windowHeight / 2) - 80);
            Textos quit("Press esc to quit",retroFont,30, ((int)windowWidth / 2) - 75, ((int)windowHeight / 2) - 40);
            Textos lifes("LIFES: ",retroFont,40, 0, 0);
            Textos numLifes("3",retroFont,40, 100, 0);

       //*  NOISES:
         //-   BUFFERS LOADING:
            SoundBuffer bufferHerida;
            SoundBuffer bufferRebote;
            SoundBuffer bufferBye;
            SoundBuffer bufferMenuMove;
            SoundBuffer bufferMenuSelect;
            SoundBuffer bufferBubbles;
            /*
             * bufferHerida: Sonara cuando se pierda una vida.
             * bufferRebote:Sonara cuando la pelota rebote en alguna superficie.
             * bufferBye:   Sonara cuando se cierre el programa.
             * bufferMenuMove: Sonara cuando se baje o suba por las opciones del menu.
             * bufferMenuSelect: Sonara cuando se seleccione una opcion en el menu.
             * bufferBubbles: Sonara cuando se recarguen las vidas.
             */
         //-   SOUNDS LOADING:
            Sound soundBubbles;
            if(!bufferBubbles.loadFromFile("audios/Bubbles.wav")){
                std::cout<<"No se pudo cargar el sonido"<<std::endl;
            }
            Sound soundMenuSelect;
            if(!bufferMenuSelect.loadFromFile("audios/Menuselect.wav")){
                std::cout<<"No se pudo cargar el sonido"<<std::endl;
            }
            Sound soundMenuMove;
            if(!bufferMenuMove.loadFromFile("audios/Menumove.wav")){
                std::cout<<"No se pudo cargar el sonido"<<std::endl;
            }
            Sound soundHerida;
            if(!bufferHerida.loadFromFile("audios/Golpe.wav")){
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
         //-   SOUNDS ASSIGNMENT:
            soundHerida.setBuffer(bufferHerida);
            soundRebote.setBuffer(bufferRebote);
            soundBye.setBuffer(bufferBye);
            soundMenuMove.setBuffer(bufferMenuMove);
            soundMenuMove.setVolume(30);
            soundMenuSelect.setBuffer(bufferMenuSelect);
            soundMenuSelect.setVolume(60);
            soundBubbles.setBuffer(bufferBubbles);
            soundBubbles.setVolume(60);
         //-   MUSIC LOADING:
            Music turboMusic;
            if(!turboMusic.openFromFile("audios/Turbomusic.wav")){
                std::cout<<"No se pudo cargar la musica"<<std::endl;
            }
            Music gameMusic;
            if(!gameMusic.openFromFile("audios/Tetrismusic.wav")){
                std::cout<<"No se pudo cargar la musica"<<std::endl;
            }
            Music sadMusic;
            if(!sadMusic.openFromFile("audios/Sadmusic.wav")){
                std::cout<<"No se pudo cargar la musica"<<std::endl;
            }
            Music menuMusic;
            if(!menuMusic.openFromFile("audios/Menumusic.wav")){
                std::cout<<"No se pudo cargar la musica"<<std::endl;
            }
         //-   MUSIC SETTINGS:
            gameMusic.setVolume(40);
            gameMusic.setLoop(true);
            sadMusic.setVolume(60);
            sadMusic.setLoop(true);
            menuMusic.setVolume(40);
            menuMusic.play();
            menuMusic.setLoop(true);
            turboMusic.setVolume(100);
            turboMusic.setLoop(true);
            /*
             * gameMusic:   Musica que sonara durante la partida.
             * sadMusic:    Musica que sonara al perder.
             * menuMusic:   Musica que sonara durante el menú.
             */
         //-   PROPERTIES:
            bool missed = false;
            int turboOn=1;
            /*
             * missed: Si esta en verdadero, indicara que se ha perdido y empezara a sonar la música triste.
             * turboOn: Si vale 1, entonces se activara la musica rapida.
             */

       //*  OBJECTS:
         //-   SET TEXTURES:
            Texture tPlayerbar;
            tPlayerbar.loadFromFile("imagenes/playerbar.png");
            Texture tBall;
            tBall.loadFromFile("imagenes/ball.png");
            Texture tScreenBackground;
            tScreenBackground.loadFromFile("imagenes/fondoConMuro.jpg");
            Texture tMenuBackground;
            tMenuBackground.loadFromFile("imagenes/fondomenu.jpg");
            /*
             * tPlayerbar:          Textura de la barra del jugador.
             * tBall:               Textura de la pelota.
             * tScreenBackground:   Textura del fondo de pantalla al jugar.
             * tMenuBackground:     Textura del fondo de pantalla en el menú.
             */
         //-   SET SPRITES:
            Sprite sScreenBackground;
            sScreenBackground.setTexture(tScreenBackground);
            sScreenBackground.setScale(((float)w.getSize().x / sScreenBackground.getTexture()->getSize().x), ((float)w.getSize().y / sScreenBackground.getTexture()->getSize().y));
            Sprite sMenuBackground;
            sMenuBackground.setTexture(tMenuBackground);
            sMenuBackground.setScale(((float)w.getSize().x / sMenuBackground.getTexture()->getSize().x), ((float)w.getSize().y / sMenuBackground.getTexture()->getSize().y));
         //-   START OBJECTS:
            Playerbar playerbar(&w,&tPlayerbar,127.8);
            Ball ball(playerbar, &tBall,28.7);
            crearLadrillos(ladrillos);

       //*  SCOREBOARD:
         //-   SCOREBOARD SETTINGS:

//  //  //  //  //  //  //  //  //  //  //

       //*  WINDOWS OPEN:
            while (w.isOpen()){//Beginning While.
         //-   EVENT STATEMENT:
                Event e;
         //-   EVENT ACTION:
                    while(w.pollEvent(e)){//Beginning While.
                        //-   EVENT ACTION:
                            //--   CLOSE WINDOW:
                            if(e.type == Event::Closed) {//Beginning If.
                                gameMusic.stop();
                                menuMusic.stop();
                                sadMusic.stop();
                                soundBye.play();
                                sleep(seconds(1.5));
                                w.close();
                            }//End If.
                            //--   MENU ACTIONS:
                            if(menu == 'V'){//Beginning If.
                                //---   MOVE UP:
                                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                                    menuPrincipal.moveUp();
                                    soundMenuMove.play();
                                }
                                //---   MOVE DOWN:
                                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                                    menuPrincipal.moveDown();
                                    soundMenuMove.play();
                                }
                                //---   SELECT:
                                if (Keyboard::isKeyPressed(Keyboard::Enter)) {//Beginning If.
                                    switch (menuPrincipal.getSelectedItemIndex()){//Beginning Switch.
                                        case 0://START.
                                            soundMenuSelect.play();
                                            menuMusic.stop();
                                            sleep(seconds(1));
                                            gameMusic.play();
                                            menu='F';
                                            break;
                                        case 1://QUIT.
                                            soundMenuSelect.play();
                                            menuMusic.stop();
                                            sleep(seconds(1));
                                            soundBye.play();
                                            sleep(seconds(1.5));
                                            w.close();
                                            break;
                                    }//End switch.
                                }//End if.
                            }//End if menu.
                    }//End while event action.
                            //--   INGAME ACTIONS:
                                if(menu=='F'){//Beginning If.
                                    if((stackFullHeart.size()==0) && !missed){ //If user lose.
                                        gameMusic.stop();
                                        sadMusic.play();
                                        missed=true;
                                    }//End if.
                                    if(stackFullHeart.size() > 0) {//If user play.
                                        if (!ball.isDrew){//Move ball with the playerbar.
                                            ball.moveBallWithPlayerbar(playerbar); // Start on the middle of the bar
                                        }
                                //---   MOVE RIGHT:
                                    if (Keyboard::isKeyPressed(Keyboard::Right)) {
                                        if (playerbar.xPlayerbar >= (float) windowWidth - 130 - (playerbar.getLongX(&tPlayerbar) * 0.2)) {//Check limit.
                                            std::cout << "Limite derecho de la pantalla alcanzado" << std::endl;
                                        } else {
                                            playerbar.mover('d');
                                        }
                                        if (!ball.isDrew) {//Follow the playerbar.
                                            ball.moveBallWithPlayerbar(playerbar);
                                        }
                                    }
                                //---   MOVE LEFT:
                                        if (Keyboard::isKeyPressed(Keyboard::Left)) {
                                            if (playerbar.xPlayerbar <= 140) {//Check limit.
                                                std::cout << "Limite izquierdo de la pantalla alcanzado" << std::endl;
                                            } else {
                                                playerbar.mover('i');
                                            }
                                            if (!ball.isDrew) {//Follow the playerbar.
                                                ball.moveBallWithPlayerbar(playerbar);
                                            }
                                        }
                                //---   TURBO:
                                        if (Keyboard::isKeyPressed(Keyboard::T)) {
                                            w.setFramerateLimit(120);
                                            if(turboOn == 1){
                                                gameMusic.setVolume(3);
                                                turboMusic.play();
                                                turboOn=0;
                                            }

                                        }else{
                                            gameMusic.setVolume(40);
                                            turboOn=1;
                                            w.setFramerateLimit(40);
                                            turboMusic.stop();
                                        }
                                //---   BALL RELEASE:
                                        if (Keyboard::isKeyPressed(Keyboard::Space)) {
                                            if (!ball.isDrew) {
                                                soundRebote.play();
                                                ball.isDrew = true;
                                            }
                                        }
                                //---   BALL DISPLACEMENT:
                                        if (ball.isDrew) {//Beginning If.
                                            ball.move(playerbar,ball,&w,&vidas,&resetPosition,&perdidaVida,&colisiono);
                                            if(perdidaVida=='V'){//Lose a life.
                                                perdidaVida='F';
                                                stackFullHeart.pop();
                                                stackEmptyHeart.push(1);
                                            }
                                            if (resetPosition == 'V') {//Restart position.
                                            soundHerida.play();
                                            playerbar.centrar(&w,playerbar);
                                            resetPosition = 'F';
                                            }
                                            if(colisiono == 'V'){
                                                colisiono='F';
                                                soundRebote.play();
                                            }
                                        }//End if.
                                    }//End if user play.
                            //--   REFRESH SCREEN:
                                w.clear(Color(20, 20, 100, 150));
                            //--   LIFES CONTROL:
                                if(menu == 'F'){//Beginning of play.
                                    switch (vidas) {//Beginning of switch.
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
                                    }//End switch.
                                }//End if play.
                        //-   OBJECT ILLUSTRATION:
                            w.draw(sScreenBackground);
                            playerbar.dibujar(&w);
                            ball.draw(&w);
                            lifes.draw(&w);
                            numLifes.draw(&w);
                            mostrarLadrillos(ladrillos,&w);
                            int aux=0;
                            for (int i=0;i<stackEmptyHeart.size();i++){//Draw empty hearts.
                                aux=i+1;
                                Vidas vid(&w,aux);
                                vid.draw(&w,0);
                            }
                            for (int i=0;i<stackFullHeart.size();i++){//Draw full hearts.
                                aux=aux+1;
                                Vidas vid(&w,aux);
                                vid.draw(&w,1);
                            }
                            //--   LOSE CONDITIONS:
                            if(stackFullHeart.size() == 0){ //Beginning of if lose.
                                turboMusic.stop();
                                gameOver.draw(&w);
                                tryAgain.draw(&w);
                                quit.draw(&w);
                                if (Keyboard::isKeyPressed(Keyboard::Space)){
                                    vidas = 3;
                                    soundBubbles.play();
                                    for(int i=0;i<3;i++){//Charge full hearts.
                                        stackFullHeart.push(1);
                                    }
                                    for(int i=0;i<3;i++){//Empty empty hearts.
                                        stackEmptyHeart.pop();
                                    }
                                    sadMusic.stop();
                                    missed=false;
                                    gameMusic.play();
                                }
                                if (Keyboard::isKeyPressed(Keyboard::Escape)){
                                    sadMusic.stop();
                                    soundBye.play();
                                    sleep(seconds(1.5));
                                    w.close();
                                }
                            }//End if lose.
                    }//End if play.
                    else{
                        w.draw(sMenuBackground);
                        menuPrincipal.draw(w);
                    }
                        //-   OBJECT ILLUSTRATION:
                            w.display();
                              }//End While Windows Open.
    //*  CLOSING PROGRAM:
    return 0;
}//END MAIN.

void crearLadrillos(LinkedList <Ladrillo*> &bricks){


    int idLadrilloX = 0, i = 0;
    std::string linea;
    int fila =0;
    std::ifstream a("textos/level.txt");
    fflush(stdin);
    while(getline(a,linea)){
        for(int col =0; col < linea.length(); col++){
            if(linea[col] == 'o')

                bricks.put(new Ladrillo(140,0,col,fila), 0);

        }
        fila++;
    }
    a.close();


//    for (idLadrilloX = 0; idLadrilloX < 10; idLadrilloX++){
//
//        bricks.put(new Ladrillo(140,0,idLadrilloX,0), i);
//
//        i++;
//    }
}

void mostrarLadrillos(LinkedList <Ladrillo*> &bricks, RenderWindow *w) {

    for(bricks.begin(); !bricks.ended() ; bricks.next()){
        bricks.get()->draw(w);
    }
}