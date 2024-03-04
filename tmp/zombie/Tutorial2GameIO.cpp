#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef unsigned int uint;

// 程序使用的常量值
const uint NUM_ENEMIES = 4;    // 敌人数量
const uint MAX_MSG_LEN = 40;   // 最大消息长度

struct position
{
    uint x;   // x坐标
    uint y;   // y坐标
};

// 函数声明
int      scanf_s(const char* format, char* str, size_t bufferSize);
errno_t  strcpy_s(char* dest, size_t numberOfElements, const char* src);
position movePlayer(position p, position maxPos, int xMove, int yMove);
void     updateGrid(char** aa_grid, position playerPos, position maxPos, position* a_enemies,
                    uint numEnemies);
void     printGrid(char** aa_grid, position maxPos);
position userAction(position playerPos, position maxPos, char* lastMsg, uint bufferSize);
void     gameLoop(position playerPos, int width, int height);
uint     getWidth(int argc, char** argv);
uint     getHeight(int argc, char** argv);
position getPlayerPos(int argc, char** argv);

/* 主函数
运行程序时，输入宽度和高度的参数，格式如下例所示。如果没有给出宽度和高度，则使用默认值。示例程序调用：
Tutorial3GameControls.exe /w 10 /h 7 /p (1, 1)
*/
int main(int argc, char** argv)
{
    uint width;
    uint height;
    char lastMsg[MAX_MSG_LEN];

    // 为了快速展示 argc 和 argv 的工作方式
    for (int i = 0; i < argc; i++) {
        printf("%i: %s\n", i, argv[i]);
    }
    position playerPos = getPlayerPos(argc, argv);
    width              = getWidth(argc, argv);
    height             = getHeight(argc, argv);

    gameLoop(playerPos, width, height);
}

/* 玩家位移函数
按照一定量移动玩家。如果新位置不在网格内，则修正位置为最接近的有效值。
position p: 玩家当前的位置
position maxPos: 玩家可以占据的绝对最大网格位置。
int xMove: x维度上的移动量。
int yMove: y维度上的移动量。
返回玩家更新后的位置。
*/
position movePlayer(position p, position maxPos, int xMove, int yMove)
{
    // 使用临时变量，以防我们移动后的位置<0，被认为是一个很大的数字
    int testX = p.x + xMove;
    int testY = p.y + yMove;

    p.x = (testX < 0) ? 0 : testX;
    p.y = (testY < 0) ? 0 : testY;

    testX = p.x;
    testY = p.y;
    p.x   = (testX > maxPos.x) ? maxPos.x : testX;
    p.y   = (testY > maxPos.y) ? maxPos.y : testY;

    return p;
}

/* 更新网格函数
根据新的敌人和玩家角色位置盲目更新网格（一个字符网格）。
*/
void updateGrid(char** aa_grid, position playerPos, position maxPos, position* a_enemies,
                uint numEnemies)
{
    for (int i = 0; i <= maxPos.y; i++) {
        for (int j = 0; j <= maxPos.x; j++) {
            aa_grid[i][j] = '-';
        }
    }
    aa_grid[playerPos.y][playerPos.x] = 'P';
    for (int i = 0; i < numEnemies; i++) {
        int eY          = a_enemies[i].y;
        int eX          = a_enemies[i].x;
        aa_grid[eY][eX] = 'E';
    }
}

/* 打印网格函数
输出一个字符网格，表示敌人和玩家所在的位置。
这将呈现一个矩形网格，其中
    - 表示没有任何东西的位置，
    E 表示敌人，
    P 表示玩家角色。
*/
void printGrid(char** aa_grid, position maxPos)
{
    for (int i = 0; i <= maxPos.y; i++) {
        for (int j = 0; j <= maxPos.x; j++) {
            printf("%c", aa_grid[i][j]);
        }
        printf("\n");
    }
}

// 用户操作函数
position userAction(position playerPos, position maxPos, char* lastMsg, uint bufferSize)
{
    int moveAmount;

    printf("%s%s%s\n",
           "请输入你的下一个指令：向上(U)、向下(D)、向左(L)、向右(R)移动 + "
           "移动的空格数，攻击(A)和退出(Q)\n",
           "示例: U4 表示玩家向上移动4个空格。");
    scanf_s("%s", lastMsg, MAX_MSG_LEN);
    // 玩家的方向指令 UDLR + 给定方向的移动数（单个方向）
    switch (lastMsg[0]) {
    case 'u':
    case 'U':
        moveAmount = atoi(lastMsg + 1);
        playerPos  = movePlayer(playerPos, maxPos, 0, -moveAmount);
        break;
    case 'd':
    case 'D':
        moveAmount = atoi(lastMsg + 1);
        playerPos  = movePlayer(playerPos, maxPos, 0, moveAmount);
        break;
    case 'l':
    case 'L':
        moveAmount = atoi(lastMsg + 1);
        playerPos  = movePlayer(playerPos, maxPos, -moveAmount, 0);
        break;
    case 'r':
    case 'R':
        moveAmount = atoi(lastMsg + 1);
        playerPos  = movePlayer(playerPos, maxPos, moveAmount, 0);
        break;
    }   // switch 结束

    return playerPos;
}

// 游戏循环函数
void gameLoop(position playerPos, int width, int height)
{
    char lastMsg[MAX_MSG_LEN];

    position maxPos;
    maxPos.x = width - 1;
    maxPos.y = height - 1;

    position a_enemies[NUM_ENEMIES];
    char**   aa_grid = (char**)malloc(sizeof(char*) * height);
    for (int i = 0; i < height; i++) {
        aa_grid[i] = (char*)malloc(sizeof(char) * width);
    }
    // 设置敌人的初始位置。
    for (int i = 0; i < NUM_ENEMIES; i++) {
        a_enemies[i].x = width - 1;
        a_enemies[i].y = i;
    }

    strcpy_s(lastMsg, MAX_MSG_LEN, "");
    int moveAmount = 0;
    do {
        updateGrid(aa_grid, playerPos, maxPos, a_enemies, NUM_ENEMIES);
        printGrid(aa_grid, maxPos);
        playerPos = userAction(playerPos, maxPos, lastMsg, MAX_MSG_LEN);

    } while (strcmp(lastMsg, "q") && strcmp(lastMsg, "Q"));
    // 只要 lastMsg 不是 Q 或 q，就一直循环（在这种情况下，0 && 什么 == 0）

    // 结束时释放数组
    for (int i = 0; i < height; i++) {
        free(aa_grid[i]);
    }
    free(aa_grid);
    aa_grid = NULL;
}   // gameLoop 函数结束

// 获取宽度函数
uint getWidth(int argc, char** argv)
{
    uint width = 5;   // 默认宽度
    for (int i = 0; i < argc; i++) {
        if ((argv[i][0] == '/') && ((argv[i][1] == 'w') || (argv[i][1] == 'W'))) {
            assert(i < argc);
            width = atoi(argv[i + 1]);
            return width;
        }
    }
    return width;
}

// 获取高度函数
uint getHeight(int argc, char** argv)
{
    uint height = 5;   // 默认高度
    for (int i = 0; i < argc; i++) {
        if ((argv[i][0] == '/') && ((argv[i][1] == 'h') || (argv[i][1] == 'H'))) {
            assert(i < argc);
            height = atoi(argv[i + 1]);
            return height;
        }
    }
    return height;
}

// 获取玩家位置函数
position getPlayerPos(int argc, char** argv)
{
    position playerPos = {0, 0};   // 默认玩家位置

    for (int i = 0; i < argc; i++) {
        if ((argv[i][0] == '/') && ((argv[i][1] == 'p') || (argv[i][1] == 'P'))) {
            assert(i + 1 < argc);
            playerPos.x = atoi(argv[i + 1]);
            playerPos.y = atoi(argv[i + 2]);
            return playerPos;
        }
    }
    return playerPos;
}

// 由于 Clang++ 不支持 scanf_s 和 strcpy_s 函数，所以需要自定义这两个函数
// 自定义的 scanf_s 函数，仅用于演示读取字符串的情况，如果不需要可以注释掉。
int scanf_s(const char* format, char* str, size_t bufferSize)
{
    if (!str || bufferSize == 0) return -1;   // 确保参数有效

    // 为了安全起见，直接在这里限制输入长度
    // 假设 format 是 "%s"，这里不处理其他类型的格式化输入
    char safeFormat[256];
    snprintf(safeFormat, sizeof(safeFormat), "%%%zus", bufferSize - 1);

    return scanf(safeFormat, str);
}

// 自定义的 strcpy_s 函数
errno_t strcpy_s(char* dest, size_t numberOfElements, const char* src)
{
    if (numberOfElements == 0 || !dest || !src) {
        return EINVAL;   // 无效参数
    }
    if (strlen(src) + 1 > numberOfElements) {
        dest[0] = '\0';   // 不能完全复制，清空目标字符串
        return ERANGE;    // 给定的缓冲区太小
    }
    // 安全复制字符串
    strncpy(dest, src, numberOfElements);
    dest[numberOfElements - 1] = '\0';   // 确保字符串以 null 结尾
    return 0;                            // 成功
}
