/////////////////////////////////////////////////////////////////
//
//    SemErrors - Semantic errors for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
////////////////////////////////////////////////////////////////

#pragma once

#include "antlr4-runtime.h"

#include <string>
#include <vector>

// using namespace std;


////////////////////////////////////////////////////////////////
// Class SemErrors: this class contains methods that emit
// semantic error messages with their localization.
// It is used by the semantic visitors:
//   - SymbolsVisitor
//   - TypeCheckVisitor
// Semantic errors emitted are kept in a vector and when the
// typecheck finishes they will be printed (sorted by line/column number)

class SemErrors {

public:

  // Constructor
  SemErrors() = default;

  // Write the semantic errors ordered by line number
  void print ();

  // Accessor to get the number of semantic errors
  std::size_t getNumberOfSemanticErrors () const;

  // Methods that store the error messages
  //   node is the terminal node correspondig to the token IDENT in a declaration
  void declaredIdent                (antlr4::tree::TerminalNode *node);
  //   node is the terminal node correspondig to the token IDENT in an expression
  void undeclaredIdent              (antlr4::tree::TerminalNode *node);
  //   node is the terminal node correspondig to the token ASSIG
  void incompatibleAssignment       (antlr4::tree::TerminalNode *node);
  //   ctx is the node corresponding to the left expression
  void nonReferenceableLeftExpr     (antlr4::ParserRuleContext *ctx);
  //   node is the labeled operator token (referenced by op in the grammar)
  void incompatibleOperator         (antlr4::Token *node);
  //   ctx is the node corresponding to an array access
  void nonArrayInArrayAccess        (antlr4::ParserRuleContext *ctx);
  //   ctx is the node corresponding to the index expression in an array access
  void nonIntegerIndexInArrayAccess (antlr4::ParserRuleContext *ctx);
  //   ctx is the node corresponding to the expression
  void booleanRequired              (antlr4::ParserRuleContext *ctx);
  //   ctx is the node corresponding to the function identifier 
  void isNotCallable                (antlr4::ParserRuleContext *ctx);
  //   ctx is the node corresponding to the function identifier
  //   This error will not be emitted (productive functions can be called as procedures)
  void isNotProcedure               (antlr4::ParserRuleContext *ctx);
  //   ctx is the node corresponding to the identifier
  void isNotFunction                (antlr4::ParserRuleContext *ctx);
  //   ctx is the node corresponding to the function identifier
  void numberOfParameters           (antlr4::ParserRuleContext *ctx);
  //   pCtx is actual parameter node
  //   n is the number of argument starting from 1
  //   cCtc is the call node
  void incompatibleParameter        (antlr4::ParserRuleContext *pCtx,
				     unsigned int n,
				     antlr4::ParserRuleContext *cCtx);
  //   pCtx is actual parameter node
  //   n is the number of argument starting from 1
  //   cCtc is the call node
  void referenceableParameter       (antlr4::ParserRuleContext *pCtx,
				     unsigned int n,
				     antlr4::ParserRuleContext *cCtx);
  //   node is the terminal node correspondig to the token RETURN
  void incompatibleReturn           (antlr4::tree::TerminalNode *node);
  //   ctx is the read or write instruction
  void readWriteRequireBasic        (antlr4::ParserRuleContext *ctx);
  //   ctx is the instruction that needs a referenceable expression
  void nonReferenceableExpression   (antlr4::ParserRuleContext *ctx);
  //   ctx is the program node (grammar start symbol) 
  void noMainProperlyDeclared       (antlr4::ParserRuleContext *ctx);


private:

  class ErrorInfo {
  public:
    ErrorInfo() = delete;
    ErrorInfo(std::size_t line, std::size_t coln, std::string message);
    std::size_t getLine() const;
    std::size_t getColumnInLine() const;
    std::string getMessage() const;
    void print() const;
  private:
    std::size_t line, coln;
    std::string message;
  };

  // List of semantic errors
  std::vector<ErrorInfo> ErrorList;

  // Compare two errors to determine the order (needed in print)
  static bool less(const ErrorInfo & e1, const ErrorInfo & e2);

};  // class SemErrors
