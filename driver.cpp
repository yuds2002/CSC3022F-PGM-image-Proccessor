#include <iostream>
#include <string>
#include <vector>
#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"
int main(int argc, char *argv[])
{
    std::string in_filename;
    in_filename = argv[argc - 1];
    srkyud001::PGMimageProcessor ip(in_filename);
    unsigned char threshold = 128;
    int min = 3;
    int max = 3;
    std::string out_filename;

    for (int i = 0; i < argc; i++)
    {
        std::string s = argv[i];

        if (s == "-s")
        {
            min = std::stoi(argv[i + 1]);
            max = std::stoi(argv[i + 2]);
            ip.filterComponentsBySize(min, max);
        }

        if (s == "-t")
        {
            threshold = std::stoi(argv[i + 1]);
            ip.extractComponents(threshold, min);
        }

        if (s == "-p")
        {
            for (int i = 0; i < ip.components.size(); i++)
            {
                ip.printComponentData(ip.components[i]);
            }
            std::cout << "There are " << ip.getComponentCount() << " components" << std::endl;
            std::cout << "The largest component has size: " << ip.getLargestSize() << std::endl;
            std::cout << "The smallest component has size: " << ip.getSmallestSize() << std::endl;
        }

        if (s == "-w")
        {
            out_filename = argv[i + 1];
            ip.writeComponents(out_filename);
        }
    }

    return 0;
}