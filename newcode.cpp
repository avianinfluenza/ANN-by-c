#include <stdio.h>



static int input[100][2], label[100];
static int layer, input_n;

struct perceptron{
	double weight[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	double output;
};

struct hidden_layer{
	struct perceptron perceptron[10];
	int length = 2;
};

struct input_layer{
	int input[10];
};

struct output_layer{
	struct perceptron perceptron;
	int length = 1;
};
 
static struct hidden_layer hi_layer[1];
static struct output_layer ou_layer;

int main(){
	printf("layer : ");
	scanf("%d", &layer);
	printf("input : ");
	scanf("%d", &input_n);
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
		printf("layer[%d] : %d\n", i, label[i]);
		
	}
}

