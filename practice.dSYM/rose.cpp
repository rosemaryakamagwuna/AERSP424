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




int main() {
    double P = 1.0;   // Initialize P with 1.0 
    double dt = 0.01; // Initialize dt with 0.01 
    double Lp, Ld;
    int d;
    int t;
    int K;
    double K_double;
    int a;

    // Question 1
    for (Lp = -0.8, Ld = -0.7, t = 1; Lp < 0.9 && Ld < 0.8 && t < 6; Lp += 0.1, Ld += 0.1, ++t) {
        if (t <= 2) {
            d = 1;
        } else {
            d = 0;
        }
        double P_increment_1 = aircraft(Lp, Ld, d, P, dt);
        std::cout << "The roll rate is: " << P_increment_1 << std::endl;
    }

    // Question 2
    P = 1.0;   // Reset P
    dt = 0.01; // Reset dt
    K = 1;     // Initialize K
    for (Lp = -0.8, Ld = -0.7, t = 1; Lp < 0.9 && Ld < 0.8 && t < 6; Lp += 0.1, Ld += 0.1, ++t) {
        d = -K * P;
        double P_increment_2 = autopilot(Lp, Ld, d, P, dt, K);
        std::cout << "The roll rate is: " << P_increment_2 << std::endl;
    }

    // Question 3
    P = 1.0;   // Reset P
    dt = 0.01; // Reset dt
    K_double = 2.0; // Initialize K as double
    a = 1;     // Initialize a
    for (Lp = -0.8, Ld = -0.7, t = 1; Lp < 0.9 && Ld < 0.8 && t < 6; Lp += 0.1, Ld += 0.1, ++t) {
        double P_increment_3 = constantgain(Lp, Ld, d, P, dt, K_double, a);
        K_double = K_double + a * P_increment_3 * P_increment_3;
        d = -K_double * P;
        std::cout << "The roll rate is: " << P_increment_3 << std::endl;
    }

    // Question 4
    std::vector<double> w = {0.0001, 0.0001, 0.0001};
    std::vector<double> x = {124, 31.89, 20.945};
    double z = dot_product(w, x);
    std::cout << "The dot product z is: " << z << std::endl;

    // Question 5a
    double z_ = 0.0176835; 
    double sigmoid_z = sigmoid(z_);
    std::cout << "The sigmoid function value is: " << sigmoid_z << std::endl;

    // Question 5b
    double gradient_sigmoid_z = gradient_sigmoid(sigmoid_z);
    std::cout << "The gradient_sigmoid function value is: " << gradient_sigmoid_z << std::endl;

    //Question 6
    double ypred = 0.504421;
    int y = 1;
    double dC = gradient_cost(ypred , y);
    std::cout << "The gradient_cost function value is:"<< dC << std::endl;

    // Question 7a
    std::vector<double> w_ = {0.0001, 0.0001, 0.0001};
    std::vector<double> x_ = {124, 31.89, 20.945};
    int y_ = 1;
    
    double sigmoid_wtx = sigmoid_dot(w_, x_);
    std::vector<double> gradient_w = gradient_weight(x_, y_, sigmoid_wtx);
    
    // Print the result
    for (double weight : gradient_w) {
    std::cout << "The gradient_weight function is: " << weight << std::endl;
    }

    //Question 7b

    // Define 'dw' and 'alpha'
    std::vector<double> dw = gradient_w;
    double alpha = 0.001;

    // Call the 'update_weights' function to update 'w'
    update_weights(w, dw, alpha);

    // Print the updated 'w' vector
    for (double weights : w) {
    std::cout << "The update_weights function is: " << weights << std::endl;
    }

    //Question 8
    std::vector<double> ww = {0.0001, 0.0001, 0.0001}; 
    double alpha_ = 0.001;
    std::vector<std::vector<double>> predictor_x;

    // Add [approach speed, wingspan, MTOW] to the predictor_x vector
    predictor_x.push_back({124.0, 74.0, 103.0, 77.0, 104.0, 92.0, 130.0, 73.0});
    predictor_x.push_back({31.89, 51.08, 34,67, 52.00, 35.63, 56.00, 31.29, 52.00});
    predictor_x.push_back({20.945, 9.170, 8.300, 9.400, 13.000, 12.500, 17.637, 9.600});

    std::vector<int> response_y = {1,0,1,0,1,0,1,0};
    
   


    return 0;
}

// Function Definitions

// Question 1
double aircraft(double Lp, double Ld, int d, double P, double dt) {
    return P + (Lp * P + Ld * d) * dt;
}

// Question 2
double autopilot(double Lp, double Ld, int d, double P, double dt, int K) {
    return P + (Lp * P + Ld * d) * dt;
}

// Question 3
double constantgain(double Lp, double Ld, int d, double P, double dt, double K, int a) {
    return P + (Lp * P + Ld * d) * dt;
}

// Question 4
double dot_product(const std::vector<double>& w, const std::vector<double>& x) {
    if (w.size() != x.size()) {
        std::cerr << "Error: Vectors must have the same size." << std::endl;
        return 0.0; // Return an error value
    }

    double result = 0.0;
    for (std::size_t i = 0; i < w.size(); i++) {
        result += w[i] * x[i];
    }

    return result;
}

// Question 5a
double sigmoid(double z_) {
    return 1.0 / (1.0 + std::exp(-z_));
}

// Question 5b
double gradient_sigmoid(double sigmoid_z) {
    return sigmoid_z * (1.0 - sigmoid_z);
}

//Question 6

double gradient_cost(double ypred , int y){
    return 2*(ypred - y);
}

//Question 7a


double sigmoid_dot(const std::vector<double>& w_, const std::vector<double>& x_) {
    double z = dot_product(w_, x_);
    return sigmoid(z);
}

std::vector<double> gradient_weight(const std::vector<double>& x_, int y_, double sigmoid_wtx) {
    std::vector<double> gradient_w;

    // Calculate the gradient weights for each xi
    for (std::size_t i = 0; i < x_.size(); i++) {
        double gradient_wi = 2 * (sigmoid_wtx - y_) * (sigmoid_wtx * (1 - sigmoid_wtx)) * x_[i];
        gradient_w.push_back(gradient_wi);
    }

    return gradient_w;
}


    //Question 7b

void update_weights(std::vector<double>& w_, const std::vector<double>& dw, double alpha) {
    if (w_.size() != dw.size()) {
        std::cerr << "Error: Vectors must have the same size." << std::endl;
        return; // Return without updating if sizes do not match
    }

    for (std::size_t i = 0; i < w_.size(); i++) {
        w_[i] -= alpha * dw[i];
    }
}

    

