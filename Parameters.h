#pragma once
#include <vector>

using namespace std;

class Parameters 
{
public:
	//default constructor 
	Parameters();
	//destructor 
	~Parameters() {};
	//member functions
	void Set_Param(); //read parameters.txt and put in parameters_vector (private )
	vector<vector<double>> Get_Param() { return parameters_vector;}// getting items from parameters file in a 2D vector
private:
	//setting contents of parameters.txt to private
	vector<vector<double>> parameters_vector;
};



