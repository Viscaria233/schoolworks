// Maze.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

const int MAXROW = 10;
const int MAXCOL = 10;

int Maze(int maze[MAXROW][MAXCOL], int row, int col, int dep) {
    int top = 0;
    int dRow[] = {0, 1, 0, -1};
    int dCol[] = {1, 0, -1, 0};
    if (row >= MAXROW || col >= MAXCOL || maze[row][col] != 0) {
        return 0;
    }

    maze[row][col] = dep++;
    if (row == MAXROW - 1 && col == MAXCOL - 1) {
        return 1;
    }

    for (int i = 0; i < 4; ++i) {
        if (Maze(maze, row + dRow[i], col + dCol[i], dep) == 1) {
            return 1;
        }
    }
    maze[row][col] = -2;
    return 0;
}

int _tmain(int argc, _TCHAR* argv[]) {
    int maze[MAXROW][MAXCOL] = {
        { 0, -1, -1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, -1, -1, 0, -1, -1, -1, -1, -1, 0 },
        { 0, -1, -1, 0, -1, 0, 0, 0, -1, 0 },
        { 0, -1, -1, 0, 0, 0, -1, 0, -1, 0 },
        { 0, 0, 0, -1, -1, -1, -1, 0, -1, 0 },
        { 0, -1, 0, 0, 0, 0, -1, 0, -1, 0 },
        { 0, -1, -1, 0, -1, 0, -1, 0, -1, 0 },
        { 0, -1, 0, 0, 0, 0, -1, 0, -1, 0 },
        { 0, -1, -1, -1, -1, -1, -1, 0, -1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, -1, 0 },
    };
    int find = Maze(maze, 0, 0, 1);
    if (find == 1) {
        for (int i = 0; i < MAXROW; ++i) {
            for (int j = 0; j < MAXCOL; ++j) {
                printf("%4d", maze[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("not found\n");
    }
    getchar();
	return 0;
}

