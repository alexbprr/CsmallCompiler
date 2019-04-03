#include "IO.h"
using namespace std;
IO::IO()
{

}

IO::IO(int argc, char* argv[])
{
    count = 0;
    eof_ = 0;
    printf("Tamanho do buffer %d. \n", BUFFER_SIZE);
    Buffer* buffer0 = new Buffer(BUFFER_SIZE);
    Buffer* buffer1 = new Buffer(BUFFER_SIZE);
    bufferes.push_back(buffer0);
    bufferes.push_back(buffer1);
    bufferes[0]->forward = 0;
    bufferes[1]->forward = 0;

    if(argc > 1)
    {
        fileName = (char*)malloc(sizeof(argv[1]));
        strcpy(fileName,argv[1]);
        printf("O nome do arquivo de entrada é %s\n", fileName);
    }
    else
    {
        fileName = (char*)malloc(sizeof("teste1.c"));
        strcpy(fileName,"teste1.c");
        printf("O nome do arquivo de entrada é %s\n", fileName);
    }
}

char* IO::getFileName()
{
  //std::string aux(this->fileName);
  //return aux;
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
    bufferAtual = count % 2;
    nbytesRead = fread(bufferes[bufferAtual]->buffer,1,BUFFER_SIZE,fd);
    if((int)nbytesRead == -1)
    {
        printf("Ocorreu um erro na tentativa de leitura do arquivo.\n");
        exit(-1);
    }
    else if((int)nbytesRead == 0)
    {
        printf("Cheguei ao fim do arquivo nenhuma leitura adicional foi feita.\n");
    }
    else
        if((int)nbytesRead == BUFFER_SIZE)//tenho que carregar o outro buffer
        {
            count++;
            bufferAtual = count %2;
            nbytesRead = fread(bufferes[bufferAtual]->buffer,1,BUFFER_SIZE,fd);
            if(nbytesRead == -1)
            {
                printf("Ocorreu um erro na tentativa de leitura do arquivo.\n");
                exit(-1);
            }
            else if(nbytesRead == 0)
            {
                printf("Cheguei ao fim do arquivo nenhuma leitura adicional foi feita.\n");
            }
            count++;
            bufferAtual = count %2;
        }
        else
        {
            bufferes[bufferAtual]->buffer[nbytesRead] = '$';
        }
}

void IO::reloadBuffer()
{
    ///tenho que carregar o buffer que acabou de ser usado
    bufferes[bufferAtual]->forward = 0;
    nbytesRead = fread(bufferes[bufferAtual]->buffer,1,BUFFER_SIZE,fd);
    if((int)nbytesRead == -1)
    {
        printf("Ocorreu um erro na tentativa de leitura do arquivo.\n");
        exit(-1);
    }
    else if((int)nbytesRead == 0)
    {
        printf("Cheguei ao fim do arquivo nenhuma leitura adicional foi feita.\n");
    }
    if((int)nbytesRead == BUFFER_SIZE)
    {
        count++;
        bufferAtual = count % 2;
        bufferes[bufferAtual]->forward = 0;
    }
    else
    {
        bufferes[bufferAtual]->buffer[nbytesRead] = '$';
        count++;
        bufferAtual = count % 2;
        bufferes[bufferAtual]->forward = 0;
    }
    printfBuffersContent();
}


int IO::isEOF()
{
    return eof_;
}

char IO::getNextChar()
{
    char c;
    if(bufferes[bufferAtual]->forward < BUFFER_SIZE)
    {
        c = bufferes[bufferAtual]->buffer[bufferes[bufferAtual]->forward];
        if(c == '$')
            eof_ = 1; //cheguei ao fim da entrada
        else
            bufferes[bufferAtual]->forward++;
    }
    else {
        if(!eof_)
        {
            reloadBuffer();
            c = bufferes[bufferAtual]->buffer[bufferes[bufferAtual]->forward];
            if(c == '$')
                eof_ = 1; //cheguei ao fim da entrada
            else
                bufferes[bufferAtual]->forward++;
        }
        else {
            c = bufferes[bufferAtual]->buffer[bufferes[bufferAtual]->forward];
            bufferes[bufferAtual]->forward++;
        }
    }
    return c;
}

void IO::retract()
{
    if(bufferes[bufferAtual]->forward > 0)
        bufferes[bufferAtual]->forward--;
    else
    {
        bufferes[bufferAtual]->forward = 0;
        count++;
        bufferAtual = count % 2;
        bufferes[bufferAtual]->forward = BUFFER_SIZE-1;
    }
}

void IO::printfBuffersContent()
{
    int i, count = 0;
    Buffer* b;
    for(std::vector<Buffer*>::iterator it = bufferes.begin(); it != bufferes.end(); ++it)
    {
        b = (Buffer*)*it;
        printf("\n --------------//------------------ \n  Conteudo do buffer %d\n", count%2);
        count++;
        for(i = 0; i < b->bufferSize; i++)
        {
            printf("%c", b->buffer[i]);
        }
    }
    printf("\n");
}

IO::~IO()
{
    //dtor
}
