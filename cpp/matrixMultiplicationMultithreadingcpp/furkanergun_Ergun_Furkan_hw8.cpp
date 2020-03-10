#include <iostream>
#include <string>
#include <thread>
using namespace std;

//MATRIX_SIZE should be divisible by NUM_THREADS
#define MATRIX_SIZE 500
#define NUM_THREADS 4

//Display the matrix on the screen (not a good idea for a huge matrix)
void display(int* matrix[MATRIX_SIZE]) {
  for(int i = 0; i < MATRIX_SIZE; ++i) {
    for(int j = 0; j < MATRIX_SIZE; ++j) {
      cout << matrix[i][j] << " ";
      if(j == MATRIX_SIZE-1)
	cout << endl;
    }
  }
}

//Calculating sum of the elements of the matrix. Use this function to check if your result matrix C is true. 
void check_total(int* matrix[MATRIX_SIZE]){
  int total = 0;
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      total += matrix[i][j];
    }
  }
  cout<< "Added all elements of the result matrix. Total :" << total <<endl;
}

//Fill matrix with all 1s
void fill_matrix(int* matrix[MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      matrix[i][j] = 1;
    }
  }
}

//Sequential function to multiply matrices (A X B)
void multiply(int* A[MATRIX_SIZE], int* B[MATRIX_SIZE], int* C[MATRIX_SIZE]) {
  for(int i=0; i<MATRIX_SIZE; i++) {
    for(int j=0; j<MATRIX_SIZE; j++) { 
      for(int k=0; k<MATRIX_SIZE; k++) {
	C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

//Calculate function is used to find the multiplication of the matrices using multi-threaded approach 
// t_id : thread id 
void calculate(int t_id ,int* A[MATRIX_SIZE], int* B[MATRIX_SIZE], int* C[MATRIX_SIZE]) {
	int nofRows = MATRIX_SIZE / NUM_THREADS;		//125					for Matrix_size=500, Num_Threads=125
	int end = (t_id+1)*nofRows;						//125,250,375,500
	for (int i = (end-nofRows) ; i < MATRIX_SIZE; i++) {		
		for (int j = 0; j < MATRIX_SIZE; j++) {		
			for (int k = 0; k < MATRIX_SIZE; k++) {
				if (i == nofRows) {					//If the for loop reaches row count, terminate the execution.
					return;
				}
				C[i][j] += A[i][k] * B[k][j];

			}
		}
	}
}
	
	
	/*
	111		222		222
	111		222		222
	111		222
	
	
	*/

	
	
	


void hello() {};

int main() {
  int *A[MATRIX_SIZE];
  int *B[MATRIX_SIZE];
  int *C[MATRIX_SIZE];
  int *C_multithread[MATRIX_SIZE];
  
  for(int i = 0; i < MATRIX_SIZE; i++) {
    A[i] = new int[MATRIX_SIZE];
    B[i] = new int[MATRIX_SIZE];
    C[i] = new int[MATRIX_SIZE];
    C_multithread[i] = new int[MATRIX_SIZE];
  }

  fill_matrix(A);
  cout<<"Matrix A is created"<<endl;
  fill_matrix(B);
  cout<<"Matrix B is created"<<endl;
  
  // Initializing elements of result matrices to 0.
  for(int i = 0; i < MATRIX_SIZE; ++i) {
    for(int j = 0; j < MATRIX_SIZE; ++j) {
      C[i][j] = 0;
      C_multithread[i][j] = 0;
    }
  }

  cout<<"Single thread multiplication has started..."<<endl;  
  auto start = chrono::steady_clock::now();
  multiply(A, B, C);
  auto end = chrono::steady_clock::now();
  auto diff = end - start;  
  cout<<"Single thread multiplication has completed..."<<endl;
  cout << "Time single thread: " << chrono::duration <double, milli> (diff).count()  << " ms." << endl;
  check_total(C); //checking if the result is true
    
  //multithreaded multiplication of (A x B)
  cout<<"Multi thread multiplication has started..."<<endl;

  start = chrono::steady_clock::now();
  
  /*******************************************************************************************************/
  
  //TODO:
  //Create your threads here and call calculate function 
  //Do not forget to join threads
  thread threads[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
	  threads[i] = thread(calculate,i,A,B,C_multithread);	//Creating all the threads
  }
  for (int i = 0; i < NUM_THREADS; i++) {	
	  threads[i].join();									//Joining all the threads
  }
  
  
   /*******************************************************************************************************/
  
  end = chrono::steady_clock::now();
  diff = end - start;
  cout<<"Multi thread multiplication has completed..."<<endl;
  cout << "Time multi thread: " << chrono::duration <double, milli> (diff).count()  << " ms." << endl;

  
  
  //Use following functions to check your multi-threaded result
  check_total(C_multithread);

  return 0;
}
