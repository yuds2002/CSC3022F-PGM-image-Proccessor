#ifndef PGMimageProcessor_h
#define PGMimageProcessor_h
#include <string>
#include <vector>
#include <iostream>
#include "ConnectedComponent.h"

namespace srkyud001{

    class PGMimageProcessor
    {
    private:
        /* data */
    public:
        PGMimageProcessor(/* args */);
        ~PGMimageProcessor();

        //big 6

        int extractComponents(unsigned char threshold, int minValidSize);
        int filterComponentsBySize(int minSize, int maxSize);
        bool writeComponents(const std::string & outFileName);
        int getLargestSize(void) const;
        int getSmallestSize(void) const;
        void printComponentData(const ConnectedComponent & theComponent) const;
    };

    
}

#endif