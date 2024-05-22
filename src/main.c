#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <unistd.h>
#include <math.h>

int x = 15, y = 25;
int incX = 1, incY = 1;

// criando os carros por meio de uma lista encadeada
struct car{
  int carIncX, carIncY;  
  int carX, carY;
  int carNextX, carNextY; 
  
  struct car *next;
}car;

// Criando o jogador
void printNewPosition(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf(" ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("𖠊");
}

void adicionarScore() {
  char nome[4];
  printf("Game Over\n");
  printf("Digite seu nome (3 caracteres): ");
  scanf("%3s", nome);
  const char *scores = "score.txt";

  FILE *file = fopen(scores, "a");
  if (file == NULL) {
      return;
  }

  fprintf(file, "%s\n", nome);

  fclose(file);
}

void exibirScore() {
  const char *scores = "score.txt";
  char linha[256];

  FILE *file = fopen(scores, "r");
  if (file == NULL) {
      return;
  }
  
  while (fgets(linha, sizeof(linha), file) != NULL){
    printf("%s", linha);
  }

  fclose(file);
}

//para criar um carro se movendo tem que criar variaveis independentes que vao mudar de posicao

void printscenary(int x, int y){
  screenGotoxy(x,y);
  printf("-----------------------------");
}
int perder(int x, int y , int inimigoX, int inimigoY ){
  if(inimigoX == x && inimigoY == y ){
    return 1;
  }
  return 0;
};



void adicionar(struct car **head,int localx,int localy,int localincX,int localincY){
  struct car *novo = (struct car *)malloc(sizeof(struct car));
  novo->carX = localx;
  novo->carY = localy;
  novo->carIncX = localincX;
  novo->carIncY = localincY;
  novo->next = NULL;

  novo->next=(*head);
  (*head)=novo;
    
  
  
}
int printCar(struct car **head){
  struct car *temp = *head;

  while(temp != NULL){
    int newX=temp->carX+temp->carIncX;
    if (newX >= (MAXX -strlen("()") -6) || newX <= MINX+1) temp->carIncX = -temp->carIncX;
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(temp->carX,temp->carY);
    printf("  ");
    temp->carX = newX;
    screenGotoxy(temp->carX,temp->carY);
    printf("  ");
    char draw[3][1] = {
    {'('} ,{' '}, { ')' } 
    };
    for(int i = 0; i < 3; i++){
      for(int j = 0; j <1; j++){
        printf("%c", draw[i][j]);
      }
    }
    if (perder(x,y,temp->carX, temp->carY) == 1){
      screenClear();
      adicionarScore();
      exibirScore();
      return 1;
    }
    temp = temp->next;
    printf("  ");
  }


};

int pirntmoscas(int x, int y, int pontX, int pontY){
  screenGotoxy(pontX,pontY);
  printf("𖠑");
  if(perder(x, y,pontX,pontY)==1){
    screenGotoxy(pontX,pontY);
    printf(" ");
    return 0;
  }else{
    return 1;
  }
}

int main() 
{
    srand(time(NULL));
    static int ch = 0;
    struct car *head=NULL;
    int localx=3,localy=20,localincX=1,localincY=0;
    int pontX, pontY, fly=1;
  
    pontX = rand() % (MAXX - MINX + 1) + MINX;
    pontY = rand() % (MAXY - MINY + 1) + MINY;
    
  for(int i=0; i<5; i++){

      adicionar(&head,localx,localy,localincX,localincY);
      if(0==i)localy-=4,localx+=20;
      if(1==i)localy-=5,localx-=20;
      if(2==i)localy-=2,localx+=20;
      if(3==i)localy-=4,localx-=20;
  
    }
    screenInit(1);
    keyboardInit();
    timerInit(50);
    
    printNewPosition(x, y);
    screenUpdate();


    
    
    while (ch != 10) //enter
    {
      printscenary(3,19);
      printscenary(3,21);
      printscenary(3,17);
      printscenary(3,15);
      printscenary(3,12);
      printscenary(3,10);
      printscenary(3,8);
      printscenary(3,6);
      printscenary(3,4);
      

     

      if(pirntmoscas(x, y, pontX, pontY) == 0 ){
        pontX = rand() % (MAXX - MINX + 1) + MINX;
        pontY = rand() % (MAXY - MINY + 1) + MINY;
      }
      
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
          if(nextX==31){
            nextX=30;
          }
         
        }
        
        
      }
      
      printNewPosition(nextX, nextY);
      

      //Printando todos os carros
     if(printCar(&head)==1)break ;
       
      ch=0;
      screenUpdate();
      usleep(90000);
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}