#pragma once
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cmath>
#include <array>

#ifdef _MSC_VER
#define INLINE __force_inline __flatten __declspec(nothrow) inline
#define CONST __declspec(noalias)
#else
#define INLINE __attribute__((always_inline,flatten,nothrow)) inline
#define CONST __attribute__((const))
#endif


template<typename T>
concept scalar = std::integral<T> || std::floating_point<T>;

template<typename T>
struct ops
{
	template<typename T_RHS>
	INLINE T& operator=(const T_RHS& rhs) requires(rhs.size() > 0)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < std::min(dst.size(),rhs.size()); i++)
			dst[i] = rhs[i];
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator=(const T_RHS& rhs) requires(scalar<T>)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < dst.size(); i++)
			dst[i] = rhs;
		return dst;
	}

	template<typename T_RHS>
	INLINE T& operator+=(const T_RHS& other) requires(other.size() > 0)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < std::min(dst.size(),other.size()); i++)
			dst[i] += other[i];
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator-=(const T_RHS& other) requires(other.size() > 0)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < std::min(dst.size(),other.size()); i++)
			dst[i] -= other[i];
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator*=(const T_RHS& other) requires(other.size() > 0)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < std::min(dst.size(),other.size()); i++)
			dst[i] *= other[i];
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator/=(const T_RHS& other) requires(other.size() > 0)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < std::min(dst.size(),other.size()); i++)
			dst[i] /= other[i];
		return dst;
	}
	template<typename T_LHS>
	friend constexpr INLINE T operator+(const T_LHS& lhs, const T& rhs) { return (T{lhs} += rhs); }
	template<typename T_LHS>
	friend constexpr INLINE T operator-(const T_LHS& lhs, const T& rhs) { return (T{lhs} -= rhs); }
	template<typename T_LHS>
	friend constexpr INLINE T operator*(const T_LHS& lhs, const T& rhs) { return (T{lhs} *= rhs); }
	template<typename T_LHS>
	friend constexpr INLINE T operator/(const T_LHS& lhs, const T& rhs) { return (T{lhs} /= rhs); }
};

template<size_t N, typename T, size_t N_POW2 = std::bit_ceil<size_t>(N)>
struct alignas((N == N_POW2 ? N : 1) * alignof(T)) vec : std::array<T,N>, ops<vec<N,T>>
{
	template<scalar... S>
	constexpr INLINE vec(const S... args) requires(sizeof...(S) > 1) : std::array<T,N>{ static_cast<T>(args)... } 
	{
	}

	INLINE vec(const T& src)
	{
		#pragma omp simd
		for(size_t i = 0; i < N; i++)
			(*this)[i] = src;
	}
	template<size_t N_O, typename T_O>
	INLINE vec(const vec<N_O,T_O>& src) 
	{
		#pragma omp simd
		for(size_t i = 0; i < std::min(N,src.size()); i++)
			(*this)[i] = src[i];
	}
	template<typename... I>
	constexpr INLINE vec<sizeof...(I),T> perm(const I... args) const { return vec<sizeof...(I),T>{ (*this)[args % N]... }; }
};

template<size_t N_A, typename T_A, size_t N_B, typename T_B, typename T_DST = decltype((T_A)1 * (T_B)1 + (T_A)2 * (T_B)2)>
INLINE T_DST dot(const vec<N_A,T_A>& a, vec<N_B,T_B>& b, size_t N = std::min(N_A,N_B), double seed = (double)0)
{
	T_DST dst = (T_DST)seed;
	#pragma omp simd reduction(+:dst)
	for(size_t i = 0; i < N; i++)
		dst += a[i] * b[i];
	return dst;
}

template<size_t N, typename T, size_t N_O, typename T_O, typename T_DST = decltype((T)1 * (T_O)1 - (T)1 * (T_O)1)>
constexpr INLINE vec<3,T_DST> cross3(const vec<N,T>& a, const vec<N_O,T_O>& b)
{
	return a.perm(1,2,0) * b.perm(2,0,1)
	     - a.perm(2,0,1) * b.perm(1,2,0);
}

template<size_t N=1>
using i8  = vec<N,int8_t>;
template<size_t N=1>
using i16 = vec<N,int16_t>;
template<size_t N=1>
using i32 = vec<N,int32_t>;
template<size_t N=1>
using i64 = vec<N,int64_t>;
template<size_t N=1>
using u8  = vec<N,uint8_t>;
template<size_t N=1>
using u16 = vec<N,uint16_t>;
template<size_t N=1>
using u32 = vec<N,uint32_t>;
template<size_t N=1>
using u64 = vec<N,uint32_t>;
template<size_t N=1>
using f32 = vec<N,float>;
template<size_t N=1>
using f64 = vec<N,double>;

