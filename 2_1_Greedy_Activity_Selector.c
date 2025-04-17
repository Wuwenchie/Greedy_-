/*
  問題敘述:
  今天有 N 個活動可以參加，每個活動有自己的開始與結束時間。
  使用貪婪演算法，想辦法參加最多的活動。

  提醒:
  1.變數都是int。
  2.將活動先依照結束時間排序。
  3.請使用O(nlgn)的排序演算法，如內建函式 sort qsort 等。 
  
  輸入說明:
  第 1 行輸入包含一個整數 N 代表活動數量。 
  第 2~N+1 行輸入每行給定兩個整數 s[i], f[i] 分別代表第 i 個活動的開始時間、結束時間，數字間以一個空白區隔。
  
  1 ≤ N ≤ 2 · 105
  0 ≤ s[i], f[i] ≤ 109
  
  輸出說明:
  輸出一個整數，代表最多參加的活動數量。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int finish;
} activity;

// 比較函式：依照結束時間排序（小的排前面）
int compare(const void *a, const void *b) {
    activity *act1 = (activity *)a;
    activity *act2 = (activity *)b;
    return act1->finish - act2->finish;
}

int Greedy_Activity_Selector(activity A[], int N){
    // 貪婪選擇活動
    int count = 1; // 至少可以選第一個活動
    int last_finish = A[0].finish;

    for (int i = 1; i < N; i++) {
        if (A[i].start >= last_finish) {
            count++;
            last_finish = A[i].finish;
        }
    }
    return count;
}    
    


int main() {
    int N;
    scanf("%d", &N);

    activity *A = (activity *)malloc(N * sizeof(activity));
    if (A == NULL) {
        printf("記憶體分配失敗\n");
        return 1;
    }

    // 輸入活動資料
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &A[i].start, &A[i].finish);
    }

    // 按結束時間排序
    qsort(A, N, sizeof(activity), compare);

    int count = Greedy_Activity_Selector(A, N);

    printf("%d\n", count);

    free(A);
    return 0;
}
