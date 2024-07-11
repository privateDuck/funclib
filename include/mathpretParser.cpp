
// Generated from mathpret.g4 by ANTLR 4.13.1


#include "mathpretListener.h"

#include "mathpretParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MathpretParserStaticData final {
  MathpretParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MathpretParserStaticData(const MathpretParserStaticData&) = delete;
  MathpretParserStaticData(MathpretParserStaticData&&) = delete;
  MathpretParserStaticData& operator=(const MathpretParserStaticData&) = delete;
  MathpretParserStaticData& operator=(MathpretParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag mathpretParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
MathpretParserStaticData *mathpretParserStaticData = nullptr;

void mathpretParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (mathpretParserStaticData != nullptr) {
    return;
  }
#else
  assert(mathpretParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MathpretParserStaticData>(
    std::vector<std::string>{
      "input", "line", "param_decl", "initializer", "var_decl", "func_decl", 
      "func", "arg_block", "exp", "call"
    },
    std::vector<std::string>{
      "", "'\\n'", "'param'", "','", "'='", "'var'", "'('", "')'", "'-'", 
      "'^'", "'*'", "'/'", "'+'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "ID", "LITERAL", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,15,129,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,1,0,5,0,22,8,0,10,0,12,0,25,9,0,1,0,1,0,1,1,1,1,
  	4,1,31,8,1,11,1,12,1,32,1,1,1,1,4,1,37,8,1,11,1,12,1,38,1,1,1,1,4,1,43,
  	8,1,11,1,12,1,44,3,1,47,8,1,1,2,1,2,1,2,1,2,5,2,53,8,2,10,2,12,2,56,9,
  	2,1,3,1,3,1,3,1,3,3,3,62,8,3,1,4,1,4,1,4,1,4,5,4,68,8,4,10,4,12,4,71,
  	9,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,3,6,83,8,6,1,7,1,7,1,7,1,
  	7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,99,8,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,5,8,112,8,8,10,8,12,8,115,9,8,1,9,1,9,1,9,
  	1,9,1,9,5,9,122,8,9,10,9,12,9,125,9,9,1,9,1,9,1,9,0,1,16,10,0,2,4,6,8,
  	10,12,14,16,18,0,2,1,0,10,11,2,0,8,8,12,12,137,0,23,1,0,0,0,2,46,1,0,
  	0,0,4,48,1,0,0,0,6,61,1,0,0,0,8,63,1,0,0,0,10,72,1,0,0,0,12,82,1,0,0,
  	0,14,84,1,0,0,0,16,98,1,0,0,0,18,116,1,0,0,0,20,22,3,2,1,0,21,20,1,0,
  	0,0,22,25,1,0,0,0,23,21,1,0,0,0,23,24,1,0,0,0,24,26,1,0,0,0,25,23,1,0,
  	0,0,26,27,5,0,0,1,27,1,1,0,0,0,28,30,3,4,2,0,29,31,5,1,0,0,30,29,1,0,
  	0,0,31,32,1,0,0,0,32,30,1,0,0,0,32,33,1,0,0,0,33,47,1,0,0,0,34,36,3,8,
  	4,0,35,37,5,1,0,0,36,35,1,0,0,0,37,38,1,0,0,0,38,36,1,0,0,0,38,39,1,0,
  	0,0,39,47,1,0,0,0,40,42,3,10,5,0,41,43,5,1,0,0,42,41,1,0,0,0,43,44,1,
  	0,0,0,44,42,1,0,0,0,44,45,1,0,0,0,45,47,1,0,0,0,46,28,1,0,0,0,46,34,1,
  	0,0,0,46,40,1,0,0,0,47,3,1,0,0,0,48,49,5,2,0,0,49,54,3,6,3,0,50,51,5,
  	3,0,0,51,53,3,6,3,0,52,50,1,0,0,0,53,56,1,0,0,0,54,52,1,0,0,0,54,55,1,
  	0,0,0,55,5,1,0,0,0,56,54,1,0,0,0,57,62,5,13,0,0,58,59,5,13,0,0,59,60,
  	5,4,0,0,60,62,5,14,0,0,61,57,1,0,0,0,61,58,1,0,0,0,62,7,1,0,0,0,63,64,
  	5,5,0,0,64,69,5,13,0,0,65,66,5,3,0,0,66,68,5,13,0,0,67,65,1,0,0,0,68,
  	71,1,0,0,0,69,67,1,0,0,0,69,70,1,0,0,0,70,9,1,0,0,0,71,69,1,0,0,0,72,
  	73,3,12,6,0,73,74,5,4,0,0,74,75,3,16,8,0,75,11,1,0,0,0,76,83,5,13,0,0,
  	77,78,5,13,0,0,78,79,5,6,0,0,79,80,3,14,7,0,80,81,5,7,0,0,81,83,1,0,0,
  	0,82,76,1,0,0,0,82,77,1,0,0,0,83,13,1,0,0,0,84,85,5,13,0,0,85,86,5,3,
  	0,0,86,87,5,13,0,0,87,15,1,0,0,0,88,89,6,8,-1,0,89,90,5,8,0,0,90,99,3,
  	16,8,9,91,99,3,18,9,0,92,93,5,6,0,0,93,94,3,16,8,0,94,95,5,7,0,0,95,99,
  	1,0,0,0,96,99,5,13,0,0,97,99,5,14,0,0,98,88,1,0,0,0,98,91,1,0,0,0,98,
  	92,1,0,0,0,98,96,1,0,0,0,98,97,1,0,0,0,99,113,1,0,0,0,100,101,10,6,0,
  	0,101,102,5,9,0,0,102,112,3,16,8,6,103,104,10,5,0,0,104,105,7,0,0,0,105,
  	112,3,16,8,6,106,107,10,4,0,0,107,112,3,16,8,5,108,109,10,3,0,0,109,110,
  	7,1,0,0,110,112,3,16,8,4,111,100,1,0,0,0,111,103,1,0,0,0,111,106,1,0,
  	0,0,111,108,1,0,0,0,112,115,1,0,0,0,113,111,1,0,0,0,113,114,1,0,0,0,114,
  	17,1,0,0,0,115,113,1,0,0,0,116,117,5,13,0,0,117,118,5,6,0,0,118,123,3,
  	16,8,0,119,120,5,3,0,0,120,122,3,16,8,0,121,119,1,0,0,0,122,125,1,0,0,
  	0,123,121,1,0,0,0,123,124,1,0,0,0,124,126,1,0,0,0,125,123,1,0,0,0,126,
  	127,5,7,0,0,127,19,1,0,0,0,13,23,32,38,44,46,54,61,69,82,98,111,113,123
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mathpretParserStaticData = staticData.release();
}

}

mathpretParser::mathpretParser(TokenStream *input) : mathpretParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

mathpretParser::mathpretParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  mathpretParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *mathpretParserStaticData->atn, mathpretParserStaticData->decisionToDFA, mathpretParserStaticData->sharedContextCache, options);
}

mathpretParser::~mathpretParser() {
  delete _interpreter;
}

const atn::ATN& mathpretParser::getATN() const {
  return *mathpretParserStaticData->atn;
}

std::string mathpretParser::getGrammarFileName() const {
  return "mathpret.g4";
}

const std::vector<std::string>& mathpretParser::getRuleNames() const {
  return mathpretParserStaticData->ruleNames;
}

const dfa::Vocabulary& mathpretParser::getVocabulary() const {
  return mathpretParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView mathpretParser::getSerializedATN() const {
  return mathpretParserStaticData->serializedATN;
}


//----------------- InputContext ------------------------------------------------------------------

mathpretParser::InputContext::InputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* mathpretParser::InputContext::EOF() {
  return getToken(mathpretParser::EOF, 0);
}

std::vector<mathpretParser::LineContext *> mathpretParser::InputContext::line() {
  return getRuleContexts<mathpretParser::LineContext>();
}

mathpretParser::LineContext* mathpretParser::InputContext::line(size_t i) {
  return getRuleContext<mathpretParser::LineContext>(i);
}


size_t mathpretParser::InputContext::getRuleIndex() const {
  return mathpretParser::RuleInput;
}

void mathpretParser::InputContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInput(this);
}

void mathpretParser::InputContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInput(this);
}

mathpretParser::InputContext* mathpretParser::input() {
  InputContext *_localctx = _tracker.createInstance<InputContext>(_ctx, getState());
  enterRule(_localctx, 0, mathpretParser::RuleInput);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8228) != 0)) {
      setState(20);
      line();
      setState(25);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(26);
    match(mathpretParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LineContext ------------------------------------------------------------------

mathpretParser::LineContext::LineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

mathpretParser::Param_declContext* mathpretParser::LineContext::param_decl() {
  return getRuleContext<mathpretParser::Param_declContext>(0);
}

mathpretParser::Var_declContext* mathpretParser::LineContext::var_decl() {
  return getRuleContext<mathpretParser::Var_declContext>(0);
}

mathpretParser::Func_declContext* mathpretParser::LineContext::func_decl() {
  return getRuleContext<mathpretParser::Func_declContext>(0);
}


size_t mathpretParser::LineContext::getRuleIndex() const {
  return mathpretParser::RuleLine;
}

void mathpretParser::LineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLine(this);
}

void mathpretParser::LineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLine(this);
}

mathpretParser::LineContext* mathpretParser::line() {
  LineContext *_localctx = _tracker.createInstance<LineContext>(_ctx, getState());
  enterRule(_localctx, 2, mathpretParser::RuleLine);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(46);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case mathpretParser::T__1: {
        enterOuterAlt(_localctx, 1);
        setState(28);
        param_decl();
        setState(30); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(29);
          match(mathpretParser::T__0);
          setState(32); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == mathpretParser::T__0);
        break;
      }

      case mathpretParser::T__4: {
        enterOuterAlt(_localctx, 2);
        setState(34);
        var_decl();
        setState(36); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(35);
          match(mathpretParser::T__0);
          setState(38); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == mathpretParser::T__0);
        break;
      }

      case mathpretParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(40);
        func_decl();
        setState(42); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(41);
          match(mathpretParser::T__0);
          setState(44); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == mathpretParser::T__0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Param_declContext ------------------------------------------------------------------

mathpretParser::Param_declContext::Param_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<mathpretParser::InitializerContext *> mathpretParser::Param_declContext::initializer() {
  return getRuleContexts<mathpretParser::InitializerContext>();
}

mathpretParser::InitializerContext* mathpretParser::Param_declContext::initializer(size_t i) {
  return getRuleContext<mathpretParser::InitializerContext>(i);
}


size_t mathpretParser::Param_declContext::getRuleIndex() const {
  return mathpretParser::RuleParam_decl;
}

void mathpretParser::Param_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam_decl(this);
}

void mathpretParser::Param_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam_decl(this);
}

mathpretParser::Param_declContext* mathpretParser::param_decl() {
  Param_declContext *_localctx = _tracker.createInstance<Param_declContext>(_ctx, getState());
  enterRule(_localctx, 4, mathpretParser::RuleParam_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    match(mathpretParser::T__1);
    setState(49);
    initializer();
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == mathpretParser::T__2) {
      setState(50);
      match(mathpretParser::T__2);
      setState(51);
      initializer();
      setState(56);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerContext ------------------------------------------------------------------

mathpretParser::InitializerContext::InitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* mathpretParser::InitializerContext::ID() {
  return getToken(mathpretParser::ID, 0);
}

tree::TerminalNode* mathpretParser::InitializerContext::LITERAL() {
  return getToken(mathpretParser::LITERAL, 0);
}


size_t mathpretParser::InitializerContext::getRuleIndex() const {
  return mathpretParser::RuleInitializer;
}

void mathpretParser::InitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializer(this);
}

void mathpretParser::InitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializer(this);
}

mathpretParser::InitializerContext* mathpretParser::initializer() {
  InitializerContext *_localctx = _tracker.createInstance<InitializerContext>(_ctx, getState());
  enterRule(_localctx, 6, mathpretParser::RuleInitializer);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(61);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(57);
      match(mathpretParser::ID);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(58);
      match(mathpretParser::ID);
      setState(59);
      match(mathpretParser::T__3);
      setState(60);
      match(mathpretParser::LITERAL);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_declContext ------------------------------------------------------------------

mathpretParser::Var_declContext::Var_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> mathpretParser::Var_declContext::ID() {
  return getTokens(mathpretParser::ID);
}

tree::TerminalNode* mathpretParser::Var_declContext::ID(size_t i) {
  return getToken(mathpretParser::ID, i);
}


size_t mathpretParser::Var_declContext::getRuleIndex() const {
  return mathpretParser::RuleVar_decl;
}

void mathpretParser::Var_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar_decl(this);
}

void mathpretParser::Var_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar_decl(this);
}

mathpretParser::Var_declContext* mathpretParser::var_decl() {
  Var_declContext *_localctx = _tracker.createInstance<Var_declContext>(_ctx, getState());
  enterRule(_localctx, 8, mathpretParser::RuleVar_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    match(mathpretParser::T__4);
    setState(64);
    match(mathpretParser::ID);
    setState(69);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == mathpretParser::T__2) {
      setState(65);
      match(mathpretParser::T__2);
      setState(66);
      match(mathpretParser::ID);
      setState(71);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_declContext ------------------------------------------------------------------

mathpretParser::Func_declContext::Func_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

mathpretParser::FuncContext* mathpretParser::Func_declContext::func() {
  return getRuleContext<mathpretParser::FuncContext>(0);
}

mathpretParser::ExpContext* mathpretParser::Func_declContext::exp() {
  return getRuleContext<mathpretParser::ExpContext>(0);
}


size_t mathpretParser::Func_declContext::getRuleIndex() const {
  return mathpretParser::RuleFunc_decl;
}

void mathpretParser::Func_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_decl(this);
}

void mathpretParser::Func_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_decl(this);
}

mathpretParser::Func_declContext* mathpretParser::func_decl() {
  Func_declContext *_localctx = _tracker.createInstance<Func_declContext>(_ctx, getState());
  enterRule(_localctx, 10, mathpretParser::RuleFunc_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    func();
    setState(73);
    match(mathpretParser::T__3);
    setState(74);
    exp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncContext ------------------------------------------------------------------

mathpretParser::FuncContext::FuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* mathpretParser::FuncContext::ID() {
  return getToken(mathpretParser::ID, 0);
}

mathpretParser::Arg_blockContext* mathpretParser::FuncContext::arg_block() {
  return getRuleContext<mathpretParser::Arg_blockContext>(0);
}


size_t mathpretParser::FuncContext::getRuleIndex() const {
  return mathpretParser::RuleFunc;
}

void mathpretParser::FuncContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc(this);
}

void mathpretParser::FuncContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc(this);
}

mathpretParser::FuncContext* mathpretParser::func() {
  FuncContext *_localctx = _tracker.createInstance<FuncContext>(_ctx, getState());
  enterRule(_localctx, 12, mathpretParser::RuleFunc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(82);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(76);
      match(mathpretParser::ID);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(77);
      match(mathpretParser::ID);
      setState(78);
      match(mathpretParser::T__5);
      setState(79);
      arg_block();
      setState(80);
      match(mathpretParser::T__6);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Arg_blockContext ------------------------------------------------------------------

mathpretParser::Arg_blockContext::Arg_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> mathpretParser::Arg_blockContext::ID() {
  return getTokens(mathpretParser::ID);
}

tree::TerminalNode* mathpretParser::Arg_blockContext::ID(size_t i) {
  return getToken(mathpretParser::ID, i);
}


size_t mathpretParser::Arg_blockContext::getRuleIndex() const {
  return mathpretParser::RuleArg_block;
}

void mathpretParser::Arg_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArg_block(this);
}

void mathpretParser::Arg_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArg_block(this);
}

mathpretParser::Arg_blockContext* mathpretParser::arg_block() {
  Arg_blockContext *_localctx = _tracker.createInstance<Arg_blockContext>(_ctx, getState());
  enterRule(_localctx, 14, mathpretParser::RuleArg_block);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    match(mathpretParser::ID);

    setState(85);
    match(mathpretParser::T__2);
    setState(86);
    match(mathpretParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

mathpretParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<mathpretParser::ExpContext *> mathpretParser::ExpContext::exp() {
  return getRuleContexts<mathpretParser::ExpContext>();
}

mathpretParser::ExpContext* mathpretParser::ExpContext::exp(size_t i) {
  return getRuleContext<mathpretParser::ExpContext>(i);
}

mathpretParser::CallContext* mathpretParser::ExpContext::call() {
  return getRuleContext<mathpretParser::CallContext>(0);
}

tree::TerminalNode* mathpretParser::ExpContext::ID() {
  return getToken(mathpretParser::ID, 0);
}

tree::TerminalNode* mathpretParser::ExpContext::LITERAL() {
  return getToken(mathpretParser::LITERAL, 0);
}


size_t mathpretParser::ExpContext::getRuleIndex() const {
  return mathpretParser::RuleExp;
}

void mathpretParser::ExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExp(this);
}

void mathpretParser::ExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExp(this);
}


mathpretParser::ExpContext* mathpretParser::exp() {
   return exp(0);
}

mathpretParser::ExpContext* mathpretParser::exp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  mathpretParser::ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, parentState);
  mathpretParser::ExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, mathpretParser::RuleExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(98);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(89);
      match(mathpretParser::T__7);
      setState(90);
      exp(9);
      break;
    }

    case 2: {
      setState(91);
      call();
      break;
    }

    case 3: {
      setState(92);
      match(mathpretParser::T__5);
      setState(93);
      exp(0);
      setState(94);
      match(mathpretParser::T__6);
      break;
    }

    case 4: {
      setState(96);
      match(mathpretParser::ID);
      break;
    }

    case 5: {
      setState(97);
      match(mathpretParser::LITERAL);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(113);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(111);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(100);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(101);
          match(mathpretParser::T__8);
          setState(102);
          exp(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(103);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(104);
          _la = _input->LA(1);
          if (!(_la == mathpretParser::T__9

          || _la == mathpretParser::T__10)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(105);
          exp(6);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(106);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(107);
          exp(5);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(108);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(109);
          _la = _input->LA(1);
          if (!(_la == mathpretParser::T__7

          || _la == mathpretParser::T__11)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(110);
          exp(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(115);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- CallContext ------------------------------------------------------------------

mathpretParser::CallContext::CallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* mathpretParser::CallContext::ID() {
  return getToken(mathpretParser::ID, 0);
}

std::vector<mathpretParser::ExpContext *> mathpretParser::CallContext::exp() {
  return getRuleContexts<mathpretParser::ExpContext>();
}

mathpretParser::ExpContext* mathpretParser::CallContext::exp(size_t i) {
  return getRuleContext<mathpretParser::ExpContext>(i);
}


size_t mathpretParser::CallContext::getRuleIndex() const {
  return mathpretParser::RuleCall;
}

void mathpretParser::CallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall(this);
}

void mathpretParser::CallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<mathpretListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall(this);
}

mathpretParser::CallContext* mathpretParser::call() {
  CallContext *_localctx = _tracker.createInstance<CallContext>(_ctx, getState());
  enterRule(_localctx, 18, mathpretParser::RuleCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    match(mathpretParser::ID);
    setState(117);
    match(mathpretParser::T__5);
    setState(118);
    exp(0);
    setState(123);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == mathpretParser::T__2) {
      setState(119);
      match(mathpretParser::T__2);
      setState(120);
      exp(0);
      setState(125);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(126);
    match(mathpretParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool mathpretParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 8: return expSempred(antlrcpp::downCast<ExpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool mathpretParser::expSempred(ExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 6);
    case 1: return precpred(_ctx, 5);
    case 2: return precpred(_ctx, 4);
    case 3: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void mathpretParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  mathpretParserInitialize();
#else
  ::antlr4::internal::call_once(mathpretParserOnceFlag, mathpretParserInitialize);
#endif
}
