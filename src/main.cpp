#include <iostream>
#include <armadillo>
#include <fstream>

#include "../lib/main.h"
#include "../lib/hermite.h"
#include "../lib/psi.h"
#include "../lib/energy.h"
#include "../lib/ortho.h"

using namespace std;
using namespace arma;

#define m 1e-10
#define h_bar 1e-16
#define omega 1e-10

void read_input_file(float *z_min, float *z_max, int *N_z, int *n_max)
{
    // Open the file
    std::ifstream file("input.txt");

    // Check if the file opened successfully
    if (!file)
    {
        std::cerr << "Error: Unable to open the file!" << std::endl;
        exit(1);
    }
    cout << "Reading input.txt file" << endl;
    std::string line;

    // Read the file line by line and parse the values
    while (std::getline(file, line))
    {
        // Find the position of '=' in each line
        std::size_t pos = line.find('=');
        if (pos != std::string::npos)
        {
            // Extract the parameter name and value
            std::string param_name = line.substr(0, pos);
            int value = std::stoi(line.substr(pos + 1)); // Convert the value after '=' to an integer

            // Match the parameter name and store the corresponding value
            if (param_name.find("z_min") != std::string::npos)
            {
                *z_min = value;
            }
            else if (param_name.find("z_max") != std::string::npos)
            {
                *z_max = value;
            }
            else if (param_name.find("Nombre de points") != std::string::npos)
            {
                *N_z = value;
            }
            else if (param_name.find("Degré maximal des polynômes d'Hermite") != std::string::npos)
            {
                *n_max = value;
            }
        }
    }

    // Close the file
    file.close();

    return;
}

void write_output_file(float z_min, float z_max, int N_z, int n_max, mat matrix)
{
    ofstream file("output.txt");

    // Check if the file is open and writes in it
    if (file.is_open())
    {
        file << z_min << endl;
        file << z_max << endl;
        file << N_z << endl;
        file << n_max << endl;

        // Writes the data in the file
        for (uword i = 0; i < matrix.n_rows; ++i)
        {
            for (uword j = 0; j < matrix.n_cols; ++j)
            {
                // Each element are seperated by one space
                file << matrix(i, j) << " ";
            }
            // Each ns are printed on a different row
            file << endl;
        }
        file.close(); // Close the file
        cout << "Matrice écrite dans le fichier 'output.txt'.\n" << endl;
    }
    else
    {
        cerr << "Erreur d'ouverture du fichier." << endl;
    }
}

void print_matrix(const mat &M)
{
    M.print("Matrice :");
}

int main()
{
    float z_min, z_max;
    int N_z, n_max;

    read_input_file(&z_min, &z_max, &N_z, &n_max);
    if(n_max > 10)
    {
        cerr << "Le degré maximal pour le polynôme d'Hermite doit être inférieur à 10" << endl;
        exit(2);
    }

    // Creats a vector of z
    vec z_vec = arma::linspace(z_min, z_max, N_z);

    // Computes the Hermitial polynoms
    Hermite hermite(z_vec);
    mat matrix_hermite = hermite.hermite_calc(n_max);

    // Comptues the psi_n function
    Psi psi(z_vec);
    mat matrix = psi.psi_calc(n_max, matrix_hermite);

    write_output_file(z_min, z_max, N_z, n_max, matrix);

    // Energy Check
    Energy energy(n_max);
    double dz = z_vec(1) - z_vec(0);
    energy.check_energy(matrix, z_vec, dz);

    // Orthogonality check
    make_ortho_all(n_max);

    return 0;
}