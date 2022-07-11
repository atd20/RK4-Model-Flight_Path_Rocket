#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <valarray>
#include <cmath>
#include <iterator>
#include <iomanip>
#include "Parameters.h"
#include "Environment.h"
#include "Runge.h"
using namespace std;
int main()
{
	//creating instances of three classes, Parameters and Environment and Runge
	//class containing ALL parameters from file parameters.txt
	Parameters Globalvariables;
	Globalvariables.Set_Param();//outputs whole vector 

	//class containing Environmental parameters from file parameters.txt
	Environment Environmentalvariables;
	Environmentalvariables.Set_Evironment(Globalvariables.Get_Param());//returns it 

	//class containing Runga Kutta function and output
	Runge func;
	func.Runge_out(Environmentalvariables.getRHO(), Environmentalvariables.getG(), Environmentalvariables.getC_D(), Environmentalvariables.getV_INIT(), Environmentalvariables.getH_INIT(), Globalvariables.Get_Param());
	return 0;
}


