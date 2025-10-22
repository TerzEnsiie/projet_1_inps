#ifndef MAIN_H
#define MAIN_H

#include <armadillo>

/**
 * @brief Ask the user to give a float number
 *
 * @return float
 */
float ask_for_float();

/**
 * @brief Ask the user to give an int number
 *
 * @return int
 */
int ask_for_int();

/**
 * @brief Prints an armadillo matrix
 * @details Mainly used to prints small matrixes to debug
 */
void print_matrix(const arma::mat& M);


#endif
