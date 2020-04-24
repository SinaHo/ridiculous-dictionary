//
// Author: Sina Honarvar
// Date:   1/24/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define PRINT(x) cout << x << endl;
#define MK(x) #x
#define S(x) printf(MK(x));printf(" : "); printf("%s\n", x);
#define I(x) printf(MK(x));printf(" : "); printf("%d\n", x);
#define D(x) printf(MK(x));printf(" : "); printf("%f\n", x);
//#define CONCAT(x, y) x##y
//#define N(x) string_to_name(#x)
#define PATH "./dictionary.txt"
#define TMP "./tmp.txt"


void run();

void read_inp(char *str) {
    int i = 0;
    char c = getchar();
    while (c != 0 && c != '\n') {
        str[i++] = c;
        c = getchar();
    }
    str[i] = 0;

}

void getWordCount();

int keyInLine(char *key, char *line) {
    char *k = malloc(60);
    int i = 0;
    while (line[i] != ' ') {
        k[i] = line[i];
        k[i + 1] = 0;
        i++;
    }
    return strcmp(k, key);
}

//int cmp(char*a, char*b){
//    int i = 0;
//    while(a[i] != 0 || b[i] != 0){
//        if (a[i] != b[i]) return 0;
//    }
//    return 1;
//}
void setSize();

void addWord();

void removeWord();

void takeExam();

FILE *f;
//char data[];
char *string;
long fsize;
int wordCount;

int main() {


//    fget
    setSize();

//    string = malloc(fsize + 1);
//    fread(string, 1, fsize, f);
//    fclose(f);
//    string[fsize] = 0;
//    f = fopen("./dictionary.txt", "a+");

    run();
    return 0;
}

//fputs("sdf",f);
//fclose(f);
void run() {
    int _type;
    printf("1) Add a word\n2) Remove a word\n3) Take a test\n4) Exit\n");
    scanf("%d", &_type);
    switch (_type) {
        case 1:
            addWord();
            run();
            break;
        case 2:
            removeWord();
            run();
            break;
        case 3:
            takeExam();
            run();
            break;
        case 4:
            printf("You exited the program\n");
            return;
            break;
        default:
            printf("You enter a wrong number, enter another:\n");
            run();
            break;
    }
}

void addWord() {
    f = fopen(PATH, "a");
    char wd[20];
    printf("Enter a word:\n");
    scanf("%63s", wd);
    char sn[20];
    printf("Enter its synonym:\n");
    scanf("%63s", sn);

    fputs(wd, f);
    fputs(" ", f);
    fputs(sn, f);
    fputs("\n", f);
    fclose(f);
    return;
}

void removeWord() {
//    FILE * tmp = fopen(TMP, "a");
    setSize();
    char removeWord[20];
    printf("Enter a word to Remove:\n");
    scanf("%63s", removeWord);
    char *buffer = malloc(fsize);
    f = fopen(PATH, "r");
    fread(buffer, fsize, 1, f);
    fclose(f);
    f = fopen(PATH, "w");
    fclose(f);
    f = fopen(PATH, "a");

    char *line = malloc(60);
    int i = 0;
    char *wrd = malloc(20);
    int pnt = 0;
    int flag = 0;
//    for (int x = 0; x<fsize; x++){
//        printf("%c", buffer[x]);
//    }

    while (flag == 0 && i < fsize) {
//        printf("%c ", buffer[i]);
        if (buffer[i] == '\n') {
            line[i] = 0;
            if (keyInLine(removeWord, line) == 0) {
                flag = 1;
                i++;
                break;
            }
            fputs(line, f);
            fputc('\n', f);
            line = malloc(60 * sizeof(char));

            pnt = ++i;
        } else {
            line[i - pnt] = buffer[i];
            i++;
        }
    }
    if (flag != 0) {
        printf("done\n");

    } else {
        printf("not done\n");
    }
    fclose(f);
    setSize();

}

void takeExam() {
    setSize();
    int count;
    printf("Enter number of words to take test of :\n");
    scanf("%d", &count);
    I(count)
    char *buffer = malloc(fsize);
    f = fopen(PATH, "r");
    fread(buffer, fsize, 1, f);
    fclose(f);

    int correct = 0;
    int rnd;
    getWordCount();
    count;
    srand(time(NULL));
    for (int qn = 0; qn < count+1; qn++) {
        int counter = 0;
        rnd = rand()%wordCount;
//        rnd = 2;
        int i = 0;
        int pnt = 0;
        char *line = malloc(60);
        while (i < fsize) {
            if (buffer[i] == '\n') {
                line[i] = 0;
                counter++;
                pnt = i + 1;
                i++;
                continue;
            }
            if (counter == rnd) {
                line[i - pnt] = buffer[i];
            }
            i++;
        }
        if (qn == 0)continue;
        char*wrd = malloc(20);
        char*syn = malloc(20);
        int c = 0;
        while(line[c] != ' '){
            wrd[c] = line[c];
            c++;
        }
        wrd[c] = 0;
        int x = c+1;
        c= 0;
        while(line[x]!=0){
            syn[c] = line[x];
            x++;
            c++;
        }
        syn[c] = 0;
        printf("%d: Word : %s\n",qn, wrd);
        char ans[20];
        scanf("%19s", ans);
        if (strcmp(ans, syn) == 0){
            printf("correct\n");
            correct++;
        }else{
            printf("incorrect\n");
        }
    }
    printf(" your result : %d/%d\n", correct, count);
}

void getWordCount() {
    setSize();
    char *buffer = malloc(fsize);
    f = fopen(PATH, "r");
    fread(buffer, fsize, 1, f);
    fclose(f);
    for (int i = 0; i < fsize; i++) {
        if (buffer[i] == '\n') {
            wordCount++;
        }
    }
    wordCount--;

}

void setSize() {
    f = fopen(PATH, "rb");
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
}
