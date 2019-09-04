using namespace std;
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <cstddef>
#include "../lexical_analyzer/LexicalAnalyzer.h"
#include "SyntacticAnalyzer2.h"

int main(int argc, char* argv[])
{
    string s = argv[1];
    s = s.substr(s.find("/")+1, s.size());
    string fileName = s.substr(0,s.find("."));

    IO *io = new IO(argc,argv);///recebe os argumentos de entrada e passa para o construtor da classe IO

    io->readFile();///realiza a primeira leitura carregando o buffer duplo;
    cout << "Cheguei aquii\n";
    io->printfBuffersContent();
    cout << "Cheguei aquii\n";

    LexicalAnalyzer *la = new LexicalAnalyzer(1,io);
    la->analyze();
    cout << "Cheguei aquii\n";

    string lexical_filename = "LexicalFiles/lex_" + string(fileName) + ".txt";
    ofstream lex_file;
    lex_file.open(lexical_filename.c_str());
    LexicalAnalyzer::setLexicalFile(&lex_file);
    la->saveTokenBuffer();
    lex_file.close();
    cout << "Tokens file generated" << endl;

    //SyntacticAnalyzer* synAnalyzer = new SyntacticAnalyzer(la->tokens, la->tokensNames);
    SyntacticAnalyzer2* synAnalyzer = new SyntacticAnalyzer2(la->getTokenVector(), la);
    synAnalyzer->S();
    synAnalyzer->getSymbolTable().printSymbolTable();

    // string ast_filename = "AstFiles/ast_" + string(fileName) + ".txt";
    // ofstream ast_file;
    // ast_file.open(ast_filename.c_str());
    // Astnode::setAstFile(&ast_file);
    // synAnalyzer->getAstTree().printNode(0); //Print AST
    // ast_file.close();
    // cout << "Ast file generated" << endl;
    //
    // //Generate Dot file
    // ofstream dotfile;
    // string dotfilename = "DotFiles/" + string(fileName) + ".dot";
    // dotfile.open(dotfilename.c_str());
    // Astnode::setDotFile(&dotfile);
    // dotfile << "digraph AST { " << endl;
    // int cont = 0;
    // synAnalyzer->getAstTree().generateDot(0,&cont);
    // dotfile << "}" << endl;
    // dotfile.close();
    // cout << "Dot file generated" << endl;
    //
    // //Generate the svg image
    // string svgfilename = "DotFiles/" + string(fileName) + ".svg";
    // string com = "dot -Tsvg " + dotfilename + " > " + svgfilename;
    // system(com.c_str());
    // cout << "Svg image generated" << endl;
    //
    // synAnalyzer->getAstTree().evaluate(); //Call the interpreter
    // synAnalyzer->getSymbolTable().printSymbolTable(); //Print the symbol table
    // synAnalyzer->getSymbolTable().saveSymbolTable();
    // cout << "Symbol table file generated" << endl;
    //
    // string tac_filename = "TacFiles/tac_" + string(fileName) + ".txt";
    // ofstream tac_file;
    // tac_file.open(tac_filename.c_str());
    // Astnode::setTacFile(&tac_file);
    // synAnalyzer->getAstTree().generateCode(); //Chama o gerador de código de três endereços
    // tac_file.close();
    // cout << "Three address code file generated" << endl;
    //
    // string pythonfilename = "PythonFiles/pythoncode_" + string(fileName) + ".py";
    // ofstream pythonfile;
    // pythonfile.open(pythonfilename.c_str());
    // Astnode::setPythonFile(&pythonfile);
    // pythonfile << "#!/usr/bin/env python3\n# -*- coding: utf-8 -*-\n";
    // synAnalyzer->getAstTree().generatePythonCode(0);
    // pythonfile.close();
    // cout << "Python file generated" << endl;

    delete io;
    delete la;
    delete synAnalyzer;
    return 0;
}
