#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE 4096

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

class Buffer
{
    public:
        char* buffer;
        int bufferSize;
        int inicioLexema;
        int forward;

        Buffer(int bf_size);
        virtual ~Buffer();
    protected:
    private:
};

#endif // BUFFER_H
