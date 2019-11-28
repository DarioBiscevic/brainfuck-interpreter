#include <stdio.h>
#include <string.h>

#define MAX_ARRAY_LENGTH 30000

int main(int argc, char *argv[]){

  if(argc > 1){

    char fileName[255];
    strcpy(fileName, argv[1]);

    FILE *file = fopen(fileName, "r");

    //Calculate the length of the file
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char instructions[fsize];
    long next = 0;

    char ch;

    //Filter the file by saving only the instructions inside an array
    while((ch = getc(file)) != EOF){
      if(ch == '+' || ch == '-' || ch == '<' || ch == '>' || ch == '[' || ch == ']' || ch == '.' || ch == ','){
        instructions[next] = ch;
        next++;
      }
    }

    instructions[next] = '\0';

    //Initialize the data array
    char array[MAX_ARRAY_LENGTH];
    for(int i = 0; i < MAX_ARRAY_LENGTH; i++){ array[i] = 0; }

    char *ptr = array;
    char *instr = instructions;

    int depth = 0;
    int previousDepth = 0;

    //Reading loop
    while(*instr < next){
      //printf("%c\n", instructions[instr]);
      if(*instr == '+'){ *ptr += 1; }
      if(*instr == '-'){ *ptr -= 1; }
      if(*instr == '>'){ ++ptr; }
      if(*instr == '<'){ --ptr; }
      if(*instr == '.'){ putchar(*ptr); }
      if(*instr == ','){ *ptr = getchar(); }
      if(*instr == '['){
        depth++;
        if(*ptr == 0){
          previousDepth = depth;
          while(1){
            ++instr;
            if(*instr == '['){
              depth++;
            }
            if(*instr == ']'){
              if(depth == previousDepth){
                break;
              }else{
                depth--;
              }
            }
          }
        }
      }

      if(*instr == ']'){
        if(*ptr != 0){
          previousDepth = depth;
          while(1){
            --instr;
            if(*instr == ']'){
              depth++;
            }
            if(*instr == '['){
              if(depth == previousDepth){
                break;
              }else{
                depth--;
              }
            }
          }
        }
      }

      ++instr;
    }

  }else{
    printf("No input file selected\n");
  }

  return 0;
}
