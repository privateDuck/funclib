#pragma once

#include "token.hpp"
#include <iostream>

namespace funclib {

	inline std::string GetTokenText(const _ttype t) {
		switch (t)
		{
		case TOKEN_COMMA:
			return ",";
		case TOKEN_LP:
			return "(";
		case TOKEN_RP:
			return ")";
		case TOKEN_NATIVEFUNC:
		case TOKEN_FUNC:
			return "function";
		case TOKEN_ID:
			return "identifier";
		case TOKEN_LITERAL:
			return "literal";
		case TOKEN_ENDLINE:
			return "endline";
		case TOKEN_OP_EXP:
			return "binary operator (^)";
		case TOKEN_OP_MUL:
			return "binary operator (^)";
		case TOKEN_OP_DIV:
			return "binary operator (^)";
		case TOKEN_OP_ADD:
			return "binary operator (^)";
		case TOKEN_OP_SUB:
			return "binary operator (^)";
		case TOKEN_OP_UN_NEG:
			return "unary negation operator";
		case TOKEN_OP_UN_POS:
			return "unary identity operator";
		case TOKEN_EOF:
			return "<EOF>";
		case TOKEN_COLON:
			return ":";
		default:
			break;
		}
	}

	inline std::ostream& operator<<(std::ostream& os, const ParseToken& tok)
	{
		switch (tok.type)
		{
		case TOKEN_COMMA:
		case TOKEN_LP:
		case TOKEN_RP:
			os << "Symbol: " << tok.text;
			break;
		case TOKEN_FUNC:
			os << "FUNC: " << tok.text;
			break;
		case TOKEN_ID:
			os << "ID: " << tok.text;
			break;
		case TOKEN_LITERAL:
			os << "Literal: " << tok.text;
			break;
		case TOKEN_NATIVEFUNC:
			os << "NATIVE: " << tok.text;
			break;
		case TOKEN_ENDLINE:
			os << "End Line";
			break;
		case TOKEN_OP_EXP:
			os << "OP_EXP";
			break;
		case TOKEN_OP_MUL:
			os << "OP_MUL";
			break;
		case TOKEN_OP_DIV:
			os << "OP_DIV";
			break;
		case TOKEN_OP_ADD:
			os << "OP_ADD";
			break;
		case TOKEN_OP_SUB:
			os << "OP_SUB";
			break;
		case TOKEN_OP_UN_NEG:
		case TOKEN_OP_UN_POS:
			os << "Unary OP: ";
			break;
		case TOKEN_EOF:
			os << "<EOF>";
			break;
		default:
			break;
		}
		return os;
	}
}