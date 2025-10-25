#include <stdio.h>
#include <stdlib.h> // para rand 
#include <time.h> // para numeros diferentes 

// definir jugadores o vacio
#define VACIO 0
#define JUGADOR 1
#define PC 2

// puntaje y matriz del gato
int gato[3][3];
int puntJugador = 0, puntPC = 0;

// funciones 
void iniciarGato();
void mostrarGato();
int playJugador();
int playPC();
int verificarGanador();
int gatoLleno();
void limpiarBuffer();

// para que los numeros sean diferentes siempre 
int main() {
    int turno, ganador, seguir;

    srand(time(NULL));
    
// iniciar juego y turno aleatorio 
    do {
        iniciarGato();
        ganador = 0;
        turno = rand() % 2 ? JUGADOR : PC;

        printf("\n=== JUEGO DEL GATO ===\n");
        printf("%s inicia.\n\n", turno == JUGADOR ? "Jugador" : "PC");

        mostrarGato();

// bucle de turnos 
        while (1) {
            if (turno == JUGADOR) {
                if (playJugador()) continue;
            } else {
                playPC();
            }

            mostrarGato();
            ganador = verificarGanador();

            if (ganador != 0 || gatoLleno()) break;

            turno = (turno == JUGADOR) ? PC : JUGADOR;
        }

// determinar jugador o empate 
        if (ganador == JUGADOR) {
            printf("\nGanaste esta ronda.\n");
            puntJugador++;
        } else if (ganador == PC) {
            printf("\nLa PC gana esta ronda.\n");
            puntPC++;
        } else {
            printf("\nEmpate.\n");
        }

// repetir juego o cerrar programa 
        printf("\nMarcador: Jugador = %d | PC = %d\n", puntJugador, puntPC);
        printf("\n¿Jugar otra ronda? (1 = Sí / 0 = No): ");
        scanf("%d", &seguir);
        limpiarBuffer();

    } while (seguir == 1);

    printf("\n=== RESULTADO FINAL ===\n");
    printf("Jugador: %d | PC: %d\n", puntJugador, puntPC);
    printf("Fin del juego.\n");
    return 0;
}

void iniciarGato() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            gato[i][j] = VACIO;
}

// mostrar juego 
void mostrarGato() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char simbolo;
            if (gato[i][j] == JUGADOR) simbolo = 'X';
            else if (gato[i][j] == PC) simbolo = 'O';
            else simbolo = ' ';
            printf(" %c ", simbolo);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n---+---+---\n");
    }
    printf("\n");
}

// turno jugador 
int playJugador() {
    int x, y;
    printf("Tu turno (fila y columna [1-3]): ");
    if (scanf("%d %d", &x, &y) != 2) {
        limpiarBuffer();
        printf("Entrada no válida.\n");
        return 1;
    }
    if (x < 1 || x > 3 || y < 1 || y > 3) {
        printf("Coordenadas fuera de rango.\n");
        return 1;
    }
    if (gato[x - 1][y - 1] != VACIO) {
        printf("Casilla ocupada.\n");
        return 1;
    }
    gato[x - 1][y - 1] = JUGADOR;
    return 0;
}

// turno pc 
int playPC() {
    int x, y;
    printf("\nTurno de la PC...\n");
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (gato[x][y] != VACIO);
    gato[x][y] = PC;
    return 0;
}

// para determinar ganador o empate 
int verificarGanador() {
    for (int i = 0; i < 3; i++) {
        if (gato[i][0] != VACIO && gato[i][0] == gato[i][1] && gato[i][1] == gato[i][2])
            return gato[i][0];
        if (gato[0][i] != VACIO && gato[0][i] == gato[1][i] && gato[1][i] == gato[2][i])
            return gato[0][i];
    }
    if (gato[0][0] != VACIO && gato[0][0] == gato[1][1] && gato[1][1] == gato[2][2])
        return gato[0][0];
    if (gato[0][2] != VACIO && gato[0][2] == gato[1][1] && gato[1][1] == gato[2][0])
        return gato[0][2];
    return 0;
}

int gatoLleno() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (gato[i][j] == VACIO)
                return 0;
    return 1;
}

void limpiarBuffer() {
    while (getchar() != '\n');
}
