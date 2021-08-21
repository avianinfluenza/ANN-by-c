#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define E 2.718281
#define _CRT_SECURE_NO_WARNINGS


int e, t;
double target[1000];
double learning_late = 0.01;


struct perceptron{
	double net[1000];
	double out[1000];
	double weight[100];
	double memo[1000];
	double sub[100][1000];
};


struct input{
	int n;
	struct perceptron perceptron[100];
}; 

struct hidden{
	int m;
	struct perceptron perceptron[100];
};

struct out{
	struct perceptron perceptron;
};

struct error{
	double total;
	double out[1000];
};

double sigmoid(double input){	//활성화함수 시그모이드
	return 1/(1+pow(E, -1*input));
}

static struct input input;
static struct hidden hidden;
static struct out out;
static struct error error;

void forward_pass(void){
	error.total = 0;
	for(int k = 1; k <= e; k++){
		error.out[k] = 0;
		for(int i = 1; i <= hidden.m; i++){
			hidden.perceptron[i].net[k] = 0;
			for(int j = 1; j <= input.n; j++){
				hidden.perceptron[i].net[k] += input.perceptron[j].out[k] * input.perceptron[j].weight[i];
			}
			hidden.perceptron[i].out[k] = sigmoid(hidden.perceptron[i].net[k]);
		}
		out.perceptron.net[k] = 0;
		for(int i = 1; i <= hidden.m; i++){
			out.perceptron.net[k] += hidden.perceptron[i].out[k] * hidden.perceptron[i].weight[1];
		}
		out.perceptron.out[k] = sigmoid(out.perceptron.net[k]);
		error.out[k] = (target[k] - out.perceptron.out[k]) * (target[k] - out.perceptron.out[k]) / 2;
		error.total += error.out[k];
	}
}

void backpropagation(void){
	for(int k = 1; k <= e; k++){
		for(int i = 1; i <= hidden.m; i++){
			hidden.perceptron[i].memo[k] = -1*(target[k] - out.perceptron.out[k])* out.perceptron.out[k] *(1 - out.perceptron.out[k]);
			hidden.perceptron[i].sub[1][k] = hidden.perceptron[i].memo[k] * hidden.perceptron[i].out[k];
		}
		for(int i = 1; i <= hidden.m; i++){
			for(int j =1; j <= input.n; j++){
				input.perceptron[j].sub[i][k] = hidden.perceptron[i].memo[k] * hidden.perceptron[i].weight[1] * hidden.perceptron[i].out[k] * (1 - hidden.perceptron[i].out[k]) * input.perceptron[j].out[k];
			}
		}
	}
	for(int k = 1; k <= e; k++){
		for(int i = 1; i <= hidden.m; i++){
			hidden.perceptron[i].weight[1] -= learning_late * hidden.perceptron[i].sub[1][k];
		}
		for(int i = 1; i <= hidden.m; i++){
			for(int j =1; j <= input.n; j++){
				input.perceptron[j].weight[i] -= learning_late * input.perceptron[j].sub[i][k];
			}
		}
	}
}

int main(){
	printf("n : ");
	scanf("%d", &input.n);
	printf("m : ");
	scanf("%d", &hidden.m);
	printf("e : ");
	scanf("%d", &e);
	printf("t : ");
	scanf("%d", &t);

	/*
	for(int i = 1; i <= e; i++){
		for(int j = 1; j<= input.n; j++){
			printf("input.perceptron[%d].out[%d] : ",j, i);
			scanf("%lf", &input.perceptron[j].out[i]);
		}
		printf("target[%d] : ", i);
		scanf("%lf", &target[i]);
	}
	*/
	
	srand((unsigned)time(NULL));
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			input.perceptron[i].weight[j] = ((rand()*rand())%1000000)*0.000001;	
		}
	}
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			hidden.perceptron[i].weight[j] = ((rand()*rand())%1000000)*0.000001;	
		}
	}
	for(int i = 0; i< 100; i++){
		out.perceptron.weight[i] = ((rand()*rand())%1000000)*0.000001;
	}
	
	
   	char str_tmp[1024];
    FILE *pFile = NULL;
    int index = 1;
    pFile = fopen("C:/Users/sungh/Documents/ANN-by-c-main/ANN-by-c-main/iris(150).csv", "r" );
    if( pFile != NULL )
    {   
    printf("csv file detected!\n");
    fgets( str_tmp, 1024, pFile );
        while( !feof( pFile ) ){
            fgets( str_tmp, 1024, pFile );            
			char *ptr = strtok(str_tmp, ",");      
			int cnt = 0;
			double num = atof(ptr);
			ptr = strtok(NULL, ",");      
			while (ptr != NULL)          
			{
			    if(cnt == 4){
			    	if(strcmp(ptr, "setosa\n") == 0){
			    		target[index] = 0.01;
					}
					else if(strcmp(ptr, "versicolor\n") == 0){
						target[index] = 0.50;
					}
					else{
						target[index] = 0.99;
					}
				}
				else{
					double num = atof(ptr);
					input.perceptron[cnt].out[index]  = num/10;
				}
			    ptr = strtok(NULL, ",");      
			    cnt++;
			}
			double temp = input.perceptron[1].out[index];
			input.perceptron[1].out[index] = input.perceptron[2].out[index];
			input.perceptron[2].out[index] = temp;
			index++; 
        }       
    }
    fclose( pFile );
    
    
	printf("learning_late : ");
	scanf("%lf", &learning_late);	
	for(int i = 1; i<= t; i++){
		forward_pass();
		printf("%d번째 학습 : %lf\n", i, error.total);
		backpropagation();
	}
	
	for(int i = 1; i <= e; i++){
		printf("out[%d] : %lf\n",i, out.perceptron.out[i]);
	}
}
