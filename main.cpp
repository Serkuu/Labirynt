#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <chrono>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32
#define M 15
#define N 15            //Tu mozna wpisac jak duzy jest labirynt

void gotoxy(short x, short y);
void print(char Ltab[M][N]);
void lose();
void win();
char** readfile();
int check_ending_x(char Ltab[M][N]);
int check_ending_y(char Ltab[M][N]);
int main()
{
    char** Ltab;
    Ltab = readfile();
    char Labirynt[M][N];                    //Stworzyłem nowa tablice z takimi samymi wartościami, bo inaczej nie moglem wrzucac tablicy do funkcji przez to ze Ltab to wskaznik
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            Labirynt[i][j] = Ltab[i][j];
        }
    }
    print(Labirynt);
    short x=1,y=1;
    int wygrane = 0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    while(1) {
        if (x==1&&y==1) {
            start = std::chrono::system_clock::now();
        }
        print(Labirynt);
        gotoxy( x,y );
        if(Labirynt[y][x]=='1') {           //W momencie gdy pozycja gracza pokrywa sie z 1 na tablicy -> gracz przegrywa
            system("cls");
            lose();
            gotoxy(1,1);
            x=1;
            y=1;
            int choice;
            switch (choice=getch()) {
                default: system ("cls"); print(Labirynt); continue;
            }
            break;
        }
        SetConsoleOutputCP(65001);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 6);
        printf("☺");
        if(y==check_ending_x(Labirynt) && x==check_ending_y(Labirynt)) {            //W momencie gdy pozycja gracza pokrywa sie z pozycja koncowa znaleziona w funkcji -> gracz wygrywa
            end = std::chrono::system_clock::now();
            wygrane = wygrane + 1;
            system("cls");
            win();
            gotoxy(0,6);
            std::chrono::duration<double> elapsed_seconds = end - start;        //Tu zaczyna sie nieumiejetny timer i leaderboard wynikow
            double seconds = elapsed_seconds.count();
            cout << "Time: " << seconds<<" s"<< endl;
            double topka[3];
            if (wygrane == 1) {
                topka[0] = seconds;
            }
            if (wygrane == 2) {
                topka[1] = seconds;
            }
            if (wygrane == 3) {
                topka[2] = seconds;
            }
            if (seconds<topka[0]) {
                double temp = topka[1];
                topka[1] = topka[0];
                topka[2] = temp;
                topka[0] = seconds;
            }
            else if (seconds<topka[1]) {
                topka[2] = topka[1];
                topka[1] = seconds;
            }
            else if (seconds<topka[2]) {
                topka[2]=seconds;
            }
            gotoxy(0,8);
            if (wygrane == 1) {
                cout<<"TOP 1: "<<topka[0]<<" s";
            }
            else if (wygrane == 2) {
                cout<<"TOP 1: "<<topka[0]<<" s"<<"\nTOP 2: "<<topka[1]<<" s";
            }
            else {
                cout<<"TOP 1: "<<topka[0]<<" s"<<"\nTOP 2: "<<topka[1]<<" s"<<"\nTOP 3: "<<topka[2]<<" s";              //Tu konczy sie nieumiejetny timer i leaderboard wynikow
            }
            gotoxy(1,1);
            x=1;
            y=1;
            int choice;
            switch (choice=getch()) {
                default: system ("cls"); print(Labirynt); continue;
            }
            break;
        }
        int c;
        switch(c=getch()) {
            case KEY_UP: y-=1;break;
            case KEY_DOWN: y+=1;break;
            case KEY_LEFT: x-=1;break;
            case KEY_RIGHT: x+=1;break;
            case KEY_SPACE: exit(1);
            default: ;
        }
    }

    getchar();
    system("pause");
    return 0;
}

void gotoxy(short x, short y) {             //Podwalona funkcja do poruszania sie z sudoku
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };
    SetConsoleCursorPosition(hStdout, position);
}
char** readfile() {                     //Tworzenie tablicy na podstawie pliku tekstowego layout.txt
    char** Ltab = new char*[M];
    ifstream file;
    file.open("layout.txt");
    if (file.is_open()) {
        for (int i = 0; i < M; i++) {
            Ltab[i] = new char[N];
            string line;
            getline(file, line);
            for (int j = 0; j < N; j++) {
                Ltab[i][j] = line[j];
            }
        }
        file.close();
    }
    return Ltab;
}
void print(char Ltab[M][N]) {               //Drukowanie layoutu labiryntu na podstawie danych z tabeli
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 5);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                gotoxy(j,i);
                if (Ltab[i][j]=='0') {
                    cout<<" ";
                }
                else if (Ltab[i][j]=='1') {
                    SetConsoleOutputCP(65001);
                    printf("█");
                }
                else if (Ltab[i][j]=='2') {
                    SetConsoleTextAttribute(hConsole, 6);
                    printf("░");
                    SetConsoleTextAttribute(hConsole, 5);
                }
            }
        }
    gotoxy(0,M+2);
    SetConsoleTextAttribute(hConsole, 7);
    cout << "PRESS SPACE TO QUIT";
    }
int check_ending_x(char Ltab[M][N]) {              //Znajduje pozycje punktu koncowego i porownam pozniej z pozycja gracza
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (Ltab[i][j]=='2') {
                return i;
            }
        }
    }
    return 0;
}
int check_ending_y(char Ltab[M][N]) {              //Znajduje pozycje punktu koncowego i porownam pozniej z pozycja gracza
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (Ltab[i][j]=='2') {
                return j;
            }
        }
    }
    return 0;
}
void lose() {               //Taki fajny ekranik jak sie przegrywa
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    for (int i = 0; i < 13; i++) {
        SetConsoleOutputCP(65001);
        if (i%2!=1) {
            printf("🕱");
        }
        else {
            printf(" ");
        }
    }
    for (int i = 0; i < 3; i++) {
        gotoxy(0,i+1);
        printf("🕱");
    }
    for (int i = 0; i < 3; i++) {
        gotoxy(12,i+1);
        printf("🕱");
    }
    gotoxy(0,4);
    for (int i = 0; i < 13; i++) {
        SetConsoleOutputCP(65001);
        if (i%2!=1) {
            printf("🕱");
        }
        else {
            printf(" ");
        }
    }
    gotoxy(2,2);
    printf("YOU  LOST");
    gotoxy(0,6);
    SetConsoleTextAttribute(hConsole, 7);
    cout<<"PRESS ANY KEY TO RESTART";
}
void win() {                //Taki fajny ekranik jak sie wygrywa
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 2);
    for (int i = 0; i < 11; i++) {
        SetConsoleOutputCP(65001);
        if (i%2!=1) {
            printf("✩");
        }
        else {
            printf(" ");
        }
    }
    for (int i = 0; i < 3; i++) {
        gotoxy(0,i+1);
        printf("✩");
    }
    for (int i = 0; i < 3; i++) {
        gotoxy(10,i+1);
        printf("✩");
    }
    gotoxy(0,4);
    for (int i = 0; i < 11; i++) {
        SetConsoleOutputCP(65001);
        if (i%2!=1) {
            printf("✩");
        }
        else {
            printf(" ");
        }
    }
    gotoxy(2,2);
    printf("YOU WIN");
    gotoxy(2,3);
    gotoxy(0,12);
    SetConsoleTextAttribute(hConsole, 7);
    cout<<"PRESS ANY KEY TO RESTART";
}