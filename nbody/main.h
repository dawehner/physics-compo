
void output_movement_data(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, ofstream& output_file);
void output_converseved_quantities(ofstream& output_file_conserved, double E1, double L1, double great_half_axis, double excentric, const double j, const double e, const double R);
void output_orbital_parameters(double a1, double e1, ofstream& output_file_a, ofstream& output_file_e);
void nbody_adapt_timestamp(const double& dt_begin, double& dt, listv2d& a, listv2d& da);
void main_body_load_from_file( listv2d& r, listv2d& v, listv2d& a, listv2d& da, listdouble& m, double& h, double& tk, std::string& filename);
bool main_detect_closed_encounter(int& count_encounter, listdouble& m, listdouble& R_in, listv2d& r);
void main_calc_influence_radius(listdouble& R_in, const listdouble& m, const listv2d& r);
void main_prepare_mass_center_system(listv2d& r, listv2d& v, listdouble m);