#ifndef HERMITE_H
#define HERMITE_H

#include <armadillo>

/**
 * @brief Class to calculate the hermite polynomials for the 1D-HO solutions
 *
 */
class Hermite
{
public:
    Hermite(arma::vec);
    arma::mat hermite_calc(int n);
    arma::vec z_vec;
};

#endif