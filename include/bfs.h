#ifndef BFS_H
#define BFS_H

#include <deque>   // 提供双端队列容器

using namespace std;

struct point
{
    int x, y;
};

class grid
{
private:
    static const int    N = 510;      // max size of the grid
    char                Map[N][N];    // mark the coordinate info
    int                 dist[N][N];   // record the distance
    point               range;        // set range a point cuz it's always a rectangle
    point               init;         // set initial point
    point               target;       // set target point
    deque<point>        path;         // record the path
    deque<deque<point>> bfs_tier;     // record the tier of bfs
    // point direction[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    // point up = direction[(int)direction::UP];
    // point up = direction[static_cast<int>(direction::UP)];

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

public:
    /*
    enum direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    */
    // constructor
    grid(point range, point init, point target);

    // setter
    void setMap(int x, int y, char c);

    void distClear();



    // bfs
    bool isValid(int newX, int newY);
    void updatePosition(int currentX, int currentY, int newX, int newY);
    int  bfs(point foo);
};
#endif
