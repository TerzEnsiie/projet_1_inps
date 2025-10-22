#include <iostream>
#include <cmath>
#include <armadillo>
#include <stdio.h>

#include "../lib/energy.h"

using namespace std;
using namespace arma;

#define m 1e-10
#define h_bar 1e-16
#define omega 1e-10

/**
 * @brief Construct a new Energy:: Energy object
 *
 * @param _n The maximum degree of the Hermitian polynom
 */
Energy::Energy(int _n) : n(_n)
{

}

/**
 * @brief Calculate the second_derivative for Psi function
 *
 * @param psi
 * @param dz
 * @return mat
 */
mat Energy::second_derivative(const mat &psi, double dz)
{
    // Check that the size of psi is correct
    if (psi.n_rows < 3)
    {
        throw std::invalid_argument("La matrice psi doit avoir au moins 3 lignes pour calculer la dérivée seconde.");
    }

    // Creats a matrix if the same dimensions as psi
    mat d2_psi = zeros<mat>(size(psi));

    // Loop on the matrix with special treatment for the borders
    for (uword j = 0; j < psi.n_cols; ++j)
    {
        for (uword i = 1; i < psi.n_rows - 1; ++i)
        {
            d2_psi(i, j) = (psi(i - 1, j) - 2.0 * psi(i, j) + psi(i + 1, j)) / (dz * dz);
        }

        // Treats the border
        d2_psi(0, j) = (psi(1, j) - 2.0 * psi(0, j)) / (dz * dz);
        d2_psi(psi.n_rows - 1, j) = (psi(psi.n_rows - 2, j) - 2.0 * psi(psi.n_rows - 1, j)) / (dz * dz);
    }

    return d2_psi;
}

/**
 * @brief Calculates the real level energy using the formula on Wikipedia
 *
 * @return the double h_bar * omega * (n + 1/2)
 */
double Energy::calculateEnergy()
{
    return h_bar * omega * (n + 0.5);
}

/**
 * @brief Manually check the energy
 * @details The function separatly cumputes both size of the equation before comparing them
 *
 * @param psi
 * @param z_vec
 * @param dz
 */
void Energy::check_energy(const mat &psi, vec z_vec, double dz)
{
    mat C = -((h_bar*h_bar)/(2*m)) * second_derivative(psi,  dz);
    //cout << "Dimensions de C: " << C.n_rows << "x" << C.n_cols << endl;
    vec v0 = (0.5*m*omega*omega*z_vec%z_vec);
    //cout << "Dimensions de v0: " << v0.n_rows << "x" << v0.n_cols << endl;

    mat V = arma::zeros(n, z_vec.n_elem);
    for(int i = 0; i < n; i++)
    {
        for(uword j = 0; j < z_vec.n_elem; j++)
        {
            V(i, j) = v0(j)*psi(i, j);
        }
    }
    //cout << "Dimensions de V: " << V.n_rows << "x" << V.n_cols << endl;


    mat left_mat = C + V;
    //cout << "Dimensions de left_mat  : " << left_mat.n_rows << "x" << left_mat.n_cols << endl;

    double En = calculateEnergy();
    mat right_mat = En * psi;
    //cout << "Dimensions de right_mat  : " << right_mat.n_rows << "x" << right_mat.n_cols << endl;

    cout << "Vérification de l'équation de Shrödinger 1D-HO" << endl;

    if (arma::approx_equal(left_mat, right_mat, "absdiff", 1e-10))
    {
        cout << "Les deux côtés de l'équation sont égaux, donc Psi_n vérifie l'équation" << endl;
    }
    else
    {
        cout << "Psi_n ne vérifie pas l'équation" << endl;
    }
    cout << "Vérification TERMINE\n" << endl;

    return;
}




