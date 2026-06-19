#pragma once
#include <mlr/vector.hpp>

#pragma pack(push,1)
template<typename T>
struct quat : vec<4,T>
{
	template<scalar... S>
	constexpr INLINE quat(const S... args) requires(sizeof...(S) > 1) : vec<4,T>{ static_cast<T>(args)... } 
	{
	}
	template<size_t N_O, typename T_O>
	INLINE quat(const vec<N_O,T_O>& src)
	{
		#pragma omp simd
		for(size_t i = 0; i < std::min((size_t)4,N_O); i++)
			(*this)[i] = static_cast<T>(src[i]);
	}
	template<size_t N_O, typename T_O, scalar T_S>
	INLINE quat(const vec<N_O,T_O>& i, const T_S r) requires(N_O > 2)
	{
		#pragma omp simd
		for(size_t j = 0; j < 4; j++)
			(*this)[j] = j < 3 ? static_cast<T>(i[j]) : static_cast<T>(r);
	}
	template<typename T_RHS>
	INLINE quat<T>& operator*=(const T_RHS& other) requires(!scalar<T_RHS>)
	{
		return ((*this) = {this->w() * other + other.w() * (*this) + cross3(*this,other),this->w() * other.w() - (dot(*this,other,3)) });
	}
	constexpr INLINE T& real() { return this->w(); }
	constexpr INLINE operator vec<3,T>() const
	{
		return *reinterpret_cast<vec<3,T>*>(this);
	}
	constexpr INLINE operator T() const
	{
		return this->w();
	}
	/* reverse also known as the conjugate q* */
	constexpr INLINE quat<T> rev() { return this->sign(-1,-1,-1,1); }
	/* inverse quaternion q^-1 */
	constexpr INLINE quat<T> inv()
	{
		T mag = this->norm_squared();
		vec<4,T> dst = this->rev();
		if(mag != (T)1 && mag != (T)0)
			dst /= mag;
		return dst;
	}
};
#pragma pack(pop)
