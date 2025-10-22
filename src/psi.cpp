#include "../lib/psi.h"
#include "../lib/hermite.h"

#include <cmath>
#include <armadillo>
#include <stdio.h>

using namespace arma;

#define m 1e-10
#define h_bar 1e-16
#define omega 1e-10

/**
 * @brief Construct a new Psi:: Psi object
 *
 * @param _z_vec
 */
Psi::Psi(vec _z_vec) : z_vec(_z_vec)
{

}

/**
 * @brief Calculate the factorial for n where case < 0 is treated as an error
 *
 * @param n
 * @return double n!
 */
double Psi::fact(int n)
{
    if (n < 0)
    {
        cerr << "Erreur : la factorielle n'est pas définie pour les nombres négatifs." << endl;
        return 0;
    }
    if (n==0)
    {
        return 1;
    }
    if(n==1)
    {
        return 1;
    }
    else
    {
        return n*fact(n-1);
    }
}

/**
 * @brief Calculates all of the psi values
 *
 * @param n_max
 * @param matrix_hermite
 * @return arma::mat
 */
mat Psi::psi_calc(int n_max, mat matrix_hermite)
{
    // creats a matrix of zeros
    mat matrix = arma::zeros(n_max, z_vec.n_elem);

    // Comptues psi_n(z) for each element of the matrix
    for(arma::uword i=0; i < matrix.n_rows; i++)
    {
        for(arma::uword j=0; j < matrix.n_cols; j++)
        {
            matrix(i,j) = 1/sqrt(pow(2.0,i)*fact(i))*pow((m*omega)/(h_bar*M_PI),1/4)*exp(-(m*omega*pow(z_vec(j),2))/(2*h_bar))*matrix_hermite(i, j);
        }
    }
    return matrix;
}
