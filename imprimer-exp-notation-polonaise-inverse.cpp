//--------------------------------------------------------------------------------------------------
// IMPRIMER L'EXPRESSION EN NOTATION POLONAISE INVERSE'
//--------------------------------------------------------------------------------------------------

#include "imprimer-exp-notation-polonaise-inverse.h"

//--------------------------------------------------------------------------------------------------

void IdentifierExpressionAST::reversePolishNotation (void) const {
  std::cout << " " << mIdentifierValue ;
}

//--------------------------------------------------------------------------------------------------

void LiteralIntegerExpressionAST::reversePolishNotation (void) const {
  std::cout << " " << mLiteralIntegerValue ;
}

//--------------------------------------------------------------------------------------------------

void BinaryExpressionAST::reversePolishNotation (void) const {
  mLeft->reversePolishNotation () ;
  mRight->reversePolishNotation () ;
  switch (mOperator) {
  case BinaryOperator::multiply :
    std::cout << " *" ;
    break ;
  case BinaryOperator::add :
    std::cout << " +" ;
    break ;
  case BinaryOperator::subtract :
    std::cout << " -" ;
    break ;
  case BinaryOperator::divide :
    std::cout << " /" ;
    break ;
  }
}

//--------------------------------------------------------------------------------------------------

void AST::printReversePolishNotation (void) const {
  mExpression->reversePolishNotation () ;
  std::cout << "\n" ;
}

//--------------------------------------------------------------------------------------------------

void printExpressionReversePolishNotation (const AST & inAST) {
  std::cout << "Expression en notation polonaise inverse\n" ;
  inAST.printReversePolishNotation () ;
}

//--------------------------------------------------------------------------------------------------
