package net.ivosklenar.Matrix;
import java.util.Random;

public class Main {
    private static void MM_ikj(double[][] A, double[][] B, double[][] C, int n) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                double tmp = A[i][k];
                for (int j = 0; j < n; j++) {
                    C[i][j] += tmp * B[k][j];
                }
            }
        }
    }

    private static void MM_ijk(double[][] A, double[][] B, double[][] C, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }

        }
    }

    private static void MM_ijk_unroll(double[][] A, double[][] B, double[][] C, int n) {
        int uf = 4;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n / uf; k += uf) {
                    C[i][j] += A[i][k] * B[k][j];
                    C[i][j] += A[i][k + 1] * B[k + 1][j];
                    C[i][j] += A[i][k + 2] * B[k + 2][j];
                    C[i][j] += A[i][k + 3] * B[k + 3][j];
                }

                for (int k = n - ( n % uf); k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }

        }
    }

    private static void MM_ikj_unroll(double[][] A, double[][] B, double[][] C, int n) {
        int uf = 4;

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                double tmp = A[i][k];
                for (int j = 0; j < n / uf; j += uf) {
                    C[i][j] += tmp * B[k][j];
                    C[i][j + 1] += tmp * B[k][j + 1];
                    C[i][j + 2] += tmp * B[k][j + 2];
                    C[i][j + 3] += tmp * B[k][j + 3];
                }
                
                for (int j = n - ( n % uf); j < n; j++) {
                    C[i][j] += tmp * B[k][j];
                }
            }
        }
    }

    private static void RandomMatrix(double[][] matrix, Random random, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = random.nextDouble() * 150;
            }
        }
    }

    private static void MM_ijkTest() {
        for (int n = 500; n <= 3000; n += 500) {
            Random random = new Random();
            double[][] A = new double[n][n];
            double[][] B = new double[n][n];
            double[][] C = new double[n][n];
            RandomMatrix(A, random, n);
            RandomMatrix(B, random, n);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    C[i][j] = 0.0;
                }
            }

            long start = System.nanoTime();
            MM_ijk(A, B, C, n);
            long end = System.nanoTime();

            System.out.println("Size: " + n + ", ijk time: " + (end - start) / 1000000 + " ms");
        }
    }
    private static void MM_ikjTest() {
        for (int n = 500; n <= 3000; n += 500) {
            Random random = new Random();
            double[][] A = new double[n][n];
            double[][] B = new double[n][n];
            double[][] C = new double[n][n];
            RandomMatrix(A, random, n);
            RandomMatrix(B, random, n);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    C[i][j] = 0.0;
                }
            }

            long start = System.nanoTime();
            MM_ikj(A, B, C, n);
            long end = System.nanoTime();

            System.out.println("Size: " + n + ", ikj time: " + (end - start) / 1000000 + " ms");
        }
    }
    private static void MM_ijk_unrollTest() {
        for (int n = 500; n <= 3000; n += 500) {
            Random random = new Random();
            double[][] A = new double[n][n];
            double[][] B = new double[n][n];
            double[][] C = new double[n][n];
            RandomMatrix(A, random, n);
            RandomMatrix(B, random, n);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    C[i][j] = 0.0;
                }
            }

            long start = System.nanoTime();
            MM_ijk_unroll(A, B, C, n);
            long end = System.nanoTime();

            System.out.println("Size: " + n + ", ijk unroll time: " + (end - start) / 1000000 + " ms");
        }
    }
    private static void MM_ikj_unrollTest() {
        for (int n = 500; n <= 3000; n += 500) {
            Random random = new Random();
            double[][] A = new double[n][n];
            double[][] B = new double[n][n];
            double[][] C = new double[n][n];
            RandomMatrix(A, random, n);
            RandomMatrix(B, random, n);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    C[i][j] = 0.0;
                }
            }

            long start = System.nanoTime();
            MM_ikj_unroll(A, B, C, n);
            long end = System.nanoTime();

            System.out.println("Size: " + n + ", ikj unroll time: " + (end - start) / 1000000 + " ms");
        }
    }

    public static void main(String[] args) {
        MM_ijkTest();
        MM_ikjTest();
        MM_ijk_unrollTest();
        MM_ikj_unrollTest();
    }
}
