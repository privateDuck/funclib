
// Generated from mathpret.g4 by ANTLR 4.13.1


#include "mathpretLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct MathpretLexerStaticData final {
  MathpretLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MathpretLexerStaticData(const MathpretLexerStaticData&) = delete;
  MathpretLexerStaticData(MathpretLexerStaticData&&) = delete;
  MathpretLexerStaticData& operator=(const MathpretLexerStaticData&) = delete;
  MathpretLexerStaticData& operator=(MathpretLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag mathpretlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
MathpretLexerStaticData *mathpretlexerLexerStaticData = nullptr;

void mathpretlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (mathpretlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(mathpretlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MathpretLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "ID", "LITERAL", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,15,89,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,4,1,4,
  	1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,
  	5,12,64,8,12,10,12,12,12,67,9,12,1,13,1,13,1,13,4,13,72,8,13,11,13,12,
  	13,73,1,13,4,13,77,8,13,11,13,12,13,78,3,13,81,8,13,1,14,4,14,84,8,14,
  	11,14,12,14,85,1,14,1,14,0,0,15,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,
  	9,19,10,21,11,23,12,25,13,27,14,29,15,1,0,5,3,0,65,90,95,95,97,122,4,
  	0,48,57,65,90,95,95,97,122,1,0,48,57,1,0,49,57,3,0,9,9,13,13,32,32,93,
  	0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,
  	0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,
  	0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,1,31,1,0,0,0,3,33,
  	1,0,0,0,5,39,1,0,0,0,7,41,1,0,0,0,9,43,1,0,0,0,11,47,1,0,0,0,13,49,1,
  	0,0,0,15,51,1,0,0,0,17,53,1,0,0,0,19,55,1,0,0,0,21,57,1,0,0,0,23,59,1,
  	0,0,0,25,61,1,0,0,0,27,80,1,0,0,0,29,83,1,0,0,0,31,32,5,10,0,0,32,2,1,
  	0,0,0,33,34,5,112,0,0,34,35,5,97,0,0,35,36,5,114,0,0,36,37,5,97,0,0,37,
  	38,5,109,0,0,38,4,1,0,0,0,39,40,5,44,0,0,40,6,1,0,0,0,41,42,5,61,0,0,
  	42,8,1,0,0,0,43,44,5,118,0,0,44,45,5,97,0,0,45,46,5,114,0,0,46,10,1,0,
  	0,0,47,48,5,40,0,0,48,12,1,0,0,0,49,50,5,41,0,0,50,14,1,0,0,0,51,52,5,
  	45,0,0,52,16,1,0,0,0,53,54,5,94,0,0,54,18,1,0,0,0,55,56,5,42,0,0,56,20,
  	1,0,0,0,57,58,5,47,0,0,58,22,1,0,0,0,59,60,5,43,0,0,60,24,1,0,0,0,61,
  	65,7,0,0,0,62,64,7,1,0,0,63,62,1,0,0,0,64,67,1,0,0,0,65,63,1,0,0,0,65,
  	66,1,0,0,0,66,26,1,0,0,0,67,65,1,0,0,0,68,69,7,2,0,0,69,71,5,46,0,0,70,
  	72,7,2,0,0,71,70,1,0,0,0,72,73,1,0,0,0,73,71,1,0,0,0,73,74,1,0,0,0,74,
  	81,1,0,0,0,75,77,7,3,0,0,76,75,1,0,0,0,77,78,1,0,0,0,78,76,1,0,0,0,78,
  	79,1,0,0,0,79,81,1,0,0,0,80,68,1,0,0,0,80,76,1,0,0,0,81,28,1,0,0,0,82,
  	84,7,4,0,0,83,82,1,0,0,0,84,85,1,0,0,0,85,83,1,0,0,0,85,86,1,0,0,0,86,
  	87,1,0,0,0,87,88,6,14,0,0,88,30,1,0,0,0,6,0,65,73,78,80,85,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mathpretlexerLexerStaticData = staticData.release();
}

}

mathpretLexer::mathpretLexer(CharStream *input) : Lexer(input) {
  mathpretLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *mathpretlexerLexerStaticData->atn, mathpretlexerLexerStaticData->decisionToDFA, mathpretlexerLexerStaticData->sharedContextCache);
}

mathpretLexer::~mathpretLexer() {
  delete _interpreter;
}

std::string mathpretLexer::getGrammarFileName() const {
  return "mathpret.g4";
}

const std::vector<std::string>& mathpretLexer::getRuleNames() const {
  return mathpretlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& mathpretLexer::getChannelNames() const {
  return mathpretlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& mathpretLexer::getModeNames() const {
  return mathpretlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& mathpretLexer::getVocabulary() const {
  return mathpretlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView mathpretLexer::getSerializedATN() const {
  return mathpretlexerLexerStaticData->serializedATN;
}

const atn::ATN& mathpretLexer::getATN() const {
  return *mathpretlexerLexerStaticData->atn;
}




void mathpretLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  mathpretlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(mathpretlexerLexerOnceFlag, mathpretlexerLexerInitialize);
#endif
}
