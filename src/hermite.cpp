#include <iostream>
#include <cmath>
#include <armadillo>
#include <stdio.h>

#include "../lib/hermite.h"

using namespace std;
using namespace arma;

#define m 1e-10
#define h_bar 1e-16
#define omega 1e-10

/**
 * @brief Construct a new Hermite:: Hermite object
 *
 * @param _z_vec
 */
Hermite::Hermite(vec _z_vec) : z_vec(_z_vec)
{

}

/**
 * @brief Computes the Hermitian polynomial for each z, up the the n-1th degree
 *
 * @param n
 * @return arma::mat
 */
mat Hermite::hermite_calc(int n)
{
    // Creates a matrix full of zeros
    mat matrix = arma::zeros(n, z_vec.n_elem);

    // We change the z values to match what we need in psi
    // Because Psi use Hn(sqrt(m*omega/h_bar)*z) not juste Hn(z)
    vec Z = sqrt(m*omega/h_bar) * z_vec;

    // Uses recursive definition of the Hermitial polynomial to compute them
    for(uword i=0; i < matrix.n_rows; i++)
    {
        for(uword j=0; j < matrix.n_cols; j++)
        {
            if (i==0)
            {
                matrix(i,j)=1;
            }
            else if(i==1)
            {
                matrix(i,j)=2*Z(j);
            }
            else
            {
                matrix(i,j)= 2*Z(j)*matrix(i-1,j)-2*(i-1)*matrix(i-2,j);
            }
        }
    }
    return matrix;
}
