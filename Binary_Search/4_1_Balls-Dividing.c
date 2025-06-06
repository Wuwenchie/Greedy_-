/*
你有一個長度為 N 整數陣列 arr，代表有 N 個裝球的袋子，其中 arr[i] 代表第 i 個袋子中的球數量。你最多可以進行 K 次操作，每次操作可以將任意一個袋子中的球分成兩個新的袋子，且兩個新袋子的球數都必須是正整數 (不必平分)。

例如: 原本一個袋子中有 5 顆球，一次操作後分成兩個袋子，兩袋子的球的數量可以是 1、4 或 3、2 等等 (但不可分成 0、5)。

你希望在至多 K 次操作之後，使得所有袋子中球數最多的袋子，其球數最少（也就是最小化最大值）。

請回傳在不超過 K 次操作後，可能得到的最小「最大袋子球數」。

題目目標:
  在不超過 K 次「分袋操作」下，使得最終所有袋子中最多球的袋子，球數 最小化。

輸入說明：
  第 1 行輸入包含兩個整數 N 、K 代表陣列長度、操作次數。 
  第 2 行輸入包含 N 個數字代表陣列 arr
  
  1 ≤ N ≤ 2 · 105
  1 ≤ K ≤ 109
  1 ≤ arr[ i ] ≤ 109

輸出說明：
  輸出一個整數，代表可獲得的最高價值，結尾需加上換行符號\n。

想法：Binary Search on Answer
1️⃣ 定義答案範圍
最小可能最大球數：1
最大可能最大球數：max(arr)（也就是一開始球最多的袋子）

2️⃣ 用 Binary Search 嘗試每個「最大球數限制」x：
對於每個袋子 arr[i]，如果它的球數 > x，我們要看看要花幾次操作才能讓它變成「每袋 ≤ x」。

一袋有 c 顆球，我們希望把它切成數個袋子，每個袋子 ≤ x，所以：
    需要的袋子數量：ceil(c / x)
    => 操作次數 = ceil(c / x) - 1
*/

#include <stdio.h>
#include <stdlib.h>

#define LL long long

// 計算在限制最大值 maxBall 時，需要的操作數
LL required_operations(LL *arr, LL n, LL maxBall) {
    LL ops = 0;
    for (LL i = 0; i < n; i++) {
        if (arr[i] > maxBall) {
            ops += (arr[i] + maxBall - 1) / maxBall - 1;
        }
    }
    return ops;
}

// Binary Search 主邏輯
LL find_min_max_balls(LL *arr, LL n, LL k) {
    LL left = 1, right = 0;
    for (LL i = 0; i < n; i++) {
        if (arr[i] > right) right = arr[i];  // 找出最大球數
    }

    while (left < right) {
        LL mid = (left + right) / 2;   // 切一半 找最大
        LL ops = required_operations(arr, n, mid);
        if (ops <= k) {
            right = mid;
        } 
        else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    LL n, k;
    scanf("%lld %lld", &n, &k);
    LL *arr = (LL *)malloc(sizeof(LL) * n);
    for (LL i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    LL result = find_min_max_balls(arr, n, k);
    printf("%lld\n", result);

    free(arr);
    return 0;
}
