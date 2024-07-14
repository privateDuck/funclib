#pragma once

#include <string>
#include <inttypes.h>
#include <cstring>

namespace funclib {

	union _tdata {
		double value;
		uint64_t address;
	};

	enum _ttype {
		TOKEN_COMMA,
		TOKEN_LP,
		TOKEN_RP,
		TOKEN_FUNC,
		TOKEN_NATIVEFUNC,
		TOKEN_ID,	   // parse token: holds text references, math token: holds parameter or variable
		TOKEN_LITERAL, // holds constant numeric value
		TOKEN_ENDLINE,
		TOKEN_OP_EXP,
		TOKEN_OP_MUL,
		TOKEN_OP_DIV,
		TOKEN_OP_ADD,
		TOKEN_OP_SUB,
		TOKEN_OP_UN_NEG,
		TOKEN_OP_UN_POS,
		TOKEN_COLON,
		TOKEN_EOF
	};

	struct ParseToken {
	public:
		ParseToken() : type(TOKEN_EOF), text() {}
		ParseToken(_ttype type, const std::string& text) : type(type), text(text) {
			switch (type)
			{
			case TOKEN_OP_UN_NEG:
			case TOKEN_OP_UN_POS:
				precedence = 8;
				break;
			case TOKEN_OP_EXP:
				precedence = 7;
				break;
			case TOKEN_OP_MUL:
			case TOKEN_OP_DIV:
				precedence = 6;
				break;
			case TOKEN_OP_ADD:
			case TOKEN_OP_SUB:
				precedence = 5;
				break;
			default:
				precedence = 0; // Default for literals, identifiers, and other tokens
				break;
			}
		}

		ParseToken& operator=(const ParseToken& o) noexcept {
			type = o.type;
			text = o.text;
			precedence = o.precedence;
			return *this;
		}
		ParseToken(const ParseToken& o) noexcept : type(o.type), text(o.text), precedence(o.precedence) {}

		ParseToken& operator=(ParseToken&& o) noexcept {
			type = std::move(o.type);
			text = std::move(o.text);
			precedence = std::move(o.precedence);
			return *this;
		}
		ParseToken(ParseToken&& o) noexcept : type(std::move(o.type)), text(std::move(o.text)), precedence(std::move(o.precedence)) {}

		inline bool IsOperand() const { return type > TOKEN_RP && type < TOKEN_ENDLINE; }
		inline bool IsID() const { return type == TOKEN_ID; }
		inline bool IsValue() const { return type == TOKEN_ID || type == TOKEN_LITERAL; }
		inline bool IsComma() const { return type == TOKEN_COMMA; }
		inline bool IsVMFunction() const { return type == TOKEN_FUNC; }
		inline bool IsNativeFunction() const { return type == TOKEN_NATIVEFUNC; }
		inline bool IsFunction() const { return type == TOKEN_FUNC || type == TOKEN_NATIVEFUNC; }
		inline bool IsNumeric() const { return type == TOKEN_LITERAL; }
		inline bool IsOperator() const { return type > TOKEN_ENDLINE && type < TOKEN_COLON; }
		inline bool IsBinaryOP() const { return type > TOKEN_ENDLINE && type < TOKEN_OP_UN_NEG; }
		inline bool IsUnaryOP() const { return type > TOKEN_OP_SUB && type < TOKEN_COLON; }

		inline bool IsLP() const { return type == TOKEN_LP; }
		inline bool IsRP() const { return type == TOKEN_RP; }

		inline void SetToUnary() { type = type == TOKEN_OP_ADD ? TOKEN_OP_UN_POS : TOKEN_OP_UN_NEG; }
		inline void SetToFunc() { type = TOKEN_FUNC; }
		inline void SetToNativeFunc() { type = TOKEN_NATIVEFUNC; }

		inline int GetPrecedence() const { return precedence; }
		inline bool IsLeftAssoc() const { return IsOperator() && type != TOKEN_OP_EXP; }

		inline _ttype GetType() const { return type; }
		inline const std::string& GetText() const { return text; }

	private:
		int precedence = -1;
		_ttype type;
		std::string text;

		friend std::ostream& operator<<(std::ostream& os, const ParseToken& tok);
	};

	struct Token {
	public:
		Token() : type(TOKEN_EOF), arg(-2) { data.address = 0; }
		~Token() {}

		// FUNCTION TOKEN
		Token(uint64_t address, int argc , _ttype type) : type(type), arg(argc) { data.address = address; }

		// VAR/PARAM TOKEN
		explicit Token(uint64_t address) : type(TOKEN_ID), arg(-1) { data.address = address; }

		// LITERAL TOKEN
		explicit Token(double lvalue) : type(TOKEN_LITERAL), arg(-1) { data.value = lvalue; }

		// OPERATOR TOKEN
		Token(char c, bool unary) : arg(-1) {
			switch (c) {
			case '+':
				type = unary ? TOKEN_OP_UN_POS : TOKEN_OP_ADD;
				break;
			case '-':
				type = unary ? TOKEN_OP_UN_NEG : TOKEN_OP_SUB;
				break;
			case '*':
				type = TOKEN_OP_MUL;
				break;
			case '/':
				type = TOKEN_OP_DIV;
				break;
			case '^':
				type = TOKEN_OP_EXP;
				break;
			default:
				type = TOKEN_EOF;
			}
			data.address = 0;
		}

		inline constexpr uint64_t GetAddress() const { return data.address; }
		inline constexpr double GetLiteral() const { return data.value; }
		inline constexpr _ttype GetType() const { return type; }
		inline constexpr int GetArgc() const { return arg; }

	private:
		_tdata data;
		_ttype type;
		int arg;
	};

}
