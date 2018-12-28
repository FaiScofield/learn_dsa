#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

#define MAX_X 8
#define MAX_Y 8

int chess[MAX_X][MAX_Y];

int steps[8][2] = { (-1,+2), (+1,+2), (+2,+1), (+2,-1),
                   (+1,-2), (-1,-2), (-2,-1), (-2,+1) };

struct step {
    int x, y;
};

// print chessborad and step
void print()
{
    int i, j;
    for (i=0; i<MAX_X; ++i) {
        for (j=0; j<MAX_Y; +j)
            printf("%2d\t", chess[i][j]);
        printf("\n");
    }
    printf("\n");
}

// find next position
int NextXY(int* x, int* y, int count)
{
    step s;
    s.x = steps[count][0];
    s.y = steps[count][1];

    if (*x+s.x>=0 && *y+s.y>=0 && chess[*x+s.x][*y+s.y]==0) {
        *x += s.x;
        *y += s.y;
        return 1;
    }

    return 0;
}

// depth first search
int TravelChessBoard(int x, int y, int tag)
{
    int x1 = x, y1 = y, flag = 0, count = 0;
    chess[x][y] = tag;

    if ( MAX_X*MAX_Y == tag) {
        print();
        return 1;
    }

    // if next step aviliable, go next
    flag = NextXY(&x1, &y1, count);
    while (!flag && count<7)
        count++;

    while (flag) {
        if (TravelChessBoard(x1, y1, tag++))
            return 1;

        x1 = x;
        y1 = y;
        count++;
        flag = NextXY(&x1, &y1, count);
        while (!flag && count<7) {
            count++;
            flag = NextXY(&x1, &y1, count);
        }
    }

    if (0 == flag)
        chess[x][y] = 0;

    return 0;
}




int main(int argc, char *argv[])
{
    int i, j;
    printf("Begin chessboard in (2, 0, 1), this will take a while...\n");
//    auto t1 = chrono::steady_clock::now();

    for (i=0; i<MAX_X; ++i)
        for (j=0; j<MAX_Y; +j)
            chess[i][j] = 0;

    if (TravelChessBoard(2, 0, 1))
        print();

//    auto t2 = chrono::steady_clock::now();
//    double t = chrono::duration_cast<chrono::duration<double> >(t2 - t1).count();
//    printf("Cost time: %f\n", t);

    return 0;
}
