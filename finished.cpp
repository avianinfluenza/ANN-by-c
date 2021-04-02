#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define E 2.718281
#define _CRT_SECURE_NO_WARNINGS

double learning_rate = 0.1;
double label[200][2] = {{0.01, 0.99}, {0.01, 0.99}, {0.01, 0.01}, {0.01, 0.01}};
int input_n = 150, layer = 1;

struct perceptron{
	double sub[200][4];
	double delta[200];
	double net[200];
	double out[200];
	double weight[4];
};

struct hidden_layer{
	int length = 2;
	struct perceptron perceptron[2];
};

struct input_layer{
	int n = 4;
	int length = 2;
	double input[200][10];
};

struct output_layer{
	int length = 2;
	struct perceptron perceptron[2];
};


double sigmoid(double input){
	return 1/(1+pow(E, -1*input));
}

static struct hidden_layer hidden_layer[1];
static struct input_layer input_layer[1];
static struct output_layer output_layer[1];

void foward_pass(void){
	
	for(int i = 0; i < input_layer[0].n; i++){
		for(int j = 0; j < hidden_layer[0].length; j++){
			hidden_layer[0].perceptron[j].net[i] = 0;
			for(int o = 0; o < input_layer[0].length; o++){
				hidden_layer[0].perceptron[j].net[i] += input_layer[0].input[i][o]*hidden_layer[0].perceptron[j].weight[o];
			}
			hidden_layer[0].perceptron[j].out[i] = sigmoid(hidden_layer[0].perceptron[j].net[i]);
		}
	}
	for(int i = 0; i < input_layer[0].n; i++){
		for(int j = 0; j < output_layer[0].length; j++){
			output_layer[0].perceptron[j].net[i] = 0;
			for(int o = 0; o < hidden_layer[layer-1].length; o++){
				output_layer[0].perceptron[j].net[i] += hidden_layer[layer-1].perceptron[o].out[i]*output_layer[0].perceptron[j].weight[o];
			}
			output_layer[0].perceptron[j].out[i] = sigmoid(output_layer[0].perceptron[j].net[i]);
		}
	}
}

void back_prapagation(void){
	for(int i = 0; i < input_layer[0].n; i++){
		for(int j = 0; j < output_layer[0].length; j++){
			output_layer[0].perceptron[j].delta[i] = (output_layer[0].perceptron[j].out[i]-label[i][j])*(1-output_layer[0].perceptron[j].out[i]);
			for(int k = 0; k < hidden_layer[layer-1].length; k++){
				output_layer[0].perceptron[j].sub[i][k] = output_layer[0].perceptron[j].delta[i]*hidden_layer[layer-1].perceptron[k].out[i];
			}
		}
	}
	for(int i = 0; i < input_layer[0].n; i++){
			for(int j = 0; j < hidden_layer[layer-1].length; j++){
				hidden_layer[layer-1].perceptron[j].delta[i] = 0;
				for(int k = 0; k < output_layer[0].length; k++){
					hidden_layer[layer-1].perceptron[j].delta[i] += output_layer[0].perceptron[k].delta[i]*output_layer[0].perceptron[k].weight[j];
				}
				hidden_layer[layer-1].perceptron[j].delta[i] *= hidden_layer[layer-1].perceptron[j].out[i]*(1-hidden_layer[layer-1].perceptron[j].out[i]);
				for(int k = 0; k < input_layer[0].length; k++){
					hidden_layer[layer-1].perceptron[j].sub[i][k] = hidden_layer[layer-1].perceptron[j].delta[i]*input_layer[layer-1].input[i][k];
				}
			}
		}
		
	for(int i = 0; i < input_layer[0].n; i++){
		for(int j = 0; j < hidden_layer[layer-1].length; j++){
			for(int k = 0; k < input_layer[0].length; k++){
				hidden_layer[layer-1].perceptron[j].weight[k] -= learning_rate*hidden_layer[layer-1].perceptron[j].sub[i][k];
			}
		}
	}
	for(int i = 0; i < input_layer[0].n; i++){
		for(int j = 0; j < output_layer[0].length; j++){
			for(int k = 0; k < hidden_layer[layer-1].length; k++){
				output_layer[0].perceptron[j].weight[k] -= learning_rate*output_layer[0].perceptron[j].sub[i][k];
			}
		}
	}
}

double cost_function(void){
	double temp = 0;
	for(int i = 0; i < input_layer[0].n; i++){
		temp += (output_layer[0].perceptron[0].out[i]-label[i][0])*(output_layer[0].perceptron[0].out[i]-label[i][0]);
		temp += (output_layer[0].perceptron[1].out[i]-label[i][1])*(output_layer[0].perceptron[1].out[i]-label[i][1]);
	}
	return temp;
}

int main(){
	char str_tmp[1024];
    FILE *pFile = NULL;
	int index = 0;
    pFile = fopen("C:/Users/sungh/Desktop/ANN-by-c-main/iris(150).csv", "r" );
    if( pFile != NULL )
    {   
    printf("csv file detected!\n");
    fgets( str_tmp, 1024, pFile );
        while( !feof( pFile ) ){
            fgets( str_tmp, 1024, pFile );            
			char *ptr = strtok(str_tmp, ",");      // " " 怨듬갚 臾몄옄瑜?湲곗??쇰줈 臾몄옄?댁쓣 ?먮쫫, ?ъ씤??諛섑솚
			int cnt = 0;
			double num = atof(ptr);
			ptr = strtok(NULL, ",");      // ?ㅼ쓬 臾몄옄?댁쓣 ?섎씪???ъ씤?곕? 諛섑솚
			while (ptr != NULL)          // ?먮Ⅸ 臾몄옄?댁씠 ?섏삤吏 ?딆쓣 ?뚭퉴吏 諛섎났
			{
			    if(cnt == 4){
			    	label[index][0] =0.01;
			    	if(strcmp(ptr, "setosa\n") == 0){
			    		label[index][1] = 0.01;
					}
					else if(strcmp(ptr, "versicolor\n") == 0){
						label[index][1] = 0.55;
					}
					else{
						label[index][1] = 0.99;
					}
				}
				else{
					double num = atof(ptr);
				    input_layer[0].input[index][cnt] = num/10;
				}
			    ptr = strtok(NULL, ",");      // ?ㅼ쓬 臾몄옄?댁쓣 ?섎씪???ъ씤?곕? 諛섑솚
			    cnt++;
			}
			double temp = input_layer[0].input[index][1];
			input_layer[0].input[index][1] = input_layer[0].input[index][2];
			input_layer[0].input[index][2] = input_layer[0].input[index][1];
			index++; 
        }       
    }
    fclose( pFile );
	
	
	//random weight
	
	srand((unsigned)time(NULL));
	//first hidden layer
	for(int i = 0; i < hidden_layer[0].length; i++){
		for(int j = 0 ; j < input_layer[0].length; j++){
			hidden_layer[0].perceptron[i].weight[j] = ((rand()*rand())%1000000)*0.000001;	
		}
	}
	//leftover hidden layer
	for(int k = 1; k < layer; k++){
		for(int i = 0; i < hidden_layer[k].length; i++){
			for(int j = 0 ; j < hidden_layer[k-1].length; j++){
				hidden_layer[k].perceptron[i].weight[j] = ((rand()*rand())%1000000)*0.000001;	
			}
		}
	}
	//output layer
	for(int i = 0; i < output_layer[0].length; i++){
		for(int j = 0 ; j < hidden_layer[layer-1].length; j++){
			output_layer[0].perceptron[i].weight[j] = ((rand()*rand())%1000000)*0.000001;
		}
	}
	
	
	double save = 1000000;
	printf("input_n : ");
	scanf("%d", &input_n);
	input_layer[0].n = input_n;
	for(int i = 0; i < input_n; i++){
		printf("%lf %lf\n", input_layer[0].input[i][0], input_layer[0].input[i][1]);
		printf("label[%d] : %lf %lf\n", i, label[i][0], label[i][1]);	
	}
	int temp;
	printf("temp : ");
	scanf("%d", &temp);
	while(temp--){
		foward_pass();
		if((temp+1)%10000 == 0){
			printf("**%d**\n", temp);
			for(int i = 0; i < input_layer[0].n; i++){
				printf("out[%d][1] : %lf\n", i, output_layer[0].perceptron[1].out[i]);
			}
			printf("cost : %lf\n", cost_function());
		}
		save = cost_function();
		back_prapagation();
	}
}
