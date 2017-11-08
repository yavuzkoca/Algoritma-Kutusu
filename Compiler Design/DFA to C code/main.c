#include <stdio.h>

enum STATE {START, N, NA, NAN, NANO};
enum STATE state=START;

enum STATE Start(int c);
enum STATE n(int c);
enum STATE Na(int c);
enum STATE Nan(int c);
enum STATE Nano(int c);

int main(){
    int c;
    while((char)(c=getchar()) != EOF){
        if(state == START){
            state = Start(c);
        }else if(state == N){
            state = n(c);
        }else if(state == NA){
            state = Na(c);
        }else if(state == NAN){
            state = Nan(c);
        }else if(state = NANO){
            fprintf(stdout, "string found\n");
            state = START;
        }
    }
}

enum STATE Start(int c){
    if((char)c == 'n') state = N;
    else state = START;
    return state;
}

enum STATE n(int c){
    enum STATE state = N;
    if((char)c=='n') state = N;
    else if ((char)c == 'a') state = NA;
    else state = START;
    return state;
}

enum STATE Na(int c){
    enum STATE state = NA;
    if((char)c=='n') state = NAN;
    else state = START;
    return state;
}

enum STATE Nan(int c){
    enum STATE state = NAN;
    if((char)c=='o') state = NANO;
    else if((char)c=='n') state = N;
    else if((char)c=='a') state = NA;
    else state = START;
    return state;
}

enum STATE Nano(int c){
    enum STATE state = START;
    return state;
}