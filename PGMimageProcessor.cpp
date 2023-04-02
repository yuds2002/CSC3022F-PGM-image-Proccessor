#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include "PGMimageProcessor.h"
namespace srkyud001
{

    PGMimageProcessor::PGMimageProcessor(std::string filename)
    {
        this->filename = filename;
    }
    unsigned char **image;
    int numrows = 0;
    int numcols = 0;

    bool PGMimageProcessor::found(std::vector<std::pair<int, int>> vect, std::pair<int, int> key)
    {
        auto it = std::find(vect.begin(), vect.end(), key);
        if (it != vect.end())
        {
            return true;
        }
        return false;
    }

    int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
    {

        int range = 0;

        std::stringstream ss;
        std::ifstream file(filename, std::ios::binary);
        std::string inputLine = "";

        getline(file, inputLine);
        if (inputLine.compare("P5") != 0)
            std::cerr << "Version error" << std::endl;
        else
            std::cout << "Version : " << inputLine << std::endl;

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
        ss >> range;
        std::cout << range << " = range" << std::endl;
        image = new unsigned char *[numrows];
        unsigned char c;
        for (int row = 0; row < numrows; row++)
        {
            image[row] = new unsigned char[numcols];
            for (int col = 0; col < numcols; col++)
            {
                unsigned char c = (unsigned char)(ss.get());

                if (c > threshold)
                {
                    c = 255;
                }
                else
                {
                    c = 0;
                }

                image[row][col] = c;
            }
        }

        int count0 = 0;
        int count255 = 0;

        for (int i = 0; i < numrows; i++)
        {
            for (int j = 0; j < numcols; j++)
            {
                if (image[i][j] == 0)
                {
                    ++count0;
                }
                else
                {
                    ++count255;
                }
            }
        }

        // std::cout<<int(threshold)<<std::endl;
        ss.clear();
        file.close();

        //////////////////////////////////////bfs start

        std::vector<std::pair<int, int>> seen;
        std::queue<std::pair<int, int>> q;

        int label = 1;

        for (int row = 0; row < numrows; row++)
        {
            for (int col = 0; col < numcols; col++)
            {

                if (image[row][col] == 255)
                {
                    q.push(std::make_pair(row, col));
                    seen.push_back(std::make_pair(row, col));

                    while (!q.empty())
                    {

                        auto current = q.front();
                        q.pop();

                        int i = current.first, j = current.second;
                        // std::cout << q.size();
                        // std::cout << i << " -- " << j << std::endl;
                        image[i][j] = label;
                        if (i >= 1)
                        {
                            if (image[i - 1][j] == 255 && !found(seen, std::make_pair(i - 1, j)))
                            {
                                // std::cout << "up" << std::endl;

                                seen.push_back(std::make_pair(i - 1, j));
                                q.push(std::make_pair(i - 1, j));
                            }
                        }

                        if (j >= 1)
                        {
                            if (image[i][j - 1] == 255 && !found(seen, std::make_pair(i, j - 1)))
                            {
                                // std::cout << "left" << std::endl;
                                seen.push_back(std::make_pair(i, j - 1));
                                q.push(std::make_pair(i, j - 1));
                            }
                        }

                        if (i < numrows)
                        {
                            if (image[i + 1][j] == 255 && !found(seen, std::make_pair(i + 1, j)))
                            {
                                // std::cout << "down" << std::endl;

                                seen.push_back(std::make_pair(i + 1, j));
                                q.push(std::make_pair(i + 1, j));
                            }
                        }

                        if (j < numcols)
                        {
                            if (image[i][j + 1] == 255 && !found(seen, std::make_pair(i, j + 1)))
                            {
                                // std::cout << "right" << std::endl;

                                seen.push_back(std::make_pair(i, j + 1));
                                q.push(std::make_pair(i, j + 1));
                            }
                        }
                    }
                    std::cout << label << std::endl;
                    label++;
                }
            }
        }

        //////////////////////////////////////bfs end
        //
        std::vector<ConnectedComponent> components;

        for (int i = 0; i <= label; i++)
        {
            ConnectedComponent cc;
            components.push_back(cc);
        }

        for (int r = 0; r < numrows; r++)
        {
            for (int c = 0; c < numcols; c++)
            {
                int pos = image[r][c];
                if (pos != 0)
                {
                    components[pos - 1].coord.push_back(std::make_pair(r, c));
                }
            }
        }

        for (int i = 0; i < components.size(); i++)
        {
            std::cout << components[i].coord.size() << std::endl;
        }

        std::FILE *pgmimg;
        std::stringstream n;

        pgmimg = fopen("test.pgm", "wb");

        // Writing Magic Number to the File
        fprintf(pgmimg, "P2\n");

        // Writing Width and Height
        fprintf(pgmimg, "%d %d\n", numcols, numrows);

        // Writing the maximum gray value
        fprintf(pgmimg, "255\n");

        for (int i = 0; i < numrows; i++)
        {

            for (int j = 0; j < numcols; j++)
            {

                int temp = image[i][j];

                fprintf(pgmimg, "%d ", temp);
            }
            fprintf(pgmimg, "\n");
        }

        fclose(pgmimg);

        // std::cout << components.size() << std::endl;
        return 0;
    }

    PGMimageProcessor::~PGMimageProcessor()
    {
        for (int i = 0; i < numrows; i++)
        {
            delete[] image[i];
        }
        delete[] image;

        std::cout << "pgm destructor" << std::endl;
    }

}