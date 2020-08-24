#pragma once
#include <PathTracingCPU/Core.hpp>

namespace Alice::PathTracingCPU 
{
	template<typename Scalar,int Dimension>
	class TVector : public glm::vec<Dimension, Scalar>
	{
	public:
		typedef glm::vec<Dimension, Scalar> Base;
        TVector(Scalar value = static_cast<Scalar>(0)) : Base(value) { }
	};

	template<typename Scalar>
	class TVector<Scalar,2> : public glm::vec<2, Scalar>
	{
	public:
		typedef glm::vec<2, Scalar> Base;
		TVector(Scalar value = static_cast<Scalar>(0)) : Base(value) { }
		TVector(Scalar v1,Scalar v2) : Base(v1,v2) { }
	};

	template<typename Scalar>
	class TVector<Scalar, 3> : public glm::vec<3, Scalar>
	{
	public:
		typedef glm::vec<3, Scalar> Base;
		TVector(Scalar value = static_cast<Scalar>(0)) : Base(value) { }
		TVector(Scalar v1, Scalar v2, Scalar v3) : Base(v1, v2,v3) { }
	};

	template<typename Scalar>
	class TVector<Scalar, 4> : public glm::vec<4, Scalar>
	{
	public:
		typedef glm::vec<4, Scalar> Base;
		TVector(Scalar value = static_cast<Scalar>(0)) : Base(value) { }
		TVector(Scalar v1, Scalar v2, Scalar v3, Scalar v4) : Base(v1, v2, v3,v4) { }
	};

	template <typename Scalar, int Dimension> 
	class TPoint : public glm::vec<Dimension,Scalar>
	{
	public:
		typedef glm::vec<Dimension, Scalar> Base;
		TPoint(Scalar value = static_cast<Scalar>(0)) : Base(value) { }
	};

	template <typename Scalar>
	class TPoint<Scalar,2> : public glm::vec<2, Scalar>
	{
	public:
		typedef glm::vec<2, Scalar> Base;
		TPoint(Scalar value = static_cast<Scalar>(0)) : Base(value) { }
		TPoint(Scalar v1,Scalar v2) : Base(v1,v2) { }
	};

	template <typename Scalar>
	class TPoint<Scalar, 3> : public glm::vec<3, Scalar>
	{
	public:
		typedef glm::vec<3, Scalar> Base;
		TPoint(Scalar value = static_cast<Scalar>(0)) : Base(value) { }
		TPoint(Scalar v1, Scalar v2,Scalar v3) : Base(v1, v2,v3) { }
	};

	template <typename Scalar>
	class TPoint<Scalar, 4> : public glm::vec<4, Scalar>
	{
	public:
		typedef glm::vec<4, Scalar> Base;
		TPoint(Scalar value = static_cast<Scalar>(0)) : Base(value) { }
		TPoint(Scalar v1, Scalar v2,Scalar v3,Scalar v4) : Base(v1, v2,v3,v4) { }
	};

	using Normal3f = glm::vec3;

	template<typename S, int D>
	inline constexpr TPoint<S, D> operator+ (TPoint<S, D> p,TVector<S, D> v)
	{
		// point add vector and the result should be a point.
		return p + *(static_cast<glm::vec<D, S>*>(&v));
	}

	template<typename S, int D>
	inline constexpr TPoint<S, D> operator- (TPoint<S, D> p, TVector<S, D> v)
	{
		// point sub vector and the result should be a point.
		return p - static_cast<glm::vec<D, S>>(v);
	}

	template<typename S, int D>
	inline constexpr TVector<S, D> operator- (TPoint<S, D> p1, TPoint<S, D> p2)
	{
		// point sub point and the result should be a vector.
		return static_cast<glm::vec<D, S>>(p1 - p2);
	}

	template<typename Scalar, int Dimension>
	inline static std::string ToString(glm::vec<Dimension,Scalar> v)
	{
		std::string result;
		for (size_t i = 0; i < Dimension; ++i)
		{
			result += std::to_string(v[i]);
			if (i + 1 < Dimension)
				result += ", ";
		}
		return "(" + result + ")";
	}
}