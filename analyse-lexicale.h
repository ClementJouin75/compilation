//--------------------------------------------------------------------------------------------------
//   ANALYSE LEXICALE
//--------------------------------------------------------------------------------------------------

#pragma once

//--------------------------------------------------------------------------------------------------

//#include <stdint.h>
#include <iostream> // std::cout
#include <string> // std::string
#include <vector> // std::vector

//--------------------------------------------------------------------------------------------------

enum class TokenKind {
  literalInteger,
  identifier,
  multiply,
  add,
  subtract,
  divide,
  leftParenthesis,
  rightParenthesis,
  let,
  semicolon, // ;
  eof
} ;

//--------------------------------------------------------------------------------------------------

std::string displayName (const TokenKind inTokenKind) ;

//--------------------------------------------------------------------------------------------------

class Token {
  public: const TokenKind mKind ;
  public: const uint32_t mNumberValue ; // Pour TokenKind::literalInteger, sinon toujours à 0
  public: const std::string mIdentifierValue ; // Pour TokenKind::identifier, sinon toujours à chaîne vide
  public: const int mLine ;
  public: const int mColumn ;

//--- Constructeur par défaut
  public: Token (void) ;

//--- Constructeur pour token TokenKind::number
  public: Token (const uint32_t inNumberValue, const int inLine, const int inColumn) ;

//--- Constructeur pour token TokenKind::identifier
  public: Token (const std::string & inIdentifierValue, const int inLine, const int inColumn) ;

//--- Constructeur pour token sans valeur associée
  public: Token (const TokenKind inKind, const int inLine, const int inColumn) ;

//--- Impression sur std::cout
  public: void print (void) const ;
} ;

//--------------------------------------------------------------------------------------------------
//   Analyse lexicale
//--------------------------------------------------------------------------------------------------

std::vector <Token> lexicalAnalysis (const std::string & inSourceString) ;

//--------------------------------------------------------------------------------------------------
