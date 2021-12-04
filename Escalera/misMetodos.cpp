#include "misMetodos.h"

/*
  Dibija el menu de inicio del juego donde estara la seleccion de nivel
  y contrincante de juego
*/
void menu(){
    int opcion = 0;

    while((opcion != 1) && (opcion != 2) && (opcion != 3)){
        gotoxy(0, 0); printf("Elige el nivel: ");
        gotoxy(1, 0); printf("1. Facil");
        gotoxy(2, 0); printf("2. Medio");
        gotoxy(3, 0); printf("3. Dificil");
        gotoxy(0, 16); cin>>opcion;
        gotoxy(5,0);printf("%d",opcion);
    }

    system("cls");


    if(opcion == 1){
        printf("hola");
        cantidadColumna = 11;
        cantidadFila = 7;
        canTrampaPantano =  3;
        canTrampaCangrejo = 3;
        canTrampaPierdeVida = 3;
    }
    if(opcion == 2){
        cantidadColumna = 13;
        cantidadFila = 7;
        canTrampaPantano =  4;
        canTrampaCangrejo = 4;
        canTrampaPierdeVida = 4;
    }
    if(opcion == 3){
        cantidadColumna = 17;
        cantidadFila = 7;
        canTrampaPantano =  5;
        canTrampaCangrejo = 6;
        canTrampaPierdeVida = 6;
    }
    opcion = 0;

    while((opcion != 1) && (opcion != 2)){
        gotoxy(0, 0); printf("Escoge el modo: ");
        gotoxy(1, 0); printf("1. PvP");
        gotoxy(2, 0); printf("2. PvIA");
        gotoxy(0, 16); cin>>opcion;
    }


    if(opcion == 1){
        IA = false;
    }
    if(opcion == 2){
        IA = true;
    }
    system("cls");
    iniciarJuego();
}

/*
* Genera todo el tablero del juego, llenando el arreglo de juego
* y dibujando los jugadores
*/
void iniciarJuego(){
    for(int i = 1; i <= cantidadFila + 1; i++){
        for(int j = 1; j <= cantidadColumna + 1; j++){
            arrayJuego[i][j] = 0;
        }
    }
    dibujarFigura(posicionXP1, posicionYP1, true);
    dibujarFigura(posicionXP2, posicionYP2, false);
    tablero();
    turnoJugador();
    getch();
}

/*
* Se encarga de aplicar cada uno de los efectos de las trampas a los jugadores
*/
void validarTrampa(bool jugador){
    if(jugador == true){
        if(arrayJuego[posicionXP1][posicionYP1] == 1){
            pantanoP1 = true;
            return;
        }
        if(arrayJuego[posicionXP1][posicionYP1] == 2){
            retroceder(posicionXP1, posicionYP1, true);
            return;
        }
        if(arrayJuego[posicionXP1][posicionYP1] == 3){
            vidaP1--;
            dibujarFigura(posicionXP1,posicionYP1, jugador);
            return;
        }
        if(arrayJuego[posicionXP1][posicionYP1] == 4){
            contador1++;
            pasarP1 = true;
            if(contador1 == 2){
                pasarP1 = false;
            }
            return;
        }
        if(arrayJuego[posicionXP1][posicionYP1] == 5){
            vidaP1++;
            dibujarFigura(posicionXP1,posicionYP1, true);
            return;
        }
        if(arrayJuego[posicionXP1][posicionYP1] == 6){
            limpiarJugador(posicionXP2,posicionYP2,false);
            posicionXP2 = 1;
            posicionYP2 = 1;
            dibujarFigura(posicionXP2,posicionYP2, false);
            return;
        }
    }else{
        if(arrayJuego[posicionXP2][posicionYP2] == 1){
                pantanoP2 = true;
                return;
            }
        if(arrayJuego[posicionXP2][posicionYP2] == 2){
            retroceder(posicionXP2, posicionYP2, jugador);
            return;
        }
        if(arrayJuego[posicionXP2][posicionYP2] == 3){
            vidaP2--;
            dibujarFigura(posicionXP2,posicionYP2, false);
            return;
        }
        if(arrayJuego[posicionXP2][posicionYP2] == 4){
            contador2++;
            pasarP2 = true;
            if(contador2 == 2){
                pasarP2 = false;
            }
            return;
        }
        if(arrayJuego[posicionXP2][posicionYP2] == 5){
            vidaP2++;
            dibujarFigura(posicionXP2,posicionYP2, false);
            return;
        }
        if(arrayJuego[posicionXP2][posicionYP2] == 6){
            limpiarJugador(posicionXP1,posicionYP1,true);
            posicionXP1 = 1;
            posicionYP1 = 1;
            dibujarFigura(posicionXP1,posicionYP1, true);
            return;
        }
    }
}

/*
* Se encarga de que las trampas no se generen de manera consecutiva
* y que tampoco ocupen el lugar de una ya generada
*/
bool validarImprimir(int x, int y, int tipo){
    if((x == 1) && (y == 1)){
        return false;
    }
    if((x == cantidadFila) && (y == cantidadColumna)){
        return false;
    }
    if(tipo == 1){
        if((x == cantidadFila) && (y + 2 > cantidadColumna)){
        return false;
        }
        if((x % 2 != 0) && ((y - 1 >= 1) && (y + 3 <= cantidadColumna))){
            if((arrayJuego[x][y] == 0)  && (arrayJuego[x][y-1] == 0) &&
               (arrayJuego[x][y+1] == 0) &&(arrayJuego[x][y+2] == 0) &&
               (arrayJuego[x][y+3] == 0)){
                return true;
            }
        }
        if((x % 2 == 0) && ((y - 3 >= 1) && (y + 1 <= cantidadColumna))){
            if((arrayJuego[x][y] == 0)  && (arrayJuego[x][y+1] == 0) &&
               (arrayJuego[x][y-1] == 0) &&(arrayJuego[x][y-2] == 0) &&
               (arrayJuego[x][y-3] == 0)){
                return true;
            }
        }
        if((y == 1) && (x % 2 != 0)){
            if((arrayJuego[x][y] == 0)  && (arrayJuego[x - 1][y] == 0) &&
               (arrayJuego[x][y + 1] == 0) &&(arrayJuego[x][y + 2] == 0) &&
               (arrayJuego[x][y + 3] == 0)){
                return true;
            }
        }
        if((y == 1) && (x % 2 == 0)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x + 1][y] == 0) &&
               (arrayJuego[x][y + 1] == 0) && (arrayJuego[x + 1][y + 1] == 0)&&
               (arrayJuego[x + 1][y + 2] == 0)){
                return true;
            }
        }
        if((y == cantidadColumna) && (x % 2 != 0)){
            if((arrayJuego[x][y] == 0)  && (arrayJuego[x][y - 1] == 0) &&
               (arrayJuego[x + 1][y] == 0) &&(arrayJuego[x + 1][y - 1] == 0) &&
               (arrayJuego[x + 1][y - 2] == 0)){
                return true;
            }
        }
        if((y == cantidadColumna) && (x % 2 == 0)){
            if((arrayJuego[x][y] == 0)  && (arrayJuego[x - 1][y] == 0) &&
               (arrayJuego[x][y - 1] == 0) &&(arrayJuego[x][y - 2] == 0) &&
               (arrayJuego[x][y - 3] == 0)){
                return true;
            }
        }
        return false;
    }else if(tipo == 4){
        if((x == cantidadFila) && (y + 1 > cantidadColumna)){
            return false;
        }
        if((x % 2 != 0)&&(y - 1 >= 1) && (y + 2 <= cantidadColumna)){
            if((arrayJuego[x][y] == 0)  && (arrayJuego[x][y - 1] == 0) &&
               (arrayJuego[x][y + 1] == 0) &&(arrayJuego[x][y + 2] == 0)){
                return true;
            }
        }
        if((x % 2 == 0)&&(y - 2 >= 1) && (y + 1 <= cantidadColumna)){
            if((arrayJuego[x][y] == 0)  && (arrayJuego[x][y - 1] == 0) &&
               (arrayJuego[x][y + 1] == 0) &&(arrayJuego[x][y - 2] == 0)){
                return true;
            }
        }
        if((y == 1) && (x % 2 != 0)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x - 1][y] == 0) &&
               (arrayJuego[x][y + 1] == 0) && (arrayJuego[x][y + 2] == 0)){
                return true;
            }
        }
        if((y == 1) && (x % 2 == 0)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x + 1][y] == 0) &&
               (arrayJuego[x][y + 1] == 0) && (arrayJuego[x + 1][y + 1] == 0)){
                return true;
            }
        }
        if((y == cantidadColumna) && (x % 2 != 0)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x][y - 1] == 0) &&
               (arrayJuego[x + 1][y] == 0) && (arrayJuego[x + 1][y - 1] == 0)){
                return true;
            }
        }
        if((y == cantidadColumna) && (x % 2 == 0)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x - 1][y] == 0) &&
               (arrayJuego[x][y - 1] == 0) && (arrayJuego[x][y - 2] == 0)){
                return true;
            }
        }
        return false;
    }else{
        if((y - 1 >= 1) && (y + 1 <= cantidadColumna)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x][y - 1] == 0) && (arrayJuego[x][y + 1] == 0)){
                return true;
            }
        }
        if((y == 1) && (x%2 != 0)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x - 1][y] == 0) && (arrayJuego[x][y + 1] == 0)){
                return true;
            }
        }
        if((y == 1) && (x % 2 == 0)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x + 1][y] == 0) && (arrayJuego[x][y + 1] == 0)){
                return true;
            }
        }
        if((y == cantidadColumna) && (x % 2 != 0)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x][y - 1] == 0) && (arrayJuego[x + 1][y] == 0)){
                return true;
            }
        }
        if((y == cantidadColumna) && (x % 2 == 0)){
            if((arrayJuego[x][y] == 0) && (arrayJuego[x - 1][y] == 0) && (arrayJuego[x][y - 1] == 0)){
                return true;
            }
        }
        return false;
    }
}

/*
* Retorna 5 posiciones al jugador despues de caer en la trampa cangrejo
*/
void retroceder(int x, int y, bool jugador){
    int contador = 0, auxY = 5;

    limpiarJugador(x,y,jugador);

    if((x == 1) && (y - 5 < 1)){
        if(jugador == true){
            posicionYP1 = 1;
        }else{
            posicionYP2 = 1;
        }
        dibujarFigura(1, 1, jugador);
        if(jugador == true){
            validarTrampa(true);
        }else{
            validarTrampa(false);
        }
        return;
    }
    if((x % 2 != 0) && (y - 5 >= 1)){
        if(jugador == true){
            posicionYP1 -= 5;
        }else{
            posicionYP2 -= 5;
        }
        dibujarFigura(x, y - 5, jugador);
        if(jugador == true){
            validarTrampa(true);
        }else{
            validarTrampa(false);
        }
        return;
    }
    if((x % 2 == 0) && (y + 5 <= cantidadColumna)){
        if(jugador == true){
            posicionYP1 += 5;
        }else{
            posicionYP2 += 5;
        }
        dibujarFigura(x, y + 5, jugador);
        if(jugador == true){
            validarTrampa(true);
        }else{
            validarTrampa(false);
        }
        return;
    }
    if((x % 2 != 0) && (y - 5 < 1)){
        while(y - auxY != 1){
            auxY--;
            contador++;
        }
        y -= auxY;
        x--;
        y += contador - 1;

        if(jugador == true){
            posicionXP1 = x;
            posicionYP1 = y;
        }else{
            posicionXP2 = x;
            posicionYP2 = y;
        }
        dibujarFigura(x, y, jugador);
        if(jugador == true){
            validarTrampa(true);
        }else{
            validarTrampa(false);
        }
        return;
    }
    if((x % 2 == 0) && (y + 5 > cantidadColumna)){
        while(y + auxY != cantidadColumna){
            auxY--;
            contador++;
        }
        y += auxY;
        x--;
        y -= contador - 1;
        if(jugador == true){
            posicionXP1 = x;
            posicionYP1 = y;
        }else{
            posicionXP2 = x;
            posicionYP2 = y;
        }
        dibujarFigura(x, y, jugador);
        if(jugador == true){
            validarTrampa(true);
        }else{
            validarTrampa(false);
        }
        return;
    }
}

/*
* Hace que los jugadores se alternen al tirar, y se repetira
* hasta que uno de los dos gane
*/
void turnoJugador(){
    int cantidadP1, cantidadP2;

    while(ganoP1 == false && ganoP2 == false){
        if(turnoP1 == true){
            pantanoP1 = false;
            validarTrampa(true);
            if((arrayJuego[posicionXP1][posicionXP2] == 4) && (arrayJuego[posicionXP2][posicionXP2] == 4)){
                pasarP1 == false;
            }
            if(pasarP1 == false){
                dibujarFigura(posicionXP2, posicionYP2, false);
                cantidadP1 = rotaDadoPlayer();

                for(int i = 1; i <= cantidadP1; i++){
                    moverJugador(1, posicionXP1, posicionYP1, cantidadFila, cantidadColumna, true);
                    Sleep(500);
                }
            }
            turnoP1 = false;
        }else{
            pantanoP2 = false;
            validarTrampa(false);
            if((arrayJuego[posicionXP1][posicionXP2] == 4) && (arrayJuego[posicionXP2][posicionXP2] == 4)){
                pasarP2 == false;
            }
            if(pasarP2 == false){
                if(IA == false){
                    cantidadP2 = rotaDadoPlayer();
                }else{
                    cantidadP2 = rotaDadoIA();
                }
                for(int i = 1; i <= cantidadP2; i++){
                    moverJugador(1, posicionXP2, posicionYP2, cantidadFila, cantidadColumna, false);
                    Sleep(500);
                }
            }
            turnoP1 = true;
        }
        if(vidaP1 == 0){
            ganoP2 = true;
        }
        if(vidaP2 == 0){
            ganoP1 = true;
        }
    }
    validarGanador();
}

/*
* Imprime en pantalla al ganador
*/
void validarGanador(){
    system("cls");
    gotoxy(13,32);

    if(ganoP1 == true){
        printf("GANO EL PLAYER 1");
    }else{
        printf("GANO EL PLAYER 2");
    }
}

/*
* Mueve al jugador la cantidad de veces que se le ingrese
*/
void moverJugador( int cantidad,  int posX, int posY, unsigned int fila, unsigned int columna, bool player){
    int contador = 0, i = 0;

    limpiarJugador(posX, posY, player);

    if((posY + cantidad == columna) && (posX == fila)){
        if(player == true){
            ganoP1 = true;
        }else{
            ganoP2 = true;
        }
        dibujarFigura(posX, posY + cantidad, player);
        return;
    }
    if((posY + cantidad > columna) && (posX == fila)){
        dibujarFigura(posX, posY, player);
        return;
    }
    if((posY + cantidad <= columna) && (posX%2 != 0)){
        if(player == true){
            posicionYP1 = posY + cantidad;
        }else{
            posicionYP2 = posY + cantidad;
        }
        dibujarFigura(posX, posY + cantidad, player);
        return;
    }
    if((posY - cantidad >= 1) && (posX%2 == 0)){
        if(player == true){
            posicionYP1 = posY - cantidad;
        }else{
            posicionYP2 = posY - cantidad;
        }
        dibujarFigura(posX, posY - cantidad, player);
        return;
    }
    if((posY + cantidad > columna) && (posX%2 != 0)){
        if(player == true){
            posicionXP1 = posX + 1;
        }else{
            posicionXP2 = posX + 1;
        }
        dibujarFigura(posX + 1, posY, player);
        return;
    }
    if((posY - cantidad < 1) && (posX%2 == 0)){
        if(player == true){
            posicionXP1 = posX + 1;
        }else{
            posicionXP2 = posX + 1;
        }
        dibujarFigura(posX + 1, posY, player);
        return;
    }
}

/*
* Genera las trampas y las guarda en el arreglo del juego
*/
void generarTrampas(){
    int x, y,contador = 0, auxI = 0;
    bool valido = false;
    srand(time(NULL));

    for(int i = 1; i <= canTrampaPantano; i++){
        while(valido == false){
            if(valido == false){
                x = 1 + rand() % cantidadFila;
                y = 1 + rand() % cantidadColumna;
                valido = validarImprimir(x, y, 1);
            }
        }
        dibujarTrampaPantano(x, y);
        valido = false;
    }

    for(int i = 1; i <= canTrampaPierdeturno; i++){
        while(valido == false){
            if(valido == false){
                x = 1 + rand() % cantidadFila;
                y = 1 + rand() % cantidadColumna;
                valido = validarImprimir(x, y, 4);
            }
        }
        dibujarTrampaPierdeTurnos(x, y);
        valido = false;
    }

    for(int i = 1; i <= canTrampaCangrejo; i++){
        while(valido == false){
            if(valido == false){
                x = 1 + rand() % cantidadFila;
                y = 1 + rand() % cantidadColumna;
                valido = validarImprimir(x, y, 2);
            }
        }
        dibujarTrampaCangrejo(x, y);
        valido = false;
    }
    for(int i = 1; i <= canTrampaPierdeVida; i++){
        while(valido == false){
            if(valido == false){
                x = 1 + rand() % cantidadFila;
                y = 1 + rand() % cantidadColumna;
                valido = validarImprimir(x, y, 3);
            }
        }
        dibujarTrampaPierdeVida(x, y);
        valido = false;
    }

    for(int i = 1; i <= canBeneficio1; i++){
        while(valido == false){
            if(valido == false){
                x = 1 + rand() % cantidadFila;
                y = 1 + rand() % cantidadColumna;
                valido = validarImprimir(x, y, 1);
            }
        }
        dibujarBeneficio1(x, y);
        valido = false;
    }

    for(int i = 1; i <= canBeneficio2; i++){
        while(valido == false){
            if(valido == false){
                x = 1 + rand() % cantidadFila;
                y = 1 + rand() % cantidadColumna;
                valido = validarImprimir(x, y, 1);
            }
        }
        dibujarBeneficio2(x, y);
        valido = false;
    }
}

/*
* Dibuja los bordes del tablero de juego
*/
void dibujarBorde(unsigned int numFilaInicial, unsigned int numColumnaInicial,unsigned int numFila, unsigned int numColumna){
    numFila = numFila + numFilaInicial;
    numColumna = numColumna + numColumnaInicial;

    for(int i = numFilaInicial; i <= numFila; i++){
        for(int j = numColumnaInicial; j <= numColumna; j++){
            if(j ==  numColumnaInicial || j == numColumna){
                gotoxy(i, j);
                printf("%c", BARRA_VERTICAL);
            }
            if(i== numFilaInicial || i == numFila){
                gotoxy(i, j);
                printf("%c", BARRA_HORIZONTAL);
            }
        }
    }
    gotoxy(numFilaInicial,numColumnaInicial);
    printf("%c", ESQ_SI);
    gotoxy(numFilaInicial,numColumna);
    printf("%c", ESQ_SD);
    gotoxy(numFila,numColumnaInicial);
    printf("%c", ESQ_II);
    gotoxy(numFila,numColumna);
    printf("%c", ESQ_ID);
}

/*
* Genera el tablero
*/
void tablero(){
    int filas = cantidadFila * 4;
    int columnas = cantidadColumna * 4;

    for(int i = 0; i <= filas; i++){
        for(int j = 0; j <= columnas; j++){
            if(i == 0 || i == filas){
                gotoxy(i, j);   printf("%c", BARRA_HORIZONTAL);
            }
            if(j == 0 || j == columnas){
                gotoxy(i, j);   printf("%c", BARRA_VERTICAL);
            }
            if((i != 0 && i != filas && i%4 == 0) || (j != 0 && j != columnas && j%4 == 0) ){
                    if(i%4 == 0){
                        gotoxy(i, j);   printf("%c", BARRA_HORIZONTAL);
                    }
                    if(j%4 == 0){
                        gotoxy(i, j);   printf("%c", BARRA_VERTICAL);
                    }
            }
            if(j == 0 || j == columnas){
                if(i != 0 && i != filas && j == 0 && i%4 == 0){
                    gotoxy(i, j);   printf("%c", CRUCE_DERECHA);
                }
                if(i != 0 && i != filas && j == columnas && i%4 == 0){
                    gotoxy(i, j);   printf("%c", CRUCE_IZQUIERDA);
                }
            }
            if(j != 0 && j != columnas && j%4 == 0){
                if(i == 0){
                    gotoxy(i, j);   printf("%c", T_SUPERIOR);
                }
                if(i == filas){
                    gotoxy(i, j);   printf("%c", T_INFERIOR);
                }
                if(i%4 == 0 && j%4 == 0 && i != 0 && j != 0 && i != filas && j != columnas){
                    gotoxy(i, j);   printf("%c", CRUCE);
                }
            }
        }
    }
    gotoxy(0,0);            printf("%c", ESQ_SI);
    gotoxy(0,columnas);     printf("%c", ESQ_SD);
    gotoxy(filas,0);        printf("%c", ESQ_II);
    gotoxy(filas,columnas); printf("%c", ESQ_ID);

    gotoxy(3,1);
    setColor(AZUL);
    printf("INI");
    setColor(DEFECTO);

    gotoxy(cantidadFila * 4 - 1,  cantidadColumna * 4 - 3);
    setColor(AZUL);
    printf("FIN");
    setColor(DEFECTO);

    gotoxy(6, columnas + 5);
    printf("Trampa pantano:        %d",canTrampaPantano);
    setColor(COLOR_PANTANO);
    printf(" %c", FIGURA_TRAMPA);
    setColor(DEFECTO);
    gotoxy(8, columnas + 5);
    printf("Trampa cangrejo:       %d",canTrampaCangrejo);
    setColor(COLOR_CANGREJO);
    printf(" %c", FIGURA_TRAMPA);
    setColor(DEFECTO);
    gotoxy(10, columnas + 5);
    printf("Trampa pierde vida:    %d",canTrampaPierdeVida);
    setColor(COLOR_PERDER_VIDA);
    printf(" %c", FIGURA_TRAMPA);
    setColor(DEFECTO);
    gotoxy(12, columnas + 5);
    printf("Trampa pierde turnos:  %d", canTrampaPierdeturno);
    setColor(COLOR_PERDER_TURNO);
    printf(" %c", FIGURA_TRAMPA);
    setColor(DEFECTO);
    gotoxy(14, columnas + 5);
    printf("Gana vida:             %d",canBeneficio1);
    printf(" %c", FIGURA_TRAMPA);
    gotoxy(16, columnas + 5);
    printf("Regresa al enemigo:    %d",canBeneficio2);
    setColor(COLOR_DEVUELVE_ENEMIGO);
    printf(" %c", FIGURA_TRAMPA);
    setColor(DEFECTO);
    generarTrampas();
}

int rotaDadoPlayer(){
    char tecla = 31;
    int posX = cantidadFila * 4 + 2, numDado = 1, posY;

    if(turnoP1 == true){
        setColor(ROJO);
        posY = DADO_COLUMNA_INICIAL;
        dibujarBorde(posX-1, posY-1,4,4);
        gotoxy(posX + 4, posY + 1);
        printf("P1");
    }else{
        setColor(VERDE);
        posY = DADO_COLUMNA_INICIAL + 10;
        dibujarBorde(posX-1, posY-1,4,4);
        gotoxy(posX + 4, posY + 1);
        printf("P2");
    }

    while(tecla != ESPACIO){
        if(kbhit()){
            tecla = getch();
        }
        switch(numDado){
            case 1:
                gotoxy(posX, posY);     printf("   ");
                gotoxy(posX + 1, posY); printf(" + ");
                gotoxy(posX + 2, posY); printf("   ");
                break;
            case 2:
                gotoxy(posX, posY);     printf("  +");
                gotoxy(posX + 1, posY); printf("   ");
                gotoxy(posX + 2, posY); printf("+  ");
                break;
            case 3:
                gotoxy(posX, posY);     printf("  +");
                gotoxy(posX + 1, posY); printf(" + ");
                gotoxy(posX + 2, posY); printf("+  ");
                break;
            case 4:
                gotoxy(posX, posY);     printf("+ +");
                gotoxy(posX + 1, posY); printf("   ");
                gotoxy(posX + 2, posY); printf("+ +");
                break;
            case 5:
                gotoxy(posX, posY);     printf("+ +");
                gotoxy(posX + 1, posY); printf(" + ");
                gotoxy(posX + 2, posY); printf("+ +");
                break;
            case 6:
                gotoxy(posX, posY);     printf("+ +");
                gotoxy(posX + 1, posY); printf("+ +");
                gotoxy(posX + 2, posY); printf("+ +");
                break;
        }
        if(tecla != ESPACIO){
            numDado += 1;
        }
        if(numDado > 6){
            numDado = 1;
        }
        Sleep(100);
    }
    //Pone en blanco el jugador que no este de turno
    if(turnoP1 == true){
        setColor(DEFECTO);
        posY = DADO_COLUMNA_INICIAL;
        dibujarBorde(posX-1, posY-1,4,4);
        gotoxy(posX + 4,posY + 1);
        printf("P1");
    }else{
        setColor(DEFECTO);
        posY = DADO_COLUMNA_INICIAL + 10;
        dibujarBorde(posX-1, posY-1,4,4);
        gotoxy(posX + 4,posY + 1);
        printf("P2");
    }
    //Cuando la trampa pantano esta activa solo retorna 1
    if(turnoP1 == true){
        if(pantanoP1 == false){
            return numDado;
        }else{
            return 1;
        }
    }else{
        if(pantanoP2 == false){
            return numDado;
        }else{
            return 1;
        }
    }

}

int rotaDadoIA(){
    int posX = cantidadFila * 4 + 2, posY = DADO_COLUMNA_INICIAL + 10, numDado = 1, numMaquina = 0;
    char tecla = 31;

    setColor(VERDE);
    posY = DADO_COLUMNA_INICIAL + 10;
    dibujarBorde(posX-1, posY-1,4,4);
    gotoxy(posX + 4,posY + 1);
    printf("P2");

    //Se repite mientras no presiones la tecla de parada
    while(tecla != N_1){
        srand(time(NULL));
        numMaquina = 1 + rand()%6;

        if(numMaquina == 3){
            tecla = N_1;
        }

        //Valida si se presiona una tecla
        if(kbhit()){
            tecla = getch();
        }
            switch(numDado){
                case 1:
                    gotoxy(posX, posY);     printf("   ");
                    gotoxy(posX + 1, posY); printf(" + ");
                    gotoxy(posX + 2, posY); printf("   ");
                    break;
                case 2:
                    gotoxy(posX, posY);     printf("  +");
                    gotoxy(posX + 1, posY); printf("   ");
                    gotoxy(posX + 2, posY); printf("+  ");
                    break;
                case 3:
                    gotoxy(posX, posY);     printf("  +");
                    gotoxy(posX + 1, posY); printf(" + ");
                    gotoxy(posX + 2, posY); printf("+  ");
                    break;
                case 4:
                    gotoxy(posX, posY);     printf("+ +");
                    gotoxy(posX + 1, posY); printf("   ");
                    gotoxy(posX + 2, posY); printf("+ +");
                    break;
                case 5:
                    gotoxy(posX, posY);     printf("+ +");
                    gotoxy(posX + 1, posY); printf(" + ");
                    gotoxy(posX + 2, posY); printf("+ +");
                    break;
                case 6:
                    gotoxy(posX, posY);     printf("+ +");
                    gotoxy(posX + 1, posY); printf("+ +");
                    gotoxy(posX + 2, posY); printf("+ +");
                    break;
            }
        if(tecla != N_1){
            numDado += 1;
        }
        if(numDado > 6){
            numDado = 1;
        }
        Sleep(100);
    }
    setColor(DEFECTO);
    posY = DADO_COLUMNA_INICIAL + 10;
    dibujarBorde(posX-1, posY-1,4,4);
    gotoxy(posX + 4,posY + 1);
    printf("P2");

    //Cuando la trampa pantano esta activa solo retorna 1
    if(pantanoP2 == false){
        return numDado;
    }else{
        return 1;
    }
}

void dibujarFigura(unsigned int fila, unsigned int columna, bool player){
    gotoxy(2, cantidadColumna * 4 + 5);
    printf("Vidas P1: %d", vidaP1);
    setColor(ROJO);
    printf(" %c", FIGURA_JUGADOR_1);
    setColor(DEFECTO);

    gotoxy(4, cantidadColumna * 4 + 5);
    printf("Vidas P1: %d", vidaP2);
    setColor(VERDE);
    printf(" %c", FIGURA_JUGADOR_2);
    setColor(DEFECTO);

    if(player == true){
        setColor(ROJO);
        gotoxy(fila * 4 - 3, columna * 4 - 2);
        printf("%c", FIGURA_JUGADOR_1);
        setColor(DEFECTO);
     }else{
        setColor(VERDE);
        gotoxy(fila * 4 - 2, columna * 4 - 2);
        printf("%c", FIGURA_JUGADOR_2);
        setColor(DEFECTO);
     }
}

void dibujarTrampaPantano( int x,  int y){
    int contador = 0;
    int auxY = 2;

    if((x == 1) && (y == 1)){
        return;
    }
    if((x == cantidadFila) && (y == cantidadColumna)){
        return;
    }
    if((x == cantidadFila) && (y + 2 >= cantidadColumna)){
        return;
    }
    if((x % 2 != 0) && (y + 2 <= cantidadColumna)){
        for(int i = 0; i <= 2; i++){
            gotoxy(x * 4 - 3, y * 4 - 3);
            arrayJuego[x][y] = 1;
            setColor(COLOR_PANTANO);
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            y++;
        }
        return;
    }
    if((y + 2 > cantidadColumna) && (x%2 != 0)){
        while(y + auxY > cantidadColumna){
            auxY--;
            contador++;
        }
        for(int i = 0; i <= auxY; i++){
            gotoxy(x * 4 - 3, y * 4 - 3);
            arrayJuego[x][y] = 1;
            setColor(COLOR_PANTANO);
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            if(i != auxY){
                y++;
            }
        }
        x++;
        while(contador != 0){
            gotoxy(x * 4 - 3, y * 4 - 3);
            arrayJuego[x][y] = 1;
            setColor(COLOR_PANTANO);
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            contador--;
            if(contador != 0){
                y--;
            }
        }
        return;
    }
    if((x % 2 == 0) && (y - 2 >= 1)){
        for(int i = 0; i <= auxY; i++){
            gotoxy(x * 4 - 3, y * 4 - 3);
            arrayJuego[x][y] = 1;
            setColor(COLOR_PANTANO);
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            if(i != auxY){
                y--;
            }
        }
        return;
    }
    if((y - 2 < 1) && (x%2 == 0)){
        while(y - auxY < 1){
            auxY--;
            contador++;
        }

        for(int i = 0; i <= auxY; i++){
            gotoxy(x * 4 - 3, y * 4 - 3);
            arrayJuego[x][y] = 1;
            setColor(COLOR_PANTANO);
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            if(y != 1){
                y--;
            }
        }
        x++;
        while(contador != 0){
            gotoxy(x * 4 - 3, y * 4 - 3);
            arrayJuego[x][y] = 1;
            setColor(COLOR_PANTANO);
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            contador--;
            if(contador != 0){
                y++;
            }
        }
        return;
    }
}

void dibujarTrampaCangrejo(unsigned int x, unsigned int y){
    if((x == 1) && (y == 1)){
        return;
    }
    if((x == cantidadFila) && (y == cantidadColumna)){
        return;
    }
    gotoxy(x * 4 - 3, y * 4 -3 );
    arrayJuego[x][y] = 2;
    setColor(COLOR_CANGREJO);
    printf("%c", FIGURA_TRAMPA);
    setColor(DEFECTO);
}

void dibujarTrampaPierdeVida(unsigned int x, unsigned int y){
    if((x == 1) && (y == 1)){
        return;
    }
    if((x == cantidadFila) && (y == cantidadColumna)){
        return;
    }
    gotoxy(x * 4 - 3, y * 4 -3 );
    arrayJuego[x][y] = 3;
    setColor(COLOR_PERDER_VIDA);
    printf("%c", FIGURA_TRAMPA);
    setColor(DEFECTO);
}

void dibujarTrampaPierdeTurnos(unsigned int x, unsigned int y){
    if((x == 1) && (y == 1)){
        return;
    }
    if((x == cantidadFila) && (y == cantidadColumna)){
        return;
    }
    if((x == cantidadFila) && (y + 1 >= cantidadColumna)){
        return;
    }
    if((x % 2 != 0) && (y + 1 <= cantidadColumna)){
            gotoxy(x * 4 - 3,y * 4 -3 );
            arrayJuego[x][y] = 4;
            setColor(COLOR_PERDER_TURNO );
            printf("%c", FIGURA_TRAMPA);
            y++;
            gotoxy(x * 4 - 3, y * 4 -3 );
            arrayJuego[x][y] = 4;
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            return;
    }
    if((x % 2 == 0) && (y - 1 >= 1)){
            gotoxy(x * 4 - 3, y * 4 -3 );
            arrayJuego[x][y] = 4;
            setColor(COLOR_PERDER_TURNO );
            printf("%c", FIGURA_TRAMPA);
            y--;
            gotoxy(x * 4 - 3, y * 4 -3 );
            arrayJuego[x][y] = 4;
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            return;
    }
    if((x % 2 != 0) && (y == cantidadColumna)){
            gotoxy(x * 4 - 3, y * 4 -3 );
            arrayJuego[x][y] = 4;
            setColor(COLOR_PERDER_TURNO );
            printf("%c", FIGURA_TRAMPA);
            x++;
            gotoxy(x * 4 - 3, y * 4 -3 );
            arrayJuego[x][y] = 4;
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            return;
    }
    if((x % 2 == 0) && (y == 1)){
            gotoxy(x * 4 - 3, y * 4 -3 );
            setColor(COLOR_PERDER_TURNO );
            printf("%c", FIGURA_TRAMPA);
            arrayJuego[x][y] = 4;
            x++;
            gotoxy(x * 4 - 3, y * 4 -3 );
            arrayJuego[x][y] = 4;
            printf("%c", FIGURA_TRAMPA);
            setColor(DEFECTO);
            return;
    }
}

void dibujarBeneficio1(unsigned int x, unsigned int y){
    if((x == 1) && (y == 1)){
        return;
    }
    if((x == cantidadFila) && (y == cantidadColumna)){
        return;
    }
    gotoxy(x * 4 - 3, y * 4 -3 );
    arrayJuego[x][y] = 5;
    setColor(DEFECTO);
    printf("%c", FIGURA_TRAMPA);
    setColor(DEFECTO);
}

void dibujarBeneficio2(unsigned int x, unsigned int y){
    if((x == 1) && (y == 1)){
        return;
    }
    if((x == cantidadFila) && (y == cantidadColumna)){
        return;
    }
    gotoxy(x * 4 - 3, y * 4 -3 );
    arrayJuego[x][y] = 6;
    setColor(COLOR_DEVUELVE_ENEMIGO);
    printf("%c", FIGURA_TRAMPA);
    setColor(DEFECTO);
}

/*
* Elimina la figura del jugador
*/
void limpiarJugador(unsigned int fila, unsigned int columna, bool player){
     if(player == true){
        gotoxy(fila * 4 -3, columna * 4 - 2);
        printf(" ");
     }else{
        gotoxy(fila * 4 - 2, columna * 4 - 2);
        printf(" ");
     }
}

/*
* Oculta el cursor de la pantalla de la consola
*/
void ocultarCursor(){
    HANDLE hCon;
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 100;
    cci.bVisible = FALSE;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(hCon, &cci);
}

/*
* Se dirige a una ubicacion de la pantalla de la consola con
* cordenadas cartesianas
*/
void gotoxy (unsigned int fila, unsigned int columna) {
    HANDLE hCon;
    COORD dwPos;
    dwPos.X = columna;
    dwPos.Y = fila;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition (hCon,dwPos);
}

/*
* Cambia el color de los caracteres
*/
void setColor (unsigned int textcolor) {
    int fondo = 0;
    HANDLE hCon;
    hCon = GetStdHandle (STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,fondo | textcolor);
}
