 #ifndef IO_H
#define IO_H

//#include "Buffer.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define BUFFER_SIZE 4096
using namespace std;

class IO
{
    private:
        std::vector<char*> buffers;
        char* contents;
        int bufferSize;
        std::streamsize size;
        int inicioLexema;
        int forward;

        FILE* fd;
        char fileName[100];
        int count;
        int eof_;
        int bufferAtual;
        size_t nbytesRead;
        void reloadBuffer();
        char* getFileName();
        void retract();

    public:
        IO();
        IO(int argc, char* argv[]);
        void openFile();
        void readFile();
        char getNextChar();
        int isEOF() const;
        void printfBuffersContent();
        virtual ~IO();
    protected:
    private:
};

#endif // IO_H
