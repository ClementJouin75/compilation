//--------------------------------------------------------------------------------------------------
// CLASSE PARSER
//--------------------------------------------------------------------------------------------------

#include "Parser.h"

//--------------------------------------------------------------------------------------------------

Parser::Parser (const std::vector <Token> & inTokenArray) :
mInputTokenArray (inTokenArray),
mAcceptedTokenKindArray (),
mTokenIndex (0),
mFetchNextToken (false) {
}

//--------------------------------------------------------------------------------------------------

void Parser::goToNextToken (void) {
  if (mFetchNextToken) {
    mTokenIndex += 1 ;
    mAcceptedTokenKindArray.clear () ;
    if (mTokenIndex >= mInputTokenArray.size ()) {
      mTokenIndex = mInputTokenArray.size () - 1 ;
    }
    mFetchNextToken = false ;
  }
}

//--------------------------------------------------------------------------------------------------

bool Parser::test (const TokenKind inKind) {
  goToNextToken () ;
  const bool testOk = inKind == mInputTokenArray [mTokenIndex].mKind ;
  if (testOk) {
    mFetchNextToken = true ;
  }else{
    mAcceptedTokenKindArray.push_back (inKind) ;
  }
  return testOk ;
}

//--------------------------------------------------------------------------------------------------

void Parser::check (const TokenKind inKind) {
  goToNextToken () ;
  const bool checkOk = inKind == mInputTokenArray [mTokenIndex].mKind ;
  if (!checkOk) {
    std::cout << "Erreur syntaxique ligne " << line () << ", colonne " << column () << " :\n" ;
    std::cout << "  - token courant '" << displayName (mInputTokenArray [mTokenIndex].mKind) << "'\n" ;
    std::cout << "  - tokens acceptés :\n" ;
    mAcceptedTokenKindArray.push_back (inKind) ;
    for (unsigned i = 0 ; i < mAcceptedTokenKindArray.size () ; i ++) {
      std::cout << "    - '" << displayName (mAcceptedTokenKindArray [i]) << "'\n" ;
    }
    exit (1) ;
  }
  mFetchNextToken = true ;
}

//--------------------------------------------------------------------------------------------------
