// GasFilling.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int fillGas(int *distance, int n, int k, int *stop) {
    int dis = 0;
    int nowAt = -1;
    int count = 0;
    while (nowAt < k) {
        if (n < distance[nowAt + 1]) {
            return -1;
        }

        while (dis <= n) {
            if (nowAt >= k) {
                return count;
            }
            ++nowAt;
            dis += distance[nowAt];
        }
        --nowAt;
        stop[count] = nowAt;
        ++count;
        dis = 0;
    }

    return count;
}

int _tmain(int argc, _TCHAR* argv[]) {
    int n = 0;
    int k = 0;
    FILE *file = NULL;
    //file = fopen("output.txt", "a");
    fopen_s(&file, "output.txt", "a");

    do {
        printf("Input n, k;\n");
        scanf_s("%d%d", &n, &k);

        int *stop = (int*)malloc(k * sizeof(int));
        ++k;
        int *distance = (int*)malloc(k * sizeof(int));

        printf("Input k distance(s):\n");
        for (int i = 0; i < k; ++i) {
            scanf_s("%d", distance + i);
        }

        int count = fillGas(distance, n, k, stop);

        fputc('\n', file);

        if (count == -1) {
            fputs("No Solution\n", file);
            printf("No Solution\n");
        } else {
            printf("The gas station(s) which the car should stop at:\nNo.");
            for (int i = 0; i < count; ++i) {
                if (stop[i] != -1) {
                    fprintf(file, "%d ", stop[i]);
                    printf("%d ", stop[i]);
                }
            }
            fprintf(file, "\nTOTAL: %d\n", count);
            printf("\nTOTAL: %d\n", count);
        }
        printf("Press SPACE to continue, OTHERS to quit\n");
    } while (_getch() == ' ');
    fclose(file);
    return 0;
}

