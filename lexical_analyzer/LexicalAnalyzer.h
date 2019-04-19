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
        void state1(char c);
        void state2(char c);
        void state4(char c);
        void printTokenBuffer();
        std::string *tokensNames;
        map<std::string,int> reservedWords;
        map<int,std::string> lexemaNames;
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
    public:
        LexicalAnalyzer();
        LexicalAnalyzer(int s, IO *io_);
        virtual ~LexicalAnalyzer();
        std::vector<Token*> getTokenVector() const;
        std::string* getTokensNames() const;
        //map<int,std::string> getLexemaNames() const;
        std::string getLexema(const int &token);
        static void setLexicalFile(ofstream *lexical_file);
        void analyze();
        void printSymbolTable();
        void saveTokenBuffer();
};

#endif // LEXICALANALYZER_H
