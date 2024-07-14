#pragma once

#include "token.hpp"
#include "printer.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

namespace funclib {

	
	class Parser {
	public:
		Parser() {}

		inline bool HasError() const { return parseError; }

		inline std::string GetError() const { return parseErrorMsg; }
		
		inline bool ParseSignature(const std::vector< ParseToken>& tokens,
			std::string& function_name,
			std::vector<std::string>& arguments,
			std::vector<std::string>& parameters) 
		{
			parseError = false;
			parseErrorMsg.clear();
			tokenStream = tokens;
			bool success = false;
			try {
				success = S();
			}
			catch (std::runtime_error){
				return false;
			}
			arguments = args;
			parameters = params;
			function_name = funcname;
			success &= !parseError;
			readingParams = false;
			currentIndex = 0;
			tokenStream.clear();
			return success;
		}

		inline std::vector<ParseToken> ParseExpression(const std::vector< ParseToken>& tokens) {
			std::vector<ParseToken> output;
			std::stack<ParseToken> operators;
			parseError = false;
			parseErrorMsg.clear();

			for (const auto& token : tokens)
			{
				if (token.IsValue()) {
					output.push_back(token);
				}
				else if (token.IsFunction()) {
					operators.push(token);
				}
				else if (token.IsComma()) {
					while (!operators.empty() && !operators.top().IsLP()) {
						output.push_back(operators.top());
						operators.pop();
					}
				}
				else if (token.IsOperator()) {
					while (!operators.empty() && operators.top().IsOperator() &&
						((token.IsLeftAssoc() && token.GetPrecedence() <= operators.top().GetPrecedence()) ||
							(!token.IsLeftAssoc() && token.GetPrecedence() < operators.top().GetPrecedence()))) {
						output.push_back(operators.top());
						operators.pop();
					}
					operators.push(token);
				}
				else if (token.IsLP()) {
					operators.push(token);
				}
				else if (token.IsRP()) {
					while (!operators.empty() && !operators.top().IsLP()) {
						output.push_back(operators.top());
						operators.pop();
					}
					if (!operators.empty() && operators.top().IsLP()) {
						operators.pop(); // Pop the left parenthesis
					}
					else {
						parseError = true;
						parseErrorMsg = "Mismatched parentheses detected.";
					}
					// If there is a function token on top, pop it to output
					if (!operators.empty() && operators.top().IsFunction()) {
						output.push_back(operators.top());
						operators.pop();
					}
				}
			}

			while (!operators.empty()) {
				if (operators.top().IsLP()) {
					parseError = true;
					parseErrorMsg = "Mismatched parentheses detected.";
				}
				output.push_back(operators.top());
				operators.pop();
			}

			return output;

		}

	private:
		std::vector<ParseToken> tokenStream;
		size_t currentIndex;
		bool parseError = false;
		bool readingParams = false;
		std::string parseErrorMsg, funcname;
		std::vector<std::string> args, params;

		// Signature parser
		void next() {
			currentIndex++;
		}
		bool accept(const _ttype sym) {
			if (tokenStream[currentIndex].GetType() == sym) {
				next();
				return true;
			}
			return false;
		}
		bool expect(const _ttype sym) {
			if (accept(sym)) {
				return true;
			}
			parseError = true;
			parseErrorMsg = "Signature Error: Expected '" + GetTokenText(sym) + "'. Found '" + tokenStream[currentIndex].GetText() + "'.";
			throw std::runtime_error("parse error");
		}
		// S	-> N ( arg ) | N ( arg : arg )
		// arg	-> ID arg'
		// arg'	-> , arg | $
		bool S() {
			expect(TOKEN_ID);
			funcname = tokenStream[currentIndex - 1].GetText();
			if (accept(TOKEN_LP)) {
				arg();
				if (accept(TOKEN_COLON)) {
					readingParams = true;
					arg();
				}
				expect(TOKEN_RP);
				return true;
			}
			return false;
		}
		bool arg() {
			if (accept(TOKEN_ID)) {
				if (readingParams) params.emplace_back(tokenStream[currentIndex - 1].GetText());
				else args.emplace_back(tokenStream[currentIndex - 1].GetText());
				argprime();
				return true;
			}
			return false;
		}
		bool argprime() {
			if (accept(TOKEN_COMMA)) {
				arg();
				return true;
			}
			else if (accept(TOKEN_EOF))
				return true;
			return false;
		}
	};
}
/*
	std::vector<ParseToken> output;

	std::stack<ParseToken> operators = std::stack<ParseToken>();

	for (const auto& token : tokens)
	{
		if (token.IsValue()) {
			output.push_back(token);
		}
		else if (token.IsFunction()) {
			operators.push(token);
		}
		else if (token.IsComma()) {
			while (!operators.empty() && (!operators.top().IsLP())) {
				output.push_back(operators.top());
				operators.pop();
			}
		}
		else if (token.IsOperator()) {
			if (!operators.empty()) {
				while (operators.top().IsOperator() && ((token.GetPrecedence() < operators.top().GetPrecedence()) || (token.GetPrecedence() == operators.top().GetPrecedence() && token.IsLeftAssoc())))
				{
					output.push_back(operators.top());
					operators.pop();
					if (operators.empty()) break;
				}
			}
			operators.push(token);
		}
		else if (token.IsLP()) {
			operators.push(token);
		}
		else if (token.IsRP()) {
			if (!operators.empty()) {
				while (true) {
					if (operators.top().IsLP()) {
						operators.pop();
						break;
					}
					else {
						output.push_back(operators.top());
						operators.pop();
					}

					// We never found LP (should be impossible)
					if (operators.empty()) break;
				}
			}
		}
	}

	while (!operators.empty()) {
		if (!operators.top().IsLP())
			output.push_back(operators.top());

		operators.pop();
	}

	return output;

*/