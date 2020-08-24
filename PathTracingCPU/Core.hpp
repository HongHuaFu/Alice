#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/random.hpp>
#include <algorithm>
#include <iostream>

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
		// 完美转发
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include <PathTracingCPU/Logger.hpp>