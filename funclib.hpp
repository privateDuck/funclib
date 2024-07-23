#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <memory>
#include <vector>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <stack>

namespace funclib {

#define FNL_PI 3.1415926535897932384626433832795
#define FNL_2PI 6.283185307179586476925286766559
#define FNL_4PI 12.566370614359172953850573533118
#define FNL_E 2.7182818284590452353602874713527
#define FNL_ACCESS_STACK(s,x) s.data[s.base + x]

	struct stack { 
		stack() : top(0), base(0), size(0), data(nullptr) {}
		stack(size_t size) : top(0), base(0), size(size), data(new double[size]) {}
		~stack() { delete[] data; }

		stack(const stack& o) : base(o.base), top(o.top), size(o.size) {
			data = new double[size];
			std::memcpy(data, o.data, sizeof(double) * size);
		}

		stack& operator=(const stack& o) {
			base = o.base;
			top = o.top;
			size = o.size;
			data = new double[size];
			std::memcpy(data, o.data, sizeof(double) * size);
			return *this;
		}

		stack(stack&& o) noexcept : data(std::move(o.data)), base(o.base), top(o.top), size(o.size) { o.data = nullptr; }

		stack& operator=(stack&& o) noexcept {
			base = o.base;
			top = o.top;
			size = o.size;
			data = std::move(o.data);
			o.data = nullptr;
			return *this;
		}

		inline void push(double value) {
			data[++top] = value;
		}

		double pop() {
			return data[top--];
		}

		double& peek() { return data[top]; }

		const double& peek() const { return data[top]; }

		double seek(int offset) const {
			assert(offset <= top);
			return data[top - offset];
		}

		double seek(int offset) {
			assert(offset <= top);
			return data[top - offset];
		}

		double& direct(int idx) {
			return data[idx];
		}

		const double& direct(int idx) const {
			return data[idx];
		}

		_NODISCARD unsigned int reserve_frame(unsigned int n) {
			unsigned int tmp = base;
			base = top - n + 1;
			return tmp;
		}

		_NODISCARD double& access(unsigned int address) {
			return data[base + address];
		}

		_NODISCARD const double& access(unsigned int address) const {
			return data[base + address];
		}

		void set_return_value(double value) {
			data[base] = value;
		}

		void pop_frame(unsigned int previous_base) {
			base = previous_base;
		}

		void pop_args(unsigned int n) {
			top -= n;
		}

		void mul_last() {
			data[top - 1] *= data[top];
			top--;
		}

		void add_last() {
			data[top - 1] += data[top];
			top--;
		}

		void sub_last() {
			data[top - 1] -= data[top];
			top--;
		}

		void div_last() {
			data[top - 1] /= data[top];
			top--;
		}

		void exp_last() {
			data[top - 1] = std::pow(data[top - 1], data[top]);
			top--;
		}

		void neg_last() {
			data[top] *= -1.0;
		}

		void clear() { top = 0; base = 0; }

		void resizeif() {
			if (top >= size) {
				double* tmp = new double[size * 2];
				std::memcpy(tmp, data, sizeof(double) * size);
				size *= 2;
				delete[] data;
				data = tmp;
			}
		}
		void resize() {
			double* tmp = new double[size * 2];
			std::memcpy(tmp, data, sizeof(double) * size);
			size *= 2;
			delete[] data;
			data = tmp;
		}
		unsigned int top = 0;
		unsigned int base = 0;
		unsigned int size;
		double* data;
	};

	struct FunctionSet {
		std::vector<class Function> funcSet;
		std::unordered_map<std::string, size_t> funcMap;
	};

	namespace detail {

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
			TOKEN_ARG,
			TOKEN_LITERAL, // holds constant numeric value
			TOKEN_ENDLINE,
			TOKEN_OP_EXP,
			TOKEN_OP_UN_FACT,
			TOKEN_OP_MUL,
			TOKEN_OP_DIV,
			TOKEN_OP_ADD,
			TOKEN_OP_SUB,
			TOKEN_OP_UN_NEG,
			TOKEN_OP_UN_POS,
			TOKEN_COLON,
			TOKEN_EOF
		};

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
			NF_MAX,				// Max of x and y (2 args)
			NF_MIN,				// Min of x and y (2 args)
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
		static double factorial(uint64_t n) {
			uint64_t fac = 1;
			for (uint32_t i = 1; i <= n; ++i) {
				fac *= i;
			}
			return fac;
		}
		static double gcd(int64_t a, int64_t b) {
			if (a == 0)
				return b;
			if (b == 0)
				return a;

			int64_t k;
			for (k = 0; ((a | b) & 1) == 0; ++k)
			{
				a >>= 1;
				b >>= 1;
			}

			while ((a & 1) == 0)
				a >>= 1;

			do
			{
				while ((b & 1) == 0)
					b >>= 1;

				if (a > b)
					std::swap(a, b);

				b = (b - a);
			} while (b != 0);

			return a << k;
		}
		static double lcm(int64_t a, int64_t b) {
			return (a * b) / gcd(a, b);
		}
		static double npr(uint64_t n, uint64_t r) {
			return factorial(n) / factorial(n - r);
		}
		static double ncr(uint64_t n, uint64_t r) {
			return factorial(n) / (factorial(r) * factorial(n - r));
		}
		static double expdist(const double x, const double y) {
			if (x < 0) return 0;
			return y * std::exp(-y * x);
		}
		static double chi2dist(const double x, const int64_t k) {
			if (x < 0 || k < 0) return 0;
			if (k < 64) {
				uint64_t k2 = k >> 1;
				double top = std::pow(x, k2 - 1) * std::exp(-x * 0.5);
				double bot = (1ull << k2) * std::tgamma(k2);
				return top / bot;
			}
			else {
				uint64_t k2 = k >> 1;
				double top = std::pow(x, k2 - 1) * std::exp(-x * 0.5);
				double bot = std::exp2(k2) * std::tgamma(k2);
				return top / bot;
			}
		}
		static double tdist(const double x, const int64_t k) {
			if (x < 0 || k < 0) return 0;
			uint64_t k2 = k >> 1;
			double t0 = (k + 1) * 0.5;
			double t1 = std::tgamma(t0);
			double t2 = std::sqrt(FNL_PI * k) * std::tgamma(k2);
			double t3 = 1.0 + ((x * x) / k);
			return (t1 / t2) * std::pow(t3, -t0);
		}
		static double normdist(const double x, const double m, const double a) {
			if (a < 0) return 0;
			double t1 = 1.0 / (a * std::sqrt(FNL_2PI));
			double z = (x - m) / a;
			double t2 = std::exp(-0.5 * z * z);
			return t1 * t2;
		}
		static double gammadist(const double x, const double a, const double b) {
			const double t1 = std::pow(b, a) / std::tgamma(a);
			const double t2 = std::pow(x, a - 1) * std::exp(-b * x);
			return t1 * t2;
		}
		static double betadist(const double x, const double a, const double b) {
			if (x < 0 || x > 1) return 0;
			const double t1 = std::pow(x, a - 1) * std::pow(1 - x, b - 1);
			const double B = std::tgamma(a) * std::tgamma(b) / std::tgamma(a + b);
			return t1 / B;
		}
		static double logisticdist(const double x, const double u, const double s) {
			if (s < 0) return 0;
			const double z = (x - u) / s;
			const double t1 = std::exp(-z);
			const double t2 = s * (1 + t1) * (1 + t1);
			return t1 / t2;
		}
		static double cauchydist(const double x, const double x0, const double y) {
			if (y < 0) return 0;
			const double xc = (x - x0) / y;
			return 1.0 / (FNL_PI * y * (1 + xc * xc));
		}
		static double weibulldist(const double x, const double k, const double y) {
			if (x < 0 || k < 0 || y < 0) return 0;
			const double xy = x / y;
			const double xyc = std::pow(xy, k);
			const double t1 = (k / y) * xyc / (xy);
			const double t2 = std::exp(-xyc);
			return t1 * t2;
		}
		static double lognormdist(const double x, const double u, const double a) {
			if (x < 0 || a < 0) return 0;
			return normdist(std::log(x), u, a) / x;
		}
		static double paretodist(const double x, const double xm, const double a) {
			if (xm < 0 || a < 0 || x < xm) return 0;
			return a * std::pow(xm, a) / std::pow(x, a + 1);
		}
		static double mlog(const double a)
		{
			int e = 0;
			double m = frexp(a, &e);
			if (m < 0.666666667) { // 0x1.555556p-1
				m = m + m;
				e = e - 1.0;
			}
			double i = (double)e;
			// m in [2/3, 4/3]
			m = m - 1.0;
			double s = m * m;
			// Compute log1p(m) for m in [-1/3, 1/3]
			double r = -0.130310059;  // -0x1.0ae000p-3
			double t = 0.140869141;  //  0x1.208000p-3
			r = fma(r, s, -0.121484190); // -0x1.f19968p-4
			t = fma(t, s, 0.139814854); //  0x1.1e5740p-3
			r = fma(r, s, -0.166846052); // -0x1.55b362p-3
			t = fma(t, s, 0.200120345); //  0x1.99d8b2p-3
			r = fma(r, s, -0.249996200); // -0x1.fffe02p-3
			r = fma(t, m, r);
			r = fma(r, m, 0.333331972); //  0x1.5554fap-2
			r = fma(r, m, -0.500000000); // -0x1.000000p-1
			r = fma(r, s, m);
			r = fma(i, 0.693147182, r); //  0x1.62e430p-1 // log(2)
			if (!((a > 0.0) && (a <= 3.40282346e+38))) { // 0x1.fffffep+127
				r = a + a;  // silence NaNs if necessary
				if (a < 0.0) r = 0; //  NaN
				if (a == 0.0) r = -INFINITY; // -Inf
			}
			return r;
		}

		static double erfinv(const double a)
		{
			double p = 0.0;
			double t = fma(a, 0.0 - a, 1.0);
			t = mlog(t);
			if (fabs(t) > 6.125) {
				p = 3.03697567e-10;
				p = fma(p, t, 2.93243101e-8);  
				p = fma(p, t, 1.22150334e-6);  
				p = fma(p, t, 2.84108955e-5);  
				p = fma(p, t, 3.93552968e-4);  
				p = fma(p, t, 3.02698812e-3); 
				p = fma(p, t, 4.83185798e-3); 
				p = fma(p, t, -2.64646143e-1);
				p = fma(p, t, 8.40016484e-1); 
			}
			else { 
				p = 5.43877832e-9;
				p = fma(p, t, 1.43285448e-7);  
				p = fma(p, t, 1.22774793e-6);  
				p = fma(p, t, 1.12963626e-7);  
				p = fma(p, t, -5.61530760e-5);
				p = fma(p, t, -1.47697632e-4);
				p = fma(p, t, 2.31468678e-3); 
				p = fma(p, t, 1.15392581e-2); 
				p = fma(p, t, -2.32015476e-1); 
				p = fma(p, t, 8.86226892e-1); 
			}
			double r = a * p;
			return r;
		}
		static double ResolveNativeFunction(stack& stack, size_t idx, size_t base) {
			_NativeFunctions ft = (_NativeFunctions)idx;
			switch (ft)
			{
			case funclib::detail::NF_ACOS:
				return std::acos(stack.seek(0));
			case funclib::detail::NF_ACOSH:
				return std::acosh(stack.seek(0));
			case funclib::detail::NF_ASIN:
				return std::asin(stack.seek(0));
			case funclib::detail::NF_ASINH:
				return std::asinh(stack.seek(0));
			case funclib::detail::NF_ATAN:
				return std::atan(stack.seek(0));
			case funclib::detail::NF_ATANH:
				return std::atanh(stack.seek(0));
			case funclib::detail::NF_CBRT:
				return std::cbrt(stack.seek(0));
			case funclib::detail::NF_CEIL:
				return std::ceil(stack.seek(0));
			case funclib::detail::NF_COS:
				return std::cos(stack.seek(0));
			case funclib::detail::NF_COSH:
				return std::cosh(stack.seek(0));
			case funclib::detail::NF_ERF:
				return std::erf(stack.seek(0));
			case funclib::detail::NF_ERFINV:
				return erfinv(stack.seek(0));
			case funclib::detail::NF_ERFC:
				return std::erfc(stack.seek(0));
			case funclib::detail::NF_EXP:
				return std::exp(stack.seek(0));
			case funclib::detail::NF_EXP2:
				return std::exp2(stack.seek(0));
			case funclib::detail::NF_EXPM1:
				return std::expm1(stack.seek(0));
			case funclib::detail::NF_FABS:
				return std::fabs(stack.seek(0));
			case funclib::detail::NF_FLOOR:
				return std::floor(stack.seek(0));
			case funclib::detail::NF_LGAMMA:
				return std::lgamma(stack.seek(0));
			case funclib::detail::NF_LOG:
				return std::log(stack.seek(0));
			case funclib::detail::NF_LOG10:
				return std::log10(stack.seek(0));
			case funclib::detail::NF_LOG1P:
				return std::log1p(stack.seek(0));
			case funclib::detail::NF_LOG2:
				return std::log2(stack.seek(0));
			case funclib::detail::NF_NEARBYINT:
				return std::nearbyint(stack.seek(0));
			case funclib::detail::NF_RINT:
				return std::rint(stack.seek(0));
			case funclib::detail::NF_ROUND:
				return std::round(stack.seek(0));
			case funclib::detail::NF_SIN:
				return std::sin(stack.seek(0));
			case funclib::detail::NF_SINH:
				return std::sinh(stack.seek(0));
			case funclib::detail::NF_SQRT:
				return std::sqrt(stack.seek(0));
			case funclib::detail::NF_TAN:
				return std::tan(stack.seek(0));
			case funclib::detail::NF_TANH:
				return std::tanh(stack.seek(0));
			case funclib::detail::NF_TGAMMA:
				return std::tgamma(stack.seek(0));
			case funclib::detail::NF_TRUNC:
				return std::trunc(stack.seek(0));
			case funclib::detail::NF_ATAN2:
				return std::atan2(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_FMOD:
				return std::fmod(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_POW:
				return std::pow(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_HYPOT:
				return std::hypot(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_REMAINDER:
				return std::remainder(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_MAX:
				return std::max(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_MIN:
				return std::min(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_GCD:
				return gcd(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_LCM:
				return lcm(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_NPR:
				return npr(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_NCR:
				return ncr(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_EXP_DIST:
				return expdist(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_CHI2_DIST:
				return chi2dist(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_T_DIST:
				return tdist(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_NORMAL_DIST:
				return normdist(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_GAMMA_DIST:
				return gammadist(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_BETA_DIST:
				return betadist(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_LOGISTIC_DIST:
				return logisticdist(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_CAUCHY_DIST:
				return cauchydist(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_WEIBULL_DIST:
				return weibulldist(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_LOGNORM_DIST:
				return lognormdist(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_PARETO_DIST:
				return paretodist(stack.seek(2), stack.seek(1), stack.seek(0));
#if __cplusplus >= 201703L
			case funclib::detail::NF_ASSOC_LAGUERRE:
				return std::assoc_laguerre(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_ASSOC_LEGENDRE:
				return std::assoc_legendre(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_BETA:
				return std::beta(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_COMP_ELLINT_1:
				return std::comp_ellint_1(stack.seek(0));
			case funclib::detail::NF_COMP_ELLINT_2:
				return std::comp_ellint_2(stack.seek(0));
			case funclib::detail::NF_COMP_ELLINT_3:
				return std::comp_ellint_3(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_CYL_BESSEL_I:
				return std::cyl_bessel_i(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_CYL_BESSEL_J:
				return std::cyl_bessel_j(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_CYL_BESSEL_K:
				return std::cyl_bessel_k(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_CYL_NEWMANN:
				return std::cyl_neumann(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_ELLINT_1:
				return std::ellint_1(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_ELLINT_2:
				return std::ellint_2(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_ELLINT_3:
				return std::ellint_3(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_EXPINT:
				return std::expint(stack.seek(0));
			case funclib::detail::NF_HERMITE:
				return std::hermite(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_LEGENDRE:
				return std::legendre(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_LAGUERRE:
				return std::laguerre(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_ZETA:
				return std::riemann_zeta(stack.seek(0));
			case funclib::detail::NF_SPH_BESSEL:
				return std::sph_bessel(stack.seek(1), stack.seek(0));
			case funclib::detail::NF_SPH_LEGENDRE:
				return std::sph_legendre(stack.seek(2), stack.seek(1), stack.seek(0));
			case funclib::detail::NF_SPH_NEUMANN:
				return std::sph_neumann(stack.seek(1), stack.seek(0));
#endif
			default:
				break;
			}
			return -1;
		}

		struct ParseToken {
		public:
			ParseToken() : type(TOKEN_EOF), text() {}
			ParseToken(_ttype type, const std::string& text) : type(type), text(text) {
				switch (type)
				{
				case TOKEN_OP_UN_FACT:
					precedence = 9;
					break;
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
			inline void SetToArgument() { type = TOKEN_ARG; }

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
			Token(uint64_t address, int argc, _ttype type) : type(type), arg(argc) { data.address = address; }

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
				case '!':
					type = TOKEN_OP_UN_FACT;
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

			_tdata data;
			_ttype type;
			int arg;
		};

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

		class Tokenizer {
		public:
			Tokenizer(const std::string& input) : input(input) {}

			std::vector<ParseToken> GetTokens() {
				std::vector< ParseToken> tokens;
				TokenizeFirstPass(tokens);
				TokenizeSecondPass(tokens);
				return tokens;
			}

			std::vector<ParseToken> GetTokens(const std::unordered_set<std::string>& all_fx) {
				std::vector< ParseToken> tokens;
				TokenizeFirstPass(tokens);
				TokenizeSecondPass(tokens);
				Functionize(tokens, all_fx);
				TokenizeFinalPass(tokens);
				return tokens;
			}

			void Reset(const std::string& new_input) {
				input = new_input;
				currentChar = '\0';
				currentPos = 0;
			}
		private:
			void TokenizeFirstPass(std::vector<ParseToken>& tokens)
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
			void TokenizeSecondPass(std::vector<ParseToken>& tokens)
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
					if (
						(tokens[i].IsOperand() && tokens[i + 1].IsOperand())
						||
						(tokens[i].GetType() == TOKEN_OP_UN_FACT && (tokens[i + 1].IsID() || tokens[i + 1].IsNumeric() || tokens[i + 1].IsLP()))
						)
					{
						tokens.emplace(tokens.begin() + i + 1, ParseToken(TOKEN_OP_MUL, "*"));
						i++;
					}
				}

				tokens.emplace_back(TOKEN_EOF, "\0");
			}
			void Functionize(std::vector<ParseToken>& tokens, const std::unordered_set<std::string>& all_fx) {
				for (auto& tkn : tokens) {
					if (all_fx.count(tkn.GetText()) > 0) tkn.SetToFunc();
				}
			}
			void TokenizeFinalPass(std::vector<ParseToken>& tokens) {
				for (size_t i = 0; i < tokens.size(); i++)
				{
					if ((tokens[i].IsID() || tokens[i].IsNumeric() || tokens[i].IsRP()) && tokens[i + 1].IsLP())
					{
						tokens.emplace(tokens.begin() + i + 1, ParseToken(TOKEN_OP_MUL, "*"));
						i++;
					}
				}
			}
			ParseToken GetStrToken()
			{
				std::string buf(1, input[currentPos++]);
				while (input[currentPos] == '_' || std::isalnum(input[currentPos])) {
					buf += input[currentPos];
					currentPos++;
				}
				return ParseToken(TOKEN_ID, buf);
			}
			ParseToken GetDigitToken()
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
			ParseToken GetSingleCharToken()
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
				case '!':
					return ParseToken(TOKEN_OP_UN_FACT, ":");
				case '\n':
					return ParseToken(TOKEN_ENDLINE, "\n");
				case ',':
					return ParseToken(TOKEN_COMMA, ",");
				case '(':
					return ParseToken(TOKEN_LP, "(");
				case ')':
					return ParseToken(TOKEN_RP, ")");
				case ':':
					return ParseToken(TOKEN_COLON, ":");
				default:
					return ParseToken(TOKEN_EOF, "\0");
				}
			}

			char currentChar = '\0';
			size_t currentPos = 0;
			std::string input;
		};

		class Parser {
		public:
			Parser() { }

			inline bool ParseSignature(const std::vector<ParseToken>& tokens,
				std::string& function_name,
				std::vector<std::string>& arguments,
				std::vector<std::string>& parameters)
			{
				tokenStream = tokens;
				bool success = false;
				try {
					success = S();
				}
				catch (std::runtime_error) {
					return false;
				}
				arguments = args;
				parameters = params;
				function_name = funcname;
				readingParams = false;
				currentIndex = 0;
				tokenStream.clear();
				return success;
			}

			inline std::vector<ParseToken> ParseExpression(const std::vector< ParseToken>& tokens) {
				std::vector<ParseToken> arguments;
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

		private:
			std::vector<ParseToken> tokenStream;
			size_t currentIndex = 0;
			bool readingParams = false;
			std::string funcname;
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
				throw std::runtime_error("Signature Error: Expected '" + GetTokenText(sym) + "'. Found '" + tokenStream[currentIndex].GetText() + "'.");
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

	class Function {
	public:

		Function() : m_stackSize(0), m_localStack() {}

		// Call the function with given arguments
		double operator()(const std::vector<double>& args) {
			m_localStack.clear();
			for (size_t i = 0; i < m_argc; i++)
				m_localStack.push(args[i]);
			auto base = m_localStack.reserve_frame(m_argc);
			return Invoke(m_localStack);
		}

		// Call the function with given variables and parameters
		double operator()(const std::vector<double>& variables, const std::vector<double>& params) {
			m_localStack.clear();
			for(const auto v : variables)
				m_localStack.push(v);
			for (const auto p : params)
				m_localStack.push(p);
			auto base = m_localStack.reserve_frame(m_argc);
			return Invoke(m_localStack);
		}

		// Call the function with given arguments
		template <typename ...Args>
		double operator()(Args...args) {
			m_localStack.clear();
			uint32_t i = 0;
			for (const double p : { args... }) {
				if (i >= m_argc) break;
				m_localStack.push(p);
				i++;
			}
			auto base = m_localStack.reserve_frame(m_argc);
			return Invoke(m_localStack);
		}
		
		// Call the function with previously set arguments
		double Call() {
			return Invoke(m_localStack);
		}

		// Set function arguments
		template <typename ...Args>
		void SetArgs(Args...args) {
			m_localStack.clear();
			uint32_t i = 0;
			for (const double p : { args... }) {
				if (i >= m_argc) break;
				m_localStack.push(p);
				i++;
			}
			auto base = m_localStack.reserve_frame(m_argc);
		}

		// Set function arguments
		void SetArgs(const std::vector<double>& args) {
			m_localStack.clear();
			for (size_t i = 0; i < m_argc; i++)
				m_localStack.push(args[i]);
			auto base = m_localStack.reserve_frame(m_argc);
		}
private:

		Function(size_t stksz) : m_stackSize(stksz), m_localStack(stksz) {}

		double Invoke(stack& stack) const {
			for (const auto& tk : m_expr)
			{
				switch (tk.type)
				{
				case funclib::detail::TOKEN_FUNC:
				{
					const Function& fx = m_foriegnFx.get()->funcSet.at(tk.data.address);
					uint32_t base = stack.reserve_frame(fx.m_argc);
					double result = fx.Invoke(stack);
					stack.pop_frame(base);
					stack.push(result);
					break;
				}
				case funclib::detail::TOKEN_NATIVEFUNC:
				{
					double res = detail::ResolveNativeFunction(stack, tk.data.address, 0);
					stack.pop_args(tk.arg);
					stack.push(res);
					break;
				}
				case funclib::detail::TOKEN_ID:
				{
					stack.push(FNL_ACCESS_STACK(stack, tk.data.address));
					break;
				}
				case funclib::detail::TOKEN_LITERAL:
				{
					stack.push(tk.data.value);
					break;
				}
				case funclib::detail::TOKEN_OP_EXP:
				{
					stack.exp_last();
					break;
				}
				case funclib::detail::TOKEN_OP_MUL:
				{
					stack.mul_last();
					break;
				}
				case funclib::detail::TOKEN_OP_DIV:
				{
					stack.div_last();
					break;
				}
				case funclib::detail::TOKEN_OP_ADD:
				{
					stack.add_last();
					break;
				}
				case funclib::detail::TOKEN_OP_SUB:
				{
					stack.sub_last();
					break;
				}
				case funclib::detail::TOKEN_OP_UN_NEG:
				{
					stack.neg_last();
					break;
				}
				case funclib::detail::TOKEN_OP_UN_FACT:
				{
					uint64_t oprnd = (uint64_t)stack.pop();
					uint64_t fac = detail::factorial(oprnd);
					stack.push(fac);
					break;
				}
				case funclib::detail::TOKEN_OP_UN_POS:
				default:
					break;
				}
			}
			return stack.pop();
		}

		std::vector<detail::Token> m_expr;
		std::shared_ptr<struct FunctionSet> m_foriegnFx;
		size_t m_argc = 1;
		size_t m_stackSize;
		stack m_localStack;
		friend class FuncVM;
	};

	class FuncVM {
	public:
		FuncVM() : m_fxs(std::make_shared<FunctionSet>()) {
			for (size_t i = 0; i < detail::NF_COUNT; i++)
			{
				m_nfxMap.insert(std::make_pair(function_names[i], i));
				int argc = 0;
				if (i < detail::NF_ASSOC_LAGUERRE) {
					argc = i < detail::NF_ATAN2 ? 1 : (i < detail::NF_NORMAL_DIST ? 2 : 3);
				}
				else {
					argc = function_arg_counts[i - detail::NF_ASSOC_LAGUERRE];
				}
				m_nfxData.emplace_back(function_names[i], function_descriptions[i], i, argc);
				all_fxs.insert(function_names[i]);
			}
		}

		_NODISCARD Function CreateFunction(const std::string& signature, const std::string& body) {
			std::string name;
			std::vector<std::string> args, params;
			std::vector<detail::ParseToken> postfix;

			try
			{
				detail::Tokenizer body_tokens(body);
				detail::Tokenizer sig_tokens(signature);
				detail::Parser parser;

				postfix = parser.ParseExpression(body_tokens.GetTokens(all_fxs));
				parser.ParseSignature(sig_tokens.GetTokens(), name, args, params);
				if (all_fxs.count(name) > 0) throw std::runtime_error("Function with this name already exists!");
			}
			catch (std::runtime_error e){
				hasError = true;
				errorMsg = e.what();
				return Function();
			}

			std::vector<detail::Token> expr;
			for (const auto& tk : postfix) {

				switch (tk.GetType())
				{
				case funclib::detail::TOKEN_FUNC:
				case funclib::detail::TOKEN_ID:
					expr.emplace_back(ResolveID(tk,args,params));
					break;
				case funclib::detail::TOKEN_LITERAL:
					expr.emplace_back(std::stod(tk.GetText()));
					break;
				case funclib::detail::TOKEN_OP_EXP:
					expr.emplace_back('^',false);
					break;
				case funclib::detail::TOKEN_OP_MUL:
					expr.emplace_back('*', false);
					break;
				case funclib::detail::TOKEN_OP_DIV:
					expr.emplace_back('/',false);
					break;
				case funclib::detail::TOKEN_OP_ADD:
					expr.emplace_back('+',false);
					break;
				case funclib::detail::TOKEN_OP_SUB:
					expr.emplace_back('-',false);
					break;
				case funclib::detail::TOKEN_OP_UN_FACT:
					expr.emplace_back('!', true);
					break;
				case funclib::detail::TOKEN_OP_UN_NEG:
					expr.emplace_back('-',true);
					break;
				case funclib::detail::TOKEN_OP_UN_POS:
					expr.emplace_back('+',true);
					break;
				default:
					break;
				}
			}

			size_t stackSz = ComputeStackSize(expr) + args.size() + params.size();
			Function fx(stackSz);

			fx.m_expr = expr;
			fx.m_foriegnFx = m_fxs;
			fx.m_argc = args.size() + params.size();

			m_fxs.get()->funcSet.emplace_back(fx);
			m_fxs.get()->funcMap.insert({ name, m_fxs.get()->funcSet.size() - 1});
			all_fxs.insert(name);

			return fx;
		}

		_NODISCARD Function FindFunction(const std::string& name) {
			if (m_fxs.get()->funcMap.count(name) > 0) {
				auto idx = m_fxs.get()->funcMap.at(name);
				return m_fxs.get()->funcSet.at(idx);
			}
			throw std::runtime_error("No such function can be found");
		}

		inline bool HasError() const { return hasError; }

		inline std::string GetError() const { return errorMsg; }

	private:

		uint64_t GetAddress(const std::string& text) {
			addressMap.insert({ text, addressCounter });
			addressCounter++;
			return addressMap.at(text);
		}

		detail::Token ResolveID(const detail::ParseToken& token, const std::vector<std::string>& args, const std::vector<std::string>& params) {
			if (m_nfxMap.count(token.GetText()) > 0) {
				int addr = m_nfxMap.at(token.GetText());
				return detail::Token(addr, m_nfxData[addr].argc, detail::_ttype::TOKEN_NATIVEFUNC);
			}
			else if (m_fxs.get()->funcMap.count(token.GetText()) > 0) {
				int addr = m_fxs.get()->funcMap.at(token.GetText());
				return detail::Token(addr, m_fxs.get()->funcSet.at(addr).m_argc, detail::_ttype::TOKEN_FUNC);
			}
			else if (token.GetText() == "pi") return detail::Token((double)FNL_PI);
			else if (token.GetText() == "e") return detail::Token((double)FNL_E);
			else {
				for(uint64_t i = 0; i < args.size(); i++) if(args[i] == token.GetText()) return detail::Token((uint64_t)i);
				for (uint64_t i = 0; i < params.size(); i++) if (params[i] == token.GetText()) return detail::Token((uint64_t)(i + args.size()));
				throw std::runtime_error("Unidentified indentifer!");
			}
		}

		size_t ComputeStackSize(const std::vector<detail::Token>& expr) {
			size_t count = expr.size();
			for (const auto& tk : expr)
			{
				switch (tk.type)
				{
				case funclib::detail::TOKEN_FUNC:
				{
					const Function& fx = m_fxs.get()->funcSet.at(tk.data.address);
					count += fx.m_expr.size() + fx.m_argc;
					break;
				}
				case funclib::detail::TOKEN_ID:
				case funclib::detail::TOKEN_LITERAL:
					count++;
					break;
				default:
					break;
				}
			}
			return count;
		}

		struct NFxData {
			std::string name;
			std::string desc;
			int idx;
			int argc;

			NFxData(const std::string& name, const std::string& desc, int idx, int argc):name(name), desc(desc),idx(idx),argc(argc){}
		};
		
		std::shared_ptr<FunctionSet> m_fxs;
		std::unordered_map<std::string, int> m_nfxMap;
		std::vector<NFxData> m_nfxData;
		std::unordered_map<std::string, uint64_t> addressMap;
		std::unordered_set<std::string> all_fxs;

		bool hasError = false;
		std::string errorMsg;

		static constexpr const char* function_names[] = {"acos","acosh","asin","asinh","atan","atanh","cbrt","ceil","cos","cosh","erf","erfinv",
			"erfc","exp","exp2","expm1","fabs","floor","lngamma","ln","log","log1p","log2","nearbyint","rint","round","sin","sinh","sqrt","tan",
			"tanh","gamma","trunc","atan2","fmod","pow","hypot","remainder","max","min","gcd","lcm","npr","ncr",
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
			"Max of x and y",
			"Min of x and y",
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

		uint64_t addressCounter = 0;
	};	
}