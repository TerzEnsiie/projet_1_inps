#ifndef ORTHO_H
#define ORTHO_H

#include <armadillo>
#include <cmath>
#include <iostream>

/**
 * @brief Calculate the factorial of x. It's only called by make_ortho_all so case where n < 0 is impossible to achieve
 *
 * @param n
 * @return A float with the factorial of n when n >= 0, 0 when n < 0
 */
float factoriel(int n);

/**
 * @brief It calculates the hermit polynomial for one value of n and z (so one level and on one point of the z axis)
 *
 * @param n
 * @param z
 * @return A float with the hermit polynomial Hn(z)
 */
float calc_hermit(int n,float z);

/**
 * @brief It almost checks the orthonormality between the n and the m polynomial of hermite.
 * Then,  it returns the sum of the product of weight by Hn(nodes) by Hm(Nodes)
 *
 * @param n
 * @param m
 * @return A float with the sum mentionned before stored inside
 */
float make_ortho(int n, int m);

/**
 * @brief Check the orthonormality for all solutions for energy levels from 1 to 10
 *
 * @param n_rows
 * @return true if all of the orthonormality is correct
 * @return false if one or more check is false.
 */
bool make_ortho_all(int n_rows);

#endif