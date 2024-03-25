//--------------------------------------------------------------------------------------------------
//   ANALYSE SÉMANTIQUE
//--------------------------------------------------------------------------------------------------

#include "analyse-semantique.h"

//--------------------------------------------------------------------------------------------------

void AST::buildParameterMap (std::map <std::string, int> & outParameterMap) const {
  for (unsigned i = 0 ; i < mParameterNameArray.size () ; i++) {
    const std::string parameterName = mParameterNameArray [i] ;
    const auto pair = std::make_pair (parameterName, i) ;
    if (outParameterMap.insert (pair).second == false) {
      std::cout << "Erreur sémantique, double définition du paramètre '"
                << parameterName << "'\n" ;
      exit (1) ;
    }
  }
}

//--------------------------------------------------------------------------------------------------

ExpressionIR * BinaryExpressionAST::buildIR (const std::map <std::string, int> & inParameterMap) const {
  ExpressionIR * left = mLeft->buildIR (inParameterMap) ;
  ExpressionIR * right = mRight->buildIR (inParameterMap) ;
  return new BinaryExpressionIR (left, mOperator, right) ;
}

//--------------------------------------------------------------------------------------------------

ExpressionIR * LiteralIntegerExpressionAST::buildIR (const std::map <std::string, int> & /* inParameterMap */) const {
  return new LiteralIntegerExpressionIR (mLiteralIntegerValue) ;
}

//--------------------------------------------------------------------------------------------------

ExpressionIR * IdentifierExpressionAST::buildIR (const std::map <std::string, int> & inParameterMap) const {
  auto iterator = inParameterMap.find (mIdentifierValue) ;
  if (iterator == inParameterMap.end ()) {
    std::cout << "Erreur sémantique, le paramètre '" << mIdentifierValue << "' n'existe pas\n" ;
    exit (1) ;
  }
  const int parameterIndex = iterator->second ;
  return new IdentifierExpressionIR (parameterIndex) ;
}

//--------------------------------------------------------------------------------------------------

ExpressionIR * AST::buildIR (const std::map <std::string, int> & inParameterMap) const {
  return mExpression->buildIR (inParameterMap) ;
}

//--------------------------------------------------------------------------------------------------

void semanticAnalysis (const AST & inAST, IR & outIR) {
  std::cout << "Analyse sémantique\n" ;
//--- Construction de la table des identificateurs
  std::map <std::string, int> parameterMap ;
  inAST.buildParameterMap (parameterMap) ;
  outIR.defineParameterCount (parameterMap.size ()) ;
//--- Construction de l'arbre syntaxique décoré
  ExpressionIR * expression = inAST.buildIR (parameterMap) ;
  outIR.defineExpression (expression) ;
}

//--------------------------------------------------------------------------------------------------
