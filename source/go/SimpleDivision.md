---
title: 错题本：模数扩大技巧 + 倍增求全1数
layout: page 
comments: false # 如果你不想这个页面有评论框，可以加上这句
---

- link[https://atcoder.jp/contests/abc448/tasks/abc448_e]

## 题目特征

- N 极大（游程编码给出，位数可达 $10^9$）
- 要求 $\lfloor N/M \rfloor \mod P$（有向下取整再取模）

---

## 核心难点一：向下取整破坏取模

**问题：** 不能直接对 $P$ 取模，因为取模会丢失 $N$ 除以 $M$ 的余数信息，导致除法结果彻底错误。

**例子：** $M=3, P=10007, N=10010$

- 正确答案：$\lfloor 10010/3 \rfloor \mod 10007 = 3336$
- 错误做法：$N \mod 10007 = 3$，$\lfloor 3/3 \rfloor = 1$，完全错误

---

## 核心技巧：模数扩大为 $M \times P$

**结论：** 设 $r = N \mod (M \times P)$，则答案就是 $\lfloor r/M \rfloor$。

**数学推导：**

$$N = q \cdot (M \times P) + r$$

$$\Rightarrow \frac{N}{M} = q \cdot P + \frac{r}{M}$$

$$\Rightarrow \left\lfloor\frac{N}{M}\right\rfloor = q \cdot P + \left\lfloor\frac{r}{M}\right\rfloor$$

$$\Rightarrow \left\lfloor\frac{N}{M}\right\rfloor \mod P = \left\lfloor\frac{r}{M}\right\rfloor$$

最后一步成立是因为 $r < M \times P$，所以 $\lfloor r/M \rfloor < P$，不需要再取模。

**选择 $M \times P$ 的原因：** 需要除以 $M$ 后 $q$ 的系数是 $P$ 的倍数，最简单的选择就是让模数本身是 $M$ 的倍数。

---

## 核心难点二：$N$ 的结构与求和公式

游程编码拼出的 $N$ 可以表达为：

$$N = \sum_{i=1}^{K} c_i \times R_{l_i} \times 10^{\sum_{j=i+1}^{K} l_j}$$

其中 $R_k = \underbrace{11\ldots1}_{k \text{ 个 1}}$ 称为全1数（Repunit）。

三个部分：

- $c_i$：数字本身，直接乘
- $10^{\sum l_j}$：快速幂搞定
- $R_{l_i}$：**难点**，$l_i$ 最大 $10^9$，需要倍增

---

## 核心难点三：为什么不用 $R_k = \frac{10^k - 1}{9}$

这个公式需要 $9$ 在 $\mod (M \times P)$ 下的逆元，逆元存在条件是 $\gcd(9, M \times P) = 1$。

但 $M$ 可能是 $9$ 的倍数（如 $M=9$），此时逆元不存在，公式失效。

---

## 核心技巧：倍增求 $R_{l_i}$

**关键性质：**

$$R_{2^k} = R_{2^{k-1}} \times 10^{2^{k-1}} + R_{2^{k-1}}$$

$$R_{s + 2^k} = R_s \times 10^{2^k} + R_{2^k}$$

**第一阶段：预处理**（只需约30次）

```cpp
ten[0] = 10 % mod;                                      // 10^{2^0}
for(int i = 1; i < 30; i++)
    ten[i] = ten[i-1] * ten[i-1] % mod;                // 10^{2^i}

rli[0] = 1;                                             // R_{2^0} = R_1
for(int i = 1; i < 30; i++)
    rli[i] = (rli[i-1] * ten[i-1] + rli[i-1]) % mod;  // R_{2^i}
```

**第二阶段：查询任意 $R_l$**（二进制拼接）

```cpp
ll R = 0;
for(int d = 29; d >= 0; d--){
    if(l & (1ll << d)){
        R = (R * ten[d] + rli[d]) % mod;
    }
}
```

**例子：** $l = 13 = 1101_2$

| 扫到的位 | 操作 | R的含义 |
|---------|------|---------|
| d=3 | $R = 0 \times 10^8 + R_8$ | $R_8$ |
| d=2 | $R = R_8 \times 10^4 + R_4$ | $R_{12}$ |
| d=1 | 跳过 | $R_{12}$ |
| d=0 | $R = R_{12} \times 10^1 + R_1$ | $R_{13}$ |

---

## 易错点：0-based vs 1-based

涉及"2的幂次"的倍增，**推荐用0-based**：

- `arr[d]` 直接存 $2^d$ 相关的值
- 位运算 `1<<d` 和数组下标 `d` 天然对齐，无需 +1/-1

强行1-based会导致位运算时需要全程 `d+1` 偏移，容易出错。

---

## 总体反射：何时用模数扩大技巧

遇到**除法/取整 + 取模**时：

1. **先想逆元**：若 $\gcd(\text{除数}, \text{模数}) = 1$（如模数是质数），直接用逆元
2. **逆元不可用时**：把模数扩大为 $\text{除数} \times \text{原模数}$，用本技巧

**更广泛的本质：**
> 当中间某步运算会破坏取模时，找到更大的模数，使该运算能被数学上干净地消去。

类似思想：中国剩余定理（CRT）、多模数哈希。

---

## 复杂度

- 预处理：$O(30)$
- 每项查询：$O(30)$
- 总复杂度：$O(K \log l)$，其中 $l \leq 10^9$，$\log l \approx 30$
