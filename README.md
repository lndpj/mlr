# mlr
C++ SIMD OpenMP linear algebra math library

## About

mlr implements aligned array based `vec<N,T>` type for N-dimensional linear algebra math.

**types**
- [x] `vec<N,T>`
- [x] `pos<N,T>`
- [x] `dir<N,T>`
- [x] `col<N,T,C>`
- [x] ` f32<N>`
- [x] ` f64<N>`
- [x] `f128<N>`
- [x] ` i8<N>`
- [x] ` u8<N>`
- [x] `i16<N>`
- [x] `u16<N>`
- [x] `i32<N>`
- [x] `u32<N>`
- [x] `i64<N>`
- [x] `u64<N>`
- [x] ` b8<N>`
- [x] `b32<N>`
- [x] ` c8<N>`
- [x] `c32<N>`
- [ ] `mat<C,R>`
- [ ] `bivec<N,T>`
- [ ] `mvec<N,T>`
- [ ] `quat<T>`
- [ ] `versor<T>`
- [ ] `motor<T>`
- [ ] `tensor<N,M,T>`

**operations**
- [x] dot
- [x] norm
- [x] norm_squared
- [x] normalize
- [x] normalized
- [x] cross3
- [x] perm
- [ ] det
- [ ] hat
- [ ] vee
- [ ] levi-civita
- [ ] hodge
- [ ] laplacian

## Dependencies

- [C++23][1]
- [OpenGL/KHR][2]

## Building

```sh
cmake . --install-prefix=/usr
make install
```
## Usage

```cpp
#include <mlr/vector.hpp>

int main(int argc, char** argv)
{
    f32<3> a = {1,2,3};
    f32<4> b = {4,5,6,7};
    f32<3> c = 3.0f / (a + c) - 4.0f;
    printf("[%f %f %f]\n",c[0],c[1],c[2]);
}
```
## Links

- [SYCL Overview][3]
- [OpenCL][4]

[1]: https://isocpp.org/
[2]: https://github.com/KhronosGroup/OpenGL-Registry/blob/main/api/GL/glcorearb.h
[3]: https://www.khronos.org/sycl/
[4]: https://www.khronos.org/opencl/
