#include <stdio.h>
#include <math.h>

#define E 2.718281

const int M_layer = 10;
const int M_perceptron_x = 10;
const int M_perceptron_y = 10;
const int M_input_demension_x = 10;
const int M_input_demension_y = 10;


float weight[M_layer][M_perceptron_x][M_perceptron_y][M_input_demension_x][M_input_demension_y];
float bais[M_layer][M_perceptron_x][M_perceptron_y];
float input[M_input_demension_x][M_input_demension_y];

double sigmoid(double x){
	return 1/(1+pow(E, -1*x));
}


int main(){
	printf("%lf", sigmoid(3));
}
