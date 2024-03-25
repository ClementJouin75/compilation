//--------------------------------------------------------------------------------------------------
//   ANALYSE LEXICALE
//--------------------------------------------------------------------------------------------------

#include "analyse-lexicale.h"

//--------------------------------------------------------------------------------------------------
//   Classe Token
//--------------------------------------------------------------------------------------------------

Token::Token (void) :
mKind (TokenKind::eof),
mNumberValue (0),
mIdentifierValue (),
mLine (0),
mColumn (0) {
}

//--------------------------------------------------------------------------------------------------

Token::Token (const uint32_t inNumberValue,
              const int inLine,
              const int inColumn) :
mKind (TokenKind::literalInteger),
mNumberValue (inNumberValue),
mIdentifierValue (),
mLine (inLine),
mColumn (inColumn) {
}

//--------------------------------------------------------------------------------------------------

Token::Token (const std::string & inIdentifierValue,
              const int inLine,
              const int inColumn) :
mKind (TokenKind::identifier),
mNumberValue (0),
mIdentifierValue (inIdentifierValue),
mLine (inLine),
mColumn (inColumn) {
}

//--------------------------------------------------------------------------------------------------

Token::Token (const TokenKind inKind,
              const int inLine,
              const int inColumn) :
mKind (inKind),
mNumberValue (0),
mIdentifierValue (),
mLine (inLine),
mColumn (inColumn) {
}

//--------------------------------------------------------------------------------------------------

void Token::print (void) const {
  std::cout << "line " << mLine << ", column " << mColumn << ", " << displayName (mKind) ;
  if (mKind == TokenKind::literalInteger) {
    std::cout << " " << mNumberValue ;
  }else if (mKind == TokenKind::identifier) {
    std::cout << " '" << mIdentifierValue << "'" ;
  }
}

//--------------------------------------------------------------------------------------------------

std::string displayName (const TokenKind inTokenKind) {
  std::string result ;
  switch (inTokenKind) {
  case TokenKind::literalInteger :
    result = "literal integer" ;
    break ;
  case TokenKind::identifier :
    result = "identifier" ;
    break ;
  case TokenKind::multiply :
    result = "multiply" ;
    break ;
  case TokenKind::add :
    result = "add" ;
    break ;
  case TokenKind::subtract :
    result = "subtract" ;
    break ;
  case TokenKind::divide :
    result = "divide" ;
    break ;
  case TokenKind::leftParenthesis :
    result = "left parenthesis" ;
    break ;
  case TokenKind::rightParenthesis :
    result = "right parenthesis" ;
    break ;
  case TokenKind::let :
    result = "let" ;
    break ;
  case TokenKind::semicolon :
    result = "semicolon" ;
    break ;
  case TokenKind::eof :
    result = "eof" ;
    break ;
  }
  return result ;
}

//--------------------------------------------------------------------------------------------------
//   Analyse lexicale
//--------------------------------------------------------------------------------------------------

std::vector <Token> lexicalAnalysis (const std::string & inSourceString) {
  std::vector <Token> tokenArray ;
//---
  unsigned idx = 0 ;
  int line = 1 ;
  int column = 1 ;
  while (idx < inSourceString.size ()) {
    const char c = inSourceString [idx] ;
    idx += 1 ;
    const int startColumn = column ;
    column += 1 ;
    if (c == '*') {
      tokenArray.push_back (Token (TokenKind::multiply, line, startColumn)) ;
    }else if (c == '+') {
      tokenArray.push_back (Token (TokenKind::add, line, startColumn)) ;
    }else if (c == '-') {
      tokenArray.push_back (Token (TokenKind::subtract, line, startColumn)) ;
    }else if (c == '/') {
      tokenArray.push_back (Token (TokenKind::divide, line, startColumn)) ;
    }else if (c == '(') {
      tokenArray.push_back (Token (TokenKind::leftParenthesis, line, startColumn)) ;
    }else if (c == ')') {
      tokenArray.push_back (Token (TokenKind::rightParenthesis, line, startColumn)) ;
    }else if (c == ';') {
      tokenArray.push_back (Token (TokenKind::semicolon, line, startColumn)) ;
    }else if (c == ' ') {
      // Séparateur, rien à faire à part avancer
    }else if (c == '\n') {
      line += 1 ;
      column = 1 ;
    }else if ((c >= '0') && (c <= '9')) { // Constante litérale entière
      uint32_t integerValue = uint32_t (c) - uint32_t ('0') ;
      bool loop = true ;
      while (loop && (idx < inSourceString.size ())) {
        const char cc = inSourceString [idx] ;
        idx += 1 ;
        column += 1 ;
        if ((cc >= '0') && (cc <= '9')) {
          integerValue *= 10 ;
          integerValue += uint32_t (cc) - uint32_t ('0') ;
        }else{
          loop = false ;
          idx -= 1 ;
          column -= 1 ;
        }
      }
      tokenArray.push_back (Token (integerValue, line, startColumn)) ;
    }else if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))) { // Identificateur
      std::string identifierValue ;
      identifierValue += c ;
      bool loop = true ;
      while (loop && (idx < inSourceString.size ())) {
        const char cc = inSourceString [idx] ;
        idx += 1 ;
        column += 1 ;
        if (((cc >= 'A') && (cc <= 'Z')) || ((cc >= 'a') && (cc <= 'z'))) {
          identifierValue += cc ;
        }else{
          loop = false ;
          idx -= 1 ;
          column -= 1 ;
        }
      }
      if (identifierValue == "let") {
        tokenArray.push_back (Token (TokenKind::let, line, startColumn)) ;
      }else{
        tokenArray.push_back (Token (identifierValue, line, startColumn)) ;
      }
    }else{ // Erreur, caractère inconnu
      std::cout << "Error, unknown character\n" ;
      exit (1) ;
    }
  }
//--- Ajouter eof
  tokenArray.push_back (Token (TokenKind::eof, line, column)) ;
//--- Imprimer la liste des tokens
  std::cout << "Token array\n" ;
  for (unsigned i = 0 ; i < tokenArray.size () ; i ++) {
    const Token t = tokenArray [i] ;
    std::cout << "  " << i << ": " ;
    t.print () ;
    std::cout << "\n" ;
  }
//---
  return tokenArray ;
}

//--------------------------------------------------------------------------------------------------
