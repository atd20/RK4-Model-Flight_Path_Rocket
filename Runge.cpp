#include "Runge.h"
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
//declaration of Runge-Kutta function
void RungeKutta4(double& v_init, double& h_init, double& mass, double rho, double c_d, double area, double& m_dot, double& exhaust, double& d_time, double g, double& t);
void Runge::Runge_out(double rh, double G, double C_D, double V_INIT, double H_INIT, vector<vector<double>> input_vector)
{
	vector<vector<double>> Parameters_Vec = input_vector; //returns vector with all parameter values   Parameters_Vec = input_vector.Get_Param;
	//assignes Environmental parameters to variables
	double  rho, g, c_d, v_init, h_init;
	rho = rh;
	g = G;
	c_d = C_D;
	v_init = V_INIT;
	h_init = H_INIT;

	//set time to zero and determine number of stages depending on how many stages are in the rocket file 
	int stage_number = Parameters_Vec.size() - 1;
	//set time to 0
	double t = 0.0;
	//defining total mass  
	double mass = 0.0;
	//if there is only 1 stage, total mass is only value of the first mass given in parameters.txt, otherwise it will sum stages of all masses
	if (stage_number == 1) {
		mass = Parameters_Vec[1][0];
	}
	else {
		//computing total mass of all the stages for total rocket mass if there are multiple rocket stages 
		for (unsigned int i = 1; i < Parameters_Vec.size(); i++) {
			mass += Parameters_Vec[i][0];
		}
	}
	//outputting results to file called output.txt
	ofstream output_file("output.txt");
	//variable initialisation for non Enviromental factors 
	double m_tot, m_rock, area, m_dot, exhaust, d_time;
	//assigning non environmental parameters from second row onwards depending on how many rows there are. 
	for (unsigned int z = 1; z < Parameters_Vec.size(); z++) {
		m_tot = Parameters_Vec[z][0];//(row,column)
		m_rock = Parameters_Vec[z][1];
		area = Parameters_Vec[z][2];
		m_dot = Parameters_Vec[z][3];
		exhaust = Parameters_Vec[z][4];
		d_time = Parameters_Vec[z][5];

		//outputting initial height, velocity, mass and time values to output.txt file and to terminal 
		cout << setprecision(8);
		output_file << setprecision(8);
		output_file << setprecision(8);
		output_file << setw(15) << t << setw(15) << h_init << setw(15) << v_init << setw(15) << mass << endl;   //output to output text file 
		cout << setw(15) << t << setw(15) << h_init << setw(15) << v_init << setw(15) << mass << endl;
		//loop runs until the height remians above zero and total mass is greater than that of the rocket mass at each stage 
		while (h_init >= 0.0 && (m_tot - m_rock) > 0.0) {
			//calling Runge-Kutta functtion
			RungeKutta4(v_init, h_init, mass, rho, c_d, area, m_dot, exhaust, d_time, g, t);
			//output values to terminal and output.txt file 
			cout << setprecision(8);
			output_file<< setprecision(8);
			output_file << setw(15) << t << setw(15) << h_init << setw(15) << v_init << setw(15) << mass << endl;   //output to output text file 
			cout << setw(15) << t << setw(15) << h_init << setw(15) << v_init << setw(15) << mass << endl;

			//calculating depleting total mass with mass flow rate 
			m_tot -= (m_dot * d_time);
			//if the mass calculated decreases below the mass of the rocket at  the end stage,  mass flow rate, exhaust velocity and total mass are set to zero  and the rocket can free fall
			double fuel = (mass - Parameters_Vec[stage_number][1]);
			if (fuel < 0) {
				m_dot = 0.0;
				exhaust = 0.0;
				mass = Parameters_Vec[stage_number][1];
			}
		}
		//dropping rocket mass after the stage is completed 
		mass -= m_rock;
	}
	output_file.close();//closing output.txt
}

//runge kutta function, taking in rocket and environmental parameters and outputting uodates mass, time and height.
void RungeKutta4(double& v_init, double& h_init, double& mass, double rho, double c_d, double area, double& m_dot, double& exhaust, double& d_time, double g, double& t)
{
	//calculating velocity coefficient 
	double KVEL1, KVEL2, KVEL3, KVEL4;// change this 
	KVEL1 = -g + ((-0.5 * rho * v_init * fabs(v_init) * c_d * area) / mass + v_init * m_dot * exhaust / fabs(v_init * mass));// WATCH OUT ACCORDING TO ORIGINAL CODE YOU WILL TIMES BY STEP 
	KVEL2 = -g + ((-0.5 * rho * (v_init + 0.5 * KVEL1 * d_time) * fabs((v_init + 0.5 * KVEL1 * d_time)) * c_d * area) / mass + (v_init + 0.5 * KVEL1 * d_time) * m_dot * exhaust / fabs((v_init + 0.5 * KVEL1 * d_time) * mass));
	KVEL3 = -g + ((-0.5 * rho * (v_init + 0.5 * KVEL2 * d_time) * fabs((v_init + 0.5 * KVEL2 * d_time)) * c_d * area) / mass + (v_init + 0.5 * KVEL2 * d_time) * m_dot * exhaust / fabs((v_init + 0.5 * KVEL2 * d_time) * mass));
	KVEL4 = -g + ((-0.5 * rho * (v_init + KVEL3 * d_time) * fabs((v_init + KVEL3 * d_time)) * c_d * area) / mass + (v_init + KVEL3 * d_time) * m_dot * exhaust / fabs((v_init + KVEL3 * d_time) * mass));

	double KHEI1, KHEI2, KHEI3, KHEI4;// change this 

	//calculating height coefficients
	KHEI1 = d_time * v_init;
	KHEI2 = d_time * (v_init + (0.5 * KVEL1 * d_time));
	KHEI3 = d_time * (v_init + 0.5 * KVEL2 * d_time);
	KHEI4 = d_time * (v_init + KVEL3 * d_time);

	//calculating mass coefficient 
	double k1m, k2m, k3m, k4m;// change this 
	k1m = -m_dot;
	k2m = -m_dot;
	k3m = -m_dot;
	k4m = -m_dot;

	//updating mass, height, velocity and time
	mass += ((k1m + 2.0 * k2m + 2.0 * k3m + k4m) * d_time) / 6.0;
	v_init += ((KVEL1 + 2.0 * KVEL2 + 2.0 * KVEL3 + KVEL4) * d_time) / 6.0;
	h_init += ((KHEI1 + 2.0 * KHEI2 + 2.0 * KHEI3 + KHEI4)) / 6.0;
	//time
	t += d_time;
}  








