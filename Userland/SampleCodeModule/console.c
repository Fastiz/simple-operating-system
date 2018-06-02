#include "screenManager.h"
#include "syscall.h"
#include "console.h"
#include "stdio.h"


#define ROW_HEIGHT 16
#define LETTER_WIDTH 9
#define HORIZONTAL_MARGIN 2
#define VERTICAL_MARGIN 2

#define LETTER_SPACE 10

char buffer[200];
int bufferIndex =0;

static const char* consoleName = "Consola\\::";

static const struct RGB consoleBackground = {0,0,0};
static const struct RGB consoleColor = {50,50,255};
static const struct RGB STDOUTColor = {255, 255, 255};
static const struct RGB STDINColor = {255, 255, 255};
static const struct RGB STDERRColor = {255, 50, 50};

 int windowWidth;
 int windowHeight;
int letterSize = 1;
int line=VERTICAL_MARGIN, linePosition=HORIZONTAL_MARGIN;

void console(){
  init();
  consoleLoop();
}

//void newLine(){}

void init(){
  //prueba
  // fillScreen(consoleBackground);
  // fillScreen(consoleColor);
  // fillScreen(STDOUTColor);
  // fillScreen(STDINColor);
  // fillScreen(consoleBackground);
  // fillScreen(consoleColor);
  // fillScreen(STDOUTColor);
  // fillScreen(STDINColor);
  // fillScreen(consoleBackground);
  // fillScreen(consoleColor);
  // fillScreen(STDOUTColor);
  // fillScreen(STDINColor);
  // fillScreen(consoleBackground);
  // fillScreen(consoleColor);
  // fillScreen(STDOUTColor);
  // fillScreen(STDINColor);

  windowWidth = _syscall(_getScreenWidth);
  windowHeight = _syscall(_getScreenHeight);
  fillScreen(consoleBackground);
  char * texto = "ESTO ES UN ERROR";
  for(;*texto != 0;texto++){
    _syscall(_write, 2, *texto);
  }
texto = "ESTO ES UN MENSAJE!!!!!!!!!!!! COSAS COSAS COSAS @@@@@@@@@@@@@@@";
  for(;*texto != 0;texto++){
    putchar(*texto);
  }
}

void consoleLoop(){
  while(1){
    stdin();
    stdout();
    stderr();
  }

}

int callCommand(){
  //Llamar comando

  //Limpiar buffer de entrada
}

void checkSpace(){
  if(linePosition*letterSize*LETTER_SPACE >= windowWidth-HORIZONTAL_MARGIN*2*letterSize)
    newLine();
  else if(line*letterSize*ROW_HEIGHT >= windowHeight-VERTICAL_MARGIN*ROW_HEIGHT*letterSize){
    moveScreenUp(letterSize*ROW_HEIGHT, consoleBackground);
    line--;
  }
}

void stdin(){
  bufferIndex=0;
  char * text = consoleName;
  while(*text){
    writeChar(*text, linePosition*letterSize*LETTER_SPACE, line*letterSize*ROW_HEIGHT, consoleColor, letterSize);
    linePosition++;
    text++;
  }
  char c;
  while((c = _syscall(_read, 0)) != '\n'){
    if(c==8){
      if(bufferIndex!=0){
        writeChar(buffer[--bufferIndex], (--linePosition)*letterSize*LETTER_SPACE, line*letterSize*ROW_HEIGHT, consoleBackground, letterSize);
      }
    }else if(c){
      buffer[bufferIndex++] = c;
      writeChar(c, linePosition*letterSize*LETTER_SPACE, line*letterSize*ROW_HEIGHT, STDINColor, letterSize);
      linePosition++;

    }
  }
  newLine();
  callCommand();
}

void stdout(){
  int flag;
  char c;
  while(c=_syscall(_read, 1)){
    flag=1;
    writeChar(c, linePosition*letterSize*LETTER_SPACE, line*letterSize*ROW_HEIGHT, STDOUTColor, letterSize);
    linePosition++;
  }
  if(flag)
    newLine();
}

void stderr(){
  int flag;
  char c;
  while(c=_syscall(_read, 2)){
    flag=1;
    writeChar(c, linePosition*letterSize*LETTER_SPACE, line*letterSize*ROW_HEIGHT, STDERRColor, letterSize);
    linePosition++;
  }
  if(flag)
    newLine();
}

void newLine(){
  checkSpace();
  line++;
  linePosition = HORIZONTAL_MARGIN;
}
