#pragma once
#include <vector>
using namespace std;
class Environment
{
public:
	//default constructor 
	Environment();
	//destructor
	~Environment() {};
	//member function 
	void Set_Evironment(vector<vector<double>>);//takes in 2d vector and returns each value 
	//function to return all variables from first row in  parameters.txt
	double getRHO() {return RHO;} 
	double getG() { return G; }
	double getC_D() { return C_D; }
	double getV_INIT() { return V_INIT; }
	double getH_INIT() { return H_INIT; }

private:
	//inital rocket parameters set to private 
	double RHO, G, C_D, V_INIT, H_INIT;
};

