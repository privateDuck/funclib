#pragma once

#include "token.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

namespace funclib {

	
	class Parser {
	public:
		Parser() {}
		
		inline std::vector<ParseToken> ParseSignature(const std::vector<ParseToken>& tokens) {

		}

		inline std::vector<ParseToken> ParseExpression(const std::vector< ParseToken>& tokens) {
			std::vector<ParseToken> output;
			std::stack<ParseToken> operators;

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
						throw std::runtime_error("Mismatched parentheses detected.");
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
					throw std::runtime_error("Mismatched parentheses detected.");
				}
				output.push_back(operators.top());
				operators.pop();
			}

			return output;

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