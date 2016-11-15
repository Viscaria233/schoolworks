// Color.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct Arc {
    int To;
    Arc *Next;
};

struct Node {
    int Data;
    Arc *ArcHead;
};

struct Graph {
    Node *Nodes;
    int NodeCount;
};

void Init(Arc *arc) {
    arc->To = -1;
    arc->Next = NULL;
}

void Init(Node *node, int data) {
    node->Data = data;
    node->ArcHead = (Arc*)malloc(sizeof(Arc));
    Init(node->ArcHead);
}

void Init(Graph *graph, int nodeCount) {
    graph->Nodes = (Node*)malloc(nodeCount * sizeof(Node));
    graph->NodeCount = nodeCount;
}

void AddArc(Graph *g, int from, int to) {
    Arc *head = ((g->Nodes) + from)->ArcHead;
    Arc *arc = (Arc*)malloc(sizeof(Arc));
    Init(arc);
    arc->To = to;
    arc->Next = head->Next;
    head->Next = arc;
}

void AddTwoWayArc(Graph *g, int from, int to) {
    AddArc(g, from, to);
    AddArc(g, to, from);
}

int Check(Node *n, int color, int *visited) {
    for (Arc *p = n->ArcHead->Next; p != NULL; p = p->Next) {
        if (visited[p->To] == color) {
            return 0;
        }
    }
    return 1;
}

int Color(Graph *g, int nodeIndex, int colorCount, int *visited) {
    int found = 0;

    if (nodeIndex == g->NodeCount) {
        for (int i = 0; i < g->NodeCount; ++i) {
            printf("%4d", visited[i]);
        }
        printf("\n");
        return 1;
    }

    if (visited[nodeIndex] == -1) {
        for (int j = 0; j < colorCount; ++j) {
            if (Check(g->Nodes + nodeIndex, j, visited) == 1) {
                visited[nodeIndex] = j;
                found += Color(g, nodeIndex + 1, colorCount, visited);
                visited[nodeIndex] = -1;
            }
        }
    }
    return found;
}

int Color(Graph *g, int colorCount) {
    int *visited = (int*)malloc(g->NodeCount * sizeof(int));
    for (int i = 0; i < g->NodeCount; ++i) {
        visited[i] = -1;
    }
    int result = Color(g, 0, colorCount, visited);
    free(visited);
    return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
    Graph *g = (Graph*)malloc(sizeof(Graph));

    Init(g, 4);

    for (int i = 0; i < g->NodeCount; ++i) {
        Node node;
        Init(&node, i);
        g->Nodes[i] = node;
    }

    int from[] = { 0, 0, 1, 1 };
    int to[] = { 1, 2, 2, 3 };
    for (int i = 0; i < 4; ++i) {
        AddTwoWayArc(g, from[i], to[i]);
    }

    int found = Color(g, 3);
    printf("%d result(s) found\n", found);
    free(g);
    getchar();
    return 0;
}

