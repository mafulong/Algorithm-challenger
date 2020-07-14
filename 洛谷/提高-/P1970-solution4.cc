/*
 * Author        : OFShare
 * E-mail        : OFShare@outlook.com
 * Created Time  : 2020-05-18 22:03:10 PM
 * File Name     : P1970-solution4.cc
 */

#include <bits/stdc++.h>

#define ll long long
const int N = 1e5 + 5; int n, height[N], dp[N][2];
// dp[i][0](假设dp[i][0] = m1)表示前i个元素一共挑选出来m1个元素构成题目所说的波浪形, 且这m1个元素的末尾元素是波谷
// dp[i][1](假设dp[i][1] = m2)表示前i个元素一共挑选出来m2个元素构成题目所说的波浪形, 且这m2个元素的末尾元素是波峰
// 考虑dp[i][1]这个状态是由那些状态转移而来的(dp[i][0]类似)
// 假设height[i - 1] > height[i], 在考虑dp[i][1]这个状态时, dp[i - 1][1]这个状态已经更新过了

// 设dp[i - 1][1] = m, 它表示前面i - 1个元素挑选了m个元素出来构成波浪形, 且末尾元素是波峰. 注意这里我们不知道这个末尾元素
// 是等于height[i - 1]还是其他．
// 如果这个末尾元素高于第i - 1个元素, 那么我们就不用第i - 1个元素替换它(注意是不用, 因为是波峰,
// 所有我们要让末尾元素尽量高, 这样后面的元素才有更多的机会成为波谷, 贪心的思想)
// 同理如果这个末尾元素低于第i - 1个元素, 那么我们就把这个末尾元素替换为第i - 1个元素, 因为我们末尾元素是波峰, 我们要让它尽量高, 而第i - 1个元素高于
// 末尾元素, 所以就替换掉. 因为是替换, 所以序列长度还是没有变化.

// 这里我们就讲完了dp[i - 1][1] = m这个状态它具体表示的是什么．
// 简单总结就是前i - 1个元素挑选出来了m个元素构成波浪形, 且末尾的元素的高度只可能 >= height[i - 1].
// 回到最开始: 因为height[i - 1] > height[i], 所以状态dp[i][1] = dp[i - 1][1] = m
// 此时dp[i][1] = m这个状态表示, 它没有选择第i个元素, 且这m个元素构成的波浪形, 和原来的dp[i - 1][1]这个状态下的m个元素是一样的.

// 这里基本把dp[i][0], dp[i][1]这个状态到底表示的是什么讲明白了, 而且有一个贪心的思想, 波峰尽量高, 波谷尽量低(最优构造的波浪形)
// 因为dp[i - 1][0 / 1]维护的是前面i - 1个元素的状态, 所以dp[i][0 / 1]才只考虑dp[i - 1][0 / 1], 即前面一个元素(类似前缀(和)思想, 维护前缀信息)
// 这样转移就是O(1)的, 所有扫一遍就行了. 所以可以在O(N)的时间复杂度完成本题

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &height[i]);
  dp[1][0] = dp[1][1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (height[i - 1] > height[i]) {
      dp[i][1] = dp[i - 1][1];
      dp[i][0] = dp[i - 1][1] + 1;
    } else if (height[i - 1] < height[i]) {
      dp[i][0] = dp[i - 1][0];
      dp[i][1] = dp[i - 1][0] + 1;
    } else if (height[i - 1] == height[i]) {
      // do nothing, 即前面构造的最优波浪形不变
      dp[i][0] = dp[i - 1][0];
      dp[i][1] = dp[i - 1][1];
    }
  }
  printf("%d\n", std::max(dp[n][0], dp[n][1]));
  return 0;
}
