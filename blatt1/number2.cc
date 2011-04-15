#include <cmath>
#include <iostream>
#include <fstream>
#include "anomalie.cc"
#include "coordinates.cc"

using namespace std;


int main() {
  double t0 = 0;
  double t = t0;
  double temp_except = 0;
  double excent = 0.205;
  double P = 10000;
  double phi = 0;
  double r = 0;
  double x = 0;
  double y = 0;
  double a = 1000;
  double phi0 = grad_to_rad(102.95);
  
  
  double a_earth = 1.0;
  double e_earth = 0.0167;
  double phi0_earth = grad_to_rad(102.95);
  double lambda_earth = 100.46;
  double m_earth = lambda_earth - phi0_earth;
  
  double a_mars = 1.524;
  double e_mars = 0.0934;
  double phi0_mars = grad_to_rad(336.04);
  double lambda_mars = 355.46;
  double m_mars = lambda_mars - phi0_mars;

  // fstream plots;
  // plots.open("../plots.txt", ios::out);
  // plots.close();

  // 630720000 is 20 years in seconds
  // let's choose not too many steps
  int size = 1000;
  int max = 630720000 / size;
  for (int i = 0; i < max; i++) {
    // We go back in time
    t -= i * size;

	  temp_except = generate_anomalie_excent_per_time(excent, t, t0, P);
	  phi = calc_phi(temp_except, excent);
    r = calc_r(a, excent, phi, phi0);
    x = calc_x(r, phi, phi0);
    y = calc_y(r, phi, phi0);

    cout<<"r" << r;
    cout<<"phi" << phi << endl;

    // std::cout<<"x" << x;
    // std::cout<<"y" << y;
    // plots << x << ";" << y << endl;
  }

  return 0;
}