// Dynamic.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int* dynamic(int nodes[][4], int *nodeCount, int layerCount, int weight[][13], int wRow, int wCol) {
    int *result = (int*)malloc((layerCount - 1) * sizeof(int));

    for (int i = layerCount - 2; i > 0; --i) {
        int min = -1;
        for (int j = 0; j < nodeCount[i]; ++j) {
            int now = nodes[i][j];
            for (int k = 0; k < nodeCount[i + 1]; ++k) {
                int after = nodes[i + 1][k];
                if (weight[now][after] != -1) {
                    for (int l = 0; l < nodeCount[i - 1]; ++l) {
                        int before = nodes[i - 1][l];
                        if (weight[before][now] != -1) {
                            weight[before][now] += weight[now][after];
                            if (min == -1 || weight[before][now] < weight[before][min]) {
                                min = now;
                            }
                        }
                    }
                }
            }
        }
        if (min != -1) {
            result[i] = min;
        }
    }
    return result;
}

int _tmain(int argc, _TCHAR* argv[]) {
    int layerCount = 5;
    int nodes[][4] = {
        { 1 },
        { 2, 3, 4, 5 },
        { 6, 7, 8 },
        { 9, 10, 11 },
        { 12 }
    };
    int nodeCount[] = { 1, 4, 3, 3, 1 };
    int weight[][13] = {
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },     //0
        { -1, -1, 9, 7, 3, 2, -1, -1, -1, -1, -1, -1, -1 },     //1
        { -1, -1, -1, -1, -1, -1, 4, 2, 1, -1, -1, -1, -1 },     //2
        { -1, -1, -1, -1, -1, -1, 2, 7, -1, -1, -1, -1, -1 },     //3
        { -1, -1, -1, -1, -1, -1, -1, -1, 11, -1, -1, -1, -1 },     //4
        { -1, -1, -1, -1, -1, -1, -1, 11, 8, -1, -1, -1, -1 },     //5
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, 5, -1, -1 },     //6
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, 4, 3, -1, -1 },     //7
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, 6, -1 },     //8
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4 },     //9
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },     //10
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5 },     //11
    };
    int wRow = 12;
    int wCol = 13;

    int *result = dynamic(nodes, nodeCount, layerCount, weight, wRow, wCol);

    for (int i = 1; i < layerCount - 1; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    getchar();
    free(result);
    return 0;
}

