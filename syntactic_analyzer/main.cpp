using namespace std;
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <cstddef>
#include "../lexical_analyzer/LexicalAnalyzer.h"
#include "SyntacticAnalyzer.h"

int main(int argc, char* argv[])
{
    IO *io = new IO(argc,argv);///recebe os argumentos de entrada e passa para o construtor da classe IO
    io->openFile(); ///abre o arquivo de entrada
    io->readFile();///realiza a primeira leitura carregando o buffer duplo;
    io->printfBuffersContent();

    string s = argv[1];
    s = s.substr(s.find("/")+1, s.size());
    string fileName = s.substr(0,s.find("."));

    LexicalAnalyzer *la = new LexicalAnalyzer(1,io);
    la->analyze();
    la->tokens.push_back(new Token("EOF", 0, EOF));
    la->printTokenBuffer();
    string lexical_filename = "testes_lexico/saida_" + string(fileName) + ".txt";
    cout << lexical_filename << endl;
    ofstream lex_file;
    lex_file.open(lexical_filename.c_str());
    LexicalAnalyzer::setLexicalFile(&lex_file);
    la->saveTokenBuffer();
    lex_file.close();

    //SyntacticAnalyzer* synAnalyzer = new SyntacticAnalyzer(la->tokens, la->tokensNames);
    SyntacticAnalyzer* synAnalyzer = new SyntacticAnalyzer(la->tokens, la);
    synAnalyzer->Programa();
    synAnalyzer->symbolTable->printSymbolTable();

    string ast_filename = "AstFiles/ast_" + string(fileName) + ".txt";
    ofstream ast_file;
    ast_file.open(ast_filename.c_str());
    Astnode::setAstFile(&ast_file);
    synAnalyzer->astTree->printNode(0); //Imprime a AST
    ast_file.close();

    //Gera Dot file
    ofstream dotfile;
    string dotfilename = "DotFiles/" + string(fileName) + ".dot";
    dotfile.open(dotfilename.c_str());
    Astnode::setDotFile(&dotfile);
    dotfile << "digraph AST { " << endl;
    int cont = 0;
    synAnalyzer->astTree->generateDot(0,&cont);
    dotfile << "}" << endl;
    dotfile.close();

    synAnalyzer->astTree->evaluate(); //Chama o interpretador
    synAnalyzer->symbolTable->printSymbolTable(); //Imprime a tabela de símbolos

    string tac_filename = "TacFiles/three_address_code_" + string(fileName) + ".txt";
    ofstream tac_file;
    tac_file.open(tac_filename.c_str());
    Astnode::setTacFile(&tac_file);
    //synAnalyzer->astTree->generateCode(); //Chama o gerador de código de três endereços
    tac_file.close();

    string pythonfilename = "PythonFiles/pythoncode_" + string(fileName) + ".py";
    ofstream pythonfile;
    pythonfile.open(pythonfilename.c_str());
    Astnode::setPythonFile(&pythonfile);
    pythonfile << "#!/usr/bin/env python3\n# -*- coding: utf-8 -*-\n";
    synAnalyzer->astTree->generatePythonCode(0);
    pythonfile.close();
    return 0;
}
