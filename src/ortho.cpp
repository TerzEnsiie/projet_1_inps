#include <armadillo>
#include <cmath>
#include <iostream>


float xi[25]= {-6.16427243, -5.41363636, -4.78532037, -4.21860944, -3.69028288,
               -3.18829492, -2.70532024, -2.23642013, -1.77800112, -1.3272807,
               -0.88198276, -0.4401473,  0.,  0.4401473,  0.88198276,
               1.3272807,  1.77800112,  2.23642013,  2.70532024,  3.18829492,
               3.69028288,  4.21860944,  4.78532037,  5.41363636,  6.16427243
               };//This is the xi (Nodes) We use only the twenty first one so we can technically go up to 12
// "true" energy levels

float wi[25]= {2.71192351e-17, 1.25881499e-13, 6.71963842e-11, 1.01703825e-08,
               6.25703250e-07, 1.89159730e-05, 3.15083639e-04, 3.11570872e-03,
               1.92430990e-02, 7.68889952e-02, 2.03621137e-01, 3.63088989e-01,
               4.39868722e-01, 3.63088989e-01, 2.03621137e-01, 7.68889952e-02,
               1.92430990e-02, 3.11570872e-03, 3.15083639e-04, 1.89159730e-05,
               6.25703250e-07, 1.01703825e-08, 6.71963842e-11, 1.25881499e-13, // This is the wi  (weight)
               2.71192351e-17
              };



float factoriel(int n)
{
    if(n<0)
    {
        return 0;
    }
    if (n==0)
    {
        return 1;
    }
    if (n==1)
    {
        return 1;
    }
    else
    {
        return n*factoriel(n-1);
    }
}

float calc_hermite(int n, float z)
{
    if (n==0)
    {
        return 1;
    }
    if (n==1)
    {
        return 2*z;
    }
    else
    {
        return 2*z*calc_hermite(n-1,z)-2*(n-1)*calc_hermite(n-2,z);
    }
}


float make_ortho(int n, int m)
{
    float init = 0;
    float witot = 0;
    for(int i=0 ; i < 25 ; i++)
    {
        init=init + wi[i]*calc_hermite(n,xi[i])*calc_hermite(m,xi[i]);
        witot=witot+wi[i];
    }
    return init;
}

bool make_ortho_all(int n_rows)
{
    int nb_false = 0;
    int tot= 0;
    for(int i=0 ; i< n_rows ; i++)
    {
        float res1 = (1 / (sqrt(pow(2, i) * factoriel(i)))) * pow(1 / M_PI, 0.25);
        for(int j=0 ; j< n_rows ; j++ )
        {
            float res2 = (1 / (sqrt(pow(2, j) * factoriel(j)))) * pow(1 / M_PI, 0.25);

            float res = make_ortho(i,j);
            if(i==j)
            {
                if (res1*res2*res > 0.9999 && res1*res2*res < 1.0001 )
                {
                    tot++;
                }
                else
                {
                    nb_false++;
                    tot++;
                }
            }
            else
            {
                if(res1*res2*res < 0.001 && res1*res2*res > -0.001)
                {
                    tot++;
                }
                else
                {
                    nb_false++;
                    tot++;
                }
            }
        }
    }
    printf("Number of false is : %d out of %d\n", nb_false, tot);
    if(nb_false == 0)
    {
        printf("Then, every check of orthonormality is true ! Good job ! \n\n");
        return true;
    }
    else
    {
        printf("Then, we have at least one false check ! Too bad !");
        return false;
    }
}