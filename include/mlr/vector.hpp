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
	INLINE T& operator=(const T_RHS& rhs) requires(!scalar<T>)
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
	INLINE T& operator+=(const T_RHS& other) requires(!scalar<T_RHS>)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < std::min(dst.size(),other.size()); i++)
			dst[i] += other[i];
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator+=(const T_RHS& other) requires(scalar<T_RHS>)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < dst.size(); i++)
			dst[i] += other;
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator-=(const T_RHS& other) requires(!scalar<T_RHS>)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < std::min(dst.size(),other.size()); i++)
			dst[i] -= other[i];
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator-=(const T_RHS& other) requires(scalar<T_RHS>)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < dst.size(); i++)
			dst[i] -= other;
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator*=(const T_RHS& other) requires(!scalar<T_RHS>)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < std::min(dst.size(),other.size()); i++)
			dst[i] *= other[i];
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator*=(const T_RHS& other) requires(scalar<T_RHS>)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < dst.size(); i++)
			dst[i] *= other;
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator/=(const T_RHS& other) requires(!scalar<T_RHS>)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < std::min(dst.size(),other.size()); i++)
			dst[i] /= other[i];
		return dst;
	}
	template<typename T_RHS>
	INLINE T& operator/=(const T_RHS& other) requires(scalar<T_RHS>)
	{
		T& dst = (*reinterpret_cast<T*>(this));
		#pragma omp simd
		for(size_t i = 0; i < dst.size(); i++)
			dst[i] /= other;
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

template<size_t N, typename T>
struct pos;
template<size_t N, typename T>
struct dir;

#pragma pack(push,1)
template<size_t N, typename T, size_t N_POW2 = std::bit_ceil<size_t>(N)>
struct alignas((N == N_POW2 ? N : 1) * alignof(T)) vec : std::array<T,N>, ops<vec<N,T>>
{
	constexpr vec() = default;
	template<scalar... S>
	constexpr INLINE vec(const S... args) requires(sizeof...(S) > 1) : std::array<T,N>{ static_cast<T>(args)... } 
	{
	}
	INLINE vec(const std::array<T,N>& src) : std::array<T,N>{src}
	{
	}
	template<scalar T_O>
	INLINE vec(const T_O& src)
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
	constexpr INLINE vec<sizeof...(I),T> perm(const I... args) const { return std::array<T,sizeof...(I)>{ (*this)[args % N]... }; }

	template<typename T_DST = double>
	INLINE T_DST norm_squared(T_DST dst = (T_DST)0)
	{
		#pragma omp simd reduction(+:dst)
		for(size_t i = 0; i < N; i++)
			dst += (*this)[i] * (*this)[i];
		return dst;
	}

	template<typename T_DST = double>
	constexpr INLINE T_DST norm(T_DST dst = (T_DST)0)
	{
		return sqrt(norm_squared<T_DST>(dst));
	}
	constexpr INLINE vec<N,T>& normalize()
	{
		const double mag = norm_squared();
		if(mag != (double)0)
			(*this) /= sqrt(mag);
		return (*this);
	}
	constexpr INLINE vec<N,T> normalized()
	{
		const double mag = norm_squared();
		if(mag != (double)0)
			return vec<N,T>{(*this)} /= sqrt(mag);
		return (*this);
	}
	constexpr INLINE pos<N,T> position()
	{
		pos<N,T> dst{(*this)};
		dst[N-1] = (T)1;
		return dst;
	}
	constexpr INLINE dir<N,T> direction()
	{
		dir<N,T> dst{(*this)};
		dst[N-1] = (T)0;
		return dst;
	}
	T& x() requires(N > 0) { return (*this)[0]; }
	T& y() requires(N > 1) { return (*this)[1]; }
	T& z() requires(N > 2) { return (*this)[2]; }
	T& w() requires(N > 3) { return (*this)[3]; }
};
#pragma pack(pop)

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
template<size_t N=1>
using f128 = vec<N,long double>;

template<size_t N=1>
using b8  = vec<N,bool>;

enum class boolean_enum { FALSE = (const int)false, TRUE = (const int)true };
template<size_t N=1>
using b32 = vec<N,enum boolean_enum>;

template<size_t N=1>
using c8  = vec<N,char>;
template<size_t N=1>
using c32 = vec<N,char32_t>;


template<size_t N, typename T>
struct pos : vec<N, T>
{
	template<scalar... S>
	constexpr INLINE pos(const S... args) requires(sizeof...(S) > 1) : vec<N,T>{ static_cast<T>(args)... } 
	{
	}
	template<size_t N_O, typename T_O>
	INLINE pos(const vec<N_O,T_O>& src) 
	{
		#pragma omp simd
		for(size_t i = 0; i < std::min(N,src.size()); i++)
			(*this)[i] = i == N-1 ? (T)1 : src[i];
	}
	T& x() requires(N > 0) { return (*this)[0]; }
	T& y() requires(N > 1) { return (*this)[1]; }
	T& z() requires(N > 2) { return (*this)[2]; }
	T& w() requires(N > 3) { return (*this)[3]; }
	
};
template<size_t N, typename T>
struct dir : vec<N, T>
{
	template<scalar... S>
	constexpr INLINE dir(const S... args) requires(sizeof...(S) > 1) : vec<N,T>{ static_cast<T>(args)... } 
	{
	}
	template<size_t N_O, typename T_O>
	INLINE dir(const vec<N_O,T_O>& src) 
	{
		#pragma omp simd
		for(size_t i = 0; i < std::min(N,src.size()); i++)
			(*this)[i] = i == N-1 ? (T)0 : src[i];
	}
	T& x() requires(N > 0) { return (*this)[0]; }
	T& y() requires(N > 1) { return (*this)[1]; }
	T& z() requires(N > 2) { return (*this)[2]; }
	T& w() requires(N > 3) { return (*this)[3]; }
};

template<size_t N, typename T, std::array C = { 0, 1, 2, 3 }>
struct col : vec<N,T>
{

	template<scalar... S>
	constexpr INLINE col(const S... args) requires(sizeof...(S) > 1) : vec<N,T>{ static_cast<T>(args)... } 
	{
	}

	T& r() requires(N > 0) { return (*this)[C[0]]; }
	T& g() requires(N > 1) { return (*this)[C[1]]; }
	T& b() requires(N > 2) { return (*this)[C[2]]; }
	T& a() requires(N > 3) { return (*this)[C[3]]; }
};

