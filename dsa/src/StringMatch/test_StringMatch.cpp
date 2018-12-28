#include "StringMatch.h"
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

void match(char* P, char* T, int method) {
    int pos;
    switch (method) {
        case 0:
            printf("Method:  Brute Force I\n");
            pos = match_bf_I(P, T);
            break;
        case 1:
            printf("Method:  Brute Force II\n");
            pos = match_bf_II(P, T);
            break;
        case 2:
            printf("Method:  KMP\n");
            pos = match_kmp(P, T);
            break;
        case 3:
            printf("Method:  Boyer-Moore I\n");
            pos = match_bm_I(P, T);
            break;
        case 4:
            printf("Method:  Boyer-Moore II\n");
            pos = match_bm_II(P, T);
            break;
        default:
            pos = -1;
            break;
    }

    // print
    printf("Text:    "); printString(T); printf("\n");
    printf("Pattern: ");
    for (int i=0; i<pos; ++i) printf("   ");
    printString(P); printf("\n");
    if (strlen(T) < pos + strlen(P))
        printf("No matching found!\n");
    else
        printf("Matching found at #%d\n", pos);
}


/******************************************************************************************
 * 串匹配算法统一测试
 ******************************************************************************************/
int main(int argc, char* argv[]) {
    if (3 > argc) {
        fprintf(stderr, "\nUsage: %s <Pattern> <Text>\n\nFor example: \n<Pattern>: people \n<Text>: \"now is the time for all good people to come\"\n\n", argv[0]);
        return -1;
    }

    for (int i=0; i<5; ++i) {
        printf("\n####################################################\n");
        match(argv[1], argv[2], i);
    }



    return 0;
}
