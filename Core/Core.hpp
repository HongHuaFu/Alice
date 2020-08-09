#pragma once
#include <memory>

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

namespace Alice
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include <Logger.hpp>