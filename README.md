# mlr
C++ SIMD OpenMP linear algebra math library

## About

mlr implements aligned array based [vec<<T,N>] type for N-dimensional linear algebra math.

supported scalar types:

- `f32<N>`
- `f64<N>`
- ` i8<N>`
- ` u8<N>`
- `i16<N>`
- `u16<N>`
- `i32<N>`
- `u32<N>`
- `i64<N>`
- `u64<N>`

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
