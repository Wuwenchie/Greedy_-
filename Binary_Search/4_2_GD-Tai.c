/*
  題目說明：
  為因應資訊化與數位化的發展趨勢，某市長想要在城市的一些服務點上提供無線網路服務，因此他委託電信公司架設無線基地台。某電信公司負責其中 N 個服務點，這 N 個服務點位在一條筆直的大道上，它們的位置(座標)係以與該大道一端的距離 P[i] 來表示，其中 i=0~N-1。由於設備訂製與維護的因素，每個基地台的服務範圍必須都一樣，當基地台架設後，與此基地台距離不超過 R (稱為基地台的半徑)的服務點都可以使用無線網路服務，也就是說每一個基地台可以服務的範圍是 D=2R (稱為基地台的直徑)。現在電信公司想要計算，如果要架設 K 個基地台，那麼基地台的最小直徑是多少才能使每個服務點都可以得到服務。
  基地台架設的地點不一定要在服務點上，最佳的架設地點也不唯一，但本題只需要求最小直徑即可。以下是一個 N=5 的例子，五個服務點的座標分別是 1、2、5、7、8。
  
  0    1    2    3    4    5    6    7    8    9
       ▲   ▲              ▲        ▲   ▲
  
  假設 K=1，最小的直徑是 7，基地台架設在座標 4.5 的位置，所有點與基地台的距離都在半徑 3.5 以內。假設 K=2，最小的直徑是 3，一個基地台服務座標 1 與 2 的點，另一個基地台服務另外三點。在 K=3 時，直徑只要 1 就足夠了。
  
  輸入說明：
  輸入有兩行。第一行是兩個正整數 N 與 K，以一個空白間格。第二行 N 個非負整數P[0],P[1],....,P[N-1]表示 N 個服務點的位置，任意位置介於 [0,10^9] 之間，這些位置彼此之間以一個空白間格。請注意，這 N 個位置並不保證相異也未經過排序。本題中，K<N 且所有座標是整數，因此，所求最小直徑必然是不小於 1 的整數。
  
  輸出說明：
  輸出最小直徑。
  
  提示：
  1. 記得開long long
  2. 記得換行

  題目說明與想法
    本題的目的是找出「最小的基地台直徑 D」，使得可以用 K 個基地台 覆蓋所有 N 個服務點。
  
  ✅ 題目關鍵重點：
    每個基地台的有效服務範圍是長度為 D（左右半徑為 D/2）。
    
    可以選擇基地台的位置，但要求能用 K 個基地台覆蓋所有點。
    
    服務點的位置可以重複、沒排序。
  
  ✅ 題目範例解析（以直覺驗證）：
    位置為：[1, 2, 5, 7, 8]
    若 K = 2，最小 D 是 3：
    
    第一台蓋住 [1,2]，基地台設在 1.5，涵蓋範圍是 [0,3]
    
    第二台蓋住 [5,7,8]，基地台設在 6.5，涵蓋範圍是 [5,8]
  
  ✅ 解法思路（使用二分搜尋 + 貪心）：
    目標：找最小可行的 D（直徑）
  
    預處理：  
      對 P 做排序。
    
    二分搜尋答案 D（1 ~ 最大距離）
      初始 low = 1，high = 最大點距離 - 最小點距離。
      
      check(D)：是否可以用 K 台基地台覆蓋所有點
    
    使用貪心法： 
      從左往右放基地台，基地台中心設在目前最左邊未覆蓋點 + D/2
      
      然後跳過所有可以覆蓋的點
      
      每次放一台基地台，直到覆蓋完或超過 K 台

*/  



#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int N, K;
int P[MAXN];

// 比較用於 qsort
int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

// 檢查是否能用 ≤ K 個基地台，覆蓋所有點，基地台直徑為 D
int check(int D) {
    int count = 0;
    int i = 0;
    while (i < N) {
        count++; //基地台個數
        int cover = P[i] + D; // 這個基地台最遠能覆蓋到的點
        i++; //下一個服務點
        while (i < N && P[i] <= cover) { //如果這個服務站在個基地台的範圍內就跳過
            i++;
        }
    }
    return count <= K;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &P[i]);
    }

    qsort(P, N, sizeof(int), cmp);

    int left = 1, right = 1000000000;
    int ans = right;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {  //如果此半徑成功覆蓋所有服務點
            ans = mid;
            right = mid - 1; // 嘗試更小直徑
        } else {
            left = mid + 1; //嘗試更大直徑
        }
    }

    printf("%d\n", ans);
    return 0;
}
