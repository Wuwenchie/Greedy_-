/*
A baker has 𝑁 bakery orders from customers that he must fulfill, but he can only handle one order a day. For the 𝑖 𝑡ℎ order, the baker needs to spend 𝐷𝑖 (1 ≤ 𝐷𝑖 ≤ 1000) consecutive days to complete it; however, for every day of delay, the baker must be fined 𝑆𝑖 (1 ≤ 𝑆𝑖 ≤ 10000). For example, if the baker receives four orders to make biscuits, the number of days required for each order is 3, 1, 2, 5, and the penalty for each day of delay is 4, 1000, 2, 5. If the baker’s work order is 1 2 3 4, the penalty will be 4×0 + 1000×3 + 2×4 + 5×6 = 3038, but if the work order is 2 1 3 4, the penalty will be 1000×0+ 4×1+ 2×4+ 5×6. 0+ 4×1+ 2×4+ 5×6 = 42, so the latter penalty is less. Please write a program to help the baker to find out the sequence of work which has the least penalty.

Input Format 
The first line of the input has a positive integer 𝑁 representing the number of orders, followed by 𝑁 lines, each with two integers separated by a space character, representing the number of days required for each order, 𝐷, and the penalty, 𝑆, for each day of delay, in that order. 

1 ≤ N ≤  2 · 105
1 ≤ D[i] ≤ 1000
1 ≤ S[i] ≤ 10000

Output Format 
For each set of data, output the sequence of jobs with the smallest penalty on one line. Each job is represented by its number, separated by a blank. If there is more than one set of answers, print the one with the smallest dictionary order. Note that each group of jobs is numbered starting with 1. The output includes a trailing space at the end of the line and a newline character ( '\n' or endl ).

# 提意:
  這題是經典的 工作排程問題（Scheduling Problem），目的是讓麵包師傅以最少的罰金順序完成所有訂單。
# 解題思路:
  這是一個變種的 最小懲罰調度（Minimize weighted sum of completion times） 問題。

  我們可以參考 Smith Rule（史密斯法則）來決定順序：

  為每個訂單計算一個「性價比」：

  性價比 = S[i] / D[i]（單位時間罰金越高者，越應該優先處理）

  根據 S[i]/D[i] 降序排序。

  若性價比相同，則以訂單原始順序（也就是編號）排序（為了確保字典序最小）
*/

# include <stdio.h>
# include <stdlib.h>

typedef struct{
    int index;
    int days;
    int penalty;
    double ratio;
}orders;

// 比較函式： 性價比 從大排到小
int compare(const void *a, const void *b) {
    orders *order1 = (orders *)a;
    orders *order2 = (orders *)b;
    
    if(order1->ratio < order2->ratio) 
        return 1;
    else if(order1->ratio > order2->ratio)
        return -1;
    else
        return 0;
}  

int main(){
    int N;
    scanf("%d", &N);
    
    orders *A = (orders*)malloc(N*sizeof(orders));
    if (A == NULL){
        printf("記憶體分配失敗\n");
        return 1;
    }
    
    for (int i = 0; i < N; i++){
        scanf("%d %d", &A[i].days, &A[i].penalty);
        A[i].index = i;
        A[i].ratio = (double)A[i].penalty / A[i].days;
    }
        
    // 按結束ratio排序
    qsort(A, N, sizeof(orders), compare);
    
    for(int i = 0; i < N; i++){
        printf("%d ", A[i].index + 1);
    }
    printf("\n");

}
