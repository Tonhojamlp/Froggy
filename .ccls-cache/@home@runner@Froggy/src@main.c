#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>

int x = 15, y = 25;
int incX = 1, incY = 1;

// criando os carros por meio de uma lista encadeada
struct car{
  int carIncX, carIncY;  
  int carX, carY;
  int carNextX, carNextY; 
  
  struct car *next;
}car;
struct node{
  char nome[5];
  int score;
  struct node *next;
};

// Criando o jogador
void printNewPosition(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf(" ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("𓆏");
}

void adicionarScore(int score) {
  char nome[4];
  printf("Game Over\n");
  printf("Digite seu nome (3 caracteres): ");
  scanf("%3s", nome);

   const char *scores = "score.txt";

    FILE *file = fopen(scores, "a");
    if (file == NULL) {
        return;
    }  
    fprintf(file, "%s\t%d\n",nome, score);
  
    fclose(file);
  }
void adicionar1(struct node **head, char *nome, int score){
  struct node *novo = (struct node *)malloc(sizeof(struct node));
  strcpy(novo->nome, nome);
  novo->score = score;
  novo->next = NULL;
  
  if(*head==NULL || (*head)->score<novo->score){
    novo->next=*head;
    *head=novo;
  }
  else{
    struct node *atual=*head;
    while(atual->next!=NULL && atual->next->score > novo->score){
      atual=atual->next;
    }
    novo->next=atual->next;
    atual->next=novo;
  
    }
}

void exibirScore(struct node **head) {
  const char *scores = "score.txt";
  char nome[4];
  int score;
  

  FILE *file = fopen(scores, "r");
  if (file == NULL) {
      return;
  }
  while(!feof(file)){
    fscanf(file,"%s\t%d\n",nome,&score);
    adicionar1(head,nome, score);
  }
  fclose(file);
  struct node *temp=*head;
  int i=1;
  while(temp!=NULL){
    printf("[%d]\t%s\t%d\n",i,temp->nome,temp->score);
    temp=temp->next;
    i++;
  }
}

//para criar um carro se movendo tem que criar variaveis independentes que vao mudar de posicao

void printscenary(int x, int y){
  screenGotoxy(x,y);
  printf("-----------------------------");
}
int colisaomosca(int x, int y , int inimigoX, int inimigoY){
  if(inimigoX == x && inimigoY == y ){
    return 1;
  }
  return 0;
};
int colisaocarro(int x, int y, int inimigoX, int inimigoY) {
    if (inimigoY == y && inimigoX <= x && x <= inimigoX + 1) {
        return 1; // Houve colisão
    }
    return 0; // Não houve colisão
}

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
    if (colisaocarro(x,y,temp->carX, temp->carY) == 1){
      return 1;
    }
    temp = temp->next;
    printf("  ");
  }
};

int pirntmoscas(int x, int y, int pontX, int pontY){
  screenGotoxy(pontX,pontY);
  printf("𓆦");
  if(colisaomosca(x, y,pontX,pontY)==1){
    screenGotoxy(pontX,pontY);
    printf(" ");
    return 0;
  }else{
    return 1;
  }
}

void printvalor(int x , int y, int score){
  screenSetColor(YELLOW, LIGHTBLUE);
  screenGotoxy(x,y);
  printf("Score:%d",score);
}

int main() 
{
    struct node *jogadores=NULL;
    srand(time(NULL));
    static int ch = 0;
    struct car *head=NULL;
    int localx=3,localy=20,localincX=1,localincY=0;
    int pontX, pontY;
    int score = 0, opcao = 0; 
    int velocidade = 90000;
  
    pontX = rand() % ((30) - 1 ) + 1;
    pontY = rand() % ((25) - 1 ) + 1;

    printNewPosition(x, y);
    screenUpdate();
  

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
    
    


    
    
    while (ch != 10) //enter
    {
      printvalor(3,1,score);

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
        score += 100;
        pontX = rand() % ((MAXX-5) - MINX + 5) + MINX;
        pontY = rand() % ((MAXY-5) - MINY + 5) + MINY;
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
     if(printCar(&head)==1){
       break;
     } 
       
       
      ch=0;
      screenUpdate();
      usleep(velocidade-score);

    }
  keyboardDestroy();
  screenDestroy();
  timerDestroy();
  adicionarScore(score); 
  exibirScore(&jogadores);
  
    return 0;
}