#include<fstream>
#include<math.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

double m2 (double t){
	return (1.21) - sin(2 * M_PI * t) / 2 + 1 - 3.5 * t;
}
double m1 (double t){
	return 0.01 - sin(2 * M_PI * t) / 2 - 3.5 * t;
}
double m (double x){
	return pow((x+0.1),2) + x;
}
double C(double t, double x){
	return (M_PI*cos(2*M_PI*t) + 3.5)/(2*x+1.2);
}
double u(double x, double t){
 return pow((x + 0.1), 2) - sin (2 * M_PI * t) / 2 + x - 3.5 * t;
}

int main (){
	ofstream approx, func;
	approx.open("approx.txt");
	func.open("func.txt");
	cout.precision(4);
   	double *x, *t, tao, h;
	cout << "Please, insert Tao and H. Don't forget about Courant condition" << endl;
	cin >> tao;
	cin >> h;
	int N = fmax (fabs(1/tao)+10, fabs(1/h)+10);//crutch
	int i = 0;
	x = (double*)calloc(sizeof(double*), N);
	t = (double*)calloc(sizeof(double*), N);
	while ((i-1)*h < 1){
		x[i] = i*h;
		i++;
	}		
	int x_length = i;
	i = 0;
	while ((i-1)*tao < 1){
		t[i] = i*tao;
		i++;
	}
	int tao_length = i;
	
	double **U;
	U = (double**)calloc(sizeof(double*), tao_length);
	for (int i = 0; i<tao_length; i++)
		U[i] = (double*)calloc(sizeof(double), x_length);	
	

	for (int i = 0; i < tao_length; i++)
		for (int j = 0; j < x_length; j++)
			U[i][j] = 0;
	
	
	for (i = 0; i < x_length; i++) 
		U[0][i] = m(x[i]);
	for (i = 0; i < tao_length; i++){
		U[i][0] = m1(t[i]);
		U[i][x_length - 1] = m2(t[i]);
	} 
	
	


	for (int k = 1; k < tao_length; k++){
		for (i = 1; i < x_length - 1; i++){
		 U[k][i] = (U[k-1][i+1]+U[k-1][i-1])/2 - tao*C(t[k - 1],x[i])*(U[k-1][i+1]-U[k-1][i-1])/(2*h); 	
		}
		
	}
	//int sx = x_length / 30;
	//int stao  = tao_length / 30;	
	int sx = 1;
	int stao = 1;
	for (i = 0; i < tao_length; i++){
		for (int j = 0; j < x_length; j++){
				approx << x[j] << " " << t[i] << " " << U[i][j] << endl;
				func << x[j] << " " << t[i] << " " << u(x[j],t[i]) << endl;
			}
			func << endl; approx<< endl;
	}
	double max = 0;
	cout << endl;
	for (i = 0; i < tao_length -2; i++)
		for (int j = 0; j < x_length; j++)
		   	if (fabs(U[i][j]-u(x[j], t[i])) > max)  max = fabs(U[i][j]-u(x[j],t[i]));
	cout << max << endl;
	return 0;

}


