# include <stdio.h>
# include <stdlib.h>
# define max_size 100000

typedef struct{
    int weight;
    int value;
}item;

int knapsack(item A[], int N, int capacity){
    int dp[max_size] = {0};     //dp[j]: 表示當背包容量為 j 時，目前為止能取得的最大價值
    
    for(int i=0; i<N; i++){
        for(int j=capacity; j>=A[i].weight; j--){
            int include = dp[j - A[i].weight] + A[i].value;     //讓出 items[i].weight 的空間，然後從 dp[j - weight] 加上這個物品的價值
            if(include > dp[j]){      //更新 dp[j]：取目前已知的最大值與「加上這個物品」的價值兩者之間的較大者
                dp[j] = include;
            }

        }
    }
    return dp[capacity];    //回傳當背包容量為 capacity 時能裝下的最大價值
}


int main(){
    int N, W;
    
    scanf("%d %d", &N, &W);
    item *A = (item*)malloc(N*sizeof(item));
    
    for(int i=0; i<N; i++){
        scanf("%d %d", &A[i].weight, &A[i].value);
    }
    
    int result = knapsack(A, N, W);
    printf("%d\n", result);
    
}
