//--------------------------------------------------------------------------------------------------
// CLASSE PARSER
//--------------------------------------------------------------------------------------------------

#pragma once

//--------------------------------------------------------------------------------------------------

#include "analyse-lexicale.h"

//--------------------------------------------------------------------------------------------------

class Parser {
//--- Constructeur dédié
  public: Parser (const std::vector <Token> & inTokenArray) ;

//--- Méthodes d'analyse
  public: bool test (const TokenKind inKind) ;
  public: void check (const TokenKind inKind) ;

//--- Accesseurs du token courant
  public: uint32_t numberValue (void) const { return mInputTokenArray [mTokenIndex].mNumberValue ; }
  public: std::string identifierValue (void) const { return mInputTokenArray [mTokenIndex].mIdentifierValue ; }
  public: int line (void) const { return mInputTokenArray [mTokenIndex].mLine ; }
  public: int column (void) const { return mInputTokenArray [mTokenIndex].mColumn ; }

//--- Propriétées privées
  private: const std::vector <Token> mInputTokenArray ;
  private: std::vector <TokenKind> mAcceptedTokenKindArray ;
  private: unsigned long mTokenIndex ;
  private: bool mFetchNextToken ;

//--- Méthode privée
  private: void goToNextToken (void) ;

//--- Interdire la copie
  private: Parser (const Parser &) = delete ;
  private: Parser & operator = (const Parser &) = delete ;
} ;

//--------------------------------------------------------------------------------------------------
