/*
  Statement :
  在盤古大陸中，北方有一座山叫做聖山，聖山裡住著一位副本BOSS名叫盤古，打完BOSS有機率掉落傳奇武器。弓箭手 IZhna 為了得到傳奇弓-逐日，他自己跑去找盤古打架，
  戰鬥途中需要解出各種謎題才可以打贏盤古，在戰鬥中，IZhna 發現盤古手部下方有一個 N×M 大小的矩陣 A，矩陣上的每個位置都有一個數字Aij，他認為這個謎題太難了，不知道怎麼解決，
  由於他思考時間太久，神族長老看不下去了，並告訴他一個提示...。
  
  
  神族長老：「你必須要通過這個矩陣才能打贏盤古，通過這個謎題必須要走特定的路徑。路徑從第 1 行（也就是最左側）任何一個位置開始，一步步走到最後一行（最右側、第 M 行）結束。
            每一步可以移動到右邊相鄰的一格，包括上下斜對角的格子。矩陣的首尾列（第 1 列和第 N 列）視為相鄰，也就是矩陣呈現上下無限長的形狀。合法的移動方式如下圖所示」
  
  神族長老繼續說：「經過一個第 i 列第 j 行的格子需要消耗 Aij 個解毒丹，一條路徑的所需的解毒丹數量為該路徑上所有格子的數字總和，
                假如你走下方左圖這樣的路徑的話，需要消耗 16 顆解毒丹 ; 而下方右圖的話需要花 11 顆解毒丹，希望你有帶夠多的解毒丹，擊倒盤古吧！」
  
  
  IZhna 這時非常慌張，他馬上點開自己的背包，發現裡面有 K 顆解毒丹。
  聰明的你能不能幫 IZhna 找到一條路徑以通過這個謎題，並輸出此路徑最少可以花多少個解毒丹。
  如果 IZhna 的解毒丹帶不夠多，代表 IZhna 需要回皇城重新補給，請輸出 "RE: START :<" (不含引號)。
  
  
  Input format:
  以下是 Input 的格式：
  N M K
  A11 A12 ... A1M
  A21 A22 ... A2M
  ....
  AN1 AN2 ... ANM
  
  Output :
  如果 IZhna 可以使用 K 個解毒丹通過這個謎題，請輸出最少可以花多少個解毒丹。否則輸出 "RE: START :<" (不含引號)。
  
  Constraints :
  1 ≤ N,M ≤ 1000
  0 ≤ K ≤ 10^12
  0 ≤ Aij ≤ 10^9
  
  Hint1 : DP :D
  Hint2 : 數字很大記得開 long long
  Hint3 : IZhna 清明連假花了兩天打了四次盤古才拿到傳奇弓-逐日
*/


# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# define max_size 1000

# define LL long long

LL A[max_size][max_size];
LL dp[max_size][max_size];

// 找三個中最小的
LL min3(LL a, LL b, LL c){
    if(a < b)
        return a < c ? a : c;
    else
        return b < c ? b : c;
}

int main(){
    int N, M;
    LL K;
    scanf("%d %d %lld", &N, &M, &K);

    // 輸入矩陣 A
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            scanf("%lld", &A[i][j]);
        }
    }
    
    // 初始化 dp
    for(int i=0; i<N; i++){
        dp[i][0] = A[i][0];
    }
    
    // 動態規劃轉移
    for(int j=1; j<M; j++){
        for(int i=0; i<N; i++){
            int up = (i -1 + N) % N;   //從左上
            int down = (i + 1) % N;    //從左下
            dp[i][j] = A[i][j] + min3(dp[up][j-1], dp[i][j-1], dp[down][j-1]);
        }
    }
    
    // 找出最小解毒丹數
    LL result = LLONG_MAX;
    for(int i=0; i<N; i++){
        if(dp[i][M-1] < result)
            result = dp[i][M-1];
    }
    
    if(result <= K)
        printf("%lld\n", result);
    else
        printf("RE: START :<\n");

}
