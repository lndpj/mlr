# mlr
C++ SIMD OpenMP linear algebra math library

## About

mlr implements aligned array based `vec<N,T>` type for N-dimensional linear algebra math.

**floating-point**
- ` f32<N>`
- ` f64<N>`
- `f128<N>`

**integer**
- ` i8<N>`
- ` u8<N>`
- `i16<N>`
- `u16<N>`
- `i32<N>`
- `u32<N>`
- `i64<N>`
- `u64<N>`

**boolean**
- ` b8<N>`

**character**
- ` c8<N>`
- `c32<N>`

## Dependencies

- [C++23][1]
- [OpenGL/KHR][2]

## Building

```sh
cmake . --install-prefix=/usr
make install
```

## Links

- [SYCL Overview][3]
- [OpenCL][4]

[1]: https://isocpp.org/
[2]: https://github.com/KhronosGroup/OpenGL-Registry/blob/main/api/GL/glcorearb.h
[3]: https://www.khronos.org/sycl/
[4]: https://www.khronos.org/opencl/
