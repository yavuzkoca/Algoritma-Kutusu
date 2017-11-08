#include <stdio.h>
char l;

void match(char t){
    if(l == t)
        l = getchar();
    else
        printf("error");
}

void E_(){
    if(l=='t'){
        match('+');
        match('i');
        E_();
    }else return;
}

void E(){
    if(l=='i'){
        match('i');
        E_();
    }
}

int main(){
    getchar();
    E();
    if(l=='\0')
        printf("success\n");
    return 0;
}