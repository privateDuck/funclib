# funclib

## Description

**funclib** is a dynamic mathematical expression parsing and evaluation library designed to facilitate the definition and utilization of math functions at runtime. As a single header library, it is easy to integrate and use. Written in C++ for applications requiring flexible and efficient mathematical computations. It uses the common mathematical notations and semantics to describe the body of the function.
funclib currently supports functions from Rⁿ to R¹ domains. 

`funclib` comes pre-equipped with many common and useful mathematical functions. [List of predefined functions and operators](https://github.com/privateDuck/funclib?tab=readme-ov-file#predefined-functions-and-operators)

## Usage

To use `funclib`, follow these steps:

1. Include the header file `funclib.hpp`.
2. Create an instance of the `FuncVM` object.
3. Call the `create` function with the function signature and function body as parameters.
4. A `Function` object is returned.
5. Call the `Function` object with the appropriate arguments.

### Important!
* To use the special math functions provided by the C++ STL, you must enable the C++17 standard `std=c++17`.
* In MSVC, you also have to define `/Zc:__cplusplus` flag.

### Simple Example

```cpp
#include "funclib.hpp"

int main() {
    // Step 2: Create an instance of FuncVM
    funclib::FuncVM vm;

    // Step 3: Define a function with the signature "f(x)" and body "x * x"
    funclib::Function f = vm.CreateFunction("f(x)", "x * x");
    
    // Step 5: Call the function with an argument
    double result = f(5); // Should return 25
    std::cout << "f(5) = " << result << std::endl;
    
    // Another example with multiple arguments
    funclib::Function g = vm.CreateFunction("g(x, y)", "x + y * y");
    double result2 = g(3, 4); // Should return 19
    std::cout << "g(3, 4) = " << result2 << std::endl;
    
    // Example with calling user defined functions
    funclib::Function fog = vm.CreateFunction("fog(x,y)", "f(g(x,y))");
    double result3 = fog(3, 4); // Should return 19^2 = 361
    std::cout << "fog(3, 4) = " << result3 << std::endl;
}
```

## Predefined Functions and Operators

### Operators
* Factorial `!`
* Exponentiation `^`
* Multiplication `*` ( **Juxtaposition is supported** `i.e 2x will be considered as 2*x`)
* Division `/`
* Addition `+`
* Subtraction `-`

### Common Math Functions

* Arc cosine `acos`
* Inverse hyperbolic cosine `acosh`
* Arc sine `asin`
* Inverse hyperbolic sine `asinh`
* Arc tangent `atan`
* Inverse hyperbolic tangent `atanh`
* Cube root `cbrt`
* Ceiling `ceil`
* Cosine `cos`
* Hyperbolic cosine `cosh`
* Exponential (e^x) `exp`
* Exponential (2^x) `exp2`
* Exponential minus 1 `expm1`
* Absolute value `fabs`
* Floor `floor`
* Natural logarithm (base e) `ln`
* Common logarithm (base 10) `log`
* Logarithm of 1 plus x `log1p`
* Binary logarithm (base 2) `log2`
* Rounds to nearest integer, according to current rounding mode `nearbyint`
* Rounds to nearest integer value, but returns as a double `rint`
* Rounds to nearest integer value, halfway cases away from zero `round`
* Sine `sin`
* Hyperbolic sine `sinh`
* Square root `sqrt`
* Tangent `tan`
* Hyperbolic tangent `tanh`
* Truncate `trunc`
* Arc tangent of y/x `atan2`
* Floating-point remainder of x/y `fmod`
* x raised to the power y `pow`
* Hypotenuse (sqrt(x^2 + y^2)) `hypot`
* Remainder of x/y rounded to the nearest integer `remainder`
* Max of x and y `max`
* Min of x and y `min`
* Greatest common divisor `gcd`
* Least common multiple `lcm`
* nPr `npr`
* nCr `ncr`

### Probability Distributions
* Exponential distribution `exp_dist`
* Chi squared distribution `chi2_dist`
* T distribution `t_dist`
* Normal distribution `normal_dist`
* Gamma distribution `gamma_dist`
* Beta distribution `beta_dist`
* Logistic distribution `logistic_dist`
* Cauchy distribution `cauchy_dist`
* Weibull distribution `weibull_dist`
* Log normal distribution `lognorm_dist`
* Pareto distribution `pareto_dist`

### Special Functions
* Error function `erf`
* Inverse error function `erfinv`
* Complementary error function `erfc`
* Gamma function `gamma`
* Natural logarithm of the gamma function `lngamma`
* Associated Laguerre polynomials (n, m, x) `assoc_laguerre`
* Associated Legendre polynomials (n, m, x) `assoc_legendre`
* Beta function `beta`
* Complete elliptic integral 1 kind `comp_ellint_1`
* Complete elliptic integral of the second kind `comp_ellint_2`
* Complete elliptic integral of the third kind `comp_ellint_3`
* Regular modified cylindrical Bessel functions (nu, x) `cyl_bessel_i`
* Cylindrical Bessel functions (of the first kind) (nu, x) `cyl_bessel_j`
* Irregular modified cylindrical Bessel functions (nu, x) `cyl_bessel_k`
* Cylindrical Neumann functions (nu, x) `cyl_newmann`
* Incomplete elliptic integral of the first kind (k, phi) `ellint_1`
* Incomplete elliptic integral of the second kind (k, phi) `ellint_2`
* Incomplete elliptic integral of the third kind (k, nu, phi) `ellint_3`
* Exponential integral `expint`
* Hermite polynomials (n, x) `hermite`
* Legendre polynomials (n, x) `legendre`
* Laguerre polynomials (n, x) `laguerre`
* Riemann zeta function `zeta`
* Spherical Bessel functions (of the first kind) (n, x) `sph_bessel`
* Spherical associated Legendre functions (l, m, theta) `sph_legendre`
* Spherical Neumann functions (n, x) `sph_neumann`


## Examples and Benchmarks
* You can find the source code for the following test case and the examples in the **tests** directory


## Possible Improvements
* Optimizing the expression.
* Improving the expression evaluation procedure (possibly a bytecode interpreter)
* Support for the complex domain.
* Handling vector valued functions.







