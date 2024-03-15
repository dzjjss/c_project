#include "bfs.h"
#include <cstring>
#include <deque>

grid::grid(point range, point init, point target)
    : range(range)
    , init(init)
    , target(target)
{}

void grid::setMap(int x, int y, char c)
{
    this->Map[x][y] = c;
}

void grid::distClear()
{
    memset(this->dist, -1, sizeof(this->dist));
}

bool grid::isValid(int newX, int newY)
{
    return newX >= 0 && newX < this->range.x && newY >= 0 && newY < this->range.y &&
           dist[newX][newY] == -1;
}

void grid::updatePosition(int currentX, int currentY, int newX, int newY)
{
    char currentChar = Map[currentX][currentY];
    char nextChar    = Map[newX][newY];
    if (currentChar == nextChar) {
        dist[newX][newY] = dist[currentX][currentY];
        path.push_front({newX, newY});   // 优先处理，放入队列前端
    }
    else {
        dist[newX][newY] = dist[currentX][currentY] + 1;
        path.push_back({newX, newY});   // 放入队列后端
    }
}

int grid::bfs(point foo)
{
    path.push_back(this->init);   // Add starting point to the queue
    while (!path.empty()) {
        auto currentPoint = path.front();
        path.pop_front();

        for (int i = 0; i < 4; i++) {
            int newX = currentPoint.x + dx[i];   // dx[] = {-1, 0, 1, 0}
            int newY = currentPoint.y + dy[i];   // dy[] = {0, 1, 0, -1}

            // Check for validity early to skip the rest of the loop body
            if (!isValid(newX, newY)) continue;

            updatePosition(currentPoint.x, currentPoint.y, newX, newY);
            // Return as soon as the target is reached
            if (newX == target.x && newY == target.y) return dist[target.x][target.y];
        }
    }
    return -1;   // If unreachable
}
