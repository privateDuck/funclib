#pragma once

#include <stdexcept>
#include <memory>
#include "function.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

namespace funclib {

	namespace detail {
		enum _NativeFunctions {
			// CMATH
			NF_ACOS,			// Arc cosine (1 arg)
			NF_ACOSH,			// Inverse hyperbolic cosine (1 arg)
			NF_ASIN,			// Arc sine (1 arg)
			NF_ASINH,			// Inverse hyperbolic sine (1 arg)
			NF_ATAN,			// Arc tangent (1 arg)
			NF_ATANH,			// Inverse hyperbolic tangent (1 arg)
			NF_CBRT,			// Cube root (1 arg)
			NF_CEIL,			// Ceiling (1 arg)
			NF_COS,				// Cosine (1 arg)
			NF_COSH,			// Hyperbolic cosine (1 arg)
			NF_ERF,				// Error function (1 arg)
			NF_ERFINV,			// Inverse error function (1 arg)
			NF_ERFC,			// Complementary error function (1 arg)
			NF_EXP,				// Exponential (e^x) (1 arg)
			NF_EXP2,			// Exponential (2^x) (1 arg)
			NF_EXPM1,			// Exponential minus 1 (1 arg)
			NF_FABS,			// Absolute value (1 arg)
			NF_FLOOR,			// Floor (1 arg)
			NF_LGAMMA,			// Natural logarithm of the gamma function (1 arg)
			NF_LOG,				// Natural logarithm (base e) (1 arg)
			NF_LOG10,			// Common logarithm (base 10) (1 arg)
			NF_LOG1P,			// Logarithm of 1 plus x (1 arg)
			NF_LOG2,			// Binary logarithm (base 2) (1 arg)
			NF_NEARBYINT,		// Rounds to nearest integer, according to current rounding mode (1 arg)
			NF_RINT,			// Rounds to nearest integer value, but returns as a double (1 arg)
			NF_ROUND,			// Rounds to nearest integer value, halfway cases away from zero (1 arg)
			NF_SIN,				// Sine (1 arg)
			NF_SINH,			// Hyperbolic sine (1 arg)
			NF_SQRT,			// Square root (1 arg)
			NF_TAN,				// Tangent (1 arg)
			NF_TANH,			// Hyperbolic tangent (1 arg)
			NF_TGAMMA,			// Gamma function (1 arg)
			NF_TRUNC,			// Truncate (1 arg)
			// 2 args
			NF_ATAN2,			// Arc tangent of y/x (2 args)
			NF_FMOD,			// Floating-point remainder of x/y (2 args)
			NF_POW,				// x raised to the power y (2 args)
			NF_HYPOT,			// Hypotenuse (sqrt(x^2 + y^2)) (2 args)
			NF_REMAINDER,		// Remainder of x/y rounded to the nearest integer (2 args)
			// Misc
			NF_GCD,				// Greated common divisor (2 args)
			NF_LCM,				// Least common multiple (2 args)
			NF_NPR,				// nPr (2 args)
			NF_NCR,				// nCr (2 args)
			// Distributions
			NF_EXP_DIST,		// Exponential distribution (2 args)
			NF_CHI2_DIST,		// Chi squared distribution (2 args)
			NF_T_DIST,			// T distribution (2 args)
			// 3 args
			NF_NORMAL_DIST,		// Normal distribution (3 args)
			NF_GAMMA_DIST,		// Gamma distribution (3 args)
			NF_BETA_DIST,		// Beta distribution (3 args)
			NF_LOGISTIC_DIST,	// Logistic distribution (3 args)
			NF_CAUCHY_DIST,		// Cauchy distribution (3 args)
			NF_WEIBULL_DIST,	// Weibull distribution (3 args)
			NF_LOGNORM_DIST,	// Log normal distribution (3 args)
			NF_PARETO_DIST,		// Pareto distribution (3 args)
#if __cplusplus >= 201703L
			NF_ASSOC_LAGUERRE,	// Associated Laguerre polynomials (3 args (n,m,x))
			NF_ASSOC_LEGENDRE,	// associated Legendre polynomials (3 args (n,m,x))
			NF_BETA,			// beta function (2 args (x,y))
			NF_COMP_ELLINT_1,	// Complete elliptic integral 1 kind (1 arg)
			NF_COMP_ELLINT_2,	// (complete) elliptic integral of the second kind (1 arg)
			NF_COMP_ELLINT_3,	// (complete) elliptic integral of the third kind (2 args (k,nu))
			NF_CYL_BESSEL_I,	// regular modified cylindrical Bessel functions (2 args (nu,x))
			NF_CYL_BESSEL_J,	// cylindrical Bessel functions (of the first kind) (2 args (nu,x))
			NF_CYL_BESSEL_K,	// irregular modified cylindrical Bessel functions (2 args (nu,x))
			NF_CYL_NEWMANN,		// cylindrical Neumann functions (2 args (nu,x))
			NF_ELLINT_1,		// (incomplete) elliptic integral of the first kind (2 args (k,phi))
			NF_ELLINT_2,		// (incomplete) elliptic integral of the second kind (2 args (k,phi))
			NF_ELLINT_3,		// (incomplete) elliptic integral of the third kind (3 args (k,nu,phi))
			NF_EXPINT,			// exponential integral (1 arg)
			NF_HERMITE,			// Hermite polynomials (2 args (n,x))
			NF_LEGENDRE,		// Legendre polynomials (2 args (n,x))
			NF_LAGUERRE,		// Laguerre polynomials (2 args (n,x))
			NF_ZETA,			// Riemann zeta function (1 arg)
			NF_SPH_BESSEL,		// spherical Bessel functions (of the first kind) (2 args (n,x))
			NF_SPH_LEGENDRE,	// spherical associated Legendre functions (3 args (l,m,theta))
			NF_SPH_NEUMANN,		// spherical Neumann functions (2 args (n,x))
#endif
			NF_COUNT
		};

		double ResolveNativeFunction(const std::vector<double>& stack, size_t idx, size_t base) {
			_NativeFunctions ft = (_NativeFunctions)idx;
			switch (ft)
			{
			case funclib::detail::NF_ACOS:
				return std::acos(stack[base]);
			case funclib::detail::NF_ACOSH:
				return std::acosh(stack[base]);
			case funclib::detail::NF_ASIN:
				return std::asin(stack[base]);
			case funclib::detail::NF_ASINH:
				return std::asinh(stack[base]);
			case funclib::detail::NF_ATAN:
				return std::atan(stack[base]);
			case funclib::detail::NF_ATANH:
				return std::atanh(stack[base]);
			case funclib::detail::NF_CBRT:
				return std::cbrt(stack[base]);
			case funclib::detail::NF_CEIL:
				return std::ceil(stack[base]);
			case funclib::detail::NF_COS:
				return std::cos(stack[base]);
			case funclib::detail::NF_COSH:
				return std::cosh(stack[base]);
			case funclib::detail::NF_ERF:
				return std::erf(stack[base]);
			case funclib::detail::NF_ERFINV:
				//return std::erfinv(stack[base]);
				throw std::runtime_error("erfinv not defined");
				break;
			case funclib::detail::NF_ERFC:
				return std::erfc(stack[base]);
			case funclib::detail::NF_EXP:
				return std::exp(stack[base]);
			case funclib::detail::NF_EXP2:
				return std::exp2(stack[base]);
			case funclib::detail::NF_EXPM1:
				return std::expm1(stack[base]);
			case funclib::detail::NF_FABS:
				return std::fabs(stack[base]);
			case funclib::detail::NF_FLOOR:
				return std::floor(stack[base]);
			case funclib::detail::NF_LGAMMA:
				return std::lgamma(stack[base]);
			case funclib::detail::NF_LOG:
				return std::log(stack[base]);
			case funclib::detail::NF_LOG10:
				return std::log10(stack[base]);
			case funclib::detail::NF_LOG1P:
				return std::log1p(stack[base]);
			case funclib::detail::NF_LOG2:
				return std::log2(stack[base]);
			case funclib::detail::NF_NEARBYINT:
				return std::nearbyint(stack[base]);
			case funclib::detail::NF_RINT:
				return std::rint(stack[base]);
			case funclib::detail::NF_ROUND:
				return std::round(stack[base]);
			case funclib::detail::NF_SIN:
				return std::sin(stack[base]);
			case funclib::detail::NF_SINH:
				return std::sinh(stack[base]);
			case funclib::detail::NF_SQRT:
				return std::sqrt(stack[base]);
			case funclib::detail::NF_TAN:
				return std::tan(stack[base]);
			case funclib::detail::NF_TANH:
				return std::tanh(stack[base]);
			case funclib::detail::NF_TGAMMA:
				return std::tgamma(stack[base]);
			case funclib::detail::NF_TRUNC:
				return std::trunc(stack[base]);
			case funclib::detail::NF_ATAN2:
				return std::atan2(stack[base], stack[base+1]);
			case funclib::detail::NF_FMOD:
				return std::fmod(stack[base], stack[base + 1]);
			case funclib::detail::NF_POW:
				return std::pow(stack[base], stack[base + 1]);
			case funclib::detail::NF_HYPOT:
				return std::hypot(stack[base], stack[base + 1]);
			case funclib::detail::NF_REMAINDER:
				return std::remainder(stack[base], stack[base + 1]);
			case funclib::detail::NF_GCD:
				break;
			case funclib::detail::NF_LCM:
				break;
			case funclib::detail::NF_NPR:
				break;
			case funclib::detail::NF_NCR:
				break;
			case funclib::detail::NF_EXP_DIST:
				break;
			case funclib::detail::NF_CHI2_DIST:
				break;
			case funclib::detail::NF_T_DIST:
				break;
			case funclib::detail::NF_NORMAL_DIST:
				break;
			case funclib::detail::NF_GAMMA_DIST:
				break;
			case funclib::detail::NF_BETA_DIST:
				break;
			case funclib::detail::NF_LOGISTIC_DIST:
				break;
			case funclib::detail::NF_CAUCHY_DIST:
				break;
			case funclib::detail::NF_WEIBULL_DIST:
				break;
			case funclib::detail::NF_LOGNORM_DIST:
				break;
			case funclib::detail::NF_PARETO_DIST:
				break;
#if __cplusplus >= 201703L
			case funclib::detail::NF_ASSOC_LAGUERRE:
				break;
			case funclib::detail::NF_ASSOC_LEGENDRE:
				break;
			case funclib::detail::NF_BETA:
				break;
			case funclib::detail::NF_COMP_ELLINT_1:
				break;
			case funclib::detail::NF_COMP_ELLINT_2:
				break;
			case funclib::detail::NF_COMP_ELLINT_3:
				break;
			case funclib::detail::NF_CYL_BESSEL_I:
				break;
			case funclib::detail::NF_CYL_BESSEL_J:
				break;
			case funclib::detail::NF_CYL_BESSEL_K:
				break;
			case funclib::detail::NF_CYL_NEWMANN:
				break;
			case funclib::detail::NF_ELLINT_1:
				break;
			case funclib::detail::NF_ELLINT_2:
				break;
			case funclib::detail::NF_ELLINT_3:
				break;
			case funclib::detail::NF_EXPINT:
				break;
			case funclib::detail::NF_HERMITE:
				break;
			case funclib::detail::NF_LEGENDRE:
				break;
			case funclib::detail::NF_LAGUERRE:
				break;
			case funclib::detail::NF_ZETA:
				break;
			case funclib::detail::NF_SPH_BESSEL:
				break;
			case funclib::detail::NF_SPH_LEGENDRE:
				break;
			case funclib::detail::NF_SPH_NEUMANN:
#endif
			default:
				break;
			}
			return -1;
		}
	}

	class FuncSystem {
	public:
		FuncSystem() : m_fxs(std::make_shared<FunctionSet>()) {
			for (size_t i = 0; i < detail::NF_COUNT; i++)
			{
				m_nfxMap.insert(std::make_pair(function_names[i], i));
				int argc = 0;
				if (i < detail::NF_ASSOC_LAGUERRE) {
					argc = i < detail::NF_ATAN2 ? 1 : (i < detail::NF_NORMAL_DIST ? 2 : 3);
				}
				else {
					argc = function_arg_counts[i];
				}
				m_nfxData.emplace_back(function_names[i], function_descriptions[i], i, argc);
			}
		}

		Function CreateFunction(const std::string& signature, const std::string& body) {
			Tokenizer tokenizer(body);
			Parser parser;
			auto postfix = parser.ParseExpression(tokenizer.GetTokens());

			std::vector<Token> expr;
			for (const auto& tk : postfix) {

				switch (tk.GetType())
				{
				case funclib::TOKEN_FUNC:
				case funclib::TOKEN_NATIVEFUNC:
					expr.emplace_back(ResolveFunction(tk));
					break;
				case funclib::TOKEN_ID:
					expr.emplace_back(-1);
					break;
				case funclib::TOKEN_LITERAL:
					expr.emplace_back(std::stod(tk.GetText()));
					break;
				case funclib::TOKEN_OP_EXP:
					expr.emplace_back(TOKEN_OP_EXP);
					break;
				case funclib::TOKEN_OP_MUL:
					expr.emplace_back(TOKEN_OP_MUL);
					break;
				case funclib::TOKEN_OP_DIV:
					expr.emplace_back(TOKEN_OP_DIV);
					break;
				case funclib::TOKEN_OP_ADD:
					expr.emplace_back(TOKEN_OP_ADD);
					break;
				case funclib::TOKEN_OP_SUB:
					expr.emplace_back(TOKEN_OP_SUB);
					break;
				case funclib::TOKEN_OP_UN_NEG:
					expr.emplace_back(TOKEN_OP_UN_NEG);
					break;
				case funclib::TOKEN_OP_UN_POS:
					expr.emplace_back(TOKEN_OP_UN_POS);
					break;
				default:
					break;
				}
			}

			Function fx;
			fx.expr = expr;
			fx.m_foriegnFx = m_fxs;
		}

		double EvaluateString(const std::string& body) {

		}

	private:

		Token ResolveFunction(const ParseToken& token) {
			if (m_nfxMap.count(token.GetText()) > 0) {
				int addr = m_nfxMap.at(token.GetText());
				return Token(addr, m_nfxData[addr].argc, _ttype::TOKEN_NATIVEFUNC);
			}
			else if (m_fxs.get()->funcMap.count(token.GetText()) > 0) {
				int addr = m_fxs.get()->funcMap.at(token.GetText());
				return Token(addr, m_fxs.get()->funcSet[addr].argc, _ttype::TOKEN_FUNC);
			}
			else {
				throw std::runtime_error("Unrecognized function call");
			}
		}

		struct NFxData {
			std::string name;
			std::string desc;
			int idx;
			int argc;

			NFxData(const std::string& name, const std::string& desc, int idx, int argc):name(name), desc(desc),idx(idx),argc(argc){}
		};

		struct FunctionSet {
			std::vector<Function> funcSet;
			std::unordered_map<std::string, size_t> funcMap;
		};
		
		std::shared_ptr<FunctionSet> m_fxs;
		std::unordered_map<std::string, int> m_nfxMap;
		std::vector<NFxData> m_nfxData;

		static constexpr const char* function_names[] = {"acos","acosh","asin","asinh","atan","atanh","cbrt","ceil","cos","cosh","erf","erfinv",
			"erfc","exp","exp2","expm1","fabs","floor","lgamma","log","log10","log1p","log2","nearbyint","rint","round","sin","sinh","sqrt","tan",
			"tanh","tgamma","trunc","atan2","fmod","pow","hypot","remainder","gcd","lcm","npr","ncr",
			"exp_dist","chi2_dist","t_dist","normal_dist","gamma_dist","beta_dist","logistic_dist","cauchy_dist","weibull_dist","lognorm_dist","pareto_dist",
			"assoc_laguerre","assoc_legendre","beta","comp_ellint_1","comp_ellint_2","comp_ellint_3","cyl_bessel_i","cyl_bessel_j","cyl_bessel_k",
			"cyl_newmann","ellint_1","ellint_2","ellint_3","expint","hermite","legendre","laguerre","zeta","sph_bessel","sph_legendre","sph_neumann"
		};

		static constexpr const char* function_descriptions[] = {
			"Arc cosine",
			"Inverse hyperbolic cosine",
			"Arc sine",
			"Inverse hyperbolic sine",
			"Arc tangent",
			"Inverse hyperbolic tangent",
			"Cube root",
			"Ceiling",
			"Cosine",
			"Hyperbolic cosine",
			"Error function",
			"Inverse error function",
			"Complementary error function",
			"Exponential (e^x)",
			"Exponential (2^x)",
			"Exponential minus 1",
			"Absolute value",
			"Floor",
			"Natural logarithm of the gamma function",
			"Natural logarithm (base e)",
			"Common logarithm (base 10)",
			"Logarithm of 1 plus x",
			"Binary logarithm (base 2)",
			"Rounds to nearest integer, according to current rounding mode",
			"Rounds to nearest integer value, but returns as a double",
			"Rounds to nearest integer value, halfway cases away from zero",
			"Sine",
			"Hyperbolic sine",
			"Square root",
			"Tangent",
			"Hyperbolic tangent",
			"Gamma function",
			"Truncate",
			"Arc tangent of y/x",
			"Floating-point remainder of x/y",
			"x raised to the power y",
			"Hypotenuse (sqrt(x^2 + y^2))",
			"Remainder of x/y rounded to the nearest integer",
			"Greatest common divisor",
			"Least common multiple",
			"nPr",
			"nCr",
			"Exponential distribution",
			"Chi squared distribution",
			"T distribution",
			"Normal distribution",
			"Gamma distribution",
			"Beta distribution",
			"Logistic distribution",
			"Cauchy distribution",
			"Weibull distribution",
			"Log normal distribution",
			"Pareto distribution",
			"Associated Laguerre polynomials (n, m, x)",
			"Associated Legendre polynomials (n, m, x)",
			"Beta function",
			"Complete elliptic integral 1 kind",
			"Complete elliptic integral of the second kind",
			"Complete elliptic integral of the third kind",
			"Regular modified cylindrical Bessel functions (nu, x)",
			"Cylindrical Bessel functions (of the first kind) (nu, x)",
			"Irregular modified cylindrical Bessel functions (nu, x)",
			"Cylindrical Neumann functions (nu, x)",
			"Incomplete elliptic integral of the first kind (k, phi)",
			"Incomplete elliptic integral of the second kind (k, phi)",
			"Incomplete elliptic integral of the third kind (k, nu, phi)",
			"Exponential integral",
			"Hermite polynomials (n, x)",
			"Legendre polynomials (n, x)",
			"Laguerre polynomials (n, x)",
			"Riemann zeta function",
			"Spherical Bessel functions (of the first kind) (n, x)",
			"Spherical associated Legendre functions (l, m, theta)",
			"Spherical Neumann functions (n, x)"
		};
		// For C++ 17
		static constexpr const int function_arg_counts[] = {2,1,1,2,2,2,2,2,2,2,3,1,2,2,2,1,2,3,2};
	};	
}