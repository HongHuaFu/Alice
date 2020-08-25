#pragma once
#include <PathTracingCPU/Vector.hpp>
#include <PathTracingCPU/Core.hpp>

namespace Alice::PathTracingCPU::UintTest 
{
	/// Deprecate. 
#if UseTVector
	class TVectorTest 
	{
	public:
		inline static bool ConstructAssert() 
		{
			auto a = TVectorTest::ConstructTest<float, 3>(4);
			ALICE_ASSERT(a.x == a.y && a.x == a.z && a.x == 4.0f,"Error construct!");
			auto b = TVectorTest::ConstructTest<int, 2>(1);
			ALICE_ASSERT(b.x == b.y && b.x == 1, "Error construct!");
			auto c = TVectorTest::ConstructTest<double, 4>(3.14);
			ALICE_ASSERT(c.x == c.y && c.w == 3.14, "Error construct!");
			auto d = TVectorTest::ConstructTest<float, 1>(-0);
			ALICE_ASSERT(d.x == 0, "Error construct!");

			std::cout << ToString(a) << std::endl;
			std::cout << ToString(b) << std::endl;
			std::cout << ToString(c) << std::endl;
			std::cout << ToString(d) << std::endl;

			auto aa = TVector<float, 2>(1.2f, 3.2f);
			std::cout << ToString(aa) << std::endl;
			auto bb = TVector<int, 4>(2, 4, 66, 0);
			std::cout << ToString(bb) << std::endl;

			auto cc = TPoint<float, 2>(1.2f, 3.2f);
			std::cout << ToString(cc) << std::endl;
			auto dd = TPoint<int, 3>(2, 4, 66);
			std::cout << ToString(dd) << std::endl;
			auto ee = TPoint<int, 1>(2);
			std::cout << ToString(ee) << std::endl;
			auto ef = TPoint<int, 4>(2);
			std::cout << ToString(ef) << std::endl;

			auto df = Normal3f(0, 1, 3);
			std::cout << ToString(df) << std::endl;

			return true;
		}

		inline static bool MathRule() 
		{
			auto a = TVector<float,3>(2.0f, 2.0f, 2.0f);
			auto b = TPoint<float, 3>(2.0f, 2.0f, 2.0f);
			auto c = b + b;
			auto d = b + a;

			return true;
		}

	private:
		template<typename S,int D>
		inline static auto ConstructTest(S v) 
		{
			return TVector<S, D>(v);
		}
	};
#endif
}