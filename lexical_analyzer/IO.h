 #ifndef IO_H
#define IO_H
using namespace std;
#include "Buffer.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class IO
{
    private:
        std::vector<Buffer*> bufferes;
        int argc;
        char* argv;
        FILE* fd;
        char* fileName;
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
