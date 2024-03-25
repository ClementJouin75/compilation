//
//  main.cpp
//  compilateur-expression
//
//  Created by Pierre Molinaro on 15/09/2021.
//
//--------------------------------------------------------------------------------------------------

#include "analyse-lexicale.h"
#include "analyse-syntaxique.h"
#include "construction-ast.h"
#include "imprimer-liste-parametres.h"
#include "imprimer-exp-notation-polonaise-inverse.h"
#include "analyse-semantique.h"
#include "generateur-code-cpp.h"
#include "generateur-code-asm.h"
#include "generateur-code-llvm.h"

#include <fstream> // std::ifstream
#include <sstream> // std::stringstream

//--------------------------------------------------------------------------------------------------

int main (int argc, const char * argv[]) {
//--- Vérifier qu'il y a au moins un argument
  if (argc <= 1) {
    std::cout << "Erreur, pas de nom de fichier source\n";
    exit (1) ;
  }
//--- Lecture fichier source
  const std::string sourceFilePath = argv [1] ;
  std::ifstream t (sourceFilePath) ;
  if (!t.good ()) {
    std::cout << "Erreur : impossible d'ouvrir le fichier source\n";
    exit (1) ;
  }
  std::string sourceFileContents ((std::istreambuf_iterator <char> (t)),
                                  std::istreambuf_iterator <char> ()) ;
  std::cout << "Contenu fichier source :\n" << sourceFileContents << "\n" ;
//--- Analyse lexicale
  std::vector <Token> tokenArray = lexicalAnalysis (sourceFileContents) ;
//--- Analyse syntaxique
  syntaxAnalyzer (tokenArray) ;
//--- Construction AST
  AST ast ;
  astBuilder (tokenArray, ast) ;
//--- Imprimer la liste des paramètres
  printParameterList (ast) ;
//--- Imprimer l'expression en notation polonaise inverse
  printExpressionReversePolishNotation (ast) ;
//--- Analyse sémantique
  IR intermediateRepresentation ;
  semanticAnalysis (ast, intermediateRepresentation) ;
//--- Génération de code C++
  generationCodeCpp (intermediateRepresentation, sourceFilePath) ;
//--- Génération de code assembleur Cortex-M4
  generationCodeASM (intermediateRepresentation, sourceFilePath) ;
//--- Génération de code LLVM natif
  generationCodeLLVM (intermediateRepresentation, sourceFilePath) ;
//---
  return 0 ;
}

//--------------------------------------------------------------------------------------------------

//void exempleConstructionArbre (void) {
//  const ExpressionAST * deux = new LiteralIntegerExpressionAST (2) ;
//  const ExpressionAST * trois = new LiteralIntegerExpressionAST (3) ;
//  const ExpressionAST * somme = new BinaryExpressionAST (deux, BinaryOperator::add, trois) ;
//  const ExpressionAST * quatre = new LiteralIntegerExpressionAST (4) ;
//  const ExpressionAST * expression = new BinaryExpressionAST (somme, BinaryOperator::multiply, quatre) ;
//}

//--------------------------------------------------------------------------------------------------
