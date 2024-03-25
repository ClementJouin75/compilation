//--------------------------------------------------------------------------------------------------
//   CONSTRUCTION AST
//--------------------------------------------------------------------------------------------------

#pragma once
#include <map> // std::map
#include "analyse-lexicale.h"

//--------------------------------------------------------------------------------------------------

class ExpressionIR ;

//--------------------------------------------------------------------------------------------------

class ExpressionAST { // Abstract class
//--- Constructeur privé
  protected: ExpressionAST (void) {}

//--- Destructeur virtuel
  public: virtual ~ ExpressionAST (void) {}

//--- Méthodes
  public: virtual void reversePolishNotation (void) const = 0 ;
  public: virtual ExpressionIR *
           buildIR (const std::map <std::string, int> & inParameterMap) const = 0 ;

//--- No copy
  private: ExpressionAST (const ExpressionAST &) = delete ;
  private: ExpressionAST & operator = (const ExpressionAST &) = delete ;
} ;

//--------------------------------------------------------------------------------------------------

enum class BinaryOperator {
  multiply,
  add,
  subtract,
  divide
} ;

//--------------------------------------------------------------------------------------------------

class BinaryExpressionAST : public ExpressionAST {
//--- Constructeur
  public: BinaryExpressionAST (const ExpressionAST * inLeft,
                               const BinaryOperator inOperator,
                               const ExpressionAST * inRight) :
  ExpressionAST (),
  mLeft (inLeft),
  mOperator (inOperator),
  mRight (inRight) {
  }

//--- Méthodes
  public: virtual void reversePolishNotation (void) const override ;
  public: virtual ExpressionIR *
      buildIR (const std::map <std::string, int> & inParameterMap) const override ;

//--- Propriétés privées
  private: const ExpressionAST * mLeft ;
  private: const BinaryOperator mOperator ;
  private: const ExpressionAST * mRight ;
} ;

//--------------------------------------------------------------------------------------------------

class LiteralIntegerExpressionAST : public ExpressionAST {
//--- Constructeur
  public: LiteralIntegerExpressionAST (const uint32_t inLiteralIntegerValue) :
  ExpressionAST (),
  mLiteralIntegerValue (inLiteralIntegerValue) {
  }

//--- Méthodes
  public: virtual void reversePolishNotation (void) const override ;
  public: virtual ExpressionIR * buildIR (const std::map <std::string, int> & inParameterMap) const override ;

//--- Propriété privée
  private: const uint32_t mLiteralIntegerValue ;
} ;

//--------------------------------------------------------------------------------------------------

class IdentifierExpressionAST : public ExpressionAST {
//--- Constructeur
  public: IdentifierExpressionAST (const std::string & inIdentifierValue) :
  ExpressionAST (),
  mIdentifierValue (inIdentifierValue) {
  }

//--- Méthodes
  public: virtual void reversePolishNotation (void) const override ;
  public: virtual ExpressionIR * buildIR (const std::map <std::string, int> & inParameterMap) const override ;

//--- Propriété privée
  private: const std::string mIdentifierValue ;
} ;

//--------------------------------------------------------------------------------------------------

class AST {
//--- Constructeur par défaut
  public: AST (void) :
  mExpression (nullptr),
  mParameterNameArray () {
  }

//--- Ajouter un paramètre
  public: void appendParameter (const std::string & inParameterName) {
    mParameterNameArray.push_back (inParameterName) ;
  }

//--- Définir l'expression
  public: void defineExpression (ExpressionAST * inExpression) {
    mExpression = inExpression ;
  }

//--- Propriétés privées
  private: ExpressionAST * mExpression ;
  private: std::vector <std::string> mParameterNameArray ;

//--- Méthodes constantes
  public: void printParameterList (void) const ;
  public: void printReversePolishNotation (void) const ;
  public: void buildParameterMap (std::map <std::string, int> & outParameterMap) const ;
  public: ExpressionIR * buildIR (const std::map <std::string, int> & inParameterMap)  const ;

//--- Pas de recopie
  private: AST (const AST &) = delete ;
  private: AST & operator = (const AST &) = delete ;
} ;

//--------------------------------------------------------------------------------------------------

void astBuilder (const std::vector <Token> & inTokenArray, AST & ioAST) ;

//--------------------------------------------------------------------------------------------------
