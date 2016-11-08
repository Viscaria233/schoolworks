// Hanoi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int move(char towers[3], int from, int to) {
    printf("%c --> %c\n", towers[from], towers[to]);
    return 1;
}

int hanoi(int plateNumber, char towers[3], int from, int to, int between) {
    if (plateNumber < 1) {
        return 0;
    } else if (plateNumber == 1) {
        move(towers, from, to);
        return 1;
    } else {
        int moves = 0;
        moves += hanoi(plateNumber - 1, towers, from, between, to);
        moves += move(towers, from, to);
        moves += hanoi(plateNumber - 1, towers, between, to, from);
        return moves;
    }
}

int _tmain(int argc, _TCHAR* argv[]) {
    char towers[] = { 'A', 'B', 'C' };

    do {
        int plateNumber = 0;
        printf("Input the number of plates: ");
        scanf_s("%d", &plateNumber);

        int moves = hanoi(plateNumber, towers, 0, 1, 2);

        printf("Move %d times\nPress SPACE to continue, OTHERS to exit\n", moves);
    } while (_getch() == ' ');
    return 0;
}

