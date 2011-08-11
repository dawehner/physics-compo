
/**
 * Write the current positions, velocities, accells etc. into the output file.
 */
void output_movement_data(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, ofstream& output_file);

/**
 * Write the control quantities into it's output file.
 *
 * Calculated control quantities
 *
 * * energy
 * * specific angular momentum
 * * great half axis
 * * excentric
 * * abs(runge-lenz)
 */
void output_converseved_quantities(std::ofstream& output_file_conserved, double ti, double E1, double L1, double great_half_axis, double excentric, const double j, const vector2d& R);

/**
 * Adapt the current timestamp dt based on the a and da.
 */
void nbody_adapt_timestamp(const double& dt_begin, double& dt, listv2d& a, listv2d& da);

/**
 * Load the initial positions/speeds/accells/daccells/masses
 * out of the filename.
 */
void main_body_load_from_file( listv2d& r, listv2d& v, listv2d& a, listv2d& da, listdouble& m, std::string& filename);

/**
 * look up whether some bodies are near enough to have a closed encounter.
 *
 * If it's near enough count up count_encounter.
 */
bool main_detect_closed_encounter(int& count_encounter, listdouble& m, listdouble& R_in, listv2d& r, const double ti);

/**
 * Calculate the influence radius using eq(39)
 */
void main_calc_influence_radius(listdouble& R_in, const listdouble& m, const listv2d& r);

/**
 * Calculate the mass center and change the positions relative to this mass center.
 */
void main_prepare_mass_center_system(listv2d& r, listv2d& v, listdouble m);