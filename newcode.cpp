#include <stdio.h>
#include <math.h>

#define E 2.718281

static int input[100][2], label[100];
static int layer, input_n;
static double learning_rate;

double sigmoid(double x);
double deff_sigmoid(double input);

double sigmoid(double x){
	return 1/(1+pow(E, -1*x));
}

double deff_sigmoid(double input){
	return sigmoid(input)*(1-sigmoid(input));
}

struct perceptron{
	double weight[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	double output[10];//input_n의 갯수 
	double delta[10];
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
		for(int p = 1; p < layer; p++){		//inside input layer
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
		for(int i = 0; i < hi_layer[layer-1].length; i++){
			ou_layer.perceptron.weight[i] -= learning_rate*hi_layer[layer-1].perceptron[i].output[k]*ou_layer.perceptron.delta[k];
		}
		//hidden layer
		for(int p = 1; p < layer; p++){		//inside input layer
			for(int i = 1; i < hi_layer[p].length; i++){
				for(int j = 0 ;j < hi_layer[p-1].length; j++){
					
				}
			}
		}
	}
}

int main(){
	printf("layer : ");
	scanf("%d", &layer);
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
	foward_pass();
	for(int i = 0;i < hi_layer[0].length; i++){
		for(int j = 0; j < input_n; j++){
			printf("output[%d][%d] : %lf\n", i, j, hi_layer[0].perceptron[i].output[j]);
		}
	}
	
}

