#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;


#define E 2.718281

int M_layer = 10;
int M_perceptron_x = 10;
int M_perceptron_y = 10;
int M_input_demension_x = 10;
int M_input_demension_y = 10;


//float weight[M_layer][M_perceptron_x][M_perceptron_y][M_input_demension_x][M_input_demension_y];
vector< vector< vector< vector< vector<float> > > > > weight;
//float bais[M_layer][M_perceptron_x][M_perceptron_y];
vector< vector< vector<float> > > bais;
//float input[M_input_demension_x][M_input_demension_y];
vector< vector<float> > input;

double sigmoid(double x){
	return 1/(1+pow(E, -1*x));
}


int main(){
	printf("layer 갯수를 입력해주세요.\n");
	scanf("%d", &M_layer);
	printf("layer의 x축 크기를 입력해주세요.\n");
	scanf("%d", &M_perceptron_x);
	printf("layer의 y축 크기를 입력해주세요.\n");
	scanf("%d", &M_perceptron_y);
	printf("input의 x축 크기를 입력해주세요.\n");
	scanf("%d", &M_input_demension_x);
	printf("input의 y축 크기를 입력해주세요.\n");
	scanf("%d", &M_input_demension_y);
	for(int i = 0; i < M_layer; i++){
		for(int j = 0; j < M_perceptron_x; j++){
			for(int k = 0; k < M_perceptron_y; k++){
				for(int o = 0;o < M_input_demension_x; o++){
					for(int p = 0; p < M_input_demension_y; p++){
						weight[i][j][k][o][p] = 1.0;
					}
				}
			}
			printf("배열을 초기화 중입니다...");
			for(int k = 0; k <= j; k++){
				printf("#");
			}
			for(int k = j+1; k < M_perceptron_x; k++){
				printf("_");
			}
			printf("\n");
		}
	}
}
