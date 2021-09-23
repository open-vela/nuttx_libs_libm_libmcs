# LibmCS

This is the mathematical library for critical systems (LibmCS). It is being developed in compliance with ECSS E-ST-40 and Q-ST-80 to Category B.

The library has been developed by GTD GmbH under the ESA Contract No. 4000130278/20/NL/ AS.

The copyright and licensing condition of the library can be found in the COPYING.md file.

## Getting Started

```
> ./configure
> make
```

### Using Configure With Flags

For CI and similar activities it can be useful to not use an interactive script for the configuration as such it is also possible to call `configure` with flags which answer the questions otherwise asked interactively (if only some flags are set, the remaining questions will still be asked). The following flags can be set:

| Configure Flag                     | Description                                                                                                                                                                 |
|------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `--cross-compile <CROSS_COMPILE>`  | Tells `make` which toolchain to use.                                                                                                                                        |
| `--compilation-flags <CFLAGS>`     | Used do define additional flags to the compiler. Takes both user and library specific flags/defines.                                                                        |
| `--enable-denormal-handling`       | The library will assume the platform does not provide denormals and use the platform to convert denormal inputs/outputs to 0.                                               |
| `--disable-denormal-handling`      | The library will assume the platform does provide denormals properly.                                                                                                       |
| `--enable-long-double-procedures`  | Should be set if the size of `long double` is 64bit and the procedures shall be provided.                                                                                   |
| `--disable-long-double-procedures` | Should be set if the size of `long double` is not 64bit or the procedures shall note be provided. If this is set, the library will not have `long double` procedures built. |
| `--enable-complex-procedures`      | If this is set complex procedures are available.                                                                                                                            |
| `--disable-complex-procedures`     | If this is set the library will not have complex procedures built.                                                                                                          |
| `--big-endian`                     | Tells the compilation that variables are in big endian.                                                                                                                     |
| `--little-endian`                  | Tells the compilation that variables are in little endian.                                                                                                                  |

Of special note here is also that the library needs to know which endianness the platform uses. Most compilers use the define `__BYTE_ORDER__` with either `__ORDER_BIG_ENDIAN__` or `__ORDER_LITTLE_ENDIAN__` set, but if your toolchain does not provide this define you have to do it yourself (e.g. the EDISOFT RTEMS does not).

### Coverage

Coverage is not set using `configure`, it can be enabled by adding `COVERAGE=1` to the `make` call.

### Make Targets

| Make Target | Description                                                                                                                        |
|-------------|------------------------------------------------------------------------------------------------------------------------------------|
| `all`       | Builds the library. This is the default target.                                                                                    |
| `debug`     | Builds the library. Currently equivalent to `all`.                                                                                 |
| `release`   | Builds the library. Equivalent to `all` with the additional flag `-DNDEBUG` set.                                                   |
| `clean`     | Removes the build directory of the library of the current ARCH. (ARCH can be set manually or is extracted from using the compiler) |
| `cleanall`  | Removes all build directories of the library.                                                                                      |
| `distclean` | Removes the `user_make.mk` file (and other files possibly created by `configure`).                                                 |

Note: LibmCS does not have an `install` target.
