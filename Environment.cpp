#include "Environment.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <string>
#include <valarray>
#include <cmath>
#include <iomanip>
using namespace std;
Environment::Environment()
{// all initial values of firt rowof parameters file set to zero as default constructor
 RHO = 0.0;
 G = 0.0;
 C_D = 0.0;
 V_INIT = 0.0;
 H_INIT = 0.0;
}

void Environment::Set_Evironment(vector<vector<double>> input_vector) 
{
	//extracting first row of parameters file and setting them to dummy 1D vector input_vector
	RHO = input_vector[0][0];
	G = input_vector[0][1];
	C_D = input_vector[0][2];
	V_INIT = input_vector[0][3];
	H_INIT = input_vector[0][4];
}
