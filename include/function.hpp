#pragma once
#include <vector>
#include <memory>
#include "token.hpp"

namespace funclib {

	

	class Function {
	public:
		double operator()(const std::vector<double>& args) {

		}

	private:
		double Invoke();
		std::vector<Token> expr;
		std::shared_ptr<class FuncSystem::FunctionSet> m_foriegnFx;
		size_t argc = 1;
		friend class FuncSystem;
	};

}