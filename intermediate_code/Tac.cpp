using namespace std;
#include "Tac.h"

Tac::Tac(){}

Tac::Tac(int format, Operand* dst, Operand* src1, Operand* src2)
{
    this->format = format;
    this->dst = dst;
    this->src1 = src1;
    this->src2 = src2;
}
Tac::Tac(int format, Label* dstGoto, Operand* src1, Operand* src2)
{
    this->format = format;
    this->dstGoto = dstGoto;
    this->src1 = src1;
    this->src2 = src2;
}

void Tac::setLabel(Label* label)
{
    this->label = label;
}
