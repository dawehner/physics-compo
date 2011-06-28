
/**
 * Calculcate lane_emden equation on all places between 0 and the radius with the stepsize of hz.
 *
 * Therefore it uses a vector with 0 = w and 1 = dwdz
 */
vector<listDouble> lane_emden_solve(double n, double hz, double h);

/**
 * derivative helper for lane_emden.
 */
void lane_emden_derivative(const double x, listDouble& y, listDouble& dyxy_out);

/**
 * Set start values of lane emden.
 */
void lane_emden_start(listDouble& y);
