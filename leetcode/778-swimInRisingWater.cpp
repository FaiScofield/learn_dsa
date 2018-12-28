#include <iostream>
#include <vector>

using namespace std;

struct Direction {
    int x, y;
    Direction(int a, int b) { x = a; y = b; }
};

Direction up(0, -1);
Direction down(0, 1);
Direction left(-1, 0);
Direction right(1, 0);


int goNext(const vector<vector<int>>& grid, int& cpx, int& cpy, Direction d)
{
    cpx += d.x;
    cpy += d.y;
    int surround[4] = {grid[cpx][cpy-1], grid[cpx][cpy+1],
                       grid[cpx-1][cpy], grid[cpx+1][cpy]};
    // find next position
}

int swimInWater(const vector<vector<int>>& grid)
{
    // search from the end
}

int main(int argc, char *argv[])
{

    return 0;
}


