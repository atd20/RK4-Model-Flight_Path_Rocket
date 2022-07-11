#pragma once
#include <vector>
using namespace std;
class Runge
{
public:
	//default constructor
	Runge() {}
	//destructor 
	~Runge() {}
	//member function to calculate Runge kutta
	void  Runge_out(double, double, double, double, double, vector<vector<double>>);

private:

};

