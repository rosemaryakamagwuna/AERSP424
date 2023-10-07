#include <iostream>
#include <vector>
#include <cmath>

// Function Declarations

// Question 1
double aircraft(double Lp, double Ld, int d, double P, double dt);

// Question 2
double autopilot(double Lp, double Ld, int d, double P, double dt, int K);

// Question 3
double constantgain(double Lp, double Ld, int d, double P, double dt, double K, int a);

// Question 4
double dot_product(const std::vector<double>& w, const std::vector<double>& x);

// Question 5a
double sigmoid(double z_);

// Question 5b
double gradient_sigmoid(double sigmoid_z);

//Question 6
double gradient_cost(double ypred , int y);

//Question 7a

double sigmoid_dot(const std::vector<double>& w_, const std::vector<double>& x_);
std::vector<double> gradient_weight(const std::vector<double>& x_, int y_, double sigmoid_wtx);

//Question 7b

void update_weights(std::vector<double>& w_, const std::vector<double>& dw, double alpha);


