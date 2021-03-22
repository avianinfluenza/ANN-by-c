#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;


#define E 2.718281

const int M_layer = 10;
const int M_perceptron_x = 10;
const int M_perceptron_y = 10;
const int M_input_demension_x = 10;
const int M_input_demension_y = 10;
const int M_input_n = 100;
int layer, perceptron_x, perceptron_y, input_demension_x, input_demension_y, input_n, layerxy[M_layer]; //[0]이 x축, [1]이 y축 


float weight[M_layer][M_perceptron_x][M_input_demension_x];
//vector< vector< vector< vector< vector<float> > > > > weight;
float bais[M_layer][M_perceptron_x];
//vector< vector< vector<float> > > bais;
float input[M_input_n][M_input_demension_x];
//vector< vector<float> > input;
float label[M_input_n];
float output[M_input_n][M_layer][M_perceptron_x];

void foward_pass(void){
	for(int k = 1; k <= input_n; k++){		//input layer 
		for(int i = 1; i <= layerxy[1]; i++){
			float temp = 0;
			for(int j = 1; j <= input_demension_x; j++){
				temp += weight[1][i][j]*input[k][j];
			}
			output[k][1][i] = temp;
		}
		for(int o = 2; o <= layer; o++){	//hidden layer
			for(int i = 1; i <= layerxy[o]; i++){
				float temp = 0;
				for(int j = 1; j <= input_demension; j++){
					temp += weight[o][i][j]*input[k][j];
				}
				output[k][o][i] = temp;
			}
		}
		float temp = 0;
		for(int i = 1; i <= layerxy[layer]; i++){
			temp += output[k][layer][i] * weight[layer+1][1][i];
		}
		output[layer+1][1][1] = temp;
	}
}

float sigmoid(double x){
	return 1/(1+pow(E, -1*x));
}

float deff_sigmoid(float input){
	return sigmoid(input)*(1-sigmoid(input));
}

float cost_function(void){
	float cost = 0;
	for(int i= 0; i < input_n; i++){
		cost += (1/2)*(output[i][layer][1]-label[i])*(output[i][layer][1]-label[i]);
	}
	return cost;
}

void back_propagation(void){
	
}

int main(){
	printf("layer 갯수를 입력해주세요.\n");
	scanf("%d", &layer);
	for(int i = 1; i <= layer; i++){
		printf("%d번째 layer의 x축 크기를 입력해주세요.\n", i);
		scanf("%d", &perceptron_x);
	}
	printf("input의 x축 크기를 입력해주세요.\n");
	scanf("%d", &input_demension_x);
	printf("input데이터의 갯수를 입력해주세요.\n");
	scanf("%d", &input_n);
	/*
	for(int i = 1; i <= layer; i++){
		for(int j = 1; j <= input_demension_x; j++){
			for(int k = 1; k <= input_demension_y; k++){
				for(int o = 1;o <= perceptron_x; o++){
					for(int p = 1; p <= perceptron_y; p++){
						weight[i][j][k][o][p] = 1.0;
					}
				}
			}
			printf("배열을 초기화 중입니다...");
			for(int k = 1; k <= j; k++){
				printf("#");
			}
			for(int k = j+1; k <= input_demension_x; k++){
				printf("_");
			}
			printf("\n");
		}
	}
	*/
	for(int i = 1; i <= layer; i++){
		for(int j = 1; j <= input_demension_x; j++){
			for(int k = 1; k <= perceptron_x; k++){
				weight[i][j][k] = 1.0;
			}
		}
		printf("배열을 초기화 중입니다...\n");
	}
	printf("input 데이터를 입력해주세요\n");
	for(int k = 1; k <= input_n; k++){
		for(int i = 1; i <= input_demension_x; i++){
			scanf("%d", &input[k][input_demension_x]);
		}
	}
	printf("label을 입력해주세요.\n");
	for(int k = 1; k <= input_n; k++){
		scanf("%d", &label[k]);
	}
}
