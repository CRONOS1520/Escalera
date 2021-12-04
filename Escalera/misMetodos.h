#ifndef MISMETODOS_H_INCLUDED
#define MISMETODOS_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "constantes.h"

using namespace std;

void moverJugador(int cantidad,  int posX,  int posY, unsigned int fila, unsigned int columna, bool jugador);
void retroceder(int x, int y, bool jugador);
void turnoJugador();
int rotaDadoPlayer();
int rotaDadoIA();
void menu();
void tablero();
void dibujarFigura(unsigned int fila, unsigned int columna, bool jugador);
void limpiarJugador(unsigned int fila, unsigned int columna, bool jugador);
void dibujarBorde(unsigned int numFilaInicial, unsigned int numColumnaInicial,unsigned int numFila, unsigned int numColumna);
void dibujarTrampaPantano( int x,  int y);
void dibujarTrampaCangrejo(unsigned int x, unsigned int y);
void dibujarTrampaPierdeVida(unsigned int x, unsigned int y);
void dibujarTrampaPierdeTurnos(unsigned int x, unsigned int y);
void dibujarBeneficio1(unsigned int x, unsigned int y);
void dibujarBeneficio2(unsigned int x, unsigned int y);
bool validarImprimir(int x, int y, int tipo);
void generarTrampas();
void validarTrampa(bool jugador);
void iniciarJuego();
void validarGanador();
void gotoxy (unsigned int fila, unsigned int columna);
void setColor(unsigned int textColor);
void ocultarCursor();

#endif // MISMETODOS_H_INCLUDED
