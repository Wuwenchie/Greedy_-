/*
  題敘：
  給定一串矩陣的序列，請找出一種最有效率的方式來相乘這些矩陣。最有效率的方式是指：需要的乘法次數最少。
  
  由於矩陣乘法具有結合律（associative），你可以用不同的括號順序來進行乘法運算，但實際需要的乘法次數會根據括號位置大幅改變！
  
  假設有三個矩陣：
  
  𝐴 是 50×10 的矩陣
  𝐵 是 10×20 的矩陣
  𝐶 是 20×5 的矩陣
  那麼有兩種乘法順序：
  
  方案一：先算 (𝐴×𝐵) 再乘 𝐶：
  需要的乘法次數是 50×10×20 + 50×20×5 = 10000 + 5000 = 15000
  方案二：先算 (𝐵×𝐶) 再乘 𝐴：
  需要的乘法次數是 10×20×5 + 50×10×5 = 1000 + 2500 = 3500
  輸入：
  第一行：一個整數 n — 表示矩陣的數量。
  
  接下來 n 行，每行包含兩個整數 rᵢ 和 cᵢ — 表示第 i 個矩陣的列數與行數。
  
  條件限制： 
  1 ≤ n ≤ 500
  1 ≤ ri, ci ≤ 1000
  rᵢ = ci-1，對於所有 1 < i ≤ n
  
  輸出：  
  輸出一行：最少需要的乘法次數。
  
  提示：  
  1. 記得開long long
  2. 記得行尾換行

  虛擬碼參考 ch15 p.24
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LL long long
#define max_size 1000

LL m[max_size][max_size];
LL p[max_size];

int main()
{
    LL n, r, c;
    scanf("%lld", &n);
    
    for(int i=0; i<n; i++){
        scanf("%lld %lld", &r, &c);
        
        if(i==0){
            p[0] = r;
        }
        p[i+1] = c;
            
    }
    
    // 初始化，單一矩陣不需乘法運算
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // l 是鏈的長度
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = LLONG_MAX;
            for (int k = i; k < j; k++) {   // 嘗試在位置 k 括號劃分
                long long q = m[i][k] + m[k + 1][j] + 1LL * p[i - 1] * p[k] * p[j];
                
                if (q < m[i][j]) {  // 找出 k 分割點時最小的總乘法次數，更新 m[i][j]
                    m[i][j] = q;
                }
            }
        }
    }

    printf("%lld\n", m[1][n]);  // 輸出從第 1 個矩陣乘到第 n 個矩陣的最少乘法次數

    return 0;
}
