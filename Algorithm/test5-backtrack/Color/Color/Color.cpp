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

void visit(Node *n) {
    printf("%d ", n->Data);
}

void DFS(Graph *g, int n, int *visited) {
    Node *node = g->Nodes + n;
    visit(node);
    visited[n] = 1;
    for (Arc *p = node->ArcHead->Next; p != NULL; p = p->Next) {
        if (visited[p->To] == 0) {
            DFS(g, p->To, visited);
        }
    }
}

void DFS(Graph *g) {
    int *visited = (int*)malloc(g->NodeCount * sizeof(int));
    for (int i = 0; i < g->NodeCount; ++i) {
        visited[i] = 0;
    }
    for (int i = 0; i < g->NodeCount; ++i) {
        if (visited[i] == 0) {
            DFS(g, i, visited);
        }
    }
    free(visited);
}

int _tmain(int argc, _TCHAR* argv[])
{
    Graph *g = (Graph*)malloc(sizeof(Graph));
    Init(g, 10);

    for (int i = 0; i < 10; ++i) {
        Node *node = (Node*)malloc(sizeof(Node));
        Init(node, i);
        g->Nodes[i] = *node;
    }

    int from[] = { 0, 1, 4, 8, 5, 5, 2, 3, 6, 7, 7 };
    int to[] = { 1, 4, 8, 5, 2, 1, 3, 6, 7, 3, 9 };
    for (int i = 0; i < 11; ++i) {
        AddTwoWayArc(g, from[i], to[i]);
    }
    DFS(g);
    getchar();
	return 0;
}

