#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
namespace srkyud001{

int extractComponents(unsigned char threshold, int minValidSize){


    int numrows=0;
    int numcols=0;

    std::stringstream ss;
    std::ifstream file("", std::ios::binary);
    std::string inputLine = "";

    // First line : version
    getline(file, inputLine);
    if (inputLine.compare("P5") != 0)
        std::cerr << "Version error" << std::endl;
    // else
    //     std::cout << "Version : " << inputLine << std::endl;

    // Second line : comment
    getline(file, inputLine);
    while (inputLine.substr(0, 1) == "#")
    {
        // std::cout << inputLine.substr(0, 1) << std::endl;
        getline(file, inputLine);
    }
    ss << inputLine + "\n";
    ss << file.rdbuf();
    ss >> numcols >> numrows;
    std::cout << numcols << " columns and " << numrows << " rows" << std::endl;

    unsigned char **image = new unsigned char *[numrows];
    unsigned char c;
    for (int row = 0; row < numrows; row++)
    {
        image[row] = new unsigned char[numcols];
        for (int col = 0; col < numcols; col++)
        {
            unsigned char c = (unsigned char)(ss.get());
            image[row][col] = c;
        }
    }

    ss.clear();
    file.close();

    return 0;
    
}


}