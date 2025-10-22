#!/bin/bash

make clean

echo "Compilation avec make du projet"
make

echo "Execution de ./bin/main"
./bin/main

echo "Execution de plot.py pour l'affichage"
python3 src/plot.py

echo "Ouverture de l'image de résultat"
open output_graph.png