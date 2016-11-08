// combination.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int combination(int *branch, int length, int n, int r) {
    if (r == 0) {
        for (int i = 1; i < length; ++i) {
            printf("%d ", branch[i]);
        }
        printf("\n");
        return 1;
    }

    int count = 0;
    for (int i = branch[length - 1] + 1; i <= n - r + 1; ++i) {
        branch[length] = i;
        count += combination(branch, length + 1, n, r - 1);
    }
    return count;
}

int _tmain(int argc, _TCHAR* argv[]) {
    int n = 0;
    int r = 0;
    do {
        printf("\nFind all combinations with r numbers in n numbers.\n");
        printf("Input n r: ");
        scanf_s("%d%d", &n, &r);

        if (n <= 0 || r <= 0 || r > n) {
            printf("Error number input.\n\n");
            continue;
        }

        int *branch = (int*) malloc((r + 1) * sizeof(int));
        branch[0] = 0;
        int count = combination(branch, 1, n, r);
        printf("FOUND: %d combination(s)\n", count);
        printf("Press SPACE to continue, OTHERS to quit.\n");
    } while (_getch() == ' ');
    return 0;
}

