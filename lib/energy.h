#ifndef ENERGY_H
#define ENERGY_H

/**
 * @brief Class to check that the 1D-HO Shrödinger equation is verified by the psi_n function
 *
 */
class Energy
{
public:
    Energy(int n);
    double calculateEnergy();
    arma::mat second_derivative(const arma::mat& psi, double dz);
    void check_energy(const arma::mat &psi, arma::vec z_vec, double dz);
    int n;
};

#endif
