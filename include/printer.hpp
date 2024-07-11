#pragma once

#include "token.hpp"
#include <iostream>

namespace funclib {
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