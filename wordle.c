#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include<errno.h>

#define ResultGreen     1
#define ResultYellow    2
#define ResultRed       4
#define max             5000
#define ValOk           0
#define ValBadInput     1
#define ValNoSuchWord   2

#define ClrGreen        "\033[0;32m"
#define ClrYellow       "\033[0;33m"
#define ClrRed          "\033[0;31m"
#define ClrStop         "\033[0m"

typedef char ValResult;
typedef char Result;
static char words[max][5];
bool continuation;
int rounds;
bool corrects[5];
bool win;


ValResult validator(char *);
char* readline(void);
void prompt(char*);
void gameloop(char*);
void seed(void);
char *randomword(int);
int readfile(char *);
bool isin(char,char*);
void print_results(Result*,char*,char*);
Result* cw(char*,char*);
Result cc(char, int, char*);
int main(int,char**);

int readfile(char* filename){
    char buf[8];
    int i, size;
    FILE *fd;

    fd = fopen(filename, "r");
    if(!fd){
        perror("fopen");
        return -1;
    }

    i=0;
    memset(buf,0,8);

    while(fgets(buf, 7, fd)){
        size = strlen(buf);
        if(size<1){
            memset(buf,0,8);
            continue;
        }

        size--;
        buf[size] = 0;

        if(size != 5){
            memset(buf,0,8);
            continue;
        }

        words[i][0] = buf[0];
        words[i][1] = buf[1];
        words[i][2] = buf[2];
        words[i][3] = buf[3];
        words[i][4] = buf[4];

        memset(buf, 0 , 8);
        i++;

        if(max<=1) break;

    }
    fclose(fd);


    return i;
}

bool isin(char c,char* str){
    bool ret;
    int i,size;

    ret = false;
    size = strlen(str);

    for(int i=0;i<size;i++){
        if(str[i] == c){
            ret = true;
            break;
        }
    }
    return ret;
}

void prompt(char* correctword ){
    int i;

    for(int i=0;i<5;i++){
        switch(corrects[i]){
            case false:
                printf("-");
                break;
            case true:
                printf("%c", correctword[i]);
                break;    
        }
    }
    printf("\n\n%d> ",(5-rounds));
    fflush(stdout);

    return;
}

char* readline(){
    static char buf[8];
    int size;

    memset(buf, 0, 8);
    fgets(buf, 7, stdin);
    size = strlen(buf);
    assert(size > 0);
    size --;
    buf[size]=0;

    return buf;
}

ValResult validator(char* word){
    int n,i;
    bool ret;

    bool strcmp_(char* str1, char* str2){
        int s, i;

        s=0;
        for(i=0;i<5;i++){
            if(str1[i] == str2[i]) s++;
        }
        return (s==5) ? true: false;
    }
    n = strlen(word);
    if(n != 5) return ValBadInput;

    ret = false;
    for(i =0;i<max;i++){
        if(strcmp_(words[i],word)){
            ret = true;
            break;
        }
    }
    if(ret) return ValOk;
    else return ValNoSuchWord;
}

Result cc(char guess, int idx, char* word){
    char correct;

    correct = word[idx];
    if(guess == correct){
        corrects[idx] = true;
        return ResultGreen;
    }
    else if(isin(guess,word))
        return ResultYellow;

    return ResultRed;
}

Result* cw(char* guess, char* word){
    static Result res[5];
    int i;

    for(i=0;i<5;i++)
        res[i] = cc(guess[i],i,word);

    return res;
}

void print_results(Result* res,char* guess, char* correct){
    int i;
    rounds++;
    for(int i=0;i<5;i++){
        switch(res[i]){
            case ResultGreen:
                printf("%s%c%s", ClrGreen,guess[i],ClrStop);
                break;
            case ResultYellow:
                printf("%s%c%s", ClrYellow,guess[i],ClrStop);
                break;
            case ResultRed:
                printf("%s%c%s", ClrRed,guess[i],ClrStop);
                break;
            default:
                printf("Unknown: %d\n", res[i]);
                break;            
        }
    }
    printf("\n");
    return;
}

void gameloop(char* correct){
    // if(rounds == 5) {
    //     win = false;
    // }
    char* input;
    Result* res;
    ValResult valres;
    int i,c;

    printf("DEBUG: Correct word: '%s'\n",correct);
    prompt(correct);
    input = readline();
    valres = validator(input);
    switch(valres){
        case ValBadInput:
            printf("%s\n","Bad input");
            rounds++;
            return ;
        case ValNoSuchWord:
            printf("%s\n","No such word- in the wordlist");
            rounds++;
            return;
        default:
            break;              
    }
    res = cw(input, correct);
    for(i=c=0;i<5;i++)
        if(corrects[i]) c++;

    print_results(res, input, correct);

    if(c ==5 ){
        win = true;
        continuation = false;
        return ;
    }    
}


char* randomword(int m){
    int x;
    static char ret[8];

    x = rand() % m;

    ret[0] = words[x][0];
    ret[1] = words[x][1];
    ret[2] = words[x][2];
    ret[3] = words[x][3];
    ret[4] = words[x][4];
    ret[5] = 0;

    return ret;
} 

void seed() {
    int x;

    x = getpid();
    srand(x);

    return;
}


int main(int argc, char *argv[]){
    int n;
    char* p;

    corrects[0] = false;
    corrects[1] = false;
    corrects[2] = false;
    corrects[3] = false;
    corrects[4] = false;

    rounds = 0;
    win = false;

    seed();
    n = readfile("wordlist.txt");
    assert(!(n<0));
    p = randomword(n);

    printf("Enter a valid '5' Letter English Word !\n");

    continuation = true;
    while (continuation)
        if(rounds<5) gameloop(p);
        else break;

    printf("The correct word was : '%s' \n",p);
    if(win)
        printf("Congrats !!! You Won The Game. \n");
    else 
        printf("You lost. Game over. \n");

    return 0;
}
