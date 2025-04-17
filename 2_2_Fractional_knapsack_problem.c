/*
  問題敘述:
  有 N 個物品可以拿取，每個物品有不同的價值，而今天有一個背包可以裝下總重量為 C 的物品。
  使用貪婪演算法，拿取價值總和最高的物品（物品可以分割）。

  提醒:
  1.請先依據(價值/重量)排序物品。 
  2.浮點數計算請使用double型態。 
  3.請使用O(nlgn)的排序演算法，如內建函式 sort、qsort 等。 
  4.使用 %lf 或 setprecision 來做輸出。
  
  輸入說明:
  第 1 行輸入包含兩個整數 N、C 分別代表物品數量、背包容量。 
  第 2~N+1 行輸入每行給定兩個整數 v[i], w[i] 分別代表第 i 個物品的價值、重量 ，數字間以一個空白區隔。
  
  1 ≤ N ≤ 105
  1 ≤ C ≤ 107
  1 ≤ v[i] ≤ 5000
  1 ≤ w[i] ≤ 5000
  
  輸出說明:
  輸出一個浮點數代表可賣出的最高價錢，固定輸出到小數點後六位數，
  結尾有換行符號 \n。
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int weight;
    double ratio;   // ratio = value/weigt
} items;

// 比較函式： (value/weigt) 從大排到小
int compare(const void *a, const void *b) {
    items *item1 = (items *)a;
    items *item2 = (items *)b;
    
    if(item1->ratio < item2->ratio) 
        return 1;
    else if(item1->ratio > item2->ratio)
        return -1;
    else
        return 0;
}  
    
double Fractional_Knapsack(items A[], int N, int capacity){    //N=物品數量
    double load = 0;
    double load_val = 0;
    int i = 0;
    while(load < capacity && i < N){
        if(A[i].weight <= capacity-load){
            load += A[i].weight;
            load_val += A[i].value;
        }
        else{
            double remain = capacity-load;
            load_val += A[i].ratio * remain;
            load += remain;
            break;
        }
        i++;
    }
    return load_val;
}

int main() {
    int N, capacity;
    scanf("%d %d", &N, &capacity);

    items *A = (items *)malloc(N * sizeof(items));
    if (A == NULL) {
        printf("記憶體分配失敗\n");
        return 1;
    }

    // 輸入活動資料
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &A[i].value, &A[i].weight);
        A[i].ratio = (double) A[i].value / A[i].weight;
    }

    // 按結束ratio排序
    qsort(A, N, sizeof(items), compare);

    double price = Fractional_Knapsack(A, N, capacity);

    printf("%lf\n", price);

    free(A);
    return 0;
}




