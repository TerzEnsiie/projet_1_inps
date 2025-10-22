#ifndef PSI_H
#define PSI_H

#include <armadillo>

/**
 * @brief A class to calcutates the Psi_n function for each z of the given vector
 *
 */
class Psi
{
public:
    Psi(arma::vec);
    double fact(int n);
    arma::mat psi_calc(int n_max, arma::mat matrix_hermite);
    arma::vec z_vec;
};

#endif
