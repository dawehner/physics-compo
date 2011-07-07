#include <vector>

using namespace std;
/**
 * Solves the hydronamic for the radial sun.
 *
 * Step1:
 * - Set start values based on lane-emden.
 *
 * Step2:
 * - Create an array over these values.
 *
 * Step3:
 * - 
 *
 * @param t1
 * The end time of the calculation.
 * @param dt
 * The initial timestep. This might be changed based on CFL.
 */
void hsolar_solve(double t1, double dt, double n);

/**
 * Put the grid onto the values.
 */
void hsolar_single_timestamp(listDouble& rho, listDouble& u, const double dt, const double z_max, const double z_size, const int cell_n, const double gamma, const double K);

void hsolar_grid(const int N, const double cell_n, vector< listDouble >& y_list, listDouble& rho, listDouble u, double& z_max);

void hsolar_write(ofstream& file, listDouble& data);

void hsolar_rho_floor(listDouble& rho);

void hsolar_adapt_timestep(listDouble& rho, listDouble& u, const double K, const double n);