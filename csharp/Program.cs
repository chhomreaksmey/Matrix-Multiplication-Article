using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatrixMultiplication
{
    class Program
    {
        private static void MM_ikj(double[,] A, double[,] B, double[,] C, int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int k = 0; k < n; k++)
                {
                    double tmp = A[i,k];
                    for (int j = 0; j < n; j++)
                    {
                        C[i,j] += tmp * B[k,j];
                    }
                }
            }
        }

        private static void MM_ijk(double[,] A, double[,] B, double[,] C, int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    for (int k = 0; k < n; k++)
                    {
                        C[i,j] += A[i,k] * B[k,j];
                    }
                }

            }
        }

        private static void MM_ijk_unroll(double[,] A, double[,] B, double[,] C, int n)
        {
            int uf = 4;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    for (int k = 0; k < n / uf; k += uf)
                    {
                        C[i,j] += A[i,k] * B[k,j];
                        C[i,j] += A[i,k + 1] * B[k + 1,j];
                        C[i,j] += A[i,k + 2] * B[k + 2,j];
                        C[i,j] += A[i,k + 3] * B[k + 3,j];
                    }

                    for (int k = n - ( n % uf); k < n; k++)
                    {
                        C[i,j] += A[i,k] * B[k,j];
                    }
                }

            }
        }

        private static void MM_ikj_unroll(double[,] A, double[,] B, double[,] C, int n)
        {
            int uf = 4;

            for (int i = 0; i < n; i++)
            {
                for (int k = 0; k < n; k++)
                {
                    double tmp = A[i,k];
                    for (int j = 0; j < n / uf; j += uf)
                    {
                        C[i,j] += tmp * B[k,j];
                        C[i,j + 1] += tmp * B[k,j + 1];
                        C[i,j + 2] += tmp * B[k,j + 2];
                        C[i,j + 3] += tmp * B[k,j + 3];
                    }

                    for (int j = n - ( n % uf); j < n; j++)
                    {
                        C[i,j] += tmp * B[k,j];
                    }
                }
            }
        }
        
        private static void RandomMatrix(double [,] matrix, Random random, int n){
	        for (int i = 0; i < n; i++){
		        for (int j = 0; j < n; j++)
		        {
		            matrix[i, j] = random.NextDouble()*150;
		        }
	        }

        }

        private static void MM_ijkTest()
        {      
            for (int n = 500; n <= 3000; n += 500)
            {
                var random = new Random();
                var A = new double[n,n];
                var B = new double[n,n];
                var C = new double[n,n];
                RandomMatrix(A, random, n);
                RandomMatrix(B, random, n);

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        C[i, j] = 0.0;
                    }
                }
                var stopwatch = Stopwatch.StartNew();
                MM_ijk(A, B, C, n);
                stopwatch.Stop();
                long elapsed = stopwatch.ElapsedMilliseconds;

                System.Console.WriteLine(String.Format("Size: {0}, ijk time: {1} ms", n, elapsed));
            }

        }

        private static void MM_ikjTest()
        {
            for (int n = 500; n <= 3000; n += 500)
            {
                var random = new Random();
                var A = new double[n, n];
                var B = new double[n, n];
                var C = new double[n, n];
                RandomMatrix(A, random, n);
                RandomMatrix(B, random, n);

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        C[i, j] = 0.0;
                    }
                }
                var stopwatch = Stopwatch.StartNew();
                MM_ikj(A, B, C, n);
                stopwatch.Stop();
                long elapsed = stopwatch.ElapsedMilliseconds;

                System.Console.WriteLine(String.Format("Size: {0}, ikj time: {1} ms", n, elapsed));
            }
        }
        private static void MM_ijk_unrollTest()
        {
            for (int n = 500; n <= 3000; n += 500)
            {
                var random = new Random();
                var A = new double[n, n];
                var B = new double[n, n];
                var C = new double[n, n];
                RandomMatrix(A, random, n);
                RandomMatrix(B, random, n);

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        C[i, j] = 0.0;
                    }
                }
                var stopwatch = Stopwatch.StartNew();
                MM_ijk_unroll(A, B, C, n);
                stopwatch.Stop();
                long elapsed = stopwatch.ElapsedMilliseconds;

                System.Console.WriteLine(String.Format("Size: {0}, ijk unroll time: {1} ms", n, elapsed));
            }
        }
        private static void MM_ikj_unrollTest()
        {
            for (int n = 500; n <= 3000; n += 500)
            {
                var random = new Random();
                var A = new double[n, n];
                var B = new double[n, n];
                var C = new double[n, n];
                RandomMatrix(A, random, n);
                RandomMatrix(B, random, n);

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        C[i, j] = 0.0;
                    }
                }
                var stopwatch = Stopwatch.StartNew();
                MM_ikj_unroll(A, B, C, n);
                stopwatch.Stop();
                long elapsed = stopwatch.ElapsedMilliseconds;

                System.Console.WriteLine(String.Format("Size: {0}, ikj unroll time: {1} ms", n, elapsed));
            }
        }

        static void Main(string[] args)
        {
            MM_ijkTest();
            MM_ikjTest();
            MM_ijk_unrollTest();
            MM_ikj_unrollTest();

            Console.ReadLine()
        }
    }
}
