 #ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include "IO.h"
#include "Token.h"

using namespace std;

class LexicalAnalyzer
{
    private:
        void returnToInitialState();
    public:
        std::string tokensNames[N];
        map<std::string,int> reservedWords;
        vector<Token*> tokens;
        vector<string> lexemaBuffer;
        string lexema;
        vector<int> linesEndings;
        bool eof; //=false
        bool useLastChar;
        int state;//=1
        int tokenBufferIndex; //= 0
        int lineNumber; //= 0
        IO *io;
        int value;
        static ofstream *lexical_file;

        LexicalAnalyzer();
        LexicalAnalyzer(int s, IO *io_);
        virtual ~LexicalAnalyzer();
        static void setLexicalFile(ofstream *lexical_file);
        void state1(char c);
        void state2(char c);
        void state4(char c);
        void analyze();
        void printSymbolTable();
        void printTokenBuffer();
        void saveTokenBuffer();
};

#endif // LEXICALANALYZER_H
