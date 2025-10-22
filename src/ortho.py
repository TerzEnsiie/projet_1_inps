/usr/bin/env python3
#Just a little programm to obtain the hermite weights and nodes for the Gauss quadrature
import numpy

print(numpy.polynomial.hermite.hermgauss(25))