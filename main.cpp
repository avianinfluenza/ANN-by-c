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


float weight[M_layer][M_perceptron_x][M_perceptron_y][M_input_demension_x][M_input_demension_y];
//vector< vector< vector< vector< vector<float> > > > > weight;
float bais[M_layer][M_perceptron_x][M_perceptron_y];
//vector< vector< vector<float> > > bais;
float input[M_input_n][M_input_demension_x][M_input_demension_y];
//vector< vector<float> > input;
float label[M_input_n];
float output[M_layer][M_perceptron_x][M_perceptron_y];


float sigmoid(double x){
	return 1/(1+pow(E, -1*x));
}

float deff_sigmoid(float input){
	return sigmoid(input)*(1-sigmoid(input));
}

float cost_function(void){
	float cost = 0;
	for(int i= 0; i < input_n; i++){
		cost += (1/2)*(output[i]-label[i])*(output[i]-label[i]);
	}
}

void back_propagation(int epoch){
	while(epoch--){
		printf("epoch : %d,,,\n", epoch);
		
	}
}

int main(){
	int layer, perceptron_x, perceptron_y, input_demension_x, input_demension_y, input_n;
	printf("layer 갯수를 입력해주세요.\n");
	scanf("%d", &layer);
	printf("layer의 x축 크기를 입력해주세요.\n");
	scanf("%d", &perceptron_x);
	printf("layer의 y축 크기를 입력해주세요.\n");
	scanf("%d", &perceptron_y);
	printf("input의 x축 크기를 입력해주세요.\n");
	scanf("%d", &input_demension_x);
	printf("input의 y축 크기를 입력해주세요.\n");
	scanf("%d", &input_demension_y);
	printf("input데이터의 갯수를 입력해주세요.\n");
	scanf("%d", &input_n);
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
	printf("input 데이터를 입력해주세요\n");
	for(int k = 1; k <= input_n; k++){
		for(int i = 1; i <= input_demension_x; i++){
			for(int j = 1; j <= input_demension_y; j++){
				scanf("%d", &input[k][input_demension_x][input_demension_y]);
			}
		}
	}
	printf("label을 입력해주세요.\n");
	for(int k = 1; k <= input_n; k++){
		scanf("%d", &input[k]);
	}
}
