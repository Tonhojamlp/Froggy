#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <unistd.h>

int x = 15, y = 25;
int incX = 1, incY = 1;

struct car{
  int carIncX, carIncY;  
  int carX, carY;
  int carNextX, carNextY; 
}car;
void printNewPosition(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf(" ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("x");
}
//para criar um carro se movendo tem que criar variaveis independentes que vao mudar de posicao
void printCar(int *carnextX, int *carXfuturo,int carX,int carY){
  screenSetColor(CYAN, DARKGRAY);
  screenGotoxy(carX,carY);
  printf("  ");
  *carXfuturo = *carnextX;
  screenGotoxy(*carXfuturo,carY);
  printf("  ");
  char draw[3][1] = {
  {'('} ,{' '}, { ')' } 
  };
  for(int i = 0; i < 3; i++){
    for(int j = 0; j <1; j++){
      printf("%c", draw[i][j]);
    }
  }
  printf("  ");

};
void printscenary(int x, int y){
  screenGotoxy(x,y);
  printf("------------------------------");
}
int perder(int x, int y , int inimigoX, int inimigoY ){
  if(inimigoX == x && inimigoY == y ){
    printf("Game Over");
    return 1;
  }
  return 0;
};

int main() 
{
    static int ch = 0;
    struct car car2;
    struct car car3;
    struct car car4;
    struct car car5;

    //Criando o carro
    car.carIncX = 1;car.carIncY = 0; car.carX = 3 ; car.carY = 20; car.carNextX = car.carX;           car.carNextY = car.carY;

    car2.carIncX = 1;car2.carIncY = 0; car2.carX = 23 ; car2.carY = 16; car2.carNextX = car2.carX;
    car2.carNextY = car2.carY;
  
    car3.carIncX = 1;car3.carIncY = 0; car3.carX = 3 ; car3.carY = 16; car3.carNextX = car3.carX;
    car3.carNextY = car3.carY;

    car4.carIncX = 1;car4.carIncY = 0; car4.carX = 23 ; car4.carY = 16; car4.carNextX = car4.carX;
    car4.carNextY = car4.carY;
  
    car5.carIncX = 1;car5.carIncY = 0; car5.carX = 3 ; car5.carY = 16; car5.carNextX = car5.carX;
    car5.carNextY = car5.carY;
  
    
    screenInit(1);
    keyboardInit();
    timerInit(50);
    
    printNewPosition(x, y);
    screenUpdate();


    
    
    while (ch != 10) //enter
    {
      printscenary(2,19);
      printscenary(2,21);
      printscenary(2,17);
      printscenary(2,15);
      printscenary(2,12);
      printscenary(2,10);
      printscenary(2,8);
      printscenary(2,6);
      printscenary(2,4);

      
      int nextX=x,nextY=y;
      
      if (keyhit()) 
      {
          ch = readch();
          screenUpdate();
      }
      
      if(timerTimeOver() == 1){
        if(ch == 119){
          nextY = y-incY;
          if(nextY==1){
            nextY=2;
          }

        }else if (ch == 115){
          nextY = y+incY;
          if(nextY==27){
            nextY=26;
          }
          
        }else if( ch == 97){
           nextX = x-incX;
          if(nextX==1){
            nextX=2;
          }
          
        }else if( ch == 100){
           nextX = x+incX;
          if(nextX==28){
            nextX=27;
          }
         
        }
        
        
      }
      
      printNewPosition(nextX, nextY);
      int newX = car.carIncX + car.carX;
      int newX2 = car2.carIncX + car2.carX;
      int newX3 = car3.carIncX + car3.carX;
      int newX4 = car4.carIncX + car4.carX;
      int newX5 = car5.carIncX + car5.carX;


      //carros irem até a borda e voltar
      if (newX >= (MAXX -strlen("()") -6) || newX <= MINX+1) car.carIncX = -car.carIncX;
      if (newX2 >= (MAXX -strlen("()") -6) || newX2 <= MINX+1) car2.carIncX = -car2.carIncX;
      if (newX3 >= (MAXX -strlen("()") -6) || newX3 <= MINX+1) car3.carIncX = -car3.carIncX;
      if (newX4 >= (MAXX -strlen("()") -6) || newX4 <= MINX+1) car4.carIncX = -car4.carIncX;
      if (newX5 >= (MAXX -strlen("()") -6) || newX5 <= MINX+1) car5.carIncX = -car5.carIncX;

      //Printando todos os carros
      printCar(&newX,&car.carX,3,20);
      
      printCar(&newX2,&car2.carX,3,16);

      printCar(&newX3,&car3.carX,20,11);

      printCar(&newX4,&car4.carX,20,9);

      printCar(&newX5,&car5.carX,20,5);


      if (perder(x,y,car.carX, car.carY) == 1)break;
      if (perder(x,y,car2.carX, car2.carY) == 1)break;
      if (perder(x,y,car3.carX, car3.carY) == 1)break;
      if (perder(x,y,car4.carX, car4.carY) == 1)break;
      if (perder(x,y,car5.carX, car5.carY) == 1)break;

     
      ch=0;
      screenUpdate();
      usleep(90000);
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}