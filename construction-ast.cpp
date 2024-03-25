//
//--------------------------------------------------------------------------------------------------
//   CONSTRUCTION AST
//--------------------------------------------------------------------------------------------------

#include "construction-ast.h"
#include "Parser.h"

//--------------------------------------------------------------------------------------------------

static ExpressionAST * expression (Parser & inParser) ;

//--------------------------------------------------------------------------------------------------

static ExpressionAST * facteur (Parser & inParser) {
  ExpressionAST * result = nullptr ;
  if (inParser.test (TokenKind::literalInteger)) {
    result = new LiteralIntegerExpressionAST (inParser.numberValue ()) ;
  }else if (inParser.test (TokenKind::identifier)) {
    result = new IdentifierExpressionAST (inParser.identifierValue ()) ;
  }else{
    inParser.check (TokenKind::leftParenthesis) ;
    result = expression (inParser) ;
    inParser.check (TokenKind::rightParenthesis) ;
  }
  return result ;
}

//--------------------------------------------------------------------------------------------------

static ExpressionAST * suite_facteur (Parser & inParser, ExpressionAST * inLeftExpression) {
  ExpressionAST * result ;
  if (inParser.test (TokenKind::multiply)) {
    ExpressionAST * rightExpression = facteur (inParser) ;
    ExpressionAST * r = new BinaryExpressionAST (inLeftExpression, BinaryOperator::multiply, rightExpression) ;
    result = suite_facteur (inParser, r) ;
  }else if (inParser.test (TokenKind::divide)) {
    ExpressionAST * rightExpression = facteur (inParser) ;
    ExpressionAST * r = new BinaryExpressionAST (inLeftExpression, BinaryOperator::divide, rightExpression) ;
    result = suite_facteur (inParser, r) ;
  }else{
    result = inLeftExpression ;
  }
  return result ;
}

//--------------------------------------------------------------------------------------------------

static ExpressionAST * terme (Parser & inParser) {
  ExpressionAST * exp = facteur (inParser) ;
  return suite_facteur (inParser, exp) ;
}

//--------------------------------------------------------------------------------------------------

static ExpressionAST * suite_terme (Parser & inParser, ExpressionAST * inLeftExpression) {
  ExpressionAST * result = inLeftExpression ;
  if (inParser.test (TokenKind::add)) {
    ExpressionAST * rightExpression = terme (inParser) ;
    ExpressionAST * r = new BinaryExpressionAST (result, BinaryOperator::add, rightExpression) ;
    result = suite_terme (inParser, r) ;
  }else if (inParser.test (TokenKind::subtract)) {
    ExpressionAST * rightExpression = terme (inParser) ;
    ExpressionAST * r = new BinaryExpressionAST (result, BinaryOperator::subtract, rightExpression) ;
    result = suite_terme (inParser, r) ;
  }
  return result ;
}

//--------------------------------------------------------------------------------------------------

static ExpressionAST * expression (Parser & inParser) {
  ExpressionAST * exp = terme (inParser) ;
  return suite_terme (inParser, exp) ;
}

//--------------------------------------------------------------------------------------------------

void astBuilder (const std::vector <Token> & inTokenArray, AST & ioAST) {
  std::cout << "Construction de l'arbre syntaxique abstrait\n" ;
  Parser parser (inTokenArray) ;
  while (parser.test (TokenKind::let)) {
    parser.check (TokenKind::identifier) ;
    ioAST.appendParameter (parser.identifierValue ()) ;
    parser.check (TokenKind::semicolon) ;
  }
  ExpressionAST * e = expression (parser) ;
  ioAST.defineExpression (e) ;
  parser.check (TokenKind::eof) ;
  std::cout << " ok\n" ;
}

//--------------------------------------------------------------------------------------------------
