#include <cxxtest/TestSuite.h>
#include <armadillo>
#include "../lib/energy.h"

using namespace arma;

#define epsilon 10e-6
#define m 1
#define h_bar 1
#define omega 1

class TestEnergy : public CxxTest::TestSuite 
{
  public:
  void testEnergy()
  {
	Energy MyEnergy();
	mat res = - (1/2*m) * h_bar * h_bar *MyEnergy.second_derivative(psi, dz) 
	+ (0.5 * m * omega * omega * z_vec * z_vec - MyEnergy.theoretical_energy(n)) * psi;
	TS_ASSERT(res < epsilon)
  }
};