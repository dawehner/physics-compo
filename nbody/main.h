void output_movement_data(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, ofstream& output_file);
void output_converseved_quantities(double E1, double L1, ofstream& output_file_energy, ofstream& output_file_angular_momentum, const double j, const double e, const double R);
void output_orbital_parameters(double a1, double e1, ofstream& output_file_a, ofstream& output_file_e);
void main_two_body_start( listv2d& r, listv2d& v, listv2d& a, listdouble& m, double& h, double& tk);
void nbody_adapt_timestamp(const double& dt_begin, double& dt, const listv2d& a, const listv2d& da);
