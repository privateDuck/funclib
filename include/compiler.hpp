#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "mathpretBaseListener.h"
#include "mathpretLexer.h"
#include "mathpretParser.h"

namespace mathpret {

	class MathPreter : private mathpretBaseListener {

	private:
		std::unordered_map<std::string, double> params;
		std::unordered_set<std::string> vars;

		virtual void enterInput(mathpretParser::InputContext* ctx) override {
			
		}

		virtual void enterLine(mathpretParser::LineContext* /*ctx*/) override { }

		virtual void enterParam_decl(mathpretParser::Param_declContext* /*ctx*/) override { }

		virtual void enterInitializer(mathpretParser::InitializerContext* ctx) override {
			std::string id = ctx->ID()->getText();
			double value = 0.0;
			if (ctx->LITERAL() != nullptr) {
				value = std::stod(ctx->LITERAL()->getText());
			}
			if (params.count(id) == 0) {
				params.insert(std::make_pair(id, value));
			}
			else {
				// error
			}
		}

		virtual void enterVar_decl(mathpretParser::Var_declContext* ctx) override {
			for (const auto* id : ctx->ID())
				vars.insert(id->getSymbol()->getText());
		}

		virtual void enterFunc_decl(mathpretParser::Func_declContext* /*ctx*/) override { }

		virtual void enterFunc(mathpretParser::FuncContext* /*ctx*/) override { }

		virtual void enterArg_block(mathpretParser::Arg_blockContext* /*ctx*/) override { }

		virtual void enterExp(mathpretParser::ExpContext* /*ctx*/) override { }

		virtual void enterCall(mathpretParser::CallContext* /*ctx*/) override { }
	};

	class Compiler {

		bool Compile(const std::string& input);

		bool SyntaxOk(const std::string& input);
	};

}
