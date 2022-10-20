#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
// ---------------------------- CROSSY ROAD GAME   IN C++ ----------------------------
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// ------------------------ PROJECT MADE BY GEORGE ( RIZZY ) -------------------------
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
using namespace std;
int duck_posX = 2,duck_posY = 17;
//Rendering the screen
void Rendering(int width, int height,string current_hp,int mat[40][60],int cnt,int current_checkpoint){
    COORD coord = {0 , 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 5;i < height+5;i++){
        if(i == 2+5){
        SetConsoleTextAttribute(h,120);
        cout << "       STATS       ";
        SetConsoleTextAttribute(h,15);
        }
        else if(i == 4+5){
           SetConsoleTextAttribute(h,120);
            cout << " ";
            SetConsoleTextAttribute(h,15);
            cout << "  HP";
            for(int ii = 0;ii < current_hp.size();ii++){
                if(current_hp[ii] == 'B'){
                    SetConsoleTextAttribute(h,65);
                    cout << ' ';
                    SetConsoleTextAttribute(h,15);
                }
                else cout << ' ';
            }

        }else if(i == 7+5){
           SetConsoleTextAttribute(h,120);
            cout << " ";
            SetConsoleTextAttribute(h,15);
            cout << "   CHECK POINT    ";
            SetConsoleTextAttribute(h,120);
        }
        else if(i == 8+5){
           SetConsoleTextAttribute(h,120);
            cout << " ";
            SetConsoleTextAttribute(h,15);
            cout << "        " <<current_checkpoint<<"         "  ;
        }
        else if(i == 10+5){
           SetConsoleTextAttribute(h,120);
            cout << " ";
            SetConsoleTextAttribute(h,15);
            cout << "     CONTROLS     ";
        }
        else if(i == 11+5){
           SetConsoleTextAttribute(h,120);
            cout << " ";
            SetConsoleTextAttribute(h,15);
            cout << "  W A S D - move  ";
        }
        else if(i > 2+5 && i < 16+5){
            SetConsoleTextAttribute(h,120);
            cout << " ";
            SetConsoleTextAttribute(h,15);
            cout << "                  ";
        }
        else if(i == 27+5){
            SetConsoleTextAttribute(h,120);
            cout << "   MADE BY RIZZY   ";
            SetConsoleTextAttribute(h,15);
        }
        else{
        SetConsoleTextAttribute(h,120);
        cout << "                   ";
        SetConsoleTextAttribute(h,15);
        }
        for(int ii = 0;ii < width;ii++){
            if(i == 5 || ii == 0 || i == height +4|| ii == width - 1){
                SetConsoleTextAttribute(h,120);
                cout <<  ' ';
                SetConsoleTextAttribute(h,15);
            }
            else if(duck_posX == ii && duck_posY== i){
                SetConsoleTextAttribute(h,110);
                cout << ' ';
                SetConsoleTextAttribute(h,15);
            }
            else if(((ii-1)%7 == 0 || ii - 1 == 0) && (i != 5 || i != height+4))
                cout << '|';
            else if(mat[i][ii] != 0){
                SetConsoleTextAttribute(h,mat[i][ii]);
                cout <<  ' ';
                SetConsoleTextAttribute(h,15);
            }
            else cout << ' ';
        }
        cout << endl;
    }
}
void Hp_bar(int mat[][60],string &hp_bar,int width,int checkpoints){
    if(mat[duck_posY][duck_posX] != 0){
        duck_posX = checkpoints*7+1;
      for(int i = hp_bar.length();i > 0;i--){
        if(hp_bar[i] == 'B'){
            hp_bar[i] = hp_bar[i-1] = ' ';
            break;
        }
      }
    }
}
/*
           GENERAL FORMULA
start_pos = 3*rand_nr + 4*(rand_nr-1) + 1;
end_pos = start_pos + 4;
*/
template <int width, int height>
void where_are_the_cars_spawning(int (&mat)[height][width],int &cnt){
   int random_nr = rand()%9;
   for(int i = 0;i < 5;i++)
      for(int ii = 3 * random_nr + 4 * (random_nr - 1);ii < 3 * random_nr + 4 * (random_nr - 1)+ 4;ii++)
          mat[i][ii] = cnt;
   cnt++;
}
template <int width, int height>
void set_mat_to_zero(int (&mat)[height][width]){
   for(int i =  1;i < height;i++)
    for(int ii = 1;ii < width;ii++)
        mat[i][ii] = 0;
}
template <int width, int height>
void moving_cars(int (&mat)[height][width]){
   for(int i =  height-2;i > 0;i--){
        for(int ii = 1;ii < width;ii++){
            if(mat[i-1][ii] != 0){
                mat[i][ii] = mat[i-1][ii];
                mat[i-1][ii] = 0;
            }
   }
}
}
int Movement(){
    if(_kbhit()){
        switch(_getch()){
    case 'a':
        duck_posX--;
        break;
    case 'd':
        duck_posX++;
        break;
    case 's':
        duck_posY++;
        break;
    case 'w':
        duck_posY--;
        break;
        }
    }
}
void duck_hit_the_checkpoint( int &current_checkpoint,int &max_checkpoint){
    if((duck_posX - 1)%7 == 0){
        current_checkpoint = (duck_posX-1)/7;
        if(current_checkpoint > max_checkpoint)
        max_checkpoint = current_checkpoint;
    }
}
int main()
{
    int width=60-3,height = 30;
    //
    string current_hp = "   BB BB BB   ";
    int cnt = 50;
    int current_checkpoint=0,max_checkpoint = 0;
    //
    //
    int mat[40][60];
    set_mat_to_zero(mat);
    //
    //
    while(1){
        Rendering(width,height,current_hp,mat,cnt,max_checkpoint);
        if(cnt >160)
            cnt = 50;
        moving_cars(mat);
        Hp_bar(mat,current_hp,width,max_checkpoint);
        Movement();
        duck_hit_the_checkpoint(current_checkpoint,max_checkpoint);
        where_are_the_cars_spawning(mat,cnt);
        if(current_hp == "              ")
            return 0;

    }
}
