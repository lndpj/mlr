# mlr
[C++][1] [OpenMP][5] [SIMD][6] linear algebra math library

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
- [x] `quat<T>`
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
- [x] sign
- [x] id
- [x] ne
- [ ] det
- [ ] hat
- [ ] vee
- [ ] levi-civita
- [ ] hodge
- [ ] laplacian

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
[5]: https://www.openmp.org/
[6]: https://en.wikipedia.org/wiki/Single_instruction,_multiple_data
