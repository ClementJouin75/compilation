//--------------------------------------------------------------------------------------------------
//   ANALYSE SYNTAXIQUE
//--------------------------------------------------------------------------------------------------

#include "analyse-syntaxique.h"
#include "Parser.h"

//--------------------------------------------------------------------------------------------------

static void expression (Parser & inParser) ;

//--------------------------------------------------------------------------------------------------

static void facteur (Parser & inParser) {
  if (inParser.test (TokenKind::literalInteger)) {

  }else if (inParser.test (TokenKind::identifier)) {

  }else{
    inParser.check (TokenKind::leftParenthesis) ;
    expression (inParser) ;
    inParser.check (TokenKind::rightParenthesis) ;
  }
}

//--------------------------------------------------------------------------------------------------

static void suite_facteur (Parser & inParser) {
  if (inParser.test (TokenKind::multiply)) {
    facteur (inParser) ;
    suite_facteur (inParser) ;
  }else if (inParser.test (TokenKind::divide)) {
    facteur (inParser) ;
    suite_facteur (inParser) ;
  }
}

//--------------------------------------------------------------------------------------------------

static void terme (Parser & inParser) {
  facteur (inParser) ;
  suite_facteur (inParser) ;
}

//--------------------------------------------------------------------------------------------------

static void suite_terme (Parser & inParser) {
  if (inParser.test (TokenKind::add)) {
    terme (inParser) ;
    suite_terme (inParser) ;
  }else if (inParser.test (TokenKind::subtract)) {
    terme (inParser) ;
    suite_terme (inParser) ;
  }
}

//--------------------------------------------------------------------------------------------------

static void expression (Parser & inParser) {
  terme (inParser) ;
  suite_terme (inParser) ;
}

//--------------------------------------------------------------------------------------------------

void syntaxAnalyzer (const std::vector <Token> & inTokenArray) {
  std::cout << "Analyse syntaxique\n" ;
  Parser parser (inTokenArray) ;
  while (parser.test (TokenKind::let)) {
    parser.check (TokenKind::identifier) ;
    parser.check (TokenKind::semicolon) ;
  }
  expression (parser) ;
  parser.check (TokenKind::eof) ;
  std::cout << " ok\n" ;
}

//--------------------------------------------------------------------------------------------------
