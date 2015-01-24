#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <chrono>

void MM_ijk(double ** A, double ** B, double ** C, int n){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			for (int k = 0; k < n; k++){
				C[i][j] += A[i][k] * B[k][j];
			}
		}	
	
	}
}

void MM_ikj(double ** A, double ** B, double ** C, int n){
	for (int i = 0; i < n; i++){
		for (int k = 0; k < n; k++){
			double tmp = A[i][k];
			for (int j = 0; j < n; j++){
				C[i][j] += tmp * B[k][j];
			}
		}
	}
}

void MM_ijk_unroll(double ** A, double ** B, double ** C, int n){
	int uf = 4;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			for (int k = 0; k < n / uf; k += uf){
				C[i][j] += A[i][k] * B[k][j];
				C[i][j] += A[i][k + 1] * B[k + 1][j];
				C[i][j] += A[i][k + 2] * B[k + 2][j];
				C[i][j] += A[i][k + 3] * B[k + 3][j];
			}

			for (int k = n - uf; k < n; k++){
				C[i][j] += A[i][k] * B[k][j];
			}
		}	
	
	}
}

void MM_ikj_unroll(double ** A, double ** B, double ** C, int n){
	int uf = 4;

	for (int i = 0; i < n; i++){
		for (int k = 0; k < n; k++){
			double tmp = A[i][k];
			for (int j = 0; j < n / uf; j += uf){
				C[i][j]     += tmp * B[k][j];
				C[i][j + 1] += tmp * B[k][j + 1];
				C[i][j + 2] += tmp * B[k][j + 2];
				C[i][j + 3] += tmp * B[k][j + 3];
			}

			for (int j = n - uf; j < n; j++){
				C[i][j] += tmp * B[k][j];
			}
		}
	}
}


void RandomMatrix(double ** matrix, std::default_random_engine & generator, int n){
	std::uniform_real_distribution<double> distribution(0.0, 150.0);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			matrix[i][j] = distribution(generator);
		}
	}
}

void MM_ijkTest() {
    for (int n = 500; n <= 3000; n += 500) {
        std::default_random_engine generator;
        double ** A = new double * [n];
		double ** B = new double * [n];
		double ** C = new double * [n];

		for (int i = 0; i < n; i++){
			A[i] = new double [n];
			B[i] = new double [n];
			C[i] = new double [n];
		}
        RandomMatrix(A, generator, n);
        RandomMatrix(B, generator, n);

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                C[i][j] = 0.0;
            }
        }
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        MM_ijk(A, B, C, n);
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

        std::cout << "Size: "<< n << ", ijk time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        for (int i = 0; i < n; i++){
			delete [] A[i];
			delete [] B[i];
			delete [] C[i];
		}
		delete [] A;
		delete [] B;
		delete [] C;
    }
}

void MM_ikjTest() {
    for (int n = 500; n <= 3000; n += 500) {
        std::default_random_engine generator;
        double ** A = new double * [n];
		double ** B = new double * [n];
		double ** C = new double * [n];

		for (int i = 0; i < n; i++){
			A[i] = new double [n];
			B[i] = new double [n];
			C[i] = new double [n];
		}
        RandomMatrix(A, generator, n);
        RandomMatrix(B, generator, n);

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                C[i][j] = 0.0;
            }
        }
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        MM_ikj(A, B, C, n);
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

        std::cout << "Size: "<< n << ", ikj time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        for (int i = 0; i < n; i++){
			delete [] A[i];
			delete [] B[i];
			delete [] C[i];
		}
		delete [] A;
		delete [] B;
		delete [] C;
    }
}

void MM_ijk_unrollTest() {
    for (int n = 500; n <= 3000; n += 500) {
        std::default_random_engine generator;
        double ** A = new double * [n];
		double ** B = new double * [n];
		double ** C = new double * [n];

		for (int i = 0; i < n; i++){
			A[i] = new double [n];
			B[i] = new double [n];
			C[i] = new double [n];
		}
        RandomMatrix(A, generator, n);
        RandomMatrix(B, generator, n);

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                C[i][j] = 0.0;
            }
        }
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        MM_ijk_unroll(A, B, C, n);
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

        std::cout << "Size: "<< n << ", ijk unroll time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        for (int i = 0; i < n; i++){
			delete [] A[i];
			delete [] B[i];
			delete [] C[i];
		}
		delete [] A;
		delete [] B;
		delete [] C;
    }
}

void MM_ikj_unrollTest() {
    for (int n = 500; n <= 3000; n += 500) {
        std::default_random_engine generator;
        double ** A = new double * [n];
		double ** B = new double * [n];
		double ** C = new double * [n];

		for (int i = 0; i < n; i++){
			A[i] = new double [n];
			B[i] = new double [n];
			C[i] = new double [n];
		}
        RandomMatrix(A, generator, n);
        RandomMatrix(B, generator, n);

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                C[i][j] = 0.0;
            }
        }
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        MM_ikj_unroll(A, B, C, n);
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

        std::cout << "Size: "<< n << ", ikj unroll time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        for (int i = 0; i < n; i++){
			delete [] A[i];
			delete [] B[i];
			delete [] C[i];
		}
		delete [] A;
		delete [] B;
		delete [] C;
    }
}


int main(){
	MM_ijkTest();
	MM_ikjTest();
	MM_ijk_unrollTest();
	MM_ikj_unrollTest();
}