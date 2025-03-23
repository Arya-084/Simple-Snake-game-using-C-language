#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>


#define ROWS 20
#define COLOUM 40


int i,j,Field[ROWS][COLOUM],x,y,Gy,Head,Tail,Game=0,Frogs,a,b,var,dir,score,highscore;

FILE *f;

void snakeItialization(){
    f=fopen("Highscore.txt","r");
    fscanf(f,"%d",&highscore);
    fclose(f);

   for(i=0;i<ROWS;i++){
       for(j=0;j<COLOUM;j++){
           Field[i][j]=0;
       }

   }
   x=ROWS/2;
   y=COLOUM/2;
   Gy=y;
   Head=5;
   Tail=1;
   Frogs=0;
   dir='d';

   for(i=0;i<Head;i++){
    Gy++;
    Field[x][Gy-Head]=i+1;
   }

}


void print()
{
    for(i=0;i<=COLOUM+1;i++){
     if(i==0){
        printf("%c",201);
     }else if(i==COLOUM+1){
        printf("%c",187);
     }else{
        printf("%c",205);
     }
   }
printf("Current Score: %d\tHigh score: %d",score,highscore);
   printf("\n");

   for(i=0;i<ROWS;i++){
    printf("%c",186);

    for(j=0;j<COLOUM;j++){
        if(Field[i][j]==0) printf(" ");
        if(Field[i][j]>0 && Field[i][j]!=Head) printf("%c",254);
        if(Field[i][j]==Head) printf("%c",1);
        if(Field[i][j]==-1 ) printf("%c",4);
        if(j==COLOUM-1) printf("%c\n",186);

    }

   }

for(i=0;i<=COLOUM+1;i++){
     if(i==0){
        printf("%c",200);
     }else if(i==COLOUM+1){
        printf("%c",188);
     }else{
        printf("%c",205);
     }
   }
}
void ResetScreenPosition(){
      HANDLE hOut;
      COORD Position;
      hOut = GetStdHandle(STD_OUTPUT_HANDLE);
      Position.X = 0;
      Position.Y = 0;
      SetConsoleCursorPosition(hOut,Position);
}
int Random(){
    srand(time(0));
  a = 1+rand() % 18;
  b = 1+rand() % 38;

  if(Frogs==0 && Field[a][b]==0){
   Field[a][b]= -1;
   Frogs = 1;
  }
}
int getch_noblock(){
   if(_kbhit())
    return _getch();
   else
    return -1;
}

void movement(){
  var = getch_noblock();
  var = tolower(var);

if((( var=='d'||var=='a')||(var=='w'||var=='s'))
   &&abs(dir-var)>5)  dir = var;
  if(dir=='d'){
    y++;
    if(Field[x][y]!=0 && Field[x][y]!=-1) gameover();
    if(y==COLOUM-1) y = 0;
    if (Field[x][y] ==-1){
        Frogs = 0;
        score+=5;
        Tail -= 2;
    }
    Head++;
    Field[x][y] = Head;

  }
  if(dir=='a'){
    y--;
    if(y==0) y = COLOUM-1;
    if (Field[x][y] == -1){
        Frogs = 0;
        score+=5;
        Tail -= 2;
    }
    Head++;
    Field[x][y] = Head;
  }
   if(dir=='w'){
    x--;
    if(x==-1) x = ROWS-1;
    if (Field[x][y] == -1){
        Frogs = 0;
        score+=5;
        Tail -= 2;
    }
    Head++;
    Field[x][y] = Head;
  }

if(dir =='s'){
    x++;
    if(x==ROWS-1) x = 0;
    if (Field[x][y] == -1){
        Frogs = 0;
        score+=5;
        Tail -= 2;
    }
    Head++;
    Field[x][y] = Head;
  }
}
void TailRemove(){
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLOUM;j++){
            if(Field[i][j]==Tail){
                Field[i][j] = 0;
            }
        }
    }
   Tail++;
}
void gameover(){
  printf("\a");
  Sleep(1500);
  system("cls");

  if(score>highscore){
    printf("  NEW HIGH SCORE !!!!!\n\n",score);
    system("pause");
    f=fopen("Highscore.txt","w");
    fprintf(f,"%d",score);
    fclose(f);
  }
  system("cls");
  printf("\n\n\nGAME OVER !!!!");

  Game = 1;
}

 void main()
{
   snakeItialization();

   while(Game==0){
    print();
    ResetScreenPosition();
    Random();
    movement();
    TailRemove();


   }


}