#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESC 27

int body[200][2];
int long_body = 3;
int aux = 1;
int x = 10;
int y = 12;
int dir = 3;
int xFeed = 30;
int yFeed = 15;
int velocity = 100;
int h = 1;
int score = 0;
char key;

void gotoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;    
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

// Función para ocultar el cursor de la terminal
void hide_cursor(){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 50;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

// Dibuja los limites del juego
void print_limits()
{
    // Horizontales:
    for (int i = 2; i < 78; i++){
        gotoxy(i, 3); printf("%c", 205);
        gotoxy(i, 23); printf("%c", 205);
    }
    // Verticales:
    for (int i = 4; i < 23; i++){
        gotoxy(2, i); printf("%c", 186);
        gotoxy(77, i); printf("%c", 186);
    }
    // Esquinas:
    gotoxy(2, 3); printf("%c", 201);
    gotoxy(2, 23); printf("%c", 200);
    gotoxy(77, 3); printf("%c", 187);
    gotoxy(77, 23); printf("%c", 188);
}

void save_position(){
    body[aux][0] = x;
    body[aux][1] = y;
    aux++;
    if (aux == long_body)
    {
        aux = 1;
    }
}

void print_body(){
    for (int i = 1; i < long_body; i++)
    {
        gotoxy(body[i][0], body[i][1]);
        printf("*");
    }
}

void delete_body(){
    gotoxy(body[aux][0], body[aux][1]);
    printf(" ");
}

void move(){
        if (kbhit())
    {
        key = getch();
        switch (key)
        {
        case UP:
            if (dir != 2)
                dir = 1;
                break;

        case DOWN:
            if (dir != 1)
                dir = 2;
                break;

         case RIGHT:
            if (dir != 4)
                dir = 3;
                break;

        case LEFT:
            if (dir != 3)
                dir = 4;
                break;
        }
    }
}

void change_velocity(){
    if (score == h*20)
    {
        velocity -= 10;
        h++;
    } 
}

void feed(){
    if (x == xFeed && y == yFeed)
    {
        xFeed = (rand() % 73) + 4;
        yFeed = (rand() % 19) + 4;

        long_body++;
        score += 10;
        gotoxy(xFeed, yFeed); printf("%c", 4);
        change_velocity();
    }
}

bool game_over(){
    if (y == 3 || y == 23 || x == 2 || x == 77){
        return false;
    }
    for (int j = long_body - 1; j > 0; j--){   
            if ( (body[j][0] == x) && (body[j][1] == y) ){
                return false;
            }
    }
    return true;
}

void print_score(){
    gotoxy(3, 1); printf("SCORE %d", score);
}

void game_start_screen(){
    print_limits();
    hide_cursor();
    gotoxy(xFeed, yFeed); printf("%c", 4);
} 

void run_game(){
    delete_body();
    save_position();
    print_body();
    feed();
    print_score();
    move(); move();
    
    if (dir == 1) y--;
    if (dir == 2) y++;
    if (dir == 3) x++;
    if (dir == 4) x--;

    Sleep(velocity);
}

int main(int argc, char const *argv[]){

    game_start_screen();

    while(key != ESC && game_over()){
        run_game();
    }

    gotoxy(35,16); printf("GAME OVER");
    getch();
    return 0;
}
