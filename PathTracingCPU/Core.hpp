#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/random.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>

#if !defined(_WIN32) && !defined(_WIN64)
#error "Alice only support windows platform."
#endif

#ifndef ALICE_ASSERT_ENABLE
#define ALICE_ASSERT(x,...){ \
		if(!(x)){ \
			ALICE_ERROR_CORE("Assert error: {0}", __VA_ARGS__); \
			__debugbreak(); \
		} \
	}
#else
#define ALICE_ASSERT(x,...)
#endif // ALICE_ASSERT_ENABLE

namespace Alice::PathTracingCPU
{
	/// Global math values.
	auto constexpr Epsilon = glm::epsilon<float>();

	/// Glbal math functions.

	// Judge vector nan value.
	template<typename Scalar, int Dimension>
	inline static bool HasNaN(const glm::vec<Dimension, Scalar>& v)
	{
		std::string result;
		for (size_t i = 0; i < Dimension; ++i)
		{
			if (glm::isnan(v[i]))
				return true;
		}
		return false;
	}

	template<typename Scalar, int Dimension>
	inline static auto Inverse(const glm::vec<Dimension, Scalar>& v)
	{
		glm::vec<Dimension, Scalar> result;
		for (size_t i = 0; i < Dimension; ++i)
		{
			result[i] = static_cast<Scalar>(1) / v[i];
		}
		return result;
	}

	template<typename T>
	inline static std::string ToString(const T& v)
	{
		std::stringstream ss;
		ss << v;
		return ss.str();
	}

	// Forward declaration.
	template <typename Scalar, int Dimension>  
	class TVector;
	template <typename Scalar, int Dimension>  
	class TPoint;

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include <PathTracingCPU/Logger.hpp>