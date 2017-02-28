//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_FILEUTILS_H
#define TLOTK_FILEUTILS_H

#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#define MAX_FILE_SIZE 10*1024*1024
#define FDNE_ERROR -102
#define FILE_TOO_LARGE_ERROR -103

namespace utils
{
    static std::string loadFile(const std::string &fileName)
    {
        FILE *curFile;

        curFile = fopen(fileName.c_str(), "rt");
        if(curFile == NULL)  {
            perror ("Error opening file: ");
            exit(FDNE_ERROR);
        }
        fseek(curFile, 0, SEEK_END);

        long curFileLength = ftell(curFile);

        if(curFileLength >= MAX_FILE_SIZE || curFileLength < 0)
        {
            std::cout << "ERROR: File " << fileName << " too large, (" << curFileLength << "). Exiting. ";
            exit(FILE_TOO_LARGE_ERROR);
        }

        char* fileText = new char[curFileLength + 1];
        memset(fileText, 0, curFileLength + 1); // Good for file reading?

        // Seek to the beginning
        fseek(curFile, 0, SEEK_SET);
        fread(fileText, 1, curFileLength, curFile);
        fclose(curFile);

        // Create a C++ string from the char*[]
        std::string result(fileText);
        delete[] fileText;
        return result;
    }
};


#endif //TLOTK_FILEUTILS_H
