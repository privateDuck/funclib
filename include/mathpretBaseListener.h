
// Generated from mathpret.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "mathpretListener.h"


/**
 * This class provides an empty implementation of mathpretListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  mathpretBaseListener : public mathpretListener {
public:

  virtual void enterInput(mathpretParser::InputContext * /*ctx*/) override { }
  virtual void exitInput(mathpretParser::InputContext * /*ctx*/) override { }

  virtual void enterLine(mathpretParser::LineContext * /*ctx*/) override { }
  virtual void exitLine(mathpretParser::LineContext * /*ctx*/) override { }

  virtual void enterParam_decl(mathpretParser::Param_declContext * /*ctx*/) override { }
  virtual void exitParam_decl(mathpretParser::Param_declContext * /*ctx*/) override { }

  virtual void enterInitializer(mathpretParser::InitializerContext * /*ctx*/) override { }
  virtual void exitInitializer(mathpretParser::InitializerContext * /*ctx*/) override { }

  virtual void enterVar_decl(mathpretParser::Var_declContext * /*ctx*/) override { }
  virtual void exitVar_decl(mathpretParser::Var_declContext * /*ctx*/) override { }

  virtual void enterFunc_decl(mathpretParser::Func_declContext * /*ctx*/) override { }
  virtual void exitFunc_decl(mathpretParser::Func_declContext * /*ctx*/) override { }

  virtual void enterFunc(mathpretParser::FuncContext * /*ctx*/) override { }
  virtual void exitFunc(mathpretParser::FuncContext * /*ctx*/) override { }

  virtual void enterArg_block(mathpretParser::Arg_blockContext * /*ctx*/) override { }
  virtual void exitArg_block(mathpretParser::Arg_blockContext * /*ctx*/) override { }

  virtual void enterExp(mathpretParser::ExpContext * /*ctx*/) override { }
  virtual void exitExp(mathpretParser::ExpContext * /*ctx*/) override { }

  virtual void enterCall(mathpretParser::CallContext * /*ctx*/) override { }
  virtual void exitCall(mathpretParser::CallContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

