#include "IO.h"
using namespace std;
IO::IO()
{

}

IO::IO(int argc, char* argv[])
{
    if(argc > 1)
    {
        strcpy(fileName,argv[1]);
    }
    else
    {
        cout << "Digite o nome do arquivo de entrada" << endl;
        exit(-1);
    }
    std::ifstream istr(fileName);
    if (istr)
    {
        std::streambuf *pbuf = istr.rdbuf();
        size = pbuf->pubseekoff(0,istr.end);
        pbuf->pubseekoff(0,istr.beg);
        contents = new char [size];
        pbuf->sgetn(contents,size);
        istr.close();
    }
    printf("%s\n",contents);

    count = 0;
    eof_ = 0;
    inicioLexema = 0;
    forward = 0;
    fd = fopen(fileName, "r"); //fd é o file descriptor
    if(fd == NULL)
    {
        printf("Erro! Falha ao abrir o arquivo.\n");
        exit(-1);
    }
}

char* IO::getFileName()
{
  return this->fileName;
}

void IO::openFile()
{
    fd = fopen(fileName, "r"); //fd é o file descriptor
    if(fd == NULL)
    {
        printf("Erro! Falha ao abrir o arquivo.\n");
        exit(-1);
    }
}

void IO::readFile()
{
    // bufferAtual = count % 2;
    // nbytesRead = fread(buffers[bufferAtual],1,BUFFER_SIZE,fd);
    // if((int)nbytesRead == -1)
    // {
    //     printf("Ocorreu um erro na tentativa de leitura do arquivo.\n");
    //     exit(-1);
    // }
    // else if((int)nbytesRead == 0)
    // {
    //     printf("Cheguei ao fim do arquivo nenhuma leitura adicional foi feita.\n");
    // }
    // else
    //     if((int)nbytesRead == BUFFER_SIZE)//tenho que carregar o outro buffer
    //     {
    //         count++;
    //         bufferAtual = count %2;
    //         nbytesRead = fread(buffers[bufferAtual],1,BUFFER_SIZE,fd);
    //         if(nbytesRead == -1)
    //         {
    //             printf("Ocorreu um erro na tentativa de leitura do arquivo.\n");
    //             exit(-1);
    //         }
    //         else if(nbytesRead == 0)
    //         {
    //             printf("Cheguei ao fim do arquivo nenhuma leitura adicional foi feita.\n");
    //         }
    //         count++;
    //         bufferAtual = count %2;
    //     }
    //     else
    //     {
    //         buffers[bufferAtual][nbytesRead] = '$';
    //     }
}

void IO::reloadBuffer()
{
    ///tenho que carregar o buffer que acabou de ser usado
    // forward = 0;
    // nbytesRead = fread(buffers[bufferAtual],1,BUFFER_SIZE,fd);
    // if((int)nbytesRead == -1)
    // {
    //     printf("Ocorreu um erro na tentativa de leitura do arquivo.\n");
    //     exit(-1);
    // }
    // else if((int)nbytesRead == 0)
    // {
    //     printf("Cheguei ao fim do arquivo nenhuma leitura adicional foi feita.\n");
    // }
    // if((int)nbytesRead == BUFFER_SIZE)
    // {
    //     count++;
    //     bufferAtual = count % 2;
    //     forward = 0;
    // }
    // else
    // {
    //     buffers[bufferAtual][nbytesRead] = '$';
    //     count++;
    //     bufferAtual = count % 2;
    //     forward = 0;
    // }
    // printfBuffersContent();
}


int IO::isEOF() const
{
    return eof_;
}

// char c;
// if (forward < BUFFER_SIZE)
// {
//     c = buffers[bufferAtual][forward];
//     if(c == '$')
//         eof_ = 1; //cheguei ao fim da entrada
//     else
//         forward++;
// }
// else {
//     if(!eof_)
//     {
//         reloadBuffer();
//         c = buffers[bufferAtual][forward];
//         if(c == '$')
//             eof_ = 1; //cheguei ao fim da entrada
//         else
//             forward++;
//     }
//     else {
//         c = buffers[bufferAtual][forward];
//         forward++;
//     }
// }
// return c;

char IO::getNextChar()
{
    char c;
    if (forward < size)
    {
        c = contents[forward];
        forward++;
    }
    else
        eof_ = 1;
    return c;
}

void IO::retract()
{
}

void IO::printfBuffersContent()
{
    // int i, count = 0;
    // //Buffer* b;
    // for(std::vector<char*>::iterator it = buffers.begin(); it != buffers.end(); ++it)
    // {
    //     printf("\n --------------//------------------ \n  Conteudo do buffer %d\n", count%2);
    //     count++;
    //     printf("%s\n", (*it));
    //     // for(i = 0; i < b->bufferSize; i++)
    //     // {
    //     //     printf("%c", b->buffer[i]);
    //     // }
    // }
    // printf("\n");
}

void free_(char* b)
{
    //free(b);
}

IO::~IO()
{
    //for_each(buffers.begin(),buffers.end(), free_);
}
