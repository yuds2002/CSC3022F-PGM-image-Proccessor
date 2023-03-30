#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "PGMimageProcessor.h"
namespace srkyud001{

PGMimageProcessor::PGMimageProcessor(std::string filename){
    this->filename = filename;
    
}
unsigned char **image;
int numrows=0;
int numcols=0;


int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize){

    std::stringstream ss;
    std::ifstream file(filename, std::ios::binary);
    std::string inputLine = "";

    // First line : version
    getline(file, inputLine);
    if (inputLine.compare("P5") != 0)
        std::cerr << "Version error" << std::endl;
    else
        std::cout << "Version : " << inputLine << std::endl;

    // Second line : comment
    getline(file, inputLine);
    while (inputLine.substr(0, 1) == "#")
    {
        
        std::cout << inputLine.substr(0, 1) << std::endl;
        getline(file, inputLine);
    }
   
    int range=0;

    ss << inputLine + "\n";
    getline(file, inputLine);
    ss << inputLine +"\n";
    ss << file.rdbuf();
    ss >> numcols >> numrows;
    std::cout << numcols << " columns and " << numrows << " rows" << std::endl;
    ss >> range;
    std::cout<<"range = "<<range<<std::endl;
    image = new unsigned char *[numrows];
   
    for (int row = 0; row < numrows; row++)
    {
        image[row] = new unsigned char[numcols];
        for (int col = 0; col < numcols; col++)
        {
            
            //std::string s;
            //ss >>s;

            unsigned char p = (unsigned char)(ss.get());

            
           // std::cout<< s <<" ";
            
            //int p = std::stoi(s);


            if(p<threshold){
                p = 0;
            }else{
                p =255;
            }

           
           
            image[row][col] = p;
        }
    }

    int count=0;

    for (int i = 0; i < numrows; i++)
    {
        for (int j = 0; j < numcols; j++)
        {
            if(image[i][j]==255){
                count++;
            }
        }
        
    }

    
    //std::cout<<int(threshold)<<std::endl;
    ss.clear();
    file.close();

    std::FILE *pgmimg;
    pgmimg = fopen("test.pgm", "wb");

    // Writing Magic Number to the File
    fprintf(pgmimg, "P5\n");

    //comment
    fprintf(pgmimg, "#made by srkyud001\n");
    // Writing Width and Height
    fprintf(pgmimg, "%d %d\n", numcols, numrows);

    // Writing the maximum gray value
    fprintf(pgmimg, "255\n");

    for (int i = 0; i < numrows; i++)
    {
        
        for (int j = 0; j <numcols; j++)
        {
            unsigned char temp = image[i][j];
           

            //  Writing the gray values in the 2D array to the file
            fprintf(pgmimg, "%d ", temp);
        }
        fprintf(pgmimg, "\n");
    }

    fclose(pgmimg);

    //////////////////////////////////////floodfill start
    

    std::vector<std::pair<int,int>> equal;

    int label=0;
   
    for (int row = 0; row < numrows; row++)
    {
        for (int col = 0; col < numcols; col++)
        {
            
            if(image[row][col] == 255){


                if(row==0 && col ==0){
                    //ConnectedComponent cc;
                    //cc.coord.push_back(std::make_pair(row,col));
                    //components.push_back(cc);
                    label++;
                }
                //if up and left == 0 create connected component
                if(row-1>=0 && col-1>=0){
                    
                    if (image[row-1][col]==0 && image[row][col-1]==0)
                    {
                        //ConnectedComponent cc;
                        //cc.coord.push_back(std::make_pair(row,col));
                        //components.push_back(cc);

                        label++;
                        image[row][col] = label;
                        
                    }else{
                        if(image[row-1][col]==0){
                            image[row][col] = image[row][col-1];
                        }else if (image[row][col-1]==0){
                            image[row][col] = image[row-1][col];
                        }else{
                            int min = std::min(image[row][col-1],image[row-1][col]);
                            int max  = std::max(image[row][col-1],image[row-1][col]);
                            equal.push_back(std::make_pair(min,max));
                            image[row][col] = min;
                        }
                        
                        //components.back().coord.push_back(std::make_pair(row,col));
                    }
                // if there is only up and it == 0 create connected component
                }else if(row-1>=0){
                    if (image[row-1][col]==0)
                    {
                        //ConnectedComponent cc;
                        //cc.coord.push_back(std::make_pair(row,col));
                        //components.push_back(cc);

                        label++;
                        image[row][col] = label;


                    }else{
                        image[row][col] = image[row-1][col];
                        
                        //components.back().coord.push_back(std::make_pair(row,col));
                    }

                // if there is only left and it == 0 create connected component
                }else{
                    if(image[row][col-1]==0){
                        //ConnectedComponent cc;
                        //cc.coord.push_back(std::make_pair(row,col));
                        //components.push_back(cc);

                        label++;
                        image[row][col] = label;

                    }else{
                        image[row][col] = image[row][col-1];

                        //components.back().coord.push_back(std::make_pair(row,col));
                    }


                }

            }
            
        }
       
    }
    
    //////////////////////////////////////floodfill end
//

    std::cout<< count << " = '255' pixels"<< std::endl;

    std::vector<std::pair<int,int>> eql;
    std::vector<int> firsts;
    
    for (int i = 0; i < equal.size(); i++)
    {
        //std::cout<<equal[i].first << " - " << equal[i].second<<std::endl;
        if(equal[i].first != equal[i].second){
            eql.push_back(equal[i]);
            firsts.push_back(equal[i].first);
            //std::cout<<equal[i].first << " - " << equal[i].second<<std::endl;
        }
        
    }

    std::vector<int>::iterator num_comp =  std::max_element(firsts.begin(), firsts.end());
    std::cout<<*num_comp<< " components"<<std::endl;
    
    std::vector<ConnectedComponent> components;
    std::vector<int> seen;

    std::cout<<std::endl;

    for (int r = 0; r < numrows; r++)
    {
        for (int c = 0; c < numcols; c++)
        {
            for (int e = 0; e < eql.size(); e++)
            {
                if(image[r][c] == eql[e].second){
                    //std::cout<<eql[e].second<<" becomes " <<eql[e].first <<std::endl;
                    image[r][c] = eql[e].first;
                    break;
                }
                
            }
           // std::cout<<image[r][c] << " ";
        }
        //std::cout<<std::endl;
        
    }

    
    for (int i = 1; i <= *num_comp; i++)
    {
        ConnectedComponent cc;
        
        for (int r = 0; r < numrows; r++)
        {
            for (int c = 0; c < numcols; c++)
            {
                if(image[r][c] == i){
                    cc.coord.push_back(std::make_pair(r,c));
                }
            }
            
        }
        if (cc.coord.size()>0)
        {
           components.push_back(cc);
        }
        
    }
    

    for (int c = 0; c < components.size(); c++)
    {
        std::cout<<components[c].coord.size()<<std::endl;
    }
    
    

    return 0;
    
}





PGMimageProcessor::~PGMimageProcessor(){
    for (int i = 0; i < numrows; i++)
    {
        delete[] image[i];
    }
    delete[] image;

    std::cout<<"pgm destructor"<<std::endl;
}


}