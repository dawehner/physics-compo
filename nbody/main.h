
/**
 * Write the current positions, velocities, accells etc. into the output file.
 */
void output_movement_data(vector< vector3d >& r, vector< vector3d >& v, vector< vector3d >& a, vector< double >& m, ofstream& output_file);

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
void output_converseved_quantities(std::ofstream& output_file_conserved, double ti, double E1, double L1, double great_half_axis, double excentric, const double j, const vector3d& R);

/**
 * Adapt the current timestamp dt based on the a and da.
 */
void nbody_adapt_timestamp(const double& dt_begin, double& dt, listv3d& a, listv3d& da);

/**
 * Load the initial positions/speeds/accells/daccells/masses
 * out of the filename.
 */
void nbody_load_from_file( listv3d& r, listv3d& v, listv3d& a, listv3d& da, listdouble& m, std::string& filename);

/**
 * look up whether some bodies are near enough to have a closed encounter.
 *
 * If it's near enough count up count_encounter.
 */
bool nbody_detect_closed_encounter(int& count_encounter, listdouble& m, listdouble& R_in, listv3d& r, const double ti);

/**
 * Calculate the influence radius using eq(39)
 */
void nbody_calc_influence_radius(listdouble& R_in, const listdouble& m, const listv3d& r);

/**
 * Calculate the mass center and change the positions relative to this mass center.
 */
void nbody_prepare_mass_center_system(listv3d& r, listv3d& v, listdouble m);