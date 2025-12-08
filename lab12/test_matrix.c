#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "matrix.h"

// Macro to simplify error checking
#define ASSERT_OK(x) assert((x) == 0)
#define ASSERT_FAIL(x) assert((x) != 0)

// Helper: Fill matrix with sequential data for testing
// mod p is applied automatically
void fill_matrix_seq(Matrix *mat, int64_t start_val) {
    int64_t val = start_val;
    for (size_t i = 0; i < mat->rows; i++) {
        for (size_t j = 0; j < mat->cols; j++) {
            mat->data[i][j] = (val % mat->p + mat->p) % mat->p;
            val++;
        }
    }
}

// Helper: Check if two matrices are equal
int matrix_eq(const Matrix *A, const Matrix *B) {
    if (A->rows != B->rows || A->cols != B->cols || A->p != B->p) return 0;
    for (size_t i = 0; i < A->rows; i++) {
        for (size_t j = 0; j < A->cols; j++) {
            if (A->data[i][j] != B->data[i][j]) return 0;
        }
    }
    return 1;
}

// 1. Test Allocation and Deep Copy
void test_lifecycle() {
    printf("[Running] test_lifecycle...\n");
    Matrix A, B;
    int64_t p = 17;

    ASSERT_OK(matrix_create(&A, 3, 3, p));
    fill_matrix_seq(&A, 1);

    // Test Deep Copy
    ASSERT_OK(matrix_deep_copy(&A, &B));

    // Check content equality
    assert(matrix_eq(&A, &B));

    // Check pointer independence (Deep Copy)
    assert(A.data != B.data);
    assert(A.data[0] != B.data[0]);

    // Modify A, ensure B doesn't change
    A.data[0][0] = (A.data[0][0] + 1) % p;
    assert(!matrix_eq(&A, &B));

    matrix_free(&A);
    matrix_free(&B);
    printf("[Passed] test_lifecycle\n");
}

// 2. Test Addition and Scalar Mul (Modulo Checks)
void test_arithmetic() {
    printf("[Running] test_arithmetic...\n");
    Matrix A, B, C;
    int64_t p = 5; // Small prime for easy verification

    ASSERT_OK(matrix_create(&A, 2, 2, p));
    ASSERT_OK(matrix_create(&B, 2, 2, p));
    ASSERT_OK(matrix_create(&C, 2, 2, p));

    // A = [[1, 2], [3, 4]]
    A.data[0][0]=1; A.data[0][1]=2;
    A.data[1][0]=3; A.data[1][1]=4;

    // B = [[4, 3], [2, 1]]
    B.data[0][0]=4; B.data[0][1]=3;
    B.data[1][0]=2; B.data[1][1]=1;

    // Test Addition: (1+4)%5 = 0
    ASSERT_OK(matrix_add(&A, &B, &C));
    assert(C.data[0][0] == 0); // 1+4 = 5 = 0 mod 5
    assert(C.data[0][1] == 0); // 2+3 = 5 = 0 mod 5
    assert(C.data[1][0] == 0);
    assert(C.data[1][1] == 0);

    // Test Scalar Mul: A * 2 => [[2, 4], [6->1, 8->3]]
    ASSERT_OK(matrix_scalar_mul(&A, 2, &C));
    assert(C.data[1][0] == 1); // 3*2 = 6 = 1 mod 5
    assert(C.data[1][1] == 3); // 4*2 = 8 = 3 mod 5

    matrix_free(&A); matrix_free(&B); matrix_free(&C);
    printf("[Passed] test_arithmetic\n");
}

// 3. Test Multiplication and Identity
void test_multiplication() {
    printf("[Running] test_multiplication...\n");
    Matrix A, I, Res;
    int64_t p = 7;

    ASSERT_OK(matrix_create(&A, 2, 2, p));
    ASSERT_OK(matrix_create(&I, 2, 2, p));
    ASSERT_OK(matrix_create(&Res, 2, 2, p));

    fill_matrix_seq(&A, 1); // [[1, 2], [3, 4]]
    ASSERT_OK(matrix_identity(2, p, &I));

    // A * I = A
    ASSERT_OK(matrix_mul(&A, &I, &Res));
    assert(matrix_eq(&A, &Res));

    // Manual Calc Check:
    // [[1, 2], [3, 4]] * [[1, 2], [3, 4]] mod 7
    // [0][0] = 1*1 + 2*3 = 7 = 0
    ASSERT_OK(matrix_mul(&A, &A, &Res));
    assert(Res.data[0][0] == 0);

    matrix_free(&A); matrix_free(&I); matrix_free(&Res);
    printf("[Passed] test_multiplication\n");
}

// 4. Test Determinant and Inverse
void test_advanced_math() {
    printf("[Running] test_advanced_math...\n");
    Matrix A, Inv, Verify;
    int64_t p = 11;
    int64_t det;

    ASSERT_OK(matrix_create(&A, 2, 2, p));
    ASSERT_OK(matrix_create(&Inv, 2, 2, p));
    ASSERT_OK(matrix_create(&Verify, 2, 2, p));

    // A = [[3, 2], [1, 4]]
    // det = 3*4 - 2*1 = 10 (mod 11)
    A.data[0][0]=3; A.data[0][1]=2;
    A.data[1][0]=1; A.data[1][1]=4;

    ASSERT_OK(matrix_det(&A, &det));
    assert(det == 10);

    // Inverse
    ASSERT_OK(matrix_inv(&A, &Inv));

    // Check A * A_inv = I
    ASSERT_OK(matrix_mul(&A, &Inv, &Verify));

    // Check Identity
    assert(Verify.data[0][0] == 1);
    assert(Verify.data[0][1] == 0);
    assert(Verify.data[1][0] == 0);
    assert(Verify.data[1][1] == 1);

    matrix_free(&A); matrix_free(&Inv); matrix_free(&Verify);
    printf("[Passed] test_advanced_math\n");
}

// 5. Test Error Handling
void test_errors() {
    printf("[Running] test_errors...\n");
    Matrix A, B, C;
    int64_t p = 13;

    matrix_create(&A, 2, 3, p);
    matrix_create(&B, 4, 2, p); // Dimensions mismatch for A*B (3 != 4)
    matrix_create(&C, 2, 2, p); // Dummy

    // Multiplication dimension mismatch
    ASSERT_FAIL(matrix_mul(&A, &B, &C));

    // Inverse on non-square matrix
    ASSERT_FAIL(matrix_inv(&A, &C));

    // Singular matrix (det = 0)
    // [[1, 2], [2, 4]] -> det = 4-4 = 0
    Matrix Sing;
    matrix_create(&Sing, 2, 2, p);
    Sing.data[0][0]=1; Sing.data[0][1]=2;
    Sing.data[1][0]=2; Sing.data[1][1]=4;

    ASSERT_FAIL(matrix_inv(&Sing, &C));

    matrix_free(&A); matrix_free(&B); matrix_free(&C); matrix_free(&Sing);
    printf("[Passed] test_errors\n");
}

int main() {
    test_lifecycle();
    test_arithmetic();
    test_multiplication();
    test_advanced_math();
    test_errors();

    printf("\nAll tests passed successfully.\n");
    return 0;
}