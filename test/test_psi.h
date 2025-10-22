#include <cxxtest/TestSuite.h>
#include <armadillo>

#include "../lib/psi.h"
#include "../lib/hermite.h"

using namespace arma;

class PsiTestSuite : public CxxTest::TestSuite
{
public:
    /**
     * @brief Test of the psi_calc() function
     *
     */
    void testPsiCalc()
    {

        vec z_vec = {0, 1, 2, 3, 4, 5, 6, 7};

        // Computes the matrix of psi_n(z)
        Psi psi(z_vec);
        Hermite hermite(z_vec);
        mat matrix_hermite = hermite.hermite_calc(5);
        mat matrix_psi = psi.psi_calc(5, matrix_hermite);

        for (int i = 0; i <= 5; i++)
        {
            for (size_t j = 0; j < z_vec.n_elem; ++j)
            {
                double expected_value = calculateExpectedPsi(i, z_vec[j], matrix_hermite, z_vec);
                TS_ASSERT_DELTA(matrix_psi(i, j), expected_value, 1e-6);
            }
        }
    }

private:
    /**
     * @brief This function is used to compute the expected values of psi
     *
     * @param n
     * @param z
     * @param matrix_hermite
     * @param z_vec
     * @return double
     */
    double calculateExpectedPsi(int n, double z, const mat& matrix_hermite, const vec& z_vec)
    {
        // Constants
        const double m = 1e-10;
        const double h_bar = 1e-16;
        const double omega = 1e-10;

        // Computes the expected value of psi_n(z)
        double normalization_factor = 1.0 / sqrt(pow(2.0, n) * fact(n));
        double prefactor = pow((m * omega) / (h_bar * M_PI), 1.0 / 4.0);
        double exponential_term = exp(-(m * omega * pow(z, 2)) / (2 * h_bar));

        return normalization_factor * prefactor * exponential_term * matrix_hermite(n, z);
    }

    /**
     * @brief Function to calculate the factorial
     *
     * @param n
     * @return unsigned long long
     */
    unsigned long long fact(int n)
    {
        if (n < 0) return 0; // Default case
        unsigned long long result = 1;
        for (int i = 2; i <= n; ++i)
        {
            result *= i;
        }
        return result;
    }
};
