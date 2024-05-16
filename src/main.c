#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 25, y = 10;
int incX = 1, incY = 1;

struct car{
  int carIncX = 2;
  
}car;

void printNewPosition(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("  ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("x");
}
void printCar(int carnextX, int carnextY){
  screenSetColor(CYAN, DARKGRAY);
  screenGotoxy(x, y);
  printf("  ");
  x = carnextX;
  y = carnextY;
  screenGotoxy(x, y);
  printf("x");
};

int main() 
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    
    printNewPosition(x, y);
    screenUpdate();

    
    while (ch != 10) //enter
    {
      int nextX=x,nextY=y;
      
        // Handle user input
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
        ch=0;
        
      }
      
      printNewPosition(nextX, nextY);
      screenUpdate();
      
        
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}