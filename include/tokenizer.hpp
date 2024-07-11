#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include "Token.hpp"
#include <cmath>

namespace funclib {

	class Tokenizer {
	public:
		Tokenizer(const std::string& input, const std::unordered_set<std::string>& functions) : input(input), funcs(functions) {}

		std::vector<ParseToken> GetTokens();

		void Reset(const std::string& new_input) {
			input = new_input;
			currentChar = '\0';
			currentPos = 0;
		}
	private:
		void TokenizeFirstPass(std::vector<ParseToken>& tokens);
		void TokenizeSecondPass(std::vector<ParseToken>& tokens);

		ParseToken GetStrToken();
		ParseToken GetDigitToken();
		ParseToken GetSingleCharToken();
		char currentChar = '\0';
		size_t currentPos = 0;
		std::string input;
		std::unordered_set<std::string> funcs;
	};

	inline std::vector<ParseToken> Tokenizer::GetTokens() {
		std::vector< ParseToken> tokens;
		TokenizeFirstPass(tokens);
		TokenizeSecondPass(tokens);
		return tokens;
	}

	inline void Tokenizer::TokenizeFirstPass(std::vector<ParseToken>& tokens)
	{
		currentChar = input[0];
		while (currentChar != '\0') {
			currentChar = input[currentPos];
			if (currentChar == ' ' || currentChar == '\r' || currentChar == '\t') {
				currentPos++;
				continue;
			}

			if (currentChar == '_' || std::isalpha(currentChar)) {
				ParseToken t = GetStrToken();
				tokens.emplace_back(t);
			}
			else if (std::isdigit(currentChar)) {
				ParseToken t = GetDigitToken();
				tokens.emplace_back(t);
			}
			else {
				tokens.emplace_back(GetSingleCharToken());
			}
		}
	}

	inline void Tokenizer::TokenizeSecondPass(std::vector<ParseToken>& tokens)
	{
		for (size_t i = 1; i < tokens.size(); i++)
		{
			if (tokens[i].IsOperator() && !(tokens[i - 1].IsOperand() || tokens[i - 1].IsRP()))
			{
				tokens[i].SetToUnary();
			}
		}

		for (size_t i = 0; i < tokens.size(); i++)
		{
			if (tokens[i].IsOperand() && tokens[i + 1].IsOperand()) {
				tokens.emplace(tokens.begin() + i + 1, ParseToken(TOKEN_OP_MUL, "*"));
				i++;
			}
		}
	}

	inline ParseToken Tokenizer::GetStrToken()
	{
		std::string buf(1, input[currentPos++]);
		while (input[currentPos] == '_' || std::isalnum(input[currentPos])) {
			buf += input[currentPos];
			currentPos++;
		}
		if (funcs.count(buf) > 0)
			return ParseToken(TOKEN_FUNC, buf);
		else
			return ParseToken(TOKEN_ID, buf);
	}

	inline ParseToken Tokenizer::GetDigitToken()
	{
		std::string buf(1, input[currentPos++]);
		while (std::isdigit(input[currentPos]) || input[currentPos] == '.') {
			buf += input[currentPos];
			currentPos++;
		}
		int dot_counter = 0;
		for (const char c : buf)
			dot_counter += c == '.' ? 1 : 0;

		_ASSERT(dot_counter <= 1);

		return ParseToken(TOKEN_LITERAL, buf);
	}

	inline ParseToken Tokenizer::GetSingleCharToken()
	{
		currentPos++;
		switch (currentChar)
		{
		case '+':
			return ParseToken(TOKEN_OP_ADD, "+");
		case '-':
			return ParseToken(TOKEN_OP_SUB, "-");
		case '*':
			return ParseToken(TOKEN_OP_MUL, "*");
		case '/':
			return ParseToken(TOKEN_OP_DIV, "/");
		case '^':
			return ParseToken(TOKEN_OP_EXP, "^");
		case '\n':
			return ParseToken(TOKEN_ENDLINE, "\n");
		case ',':
			return ParseToken(TOKEN_COMMA, ",");
		case '(':
			return ParseToken(TOKEN_LP, "(");
		case ')':
			return ParseToken(TOKEN_RP, ")");
		default:
			return ParseToken(TOKEN_EOF, "\0");
		}
	}

}