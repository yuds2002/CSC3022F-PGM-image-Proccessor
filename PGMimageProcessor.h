#ifndef PGMimageProcessor_h
#define PGMimageProcessor_h
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include "ConnectedComponent.h"

namespace srkyud001
{

    class PGMimageProcessor
    {
    private:
        std::string filename;

    public:
        PGMimageProcessor(std::string);
        ~PGMimageProcessor();
        std::vector<ConnectedComponent> components;
        // big 6

        int extractComponents(unsigned char threshold, int minValidSize);
        int filterComponentsBySize(int minSize, int maxSize);
        bool writeComponents(const std::string &outFileName);
        int getComponentCount(void) const;
        int getLargestSize(void) const;
        int getSmallestSize(void) const;
        void printComponentData(const ConnectedComponent &theComponent) const;
        bool found(std::vector<std::pair<int, int>>, std::pair<int, int>);
    };

}

#endif