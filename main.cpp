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
#include "Queue.h"
#include <ctime>
#include "IconPower.h"
#include <string.h>
#include <cstring>
#include <utility>

struct bestPlayer{
    std::string userName;
    std::string min;
    std::string sec;
    std::string ms;
};

void compararTiempos(bestPlayer top[10], int userMin, int userSec, int userMs, std::string userName);

std::string leerPodio();


void ordenarTop(bestPlayer *top, int userMin, int userSec, int userMs, std::string userName, int pos);

void crearLadrillos(LinkedList<Ladrillo *> &bricks);

void mostrarLadrillos(LinkedList<Ladrillo *> &bricks, RenderWindow *w);

void cargarPoweup(Queue<int> &powerup);

void generarPoweup(Queue<int> &powerup, bool *isPowerupActivated, bool *activarReloj);

void readFilesLevel(std::ifstream *, LinkedList<Ladrillo *> &bricks);

void mapClean(LinkedList<Ladrillo *> &bricks);

void vericarGanar(LinkedList<Ladrillo *> &bricks, bool *menuGanar);

//  //  //  //  //  //  //  //  //  //  //

//TERMINOLOGY:
using namespace sf;
//  //  //  //  //  //  //  //  //  //  //


//BEGINNING OF MAIN:
int main() {

    enum {
        MENU,
        JUGANDO,
        GANADOR,
        PODIO,
        PERDEDOR,
    };
    int estado = MENU;


    LinkedList<Ladrillo *> ladrillos;
    Queue<int> powerup;
    cargarPoweup(powerup);
    std::ofstream fileNames;



    //  crearLadrillos(ladrillos);

    // VARIABLES:

    //*  WINDOW:
    //-   RESOLUTIONS:
    unsigned int windowHeight = 782;
    unsigned int windowWidth = 1368;
    /*
     * windowHeight:    Alto de la pantalla. -> Original del fondo |1152|.
     * windowWidth:     Ancho de la pantalla. ->Original del fondo |2048|o|1368|.
     * */
    //-   LOADING:
    RenderWindow w(VideoMode(windowWidth, windowHeight), "Chimuelo Bricks");
    //-   PERFORMANCE:
    w.setFramerateLimit(40);
    char resetPosition = 'F';
    char colisiono = 'F';
    bool verifPowerup = false;
    bool isPowerupActivated = false;
    bool comienzoPoder = true;
    bool quedanladrillos = true;

    /*
     * resetPosition: Si esta es verdadera, la barra del usuario se dibujara en el centro de la pantalla.
     * colisiono: Si es verdadera signufica que la pelota colisiono con algo.
     * verifPowerup: si es verdadera significa que se activa el powerup.
     */

    //*  TIMES:
    //-   LOADING:
    Clock *clockPower;
    Time *timePower;
    Clock *clockGame;
    Time *timeGame;
    Clock* clockTimer;
    Time* timeTimer;
    bool activarRelojTimer = true;
    bool activarReloj = true;
    int minutos = 0;
    int segundos = 0;
    int milisegundos = 0;
    bool activarRelojPrincipal = true;
    std::string timerUser;
    bool tiempoOn=true;
    auto *top = new bestPlayer [10];
    bool mostrar = false;

    int gika[50];

    //*  MENU:
    //-   LOADING:
    Menu menuPrincipal(&w);
    //-   PROPERTIES:
    bool menuGanar = false;
    std::string letra;
    int indicador = 0;
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
    for (int i = 0; i < 3; i++) {
        stackFullHeart.push(1);
    }//END FOR.
    //-   PROPERTIES:
    char perdidaVida = 'F';
    /*
     * Cuando esta se vuelva verdadera, significara que el usuario perdió una vida.
     */

    //*  TEXTS:
    //-   FONT LOADING:
    Font *retroFont = new Font();
    retroFont->loadFromFile("fuentes/Retro.ttf");
    //-   TEXTS LOADING:
    Textos gameOver("GAME OVER", retroFont, 60, ((int) windowWidth / 2) - 100, ((int) windowHeight / 2) - 150);
    Textos tryAgain("Press space to try again", retroFont, 30, 650,((int) windowHeight) - 120);
    Textos quit("Press esc to quit", retroFont, 30, 450, ((int) windowHeight) - 120);
    Textos lifes("LIFES: ", retroFont, 40, 10, 0);
    Textos numLifes("3", retroFont, 40, 100, 0);
    Textos ingUser("Ingrese su nombre de usuario:", retroFont, 40, (windowWidth / 2) - 200, (windowHeight / 2) - 50);
    Textos usuario("............", retroFont, 40, (windowWidth / 2) - 60, (windowHeight / 2) - 5);
    Textos tiempo("Tu tiempo es:", retroFont, 40, 150, 10);
    Textos timeUserTxt("", retroFont, 40, 350, 10);
    Textos win("GANASTE MISTER!", retroFont, 60, (windowWidth / 2) - 150, (windowHeight / 2) - 300);
    Textos scores(" ", retroFont, 40, (windowWidth / 2) - 100, 200);
    Textos tituloScores(" WALL OF FAME ", retroFont, 60, (windowWidth / 2) - 100, 100);

    //*  NOISES:
    //-   BUFFERS LOADING:
    SoundBuffer bufferHerida;
    SoundBuffer bufferRebote;
    SoundBuffer bufferBye;
    SoundBuffer bufferMenuMove;
    SoundBuffer bufferMenuSelect;
    SoundBuffer bufferBubbles;
    SoundBuffer bufferPower;
    /*
     * bufferHerida: Sonara cuando se pierda una vida.
     * bufferRebote:Sonara cuando la pelota rebote en alguna superficie.
     * bufferBye:   Sonara cuando se cierre el programa.
     * bufferMenuMove: Sonara cuando se baje o suba por las opciones del menu.
     * bufferMenuSelect: Sonara cuando se seleccione una opcion en el menu.
     * bufferBubbles: Sonara cuando se recarguen las vidas.
     * bufferPower: Sonara cuando se consiga el poder de velocidad.
     */
    //-   SOUNDS LOADING:
    Sound soundPower;
    if (!bufferPower.loadFromFile("audios/Powersound.wav")) {
        std::cout << "No se pudo cargar el sonido" << std::endl;
    }
    Sound soundBubbles;
    if (!bufferBubbles.loadFromFile("audios/Bubbles.wav")) {
        std::cout << "No se pudo cargar el sonido" << std::endl;
    }
    Sound soundMenuSelect;
    if (!bufferMenuSelect.loadFromFile("audios/Menuselect.wav")) {
        std::cout << "No se pudo cargar el sonido" << std::endl;
    }
    Sound soundMenuMove;
    if (!bufferMenuMove.loadFromFile("audios/Menumove.wav")) {
        std::cout << "No se pudo cargar el sonido" << std::endl;
    }
    Sound soundHerida;
    if (!bufferHerida.loadFromFile("audios/Golpe.wav")) {
        std::cout << "No se pudo cargar el sonido" << std::endl;
    }
    Sound soundRebote;
    if (!bufferRebote.loadFromFile("audios/Rebote.wav")) {
        std::cout << "No se pudo cargar el sonido" << std::endl;
    }
    Sound soundBye;
    if (!bufferBye.loadFromFile("audios/Bye.wav")) {
        std::cout << "No se pudo cargar el sonido" << std::endl;
    }
    //-   SOUNDS ASSIGNMENT:
    soundHerida.setBuffer(bufferHerida);
    soundPower.setBuffer(bufferPower);
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
    if (!turboMusic.openFromFile("audios/Turbomusic.wav")) {
        std::cout << "No se pudo cargar la musica" << std::endl;
    }
    Music gameMusic;
    if (!gameMusic.openFromFile("audios/Tetrismusic.wav")) {
        std::cout << "No se pudo cargar la musica" << std::endl;
    }
    Music sadMusic;
    if (!sadMusic.openFromFile("audios/Sadmusic.wav")) {
        std::cout << "No se pudo cargar la musica" << std::endl;
    }
    Music menuMusic;
    if (!menuMusic.openFromFile("audios/Menumusic.wav")) {
        std::cout << "No se pudo cargar la musica" << std::endl;
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
    int turboOn = 1;
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
    sScreenBackground.setScale(((float) w.getSize().x / sScreenBackground.getTexture()->getSize().x),
                               ((float) w.getSize().y / sScreenBackground.getTexture()->getSize().y));
    Sprite sMenuBackground;
    sMenuBackground.setTexture(tMenuBackground);
    sMenuBackground.setScale(((float) w.getSize().x / sMenuBackground.getTexture()->getSize().x),
                             ((float) w.getSize().y / sMenuBackground.getTexture()->getSize().y));
    //-   START OBJECTS:
    Playerbar playerbar(&w, &tPlayerbar, 127.8);
    Ball ball(playerbar, &tBall, 28.7);
    IconPower powerIcon(&w);
    crearLadrillos(ladrillos);


    RectangleShape barra(Vector2f(400, 40));
    barra.setPosition(Vector2f((windowWidth / 2) - 200, (windowHeight / 2)));
    barra.setOutlineColor(Color::Black);
    barra.setFillColor(Color::White);


    //*  SCOREBOARD:
    //-   SCOREBOARD SETTINGS:

//  //  //  //  //  //  //  //  //  //  //

    //*  WINDOWS OPEN:
    while (w.isOpen()) {//Beginning While.
        //-   EVENT STATEMENT:
        Event e;
        //-   EVENT ACTION:
        while (w.pollEvent(e)) {//Beginning While.
            //-   EVENT ACTION:
            //--   CLOSE WINDOW:
            if (e.type == Event::Closed) {//Beginning If.
                gameMusic.stop();
                menuMusic.stop();
                sadMusic.stop();
                soundBye.play();
                sleep(seconds(1.5));
                w.close();
            }//End If.
            if(estado == GANADOR){
                if ( e.type == Event::TextEntered) {
                    switch (e.text.unicode) {
                        case 13: {
                            std::string linea;
                            int fila = 0;
                            int col = 0;
                            int i=0;
                            fflush(stdin);
                            std::ifstream archtop;
                            archtop.open("textos/nombres.txt");

                            for (int j = 0; j < 10; ++j) {
                                top[j].userName = "";
                                top[j].min = "";
                                top[j].sec ="";
                                top[j].ms = "";
                            }

                            while (getline(archtop,linea,'-')){

                                    top[i].userName += linea;
                                    getline(archtop, linea, ':');
                                    top[i].min += linea;
                                    getline(archtop, linea, ':');
                                    top[i].sec += linea;
                                    getline(archtop, linea, '\n');
                                    top[i].ms += linea;
                                    i++;


                            }
                            archtop.close();
                            archtop.open("textos/nombres.txt");
                            i=0;


                            archtop.close();

                        //Escritura
                            /*
                            std::cout << "La letra." << letra << std::endl;
                            fileNames.open("textos/nombres.txt", std::ios::out);
                            if (fileNames.is_open()) {

                                fileNames << "\n";
                                fileNames << letra << "\n";
                                fileNames.close();
                            } else {
                                std::cout << "error al abrir el archivo";
                            }*/
                            estado = PODIO;
                            break;
                        }
                        case 8:
                            if(indicador > 0){
                            letra = letra.substr(0, letra.length() - 1);
                            usuario.enterName(letra);
                            indicador--;
                            }
                            break;
                        default://Cualquier letra
                            if (indicador < 10) {
                                letra.push_back(e.text.unicode);
                                usuario.enterName(letra);
                                indicador++;
                            }
                            break;
                    }
                }
            }
        }
        //--   MENU ACTIONS:
        switch (estado) {//Beginning If.
            case MENU:
                mostrar = false;
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
                if ((Keyboard::isKeyPressed(Keyboard::Enter)) ||
                    (Keyboard::isKeyPressed(Keyboard::Space))) {//Beginning If.
                    switch (menuPrincipal.getSelectedItemIndex()) {//Beginning Switch.
                        case 0://START.
                            soundMenuSelect.play();
                            menuMusic.stop();
                            sleep(seconds(1));
                            gameMusic.play();
                            estado = JUGANDO;
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
                break;
            case GANADOR: //Menu al ganar       //Hacer una funcion que evalue si quedan ladrillos y menuGanar=true
                // me fui al loop de eventos
                if (activarRelojTimer) {
                    clockTimer = new Clock();
                    timeTimer = new Time();
                    activarRelojTimer = false;
                }
                *timeTimer = clockTimer->getElapsedTime();
                if ((timeTimer->asSeconds()) >= 1) {
                    clockTimer->restart();
                    if(tiempoOn){
                        tiempoOn= false;
                    } else{
                        tiempoOn=true;
                    }
                }

                if(minutos < 10){
                    timerUser="0";
                    timerUser+=std::to_string(minutos);
                }else{
                    timerUser=std::to_string(minutos);
                }
                timerUser+=":";
                if(segundos < 10){
                    timerUser+="0";
                    timerUser+=std::to_string(segundos);
                }else{
                    timerUser+=std::to_string(segundos);
                }
                timerUser+=":";
                if(milisegundos < 10){
                    timerUser+="00";
                    timerUser+=std::to_string(milisegundos);
                }else if((milisegundos > 10) && (milisegundos < 100)){
                    timerUser+="0";
                    timerUser+=std::to_string(milisegundos);
                }else{
                    timerUser+=std::to_string(milisegundos);
                }
                tiempo.setMessage("Tu tiempo es:");
                timeUserTxt.setMessage(timerUser);

                break;
            case PODIO:
                    if (!mostrar) {
                        compararTiempos(top, minutos, segundos, milisegundos, letra);
                        letra = "";
                        mostrar = true;
                    }
                    scores.setMessage(leerPodio());

                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    vidas = 3;
                    soundBubbles.setVolume(180);
                    soundBubbles.play();
                    while(stackFullHeart.size() < 3){
                        stackFullHeart.push(1);
                    }

                    while (stackEmptyHeart.size() > 0) {//Empty empty hearts.
                        stackEmptyHeart.pop();
                    }
                    sadMusic.stop();
                    isPowerupActivated=false;
                    segundos=0;
                    milisegundos=0;
                    minutos=0;
                    letra = "";
                    usuario.enterName(letra);
                    gameMusic.play();
                    mapClean(ladrillos);
                    crearLadrillos(ladrillos);
                    menuGanar= false;
                    activarRelojPrincipal=true;
                    playerbar.centrar(&w, playerbar);
                    estado = MENU;
                    ball.changeIsDrew();
                    tiempoOn=true;
                    sleep(seconds(1));
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    sadMusic.stop();
                    soundBye.play();
                    sleep(seconds(1.5));
                    w.close();
                }

                break;
                //Insertar bloque de mostrar  mejores tiempo junto con las opciones de salir y volver a jugar;
            case PERDEDOR:
                ball.moveBallWithPlayerbar(playerbar);
                gameMusic.stop();
                sadMusic.play();
                segundos = 0;
                milisegundos = 0;
                minutos = 0;
                activarRelojPrincipal = true;

                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    vidas = 3;
                    soundBubbles.setVolume(180);
                    soundBubbles.play();
                    for (int i = 0; i < 3; i++) {//Charge full hearts.
                        stackFullHeart.push(1);
                    }
                    for (int i = 0; i < 3; i++) {//Empty empty hearts.
                        stackEmptyHeart.pop();
                    }
                    sadMusic.stop();
                    gameMusic.play();
                    milisegundos=0;
                    segundos=0;
                    minutos=0;
                    mapClean(ladrillos);
                    crearLadrillos(ladrillos);
                    sleep(seconds(1));
                    estado = MENU;
                    activarRelojPrincipal=true;
                    playerbar.centrar(&w, playerbar);
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    sadMusic.stop();
                    soundBye.play();
                    sleep(seconds(1.5));
                    w.close();
                }
                break;
            case JUGANDO:
                //---   BALL RELEASE:
                if (activarRelojPrincipal) {
                    clockGame = new Clock();
                    timeGame = new Time();
                    std::cout << "Tiempo activado" << std::endl;
                    activarRelojPrincipal = false;
                }
                *timeGame = clockGame->getElapsedTime();
                milisegundos = timeGame->asMilliseconds();
                std::cout << timeGame->asMilliseconds() << std::endl;
                if ((timeGame->asMilliseconds()) >= 1000) {
                    std::cout << "SEGUNDO" << std::endl;
                    clockGame->restart();
                    segundos++;
                    milisegundos = 0;
                }
                if (segundos >= 60) {
                    std::cout << "Minuto" << std::endl;
                    clockGame->restart();
                    segundos = 0;
                    minutos++;
                }

                if (!ball.isDrew) {//Move ball with the playerbar.
                    ball.moveBallWithPlayerbar(playerbar); // Start on the middle of the bar
                }
                //---   MOVE RIGHT:
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    if (playerbar.xPlayerbar >= (float) windowWidth - 130 -
                                                (playerbar.getLongX(&tPlayerbar) *
                                                 0.2)) {//Check limit.
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
                    if (turboOn == 1) {
                        gameMusic.setVolume(3);
                        turboMusic.play();
                        turboOn = 0;
                    }
                } else {
                    if (isPowerupActivated) {
                        w.setFramerateLimit(120);
                        if (activarReloj) {
                            soundPower.setVolume(50);
                            soundPower.play();
                            clockPower = new Clock();
                            timePower = new Time();
                            std::cout << "Tiempo activado" << std::endl;
                            activarReloj = false;
                        }
                        if (turboOn == 1) {
                            gameMusic.setVolume(3);
                            turboMusic.play();
                            turboOn = 0;
                        }
                        *timePower = clockPower->getElapsedTime();
                        std::cout << timePower->asSeconds() << std::endl;
                        if ((timePower->asSeconds()) >= 5) {
                            isPowerupActivated = false;
                            std::cout << "Tiempo terminado" << std::endl;
                            clockPower->restart();
                            soundPower.play();
                        }
                    } else {
                        gameMusic.setVolume(40);
                        turboOn = 1;
                        w.setFramerateLimit(40);
                        turboMusic.stop();
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    if (!ball.isDrew) {
                        soundRebote.play();
                        ball.isDrew = true;
                    }
                }
                //---   BALL DISPLACEMENT:
                if (ball.isDrew) {//Beginning If.
                    ball.move(playerbar, ball, &w, &vidas, &resetPosition, &perdidaVida, &colisiono, ladrillos,
                              &verifPowerup);
                    mostrarLadrillos(ladrillos, &w);
                    if (perdidaVida == 'V') {//Lose a life.
                        perdidaVida = 'F';
                        stackFullHeart.pop();
                        stackEmptyHeart.push(1);
                        if (stackFullHeart.empty()) {
                            estado = PERDEDOR;
                        }
                    }
                    if (resetPosition == 'V') {//Restart position.
                        soundHerida.play();
                        playerbar.centrar(&w, playerbar);
                        resetPosition = 'F';
                        if (isPowerupActivated) {
                            isPowerupActivated = false;
                            std::cout << "Tiempo terminado" << std::endl;
                            clockPower->restart();
                            soundPower.play();
                        }
                    }
                    if (colisiono == 'V') {
                        colisiono = 'F';
                        soundRebote.play();
                    }
                    if (verifPowerup) {//.
                        verifPowerup = false;
                        generarPoweup(powerup, &isPowerupActivated, &activarReloj);
                    }

                    vericarGanar(ladrillos, &menuGanar);
                    if (menuGanar) {
                        menuGanar = false;
                        estado = GANADOR;
                    }

                }//End if.

                switch (vidas) {//Beginning of switch.
                    case 1: {
                        numLifes.setMessage("1");
                        break;
                    }
                    case 2: {
                        numLifes.setMessage("2");
                        break;
                    }
                    case 3: {
                        numLifes.setMessage("3");
                        break;
                    }
                    default: {
                        numLifes.setMessage("0");
                        break;
                    }
                }//End switch.


                break;
        }
        //--   INGAME ACTIONS:

        //--   REFRESH SCREEN:
        w.clear(Color(20, 20, 100, 150));

        w.draw(sScreenBackground);

        //-   OBJECT ILLUSTRATION:
        switch (estado) {
            case JUGANDO: {
                playerbar.dibujar(&w);
                ball.draw(&w);
                mostrarLadrillos(ladrillos, &w);
                lifes.draw(&w);
                numLifes.draw(&w);
                if (isPowerupActivated) {
                    powerIcon.draw(&w);
                }
                int aux = 0;
                for (int i = 0; i < stackEmptyHeart.size(); i++) {//Draw empty hearts.
                    aux = i + 1;
                    Vidas vid(&w, aux);
                    vid.draw(&w, 0);
                }
                for (int i = 0; i < stackFullHeart.size(); i++) {//Draw full hearts.
                    aux = aux + 1;
                    Vidas vid(&w, aux);
                    vid.draw(&w, 1);
                }
                break;
            }
            case GANADOR:
                if(tiempoOn){
                    tiempo.draw(&w);
                    timeUserTxt.draw(&w);
                }
                win.draw(&w);
                w.draw(barra);
                ingUser.draw(&w);
                usuario.draw(&w);
                break;
            case PODIO:
                tituloScores.draw(&w);
                scores.draw(&w);
                tryAgain.draw(&w);
                quit.draw(&w);
                break;
            case PERDEDOR:
                turboMusic.stop();
                gameOver.draw(&w);
                tryAgain.draw(&w);
                quit.draw(&w);

                break;
            case MENU:
                w.draw(sMenuBackground);
                menuPrincipal.draw(w);
                break;
        }
        w.display();
    }//End While Windows Open.
//*  CLOSING PROGRAM:
    return 0;
}//END MAIN.
void mapClean(LinkedList<Ladrillo *> &bricks) {
    Ladrillo *aBorrar = nullptr;
    for (bricks.begin(); !bricks.ended(); bricks.next()) {
        aBorrar = bricks.get();
        bricks.remove(aBorrar);
        delete aBorrar;
    }
}

void crearLadrillos(LinkedList<Ladrillo *> &bricks) {
    srand(time(NULL));
    int numeroRnd = 0;
    numeroRnd = rand() % 5 + 1;
    numeroRnd = 5;
    std::ifstream a;
    std::string nombreA = "textos/level";
    nombreA += std::to_string(numeroRnd);
    nombreA += ".txt";
    a.open(nombreA);
    readFilesLevel(&a, bricks);


}

void vericarGanar(LinkedList<Ladrillo *> &bricks, bool *menuGanar) {
    if (bricks.getSize() == 0) {
        *menuGanar = true;
    }
}

void readFilesLevel(std::ifstream *a, LinkedList<Ladrillo *> &bricks) {
    int idLadri = 0;
    std::string linea;
    int fila = 0;
    fflush(stdin);
    while (getline(*a, linea)) {
        for (int col = 0; col < linea.length(); col++) {
            switch (linea[col]) {
                case 'o': {
                    bricks.put(new Ladrillo(130, 0, col, fila, idLadri, "imagenes/Brick1v2.png"), idLadri);
                    idLadri++;
                    break;
                }
                case 'l': {
                    bricks.put(new Ladrillo(130, 0, col, fila, idLadri, "imagenes/Brick5.png"), idLadri);
                    idLadri++;
                    break;
                }
                case 'm': {
                    bricks.put(new Ladrillo(130, 0, col, fila, idLadri, "imagenes/Brick7.png"), idLadri);
                    idLadri++;
                    break;
                }
                case 'r': {
                    bricks.put(new Ladrillo(130, 0, col, fila, idLadri, "imagenes/Brick4.png"), idLadri);
                    idLadri++;
                    break;
                }
            }
        }
        fila++;
    }
    a->close();
}

void mostrarLadrillos(LinkedList<Ladrillo *> &bricks, RenderWindow *w) {

    for (bricks.begin(); !bricks.ended(); bricks.next()) {
        bricks.get()->draw(w);
    }
}

void cargarPoweup(Queue<int> &powerup) {

    for (int i = 0; i < 10; i++) {
        powerup.enqueue(i);
    }
}

void generarPoweup(Queue<int> &powerup, bool *isPowerupActivated, bool *activarReloj) {
    srand(time(NULL));
    int numeroRnd = 0;
    numeroRnd = rand() % 100 + 1;
    std::cout << "El numero rnd es:" << numeroRnd << std::endl;
    if ((numeroRnd <= 60) && (numeroRnd >= 40)) {
        if ((*isPowerupActivated == false) && (!Keyboard::isKeyPressed(Keyboard::T))) {
            std::cout << "poder activado" << std::endl;
            std::cout << powerup.front() << std::endl;
            powerup.dequeue();
            *isPowerupActivated = true;
            *activarReloj = true;
        } else {

        }
    }

}

void compararTiempos(bestPlayer top[10], int userMin, int userSec, int userMs, std::string userName) {

    int topMin[10] = {0}, topSec[10] = {0}, topMs[10] = {0}, i = 0;

    /*std::cout<<"------- PODIO --------"<<"\n";
    for (int j = 0; j <10 ; ++j) {
        std::cout<<top[j].userName<<"\t";
        std::cout<<top[j].min<<"\t";
        std::cout<<top[j].sec<<"\t";
        std::cout<<top[j].ms<<"\n";
    }*/

    for (i = 0; i < 10; i++) {
        //std::cout<<top[i].min<<std::endl;
        topMin[i] = std::stoi(top[i].min);
        topSec[i] = std::stoi(top[i].sec);
        topMs[i] = std::stoi(top[i].ms);


        if (topMin[i] > userMin){
            ordenarTop(top, userMin, userSec, userMs, userName, i);
            break;

        } else if (topSec[i] > userSec){
            ordenarTop(top, userMin, userSec, userMs, userName, i);
            break;

        } else if (topMs[i] > userMs){
            ordenarTop(top, userMin, userSec, userMs, userName, i);
            break;
        }
    }

}

void ordenarTop(bestPlayer top[10], int userMin, int userSec, int userMs, std::string userName, int pos){
    bestPlayer aux[10];
    //userName = userName + "\t";
    std::ofstream archivo;
    archivo.open("textos/nombres.txt");//std::ios::out

    /*std::cout<<"------- PODIO --------"<<"\n";
       for (int j = 0; j <10 ; ++j) {
           std::cout<<top[j].userName<<"\t";
           std::cout<<top[j].min<<"\t";
           std::cout<<top[j].sec<<"\t";
           std::cout<<top[j].ms<<"\n";
       }*/
    for (int j = 0; j < 10 ; ++j) {
        aux[j].min = "";
        aux[j].sec = "";
        aux[j].ms = "";
        aux[j].userName = "";
    }

    for (int j = 0; j < 10 ; ++j) {

if (j < pos) {
    aux[j].min = top[j].min;
    aux[j].sec = top[j].sec;
    aux[j].ms = top[j].ms;
    aux[j].userName = top[j].userName;
}
        if (j == pos) {
            aux[j].min = std::to_string(userMin);
            if (aux[j].min.size() < 2){
                aux[j].min = "0" + aux[j].min;
            }
            aux[j].sec = std::to_string(userSec);
            if (aux[j].sec.size() < 2){
                aux[j].sec = "0" + aux[j].sec;
            }
            aux[j].ms = std::to_string(userMs);
            aux[j].userName = userName;

            switch (aux[j].userName.size()){
                case 1:{
                    aux[j].userName = userName + "           ";
                    break;
                }
                case 2:{
                    aux[j].userName = userName + "          ";
                    break;
                }
                case 3:{
                    aux[j].userName = userName + "         ";
                    break;
                }
                case 4:{
                    aux[j].userName = userName + "        ";
                    break;
                }
                case 5:{
                    aux[j].userName = userName + "       ";
                    break;
                }
                case 6:{
                    aux[j].userName = userName + "      ";
                    break;
                }
                case 7:{
                    aux[j].userName = userName + "     ";
                    break;
                }
                case 8:{
                    aux[j].userName = userName + "    ";
                    break;
                }
                case 9:{
                    aux[j].userName = userName + "   ";
                    break;
                }
                case 10:{
                    aux[j].userName = userName + "  ";
                    break;
                }
                case 11:{
                    aux[j].userName = userName + " ";
                    break;
                }
            }
        }
        if (j > pos) {
            aux[j].min = top[j - 1].min;
            aux[j].sec = top[j - 1].sec;
            aux[j].ms = top[j - 1].ms;
            aux[j].userName = top[j - 1].userName;
        }

        /*std::cout<<aux[j].userName<<"\t";
        std::cout<<aux[j].min<<"\t";
        std::cout<<aux[j].sec<<"\t";
        std::cout<<aux[j].ms<<"\n";*/

    }
    for (int j = 0; j < 10 ; ++j) {
        top[j].min = aux[j].min;
        top[j].sec = aux[j].sec;
        top[j].ms= aux[j].ms ;
        top[j].userName = aux[j].userName;

        archivo << top[j].userName << "-" + top[j].min << ":" + top[j].sec << ":" + top[j].ms << std::endl;

       /* std::cout<<top[j].userName<<"\t";
        std::cout<<top[j].min<<"\t";
        std::cout<<top[j].sec<<"\t";
        std::cout<<top[j].ms<<"\n";*/
    }

    std::cout<<leerPodio();
}

std::string leerPodio(){
    std::ifstream archivo;
    archivo.open("textos/nombres.txt", std::ios::in);
    std::string podio;
    std::string linea;

    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo" << std::endl;
    }
int i=0;
    while (!archivo.eof()){
        getline(archivo,linea);
        podio += linea + "\n";
    }

    return podio;
}