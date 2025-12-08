#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdint.h>

//////////////////////////////////////////////////////////
// Matrix data structure
//////////////////////////////////////////////////////////
typedef struct {
    size_t rows;     // Number of rows
    size_t cols;     // Number of columns
    int64_t p;       // Modulus for operations (prime)
    int64_t **data;  // Pointer to 2D array storing matrix elements
} Matrix;

//////////////////////////////////////////////////////////
// Matrix function declarations
//////////////////////////////////////////////////////////

// Initialize a matrix structure with allocated data array
// Caller provides an allocated Matrix struct
// Returns 0 on success, non-zero on failure
int matrix_create(Matrix *mat, size_t rows, size_t cols, int64_t p);

// Deep copy a matrix: dest = src
// Caller must allocate a Matrix struct for dest; 
// function will allocate memory for dest->data
// Returns 0 on success, non-zero on failure
int matrix_deep_copy(const Matrix *src, Matrix *dest);

// Free the memory allocated for a matrix's data array
void matrix_free(Matrix *mat);

// Print a matrix (for debugging)
void matrix_print(const Matrix *mat);

// Matrix addition: C = A + B (mod p)
// Caller must allocate Matrix C with same dimensions as A and B
// Returns 0 on success, non-zero on failure
int matrix_add(const Matrix *A, const Matrix *B, Matrix *C);

// Matrix multiplication: C = A * B (mod p)
// Caller must allocate Matrix C with correct dimensions (A->rows x B->cols)
// Returns 0 on success, non-zero on failure
int matrix_mul(const Matrix *A, const Matrix *B, Matrix *C);

// Scalar multiplication: B = k * A (mod p)
// Caller must allocate Matrix B with same dimensions as A
// Returns 0 on success, non-zero on failure
int matrix_scalar_mul(const Matrix *A, int64_t k, Matrix *B);

// Compute the determinant of a matrix (mod p)
// The determinant is stored in the output parameter det
// Returns 0 on success, non-zero on failure
int matrix_det(const Matrix *mat, int64_t *det);

// Compute the inverse of a matrix (mod p)
// Caller must allocate Matrix A_inv with same dimensions as A
// Returns 0 on success, non-zero if the matrix is not invertible
int matrix_inv(const Matrix *A, Matrix *A_inv);

// Generate an identity matrix of size n x n (mod p)
// Caller must allocate Matrix I with size n x n
// Returns 0 on success, non-zero on failure
int matrix_identity(size_t n, int64_t p, Matrix *I);

#endif // MATRIX_H
