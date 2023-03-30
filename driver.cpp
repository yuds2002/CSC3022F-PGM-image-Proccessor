#include <iostream>
#include <string>
#include <vector>
#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"
int main(int argc, char * argv[]){
  
    srkyud001::PGMimageProcessor ip ("cameraman.pgm");
    unsigned char threshold = 200;
    ip.extractComponents(threshold,1);
    return 0;
}