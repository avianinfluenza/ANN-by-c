#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define E 2.718281
#define _CRT_SECURE_NO_WARNINGS
double input[200][4] = {{0.01, 0.99}, {0.99, 0.01}, {0.01, 0.01}, {0.99, 0.99}};
double weight[8]={0.15, 0.2, 0.25, 0.3, 0.35, 0.4,0.45, 0.5};
double sub[200][8];
double delta[200][4];
double hnet[200][2];
double hout[200][2];
double onet[200][4];
double oout[200][4];
double learning_rate = 0.5;
double label[200][2] = {{0.01, 0.99}, {0.01, 0.99}, {0.01, 0.01}, {0.01, 0.01}};
int input_n = 150;

double sigmoid(double input){
	return 1/(1+pow(E, -1*input));
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
			//printf("%c", str_tmp[1]);  
			char *ptr = strtok(str_tmp, ",");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
			int cnt = 0;
			double num = atof(ptr);
			ptr = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
			while (ptr != NULL)          // 자른 문자열이 나오지 않을 때까지 반복
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
					//printf("%d\n",label[index]);
				}
				else{
					double num = atof(ptr);
				    input[index][cnt] = num/10;
				    //printf("%lf\n", input[index][cnt]);
				}
			    ptr = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
			    cnt++;
			}
			double temp = input[index][1];
			input[index][1] = input[index][2];
			input[index][2] = input[index][1];
			index++; 
        }       
    }
    fclose( pFile );
	/*
	scanf("%d", &input_n);
	for(int i = 0; i < input_n; i++){
		printf("input[%d] : ", i);
		scanf("%d %d", &input[i][0], &input[i][1]);
	}
	for(int i = 0; i < input_n; i++){
		printf("layer[%d] : ", i);
		scanf("%d", &label[i]);
	}
	*/
	srand((unsigned)time(NULL));
	//output layer
	for(int j = 0; j < 8; j++){
		weight[j] = ((rand()*rand())%1000000)*0.000001;
	}
	printf("input_n : %d\n", input_n);
	for(int i = 0; i < input_n; i++){
		printf("intput[%d] : %lf %lf\n", i, input[i][0], input[i][1]);
		printf("label[%d] : %lf %lf\n", i, label[i][0], label[i][1]);	
	}
	int temp;
	printf("temp : ");
	scanf("%d", &temp);
	while(temp--){

		for(int i = 0; i < 8; i++){
			//printf("weight[%d] : %lf\n", i,weight[i]);
		}
		//printf("\n");
		for(int i = 0; i < input_n; i++){
			hnet[i][0] = input[i][0]*weight[0]+input[i][1]*weight[1];
			hnet[i][1] = input[i][0]*weight[2]+input[i][1]*weight[3];
			//printf("%lf\n", hnet[i][0]);
			//printf("%lf\n", hnet[i][1]);
		}
		//printf("\n");
		for(int i = 0; i < input_n; i++){
			hout[i][0] = sigmoid(hnet[i][0]);
			hout[i][1] = sigmoid(hnet[i][1]);
			//printf("hout[%d][0] : %lf\n", i,hout[i][0]);
			//printf("hout[%d][1] : %lf\n", i,hout[i][1]);
		}
		//printf("\n");
		for(int i = 0; i < input_n; i++){
			onet[i][0] = hout[i][0]*weight[4]+hout[i][1]*weight[5];
			onet[i][1] = hout[i][0]*weight[6]+hout[i][1]*weight[7];
			//printf("onet[%d][0] : %lf\n", i,onet[i][0]);
			//printf("onet[%d][1] : %lf\n", i,onet[i][1]);
		}
		//printf("\n");
		for(int i = 0; i < input_n; i++){
			oout[i][0] = sigmoid(onet[i][0]);
			oout[i][1] = sigmoid(onet[i][1]);
			//printf("oout[%d][0] : %lf\n", i,oout[i][0]);
			printf("oout[%d][1] : %lf\n", i,oout[i][1]);
		}
		for(int i =0; i < input_n; i++){
			delta[i][2] = (oout[i][0]-label[i][0])*(oout[i][0]*(1-oout[i][0]));
			//printf("delta[%d][2] : %lf\n", i,delta[i][2]);
		}
		for(int i = 0; i < input_n; i++){
			sub[i][4] = delta[i][2]*hout[i][0];
			sub[i][5] = delta[i][2]*hout[i][1];
			//printf("sub[%d][5] : %lf\n", i, sub[i][4]);
			//printf("sub[%d][6] : %lf\n", i, sub[i][5]);
		}
		//printf("\n");
		for(int i =0; i < input_n; i++){
			delta[i][3] = (oout[i][1]-label[i][1])*(oout[i][1]*(1-oout[i][1]));
			//printf("delta[%d][3] : %lf\n", i,delta[i][3]);
		}
		for(int i = 0; i < input_n; i++){
			sub[i][6] = delta[i][3]*hout[i][0];
			sub[i][7] = delta[i][3]*hout[i][1];
			//printf("sub[%d][6] : %lf\n", i, sub[i][6]);
			//printf("sub[%d][7] : %lf\n", i, sub[i][7]);
		}
		//printf("\n");
		for(int i = 0; i < input_n; i++){
			delta[i][0] = (delta[i][2]*weight[4]+delta[i][3]*weight[6])*hout[i][0]*(1-hout[i][0]);
			//printf("delta[%d][0] : %lf\n", i, delta[i][0]);
		}
		for(int i = 0; i < input_n; i++){
			sub[i][0] = delta[i][0]*input[i][0];
			sub[i][1] = delta[i][0]*input[i][1];
			//printf("sub[%d][0] : %lf\n", i, sub[i][0]);
			//printf("sub[%d][1] : %lf\n", i, sub[i][1]);
		}
		//printf("\n");
		for(int i = 0; i < input_n; i++){
			delta[i][1] = (delta[i][2]*weight[5]+delta[i][3]*weight[7])*hout[i][1]*(1-hout[i][1]);
			//printf("delta[%d][1] : %lf\n", i, delta[i][1]);
		}
		for(int i = 0; i < input_n; i++){
			sub[i][2] = delta[i][1]*input[i][0];
			sub[i][3] = delta[i][1]*input[i][1];
			//printf("sub[%d][0] : %lf\n", i, sub[i][2]);
			//printf("sub[%d][1] : %lf\n", i, sub[i][3]);
		}
		printf("\n");
		for(int i = 0; i < input_n; i++){
			for(int j = 0; j < 8; j++){
				weight[j] -= learning_rate*sub[i][j];
			}
		}
		for(int i = 0; i < 8; i++){
			printf("weight[%d] : %lf\n", i,weight[i]);
		}
	}
}
