//--------------------------------------------------------------------------------------------------
//   ANALYSE SÉMANTIQUE
//--------------------------------------------------------------------------------------------------

#pragma once
#include "construction-ast.h"

//--------------------------------------------------------------------------------------------------

class ExpressionIR { // Abstract class
//--- Constructeur privé
  protected: ExpressionIR (void) {}

//--- Destructeur virtuel
  public: virtual ~ ExpressionIR (void) {}

//--- Méthodes
//  public: virtual void generateCpp (std::string & ioString) const = 0 ;
//  public: virtual void generateASM (std::string & ioString, const int inRegisterIndex) const = 0 ;
//  public: virtual std::string generateLLVM (std::string & ioString, int & ioLocalVarIndex) const = 0 ;

//--- No copy
  private: ExpressionIR (const ExpressionIR &) = delete ;
  private: ExpressionIR & operator = (const ExpressionIR &) = delete ;
} ;

//--------------------------------------------------------------------------------------------------

class BinaryExpressionIR : public ExpressionIR {
//--- Constructeur
  public: BinaryExpressionIR (ExpressionIR * inLeft, const BinaryOperator inOperator, ExpressionIR * inRight) :
  ExpressionIR (),
  mLeft (inLeft),
  mOperator (inOperator),
  mRight (inRight) {
  }

//--- Méthode
//  public: virtual void generateCpp (std::string & ioString) const override ;
//  public: virtual void generateASM (std::string & ioString, const int inRegisterIndex) const override ;
//  public: virtual std::string generateLLVM (std::string & ioString, int & ioLocalVarIndex) const override ;

//--- Propriétés privées
  private: const ExpressionIR * mLeft ;
  private: const BinaryOperator mOperator ;
  private: const ExpressionIR * mRight ;
} ;

//--------------------------------------------------------------------------------------------------

class LiteralIntegerExpressionIR : public ExpressionIR {
//--- Constructeur
  public: LiteralIntegerExpressionIR (const uint32_t inLiteralIntegerValue) :
  ExpressionIR (),
  mLiteralIntegerValue (inLiteralIntegerValue) {
  }

//--- Méthodes
//  public: virtual void generateCpp (std::string & ioString) const override ;
//  public: virtual void generateASM (std::string & ioString, const int inRegisterIndex) const override ;
//  public: virtual std::string generateLLVM (std::string & ioString, int & ioLocalVarIndex) const override ;

//--- Propriété privée
  private: const uint32_t mLiteralIntegerValue ;
} ;

//--------------------------------------------------------------------------------------------------

class IdentifierExpressionIR : public ExpressionIR {
//--- Constructeur
  public: IdentifierExpressionIR (const int inParameterIndex) :
  ExpressionIR (),
  mParameterIndex (inParameterIndex) {
  }

//--- Méthodes
//  public: virtual void generateCpp (std::string & ioString) const override ;
//  public: virtual void generateASM (std::string & ioString, const int inRegisterIndex) const override ;
//  public: virtual std::string generateLLVM (std::string & ioString, int & ioLocalVarIndex) const override ;

//--- Propriété privée
  private: const int mParameterIndex ;
} ;

//--------------------------------------------------------------------------------------------------

class IR {
//--- Constructeur par défaut
  public: IR (void) :
  mExpression (nullptr),
  mParameterCount (0) {
  }

//--- Définir l'expression
  public: void defineExpression (ExpressionIR * inExpression) {
    mExpression = inExpression ;
  }

//--- Définir le nombre de parametres
  public: void defineParameterCount (const unsigned long inParameterCount) {
    mParameterCount = inParameterCount ;
  }

//--- Propriétés privées
  private: ExpressionIR * mExpression ;
  private: unsigned long mParameterCount ;

//--- Méthodes constantes
  public: unsigned long parameterCount (void) const { return mParameterCount ; }
  public: void generateExpressionCpp (std::string & ioString) const ;
  public: void generateExpressionASM (std::string & ioString) const ;
  public: std::string generateExpressionLLVM (std::string & ioString) const ;

//--- Pas de recopie
  private: IR (const IR &) = delete ;
  private: IR & operator = (const IR &) = delete ;
} ;

//--------------------------------------------------------------------------------------------------
//   ANALYSE SÉMANTIQUE
//--------------------------------------------------------------------------------------------------

void semanticAnalysis (const AST & inAST, IR & outIR) ;

//--------------------------------------------------------------------------------------------------
