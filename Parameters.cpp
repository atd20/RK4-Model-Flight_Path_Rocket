
#include <iostream>
#include "Parameters.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <valarray>
#include <iterator>
#include <cmath>
#include <iomanip>
using namespace std;

Parameters::Parameters() 
{
	//defining default constructor 
	vector<vector<double>> parameters_vector
	{
	  {0,0,0,0,0},{0,0,0,0,0,0}//the number of lines in the parameters line does not matter, this default constructures sets all initial parameter values to zero
	};
}

//setting the variables from parameters.txt to a 2D vector
void Parameters::Set_Param()
{
	//stores in parameters vector as a 2D vector/
	ifstream param_in("Parameters.txt");//open file[ parameters.txt]
	vector<vector<double>> Parameters_Vec;//temp vector to store in the 2D vector 
	string rec;
	if (param_in.good()) {//checks if file is good, if not outputs an error 
		while (getline(param_in, rec))//while it doesnt complete reading whole file,
		{
			istringstream is(rec);//streaming file into string 
			vector<double> row((istream_iterator<double>(is)),//vector that temporary gets value of each variable in the file
				istream_iterator<double>());//reading the successive elements in format double 
			Parameters_Vec.push_back(row);//adds each number in the parameters file to the 2D vector, Parameters_Vec
		}

		//prints out the 2D vector to the terminal in the format of Parameters.txt
		cout << "Parameters file" << endl;
		for (unsigned int i = 0; i < Parameters_Vec.size(); i++) { //row,column
			for (unsigned int j = 0; j < Parameters_Vec[i].size(); j++) {
				cout << Parameters_Vec[i][j] << " ";
			}
			cout << endl;
		}
		parameters_vector = Parameters_Vec;// 2D vector stored in a temporary variable called parameters_vector
		param_in.close();//closing file 
	}

	else {
		cout << "Failed to open file" << endl;
	}
	
}


