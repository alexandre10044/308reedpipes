/*
** EPITECH PROJECT, 2019
** Work
** File description:
** main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>

using namespace std;

std::map<string, float> var;
std::vector<float> res;
std::vector<float> ordinate;
std::vector<int> abscissa = { 0, 5, 10, 15, 20 };
std::vector<float> vect = { 0, 0, 0, 0, 0 };

bool checkSyntaxInt(char *av)
{
    for (int i = 0; av[i]; i++)
        if (av[i] < '0' || av[i] > '9')
            return (false);
    return (true);
}

bool checkSyntaxDouble(char *av)
{
    for (int i = 0; av[i]; i++)
        if (av[i] != '.' && (av[i] < '0' || av[i] > '9'))
            return (false);
    return (true);
}

void compute()
{
    float A, B, C;

    A = 6 * (var["r10"] - 2 * var["r5"] + var["r0"]) / 50;
    B = 6 * (var["r15"] - 2 * var["r10"] + var["r5"]) / 50;
    C = 6 * (var["r20"] - 2 * var["r15"] + var["r10"]) / 50;
    vect[2] = (B - (A + C) / 4) * 4 / 7;
    vect[1] = A / 2 - 0.25 * vect[2];
    vect[3] = C / 2 - 0.25 * vect[2];

    for(int d = 1; d < var["n"]; d++)
    {
        float x = 20 / (var["n"] * d);
        float   i = (int)((x - 0.01) / 5) + 1;
        float result = (- vect[i - 1] / 30 * pow(x - abscissa[i], 3) \
                      + vect[i] / 30 * pow(x - abscissa[i - 1], 3)
                      - (ordinate[i - 1] / 5 - 5 / 6 * vect[i - 1])
                      * (x - abscissa[i])
                      + (ordinate[i] / 5 - 5 / 6 * vect[i])
                      * (x - abscissa[i - 1]));
        res.push_back(result);
    }
}

int main(int ac, char **av)
{
    std::string line;
    try {
        // Help
        if (ac >= 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
            std::cout << "USAGE" << std::endl;
            std::cout << "\t" << av[0] << " r0 r5 r10 r15 r20 n" << std::endl;
            std::cout << "DESCRIPTION" << std::endl;
            std::cout << "\tr0\tradius (in cm) of pipe at the 0cm abscissa" << std::endl;
            std::cout << "\tr5\tradius (in cm) of pipe at the 5cm abscissa" << std::endl;
            std::cout << "\tr10\tradius (in cm) of pipe at the 10cm abscissa" << std::endl;
            std::cout << "\tr15\tradius (in cm) of pipe at the 15cm abscissa" << std::endl;
            std::cout << "\tr20\tradius (in cm) of pipe at the 20cm abscissa" << std::endl;
            std::cout << "\tn\tnumber of points needed to display the radius" << std::endl;
            return (0);
        }
        // ErrorHandling
        if (ac != 7 || !checkSyntaxInt(av[6])) {
            std::cerr << "Bad usage." << std::endl;
            return (84);
        }
        for (int i = 1; i < 6; i++)
            if (!checkSyntaxDouble(av[i])) {
                std::cerr << "Bad usage." << std::endl;
                return (84);
            }
        // Parsing
        try {
            var["r0"] = std::atof(av[1]);
            var["r5"] = std::atof(av[2]);
            var["r10"] = std::atof(av[3]);
            var["r15"] = std::atof(av[4]);
            var["r20"] = std::atof(av[5]);
            var["n"] = std::atoi(av[6]);
        } catch (...) {
            std::cerr << "Bad input." << std::endl;
            return (84);
        }
        // ErrorHandling
        if (var["n"] <= 0 || var["r0"] <= 0 || var["r5"] <= 0 || var["r10"] <= 0 || var["r15"] <= 0 || var["r20"] <= 0) {
            std::cerr << "Bad usage." << std::endl;
            return (84);
        }
        // Engine
        if (var["r0"] != var["n"])
            ordinate.push_back(var["r0"]);
        if (var["r5"] != var["n"])
            ordinate.push_back(var["r5"]);
        if (var["r10"] != var["n"])
            ordinate.push_back(var["r10"]);
        if (var["r15"] != var["n"])
            ordinate.push_back(var["r15"]);
        if (var["r20"] != var["n"])
            ordinate.push_back(var["r20"]);
        // Engine
        compute();
        // Print
        printf("vector result: [");
        for (int i = 0; i < vect.size(); i++) {
            if ((vect[i] > 0 && vect[i] < 0.1) || (vect[i] > -0.1 && vect[i] < 0))
                printf("0.0");
            else
                printf("%.1f", vect[i]);
            if (i + 1 < vect.size())
                printf(", ");
        }
        printf("]\n");
        for (int i = 0; i < var["n"]; i++) {
            printf("abscissa: %.1f cm\tradius: %.1f cm\n", 20 / (var["n"] - 1) * i, res[i]);
        }
    } catch (...) { return (84); }
    return (0);
}