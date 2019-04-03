#include "Buffer.h"


Buffer::Buffer(int bf_size)
{
    bufferSize = bf_size;
    buffer = new char[bf_size];
    inicioLexema = 0;
    forward = 0;
}

Buffer::~Buffer()
{
    //dtor
}
