#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 32
#define MAX_M 1024

int cmp(const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}

int main() {
    int M, N, s, i, j, k, l;
    int blk_h[MAX_N], blk_w[MAX_N]; //子方阵的高度和宽度
    double blk_avg[MAX_N], blk_med[MAX_N], blk_var[MAX_N], sum;
    double arr[MAX_M][MAX_M], blk_arr[MAX_N][MAX_N][MAX_N * MAX_N];
    int blk_cnt[MAX_N], has_median[MAX_N];

    printf("请输入方阵大小M和分块数量N（M能被N整除）：\n");
    scanf("%d%d", &M, &N);
    s = M / N; //每个子方阵的大小

    //读入原方阵
    printf("请输入%d*%d的方阵：\n", M, M);
    for (i = 0; i < M; ++i) {
        for (j = 0; j < M; ++j) {
            scanf("%lf", &arr[i][j]);
        }
    }

    //计算每个子方阵的平均值、中位数、方差
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            //遍历第i行第j列的子方阵
            for (k = 0; k < s; ++k) {
                for (l = 0; l < s; ++l) {
                    blk_arr[i * N + j][k * s + l] = arr[i * s + k][j * s + l];
                }
            }

            blk_cnt[i * N + j] = s * s; //子方阵的元素个数
            sum = 0;
            for (k = 0; k < blk_cnt[i * N + j]; ++k) { //平均值
                sum += blk_arr[i * N + j][k];
            }
            blk_avg[i * N + j] = floor(sum / blk_cnt[i * N + j]);

            qsort(blk_arr[i * N + j], blk_cnt[i * N + j], sizeof(double), cmp);
            if (blk_cnt[i * N + j] % 2 == 0) { //中位数
                blk_med[i * N + j] = floor((blk_arr[i * N + j][blk_cnt[i * N + j] / 2 - 1] +
                                            blk_arr[i * N + j][blk_cnt[i * N + j] / 2]) / 2);
                has_median[i * N + j] = 1;
            } else {
                blk_med[i * N + j] = floor(blk_arr[i * N + j][blk_cnt[i * N + j] / 2]);
            }

            sum = 0;
            for (k = 0; k < blk_cnt[i * N + j]; ++k) { //方差
                sum += pow(blk_arr[i * N + j][k] - blk_avg[i * N + j], 2);
            }
            blk_var[i * N + j] = floor(sum / blk_cnt[i * N + j]);
        }
    }

    //向下取整并排序输出
    printf("平均值从大到小排序：");
    for (i = 0; i < N * N; ++i) {
        int max_idx = -1, max_val = -1;
        for (j = 0; j < N * N; ++j) {
            if (blk_avg[j] > max_val) {
                max_idx = j;
                max_val = blk_avg[j];
            }
        }
        blk_avg[max_idx] = -1;
        printf("%d ", max_val);
    }
    printf("\n");

    printf("中位数从大到小排序：");
    for (i = 0; i < N * N; ++i) {
        int max_idx = -1, max_val = -1;
        for (j = 0; j < N * N; ++j) {
            if (blk_med[j] > max_val && has_median[j]) {
                max_idx = j;
                max_val = blk_med[j];
            }
        }
        blk_med[max_idx] = -1;
        printf("%d ", max_val);
    }
    printf("\n");

    printf("方差从大到小排序：");
    for (i = 0; i < N * N; ++i) {
        int max_idx = -1, max_val = -1;
        for (j = 0; j < N * N; ++j) {
            if (blk_var[j] > max_val) {
                max_idx = j;
                max_val = blk_var[j];
            }
        }
        blk_var[max_idx] = -1;
        printf("%d ", max_val);
    }
    printf("\n");

    return 0;
}
