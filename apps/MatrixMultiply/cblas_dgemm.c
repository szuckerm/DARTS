#include "cblas_dgemm.h"
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void 
cblas_dgemm(const enum CBLAS_ORDER Order, 
            const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_TRANSPOSE TransB,
            const int     M,     const int  N,   const int K,  
            const double  alpha, 
            const double *A,     const int  lda, 
            const double *B,     const int  ldb,
            const double  beta,  double    *C,   const int ldc)
{
    double (*a)[K] = (double (*)[K]) A;
    double (*b)[N] = (double (*)[N]) B;
    double (*c)[N] = (double (*)[N]) C;

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            double tmpC = beta * c[i][j];
            for (int k = 0; k < K; ++k) {
                tmpC += alpha * a[i][k] * b[k][j];
            }
            c[i][j] = tmpC;
        }
    }
}

#ifdef __cplusplus
}
#endif // __cplusplus
