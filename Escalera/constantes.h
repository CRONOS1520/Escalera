#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

//CONSTANTES DE JUEGO
#define BARRA_HORIZONTAL 205
#define BARRA_VERTICAL 186
#define ESQ_SD 187
#define ESQ_SI 201
#define ESQ_II 200
#define ESQ_ID 188
#define CRUCE 206
#define T_SUPERIOR 203
#define T_INFERIOR 202
#define CRUCE_DERECHA 204
#define CRUCE_IZQUIERDA 185
#define ESPACIO 32
#define N_1 40
#define FLECHA 60
#define FIGURA_JUGADOR_1 3
#define FIGURA_JUGADOR_2 5
#define FIGURA_TRAMPA 223
#define DADO_COLUMNA_INICIAL 4
#define VERDE                   2
#define AZUL                    3
#define ROJO                    4
#define COLOR_PERDER_VIDA       5
#define COLOR_PANTANO           6
#define DEFECTO                 7
#define COLOR_DEVUELVE_ENEMIGO  9
#define COLOR_CANGREJO          12
#define COLOR_PERDER_TURNO      14

//Variables estaticas
static int arrayJuego[20][20];
static int vidaP1 = 3;
static int vidaP2 = 3;
static int canTrampaPantano =  3;
static int canTrampaCangrejo = 3;
static int canTrampaPierdeVida = 3;
static int canTrampaPierdeturno = 2;
static int canBeneficio1 = 2;
static int canBeneficio2 = 2;
static int cantidadColumna = 9;
static int cantidadFila = 9;
static int contador1 = 0;
static int contador2 = 0;
static int posicionXP1 = 1;
static int posicionYP1 = 1;
static int posicionXP2 = 1;
static int posicionYP2 = 1;
static bool pasarP1 = false;
static bool pasarP2 = false;
static bool pantanoP1 = false;
static bool pantanoP2 = false;
static bool turnoP1 = true;
static bool ganoP1 = false;
static bool ganoP2 = false;
static bool IA = false;

#endif // CONSTANTES_H_INCLUDED
