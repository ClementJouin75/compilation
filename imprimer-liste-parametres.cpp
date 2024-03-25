//--------------------------------------------------------------------------------------------------
// IMPRIMER LA LISTE DES PARAMÈTRES
//--------------------------------------------------------------------------------------------------

#include "imprimer-liste-parametres.h"

//--------------------------------------------------------------------------------------------------

void AST::printParameterList (void) const {
  for (size_t i = 0 ; i < mParameterNameArray.size () ; i++) {
    std::cout << " " << mParameterNameArray [i] ;
  }
  std::cout << "\n" ;
}

//--------------------------------------------------------------------------------------------------

void printParameterList (const AST & inAST) {
  std::cout << "Liste des paramètres\n" ;
  inAST.printParameterList () ;
}

//--------------------------------------------------------------------------------------------------
