# mlr
C++ SIMD OpenMP linear algebra math library

## About

mlr implements aligned array based `vec<N,T>` type for N-dimensional linear algebra math.

**types**
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
- [ ] `mat<N,M>`
- [ ] `bivec<N>`
- [ ] `mvec<N>`
- [ ] `quat<N>`
- [ ] `versor<N>`
- [ ] `motor<N>`

**operations**
- [x] dot
- [x] cross3
- [x] perm
- [ ] hat
- [ ] vee
- [ ] hodge
- [ ] laplacian
- [ ] det

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
