#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 4   // 最大行列数
#define MAX_M 256 // 最大子方阵个数

int N, M, Q; // 矩阵行列数、子方阵行列数、查询数量
int mat[MAX_N * MAX_N]; // 矩阵
int blk_cnt[MAX_N * MAX_N]; // 子方阵内元素个数
int blk_avg[MAX_N * MAX_N]; // 子方阵平均值
int blk_arr[MAX_N * MAX_N][MAX_N * MAX_N]; // 子方阵元素值
int blk_med[MAX_N * MAX_N]; // 子方阵中位数
int has_median[MAX_N * MAX_N]; // 子方阵是否已经计算过中位数
int blk_var[MAX_N * MAX_N]; // 子方阵方差

// 判断坐标是否越界
int is_valid(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N;
}

// 计算子方阵平均值
void calc_avg(int i, int j) {
    double sum = 0;
    int k, l;
    for (k = 0; k < M; k++) {
        for (l = 0; l < M; l++) {
            int x = i * M + k;
            int y = j * M + l;
            if (is_valid(x, y)) {
                sum += mat[x * N + y];
                blk_arr[i * N + j][blk_cnt[i * N + j]++] = mat[x * N + y];
            }
        }
    }
    blk_avg[i * N + j] = round(sum / blk_cnt[i * N + j]);
}

// 计算子方阵中位数
void calc_med(int i, int j) {
    int k;
    double sum = 0;
    for (k = 0; k < blk_cnt[i * N + j]; k++) {
        sum += blk_arr[i * N + j][k];
    }
    if (blk_cnt[i * N + j] % 2 == 0) { //中位数
        blk_med[i * N + j] = round(0.5 * (blk_arr[i * N + j][blk_cnt[i * N + j] / 2 - 1] +
                                           blk_arr[i * N + j][blk_cnt[i * N + j] / 2]));
        has_median[i * N + j] = 1;
    } else {
        blk_med[i * N + j] = round(blk_arr[i * N + j][blk_cnt[i * N + j] / 2]);
    }
}

// 计算子方阵方差
void calc_var(int i, int j) {
    double sum = 0;
    int k;
    for (k = 0; k < blk_cnt[i * N + j]; k++) {
        sum += pow(blk_arr[i * N + j][k] - blk_avg[i * N + j], 2);
    }
    blk_var[i * N + j] = round(sum / blk_cnt[i * N + j]);
}

int main() {
    int i, j;
    scanf("%d%d%d", &N, &M, &Q);
    for (i = 0; i < N * N; i++) {
        scanf("%d", &mat[i]);
    }
    for (i = 0; i < N / M; i++) {
        for (j = 0; j < N / M; j++) {
            calc_avg(i, j);
            calc_med(i, j);
            calc_var(i, j);
        }
    }
    while (Q--) {
        int x0, y0, x1, y1, t;
        scanf("%d%d%d%d%d", &x0, &y0, &x1, &y1, &t);
        int i0 = x0 / M;
        int i1 = x1 / M;
        int j0 = y0 / M;
        int j1 = y1 / M;
        double ans = 0;
        int cnt = 0;
        for (i = i0; i <= i1; i++) {
            for (j = j0; j <= j1; j++) {
                int x = i * M;
                int y = j * M;
                if (is_valid(x, y)) {
                    if (t == 1) { // 平均值
                        ans += blk_avg[i * N + j];
                    } else if (t == 2) { // 中位数
                        if (!has_median[i * N + j]) { // 如果还没有计算中位数，则现在再计算一遍
                            calc_med(i, j);
                        }
                        ans += blk_med[i * N + j];
                    } else { // 方差
                        ans += blk_var[i * N + j];
                    }
                    cnt++;
                }
            }
        }
        printf("%.6f\n", ans / cnt);
    }
    return 0;
}
