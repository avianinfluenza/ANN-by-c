#include <stdio.h>
#include <math.h>
#include <stdlib.h> // rand()함수 포함 라이브러리
#include <time.h> // time()함수 포함 라이브러리
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define E 2.718281

static int  label[200];
static int layer, input_n;
static double learning_rate, input[200][4];

double sigmoid(double x);
double deff_sigmoid(double input);

double sigmoid(double x){
	return 1/(1+pow(E, -1*x));
}

double deff_sigmoid(double input){
	return sigmoid(input)*(1-sigmoid(input));
}

struct perceptron{
	double weight[10];
	double output[10];//input_n의 갯수 
	double delta[10];
	double tesub[10][10];
};

struct hidden_layer{
	struct perceptron perceptron[10];
	int length = 2;
};

struct output_layer{
	struct perceptron perceptron;
	int length = 1;
};
 
static struct hidden_layer hi_layer[1];
static struct output_layer ou_layer;

void foward_pass(void){
	for(int k = 0; k < input_n; k++){
		for(int i = 0; i < hi_layer[0].length; i++){	//input layer to hidden layer
			double temp = 0;
			for(int j = 0 ; j < 2; j++){
				temp += input[k][j]*hi_layer[0].perceptron[i].weight[j];
			}
			hi_layer[0].perceptron[i].output[k] = sigmoid(temp);
		}
		for(int p = 1; p < layer; p++){		//inside hidden layer
			for(int i = 1; i < hi_layer[p].length; i++){
				double temp = 0;
				for(int j = 0 ; j < hi_layer[p-1].length; j++){
					temp += hi_layer[p-1].perceptron[j].output[k]*hi_layer[p].perceptron[i].weight[j];
				}
				hi_layer[p].perceptron[i].output[k] = sigmoid(temp);
			}
		}
		double temp = 0;
		for(int i = 0; i < hi_layer[layer-1].length; i++){
			temp += hi_layer[layer-1].perceptron[i].output[k]*ou_layer.perceptron.weight[i];
		}
		ou_layer.perceptron.output[k] = sigmoid(temp);
	}
}

void back_propagation(void){
	for(int k = 0; k < input_n; k++){
		//output layer
		ou_layer.perceptron.delta[k] = -1*(label[k]-ou_layer.perceptron.output[k])*deff_sigmoid(ou_layer.perceptron.output[k]);
		for(int j = 0; j < hi_layer[layer-1].length; j++){
			ou_layer.perceptron.tesub[j][k] = learning_rate*hi_layer[layer-1].perceptron[j].output[k]*ou_layer.perceptron.delta[k];
		}
		//hidden layer
		//highest hidden layer
		if(layer == 1){
			for(int i = 0; i < hi_layer[layer-1].length; i++){
				hi_layer[layer-1].perceptron[i].delta[k] = ou_layer.perceptron.delta[k]*ou_layer.perceptron.weight[i]*deff_sigmoid(hi_layer[layer-1].perceptron[i].output[k]);
				for(int j = 0 ; j < 2; j++){
					hi_layer[layer-1].perceptron[i].tesub[j][k] = learning_rate*input[k][j]*hi_layer[layer-1].perceptron[i].delta[k];
				}
			}
		}
	}
	for(int k = 0; k < input_n; k++){
		//output layer
		for(int j = 0; j < hi_layer[layer-1].length; j++){
			ou_layer.perceptron.weight[j] -= ou_layer.perceptron.tesub[j][k];
		}
		//hidden layer
		//highest hidden layer
		if(layer == 1){
			for(int i = 0; i < hi_layer[layer-1].length; i++){
				for(int j = 0 ; j < 2; j++){
					hi_layer[layer-1].perceptron[i].weight[j] -= hi_layer[layer-1].perceptron[i].tesub[j][k];
				}
			}
		}
	}
}

int main(){
	char str_tmp[1024];
    FILE *pFile = NULL;
	int index = 0;
    pFile = fopen("C:/Users/Administrator/Desktop/ANN-by-c-main/ANN-by-c-main/iris(150).csv", "r" );
    if( pFile != NULL )
    {   
    printf("yes\n");
    fgets( str_tmp, 1024, pFile );
        while( !feof( pFile ) ){
            fgets( str_tmp, 1024, pFile );          
            printf( "%s", str_tmp );
			//printf("%c", str_tmp[1]);  
			char *ptr = strtok(str_tmp, ",");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
			int cnt = 0;
			double num = atof(ptr);
			ptr = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
			while (ptr != NULL)          // 자른 문자열이 나오지 않을 때까지 반복
			{
			    if(cnt == 4){
			    	if(strcmp(ptr, "setosa\n") == 0){
			    		label[index] = 0;
					}
					else if(strcmp(ptr, "versicolor\n") == 0){
						label[index] = 1;
					}
					else{
						label[index] = 2;
					}
					printf("%d\n",label[index]);
				}
				else{
					double num = atof(ptr);
				    input[index][cnt] = num;
				    printf("%lf\n", input[index][cnt]);
				}
			    ptr = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
			    cnt++;
			}
			index++; 
        }       
    }
    fclose( pFile );
	/*
	printf("layer : ");
	scanf("%d", &layer);	
	srand((unsigned)time(NULL));
	//output layer
	for(int j = 0; j < hi_layer[layer-1].length; j++){
		ou_layer.perceptron.weight[j] = ((rand()*rand())%1000000)*0.000001;
	}
	//hidden layer
	//highest hidden layer
	if(layer == 1){
		for(int i = 0; i < hi_layer[layer-1].length; i++){
			for(int j = 0 ; j < 2; j++){
				hi_layer[layer-1].perceptron[i].weight[j] = ((rand()*rand())%1000000)*0.000001;
			}
		}
	}
	
	printf("input : ");
	scanf("%d", &input_n);
	printf("learning rate : ");
	scanf("%lf", &learning_rate);
	for(int i = 0; i < input_n; i++){
		printf("intput[%d] : ", i);
		scanf("%d %d", &input[i][0], &input[i][1]);
	}
	for(int i = 0; i < input_n; i++){
		printf("layer[%d] : ", i);
		scanf("%d", &label[i]);
	}
	for(int i = 0; i < input_n; i++){
		printf("intput[%d] : %d %d\n", i, input[i][0], input[i][1]);
		printf("label[%d] : %d\n", i, label[i]);	
	}
	int temp;
	printf("학습횟수 :  ");
	scanf("%d", &temp);
	while(temp--){
		foward_pass();
		for(int i = 0;i < hi_layer[0].length; i++){
			for(int j = 0; j < 2; j++){
				//printf("output[%d][%d] : %lf\n", i, j, hi_layer[0].perceptron[i].output[j]);
				printf("weight[%d][%d] : %lf\n", i, j, hi_layer[0].perceptron[i].weight[j]);
			}
		}
		for(int j = 0; j < 2; j++){
			printf("weight[3][%d] : %lf\n",  j, ou_layer.perceptron.weight[j]);
		}
		for(int j = 0; j < input_n; j++){
			printf("final[%d] : %lf\n", j, ou_layer.perceptron.output[j]);
		}
		printf("\n");
		back_propagation();
	}
	*/
}

