#include "bfs.h"
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int row, col;         // 网格的行数和列数
    int x1, y1, x2, y2;   // 起始位置和目标位置的坐标

    cout << "请依次输入网格的行数和列数，起始位置的坐标(x1, y1)以及目标位置的坐标(x2, y2)。"
         << endl;
    cout << "输入格式为: row col x1 y1 x2 y2。输入行数和列数为 0 时程序结束。" << endl;

    while (true) {
        cout << "行数 (row): ";
        if (!(cin >> row) || row < 0) {
            cout << "输入有误，请输入一个非负整数。" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "列数 (col): ";
        if (!(cin >> col) || col < 0) {
            cout << "输入有误，请输入一个非负整数。" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (row == 0 || col == 0) break;   // 结束循环的条件

        cout << "请输入起始位置的 X 坐标 (x1): ";
        cin >> x1;
        cout << "请输入起始位置的 Y 坐标 (y1): ";
        cin >> y1;
        cout << "请输入目标位置的 X 坐标 (x2): ";
        cin >> x2;
        cout << "请输入目标位置的 Y 坐标 (y2): ";
        cin >> y2;

        point range  = {row, col};   // 创建网格范围的点
        point init   = {x1, y1};     // 创建起始点
        point target = {x2, y2};     // 创建目标点

        grid myGrid(range, init, target);   // 创建 grid 实例

        cout << "请按行输入网格数据（用字符表示，例如 '.' 表示空地，'#' 表示障碍物）:" << endl;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; ++j) {
                char cell;
                cin >> cell;
                myGrid.setMap(i, j, cell);   // 使用 setMap 方法设置网格数据
            }
        }

        myGrid.distClear();   // 使用 distClear 方法清空队列和初始化距离数组

        // 执行 BFS 搜索
        int res = myGrid.bfs(init);   // 执行 BFS 搜索并获取结果

        cout << "从起始位置到目标位置的最短距离是: " << res << endl;   // 输出结果
    }
    return 0;
}
