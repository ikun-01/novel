#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_M 1024
#define MAX_N 31

int M, N;
int mat[MAX_M][MAX_M];
int blk_avg[MAX_N][MAX_N];
int blk_med[MAX_N][MAX_N];
int blk_var[MAX_N][MAX_N];
int cnt[MAX_N*MAX_N];
int avg[MAX_N*MAX_N];
int med[MAX_N*MAX_N];
int var[MAX_N*MAX_N];

// 比较函数
int cmp(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

// 判断坐标是否越界
int is_valid(int x, int y) {
    return x >= 0 && y >= 0 && x < M && y < M;
}

// 计算子方阵平均值
void calc_avg(int i, int j) {
    double sum = 0;
    int k, l;
    for (k = 0; k < M/N; k++) {
        for (l = 0; l < M/N; l++) {
            int x = i * M/N + k;
            int y = j * M/N + l;
            if (is_valid(x, y)) {
                sum += mat[x][y];
            }
        }
    }
    blk_avg[i][j] = floor(sum / (M/N) / (M/N));
}

// 计算子方阵中位数
void calc_med(int i, int j) {
    int k;
    int arr[MAX_M];
    int len = 0;
    int x, y;
    for (k = 0; k < M/N * M/N; k++) {
        x = i * M/N + k / (M/N);
        y = j * M/N + k % (M/N);
        if (is_valid(x, y)) {
            arr[len++] = mat[x][y];
        }
    }
    qsort(arr, len, sizeof(int), cmp);
    blk_med[i][j] = arr[len / 2];
}

// 计算子方阵方差
void calc_var(int i, int j) {
    double sum = 0;
    int k, l;
    for (k = 0; k < M/N; k++) {
        for (l = 0; l < M/N; l++) {
            int x = i * M/N + k;
            int y = j * M/N + l;
            if (is_valid(x, y)) {
                sum += pow(mat[x][y] - blk_avg[i][j], 2);
            }
        }
    }
    blk_var[i][j] = floor(sum / (M/N) / (M/N));
}

int main() {
    int i, j, k;
    scanf("%d%d", &M, &N);
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
    // 计算各子方阵的平均值、中位数、方差
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            calc_avg(i, j);
            calc_med(i, j);
            calc_var(i, j);
        }
    }
    // 各子方阵平均值排序
    k = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            cnt[k] = blk_avg[i][j];
            k++;
        }
    }
    qsort(cnt, N*N, sizeof(int), cmp);
    for (i = 0; i < N*N; i++) {
        avg[i] = cnt[i];
    }
    // 各子方阵中位数排序
    k = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            cnt[k] = blk_med[i][j];
            k++;
        }
    }
    qsort(cnt, N*N, sizeof(int), cmp);
    for (i = 0; i < N*N; i++) {
        med[i] = cnt[i];
    }
    // 各子方阵方差排序
    k = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            cnt[k] = blk_var[i][j];
            k++;
        }
    }
    qsort(cnt, N*N, sizeof(int), cmp);
    for (i = 0; i < N*N; i++) {
        var[i] = cnt[i];
    }
    // 按要求输出
    for (i = 0; i < N*N; i++) {
        printf("%d ", avg[i]);
    }
    printf("\n");
    for (i = 0; i < N*N; i++) {
        printf("%d ", med[i]);
    }
    printf("\n");
    for (i = 0; i < N*N; i++) {
        printf("%d ", var[i]);
    }
    printf("\n");
    return 0;
}
