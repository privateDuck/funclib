
// Generated from mathpret.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "mathpretParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by mathpretParser.
 */
class  mathpretListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterInput(mathpretParser::InputContext *ctx) = 0;
  virtual void exitInput(mathpretParser::InputContext *ctx) = 0;

  virtual void enterLine(mathpretParser::LineContext *ctx) = 0;
  virtual void exitLine(mathpretParser::LineContext *ctx) = 0;

  virtual void enterParam_decl(mathpretParser::Param_declContext *ctx) = 0;
  virtual void exitParam_decl(mathpretParser::Param_declContext *ctx) = 0;

  virtual void enterInitializer(mathpretParser::InitializerContext *ctx) = 0;
  virtual void exitInitializer(mathpretParser::InitializerContext *ctx) = 0;

  virtual void enterVar_decl(mathpretParser::Var_declContext *ctx) = 0;
  virtual void exitVar_decl(mathpretParser::Var_declContext *ctx) = 0;

  virtual void enterFunc_decl(mathpretParser::Func_declContext *ctx) = 0;
  virtual void exitFunc_decl(mathpretParser::Func_declContext *ctx) = 0;

  virtual void enterFunc(mathpretParser::FuncContext *ctx) = 0;
  virtual void exitFunc(mathpretParser::FuncContext *ctx) = 0;

  virtual void enterArg_block(mathpretParser::Arg_blockContext *ctx) = 0;
  virtual void exitArg_block(mathpretParser::Arg_blockContext *ctx) = 0;

  virtual void enterExp(mathpretParser::ExpContext *ctx) = 0;
  virtual void exitExp(mathpretParser::ExpContext *ctx) = 0;

  virtual void enterCall(mathpretParser::CallContext *ctx) = 0;
  virtual void exitCall(mathpretParser::CallContext *ctx) = 0;


};

