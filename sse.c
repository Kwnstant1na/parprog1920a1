// your C program using sse instructions
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h>

void get_walltime(double *wct){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	*wct = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}

int main(){
 
	float *a, *b;
    __m128 *vb;

    float k0 = 0.5, k1 = 0.5, k2 = 0.5, k3 = 0.5, k4 = 5.0, k5 = 0.5, k6 = 0.5, k7 = 0.5, k8 = 0.5;		//statheres k

	float *mul00, *mul11, *mul22, *mul33, *mul44, *mul55, *mul66, *mul77, *mul88;
	__m128 mul0, mul1, mul2, mul3, mul4, mul5, mul6, mul7, mul8, sum1, sum2, sum3, sum4, sum5, sum6, sum7, sumfinal;

	float z[9] = {0, 0, 0, 0, 0, 0, 0 , 0, 0};
	 

	double ts, te, mflops;
	int i, j;

//allocate
    i = posix_memalign((void **)&a, 16, N* M* sizeof(float));
    if (i!=0){
        exit(1);
    }

    i = posix_memalign((void **)&b, 16, N* M* sizeof(float));
    if (i!=0){
        exit(1);
    }

//initialize
	for(i=0; i < N *M; i++){
		a[i] = ((float)rand()/(float)(RAND_MAX));  //gemizo me random arithmous ton pinaka a
        b[i] = 1;
        //printf("%f\n", array01[i]);
        //printf("%f\n", array02[i]);
	}

	get_walltime(&ts);
	printf("%f\n", ts);


	for(i = 1; i < N - 1; i++){

        //va = (__m128*)a;
        vb = (__m128*)b;

		for(j = 1; j < M - 1; j++){

			
			z[0] = a[(i-1)+(j-1)] * k0;
			mul00 = &z[0];
			mul0 = _mm_load_pd(mul00);

			z[1] = a[(i-1)+j] * k1;
			mul11 = &z[1];
			mul1 = _mm_load_pd(mul11);

			z[2] = a[(i-1)+(j+1)] * k2;
			mul22 = &z[2];
			mul2 = _mm_load_pd(mul22);

			z[3] = a[i+(j-1)] * k3;
			mul33 = &z[3];
			mul3 = _mm_load_pd(mul33);

			z[4] = a[i+j] * k4;
			mul44 = &z[4];
			mul4 = _mm_load_pd(mul44);

			z[5] = a[i+(j+1)] * k5;
			mul55 = &z[5];
			mul5 = _mm_load_pd(mul55);

			z[6] = a[(i+1)+(j-1)] * k6;
			mul66 = &z[6];
			mul6 = _mm_load_pd(mul66);

			z[7] = a[(i+1)+j] * k7;
			mul77 = &z[7];
			mul7 = _mm_load_pd(mul77);

			z[8] = a[(i+1)+(j+1)] * k8;
			mul88 = &z[8];
			mul8 = _mm_load_pd(mul88);

			
			sum1 = _mm_add_pd(mul0, mul1);
			sum2 = _mm_add_pd(mul2, mul3);
			sum3 = _mm_add_pd(mul4, mul5);
			sum4 = _mm_add_pd(mul6, mul7);
			
			
			sum5 = _mm_add_pd(sum1, sum2);
			sum6 = _mm_add_pd(sum3, sum4);

			
			sum7 = _mm_add_pd(sum5, sum6);

			
			sumfinal = _mm_add_pd(sum7, mul8);

			*vb = sumfinal;
		}
	}

	get_walltime(&te);		
	printf("%f\n", te);
	printf("%f\n", te-ts);

	mflops = (2.0*M*N)/((te-ts)*1e6);
  
  	printf("MFLOPS/sec = %f\n",mflops);

//free
	free(a);
    free(b);
	return 0;
}
