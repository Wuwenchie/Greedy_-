#include <stdio.h>
#include <stdlib.h>
#define max_size 1000000

typedef struct {
    int u;
    int v;
    int w;
} edge;

int compare(const void *a, const void *b) {
    edge *edge1 = (edge *)a;
    edge *edge2 = (edge *)b;
    return edge1->w - edge2->w;
}

// Union-Find 陣列
int parent[max_size];

// Find：尋找根節點，並進行路徑壓縮
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// Union：將兩個集合合併 (u, v)中取大的當根結點
void unionSet(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) {
        parent[px] = py;
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    edge *A = (edge *)malloc(M * sizeof(edge));
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &A[i].u, &A[i].v, &A[i].w);
    }

    qsort(A, M, sizeof(edge), compare);  // 排序 M 條邊，不是 N

    // 初始化 Union-Find
    for (int i = 0; i < N; i++) {
        parent[i] = i;
    }

    int mini_cost = 0;
    int edge_count = 0;

    for (int i = 0; i < M && edge_count < N - 1; i++) {
        int u = A[i].u;
        int v = A[i].v;
        int w = A[i].w;

        if (find(u) != find(v)) {
            unionSet(u, v);
            mini_cost += w;
            edge_count++;
        }
    }

    printf("The cost of minimum spanning tree: %d\n", mini_cost);

    free(A);
    return 0;
}
