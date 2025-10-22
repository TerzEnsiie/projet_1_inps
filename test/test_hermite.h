#ifndef TEST_HERMITE_H
#define TEST_HERMITE_H

#include <cxxtest/TestSuite.h>
#include <armadillo>

#include "../lib/hermite.h"

using namespace arma;

#define epsilon 1e-6
//#define m 1e-10
//#define h_bar 1e-16
//#define omega 1e-10

class HermiteTestSuite : public CxxTest::TestSuite
{
public:

    // Test the hermite constructor
    void testHermiteConstructor()
    {
        vec z_vec = linspace(0, 1, 10);
        Hermite hermite(z_vec);
        TS_ASSERT_EQUALS(hermite.z_vec.n_elem, z_vec.n_elem);
        TS_ASSERT(approx_equal(hermite.z_vec, z_vec, "absdiff", 1e-12));
    }

    // Test the computing of the first hermitial polynoms
    void testHermiteCalc()
    {
        vec z_vec = {0, 1, 2, 3, 4, 5, 6, 7};
        Hermite hermite(z_vec);
        int n = 6;

        mat matrix_hermite = hermite.hermite_calc(n);

        /*
         * H_0 = 1
         * H_1 = 2X
         * H_2 = 4X² - 2
         * H_3 = 8X³ - 12X
         * H_4 = 16X⁴ - 48X² + 12
         * H_5 = 32X⁵ - 160X³ + 120X
         * */
        mat hermite_expected = mat(n, z_vec.n_elem);
        hermite_expected.row(0) = rowvec({1, 1, 1, 1, 1, 1, 1, 1});
        hermite_expected.row(1) = rowvec({0, 2, 4, 6, 8, 10, 12, 14});
        hermite_expected.row(2) = rowvec({-2, 2, 14, 34, 62, 98, 142, 194});
        hermite_expected.row(3) = rowvec({0, -4, 40, 180, 464, 940, 1656, 2660});
        hermite_expected.row(4) = rowvec({12, -20, 76, 876, 3340, 8812, 19020, 36076});
        hermite_expected.row(5) = rowvec({0, -8, -16, 3816, 23008, 80600, 214992, 483784});

        for(int i = 0; i < n; i++)
        {
            for(uword j = 0; j < z_vec.n_elem; j++)
            {
                TS_ASSERT_DELTA(matrix_hermite(i, j), hermite_expected(i, j), epsilon);
            }
        }
    }

};

#endif
