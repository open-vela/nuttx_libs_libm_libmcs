# LibmCS

This is the mathematical library for critical systems (LibmCS).

The library has been developed by GTD GmbH under the ESA Contract No. 4000130278/20/NL/ AS.

The copyright and licensing condition of the library can be found in the COPYING.md file.

## Getting Started

```
> ./configure
> make
```

### Using Make Without Configure

For CI and similar activities it can be useful to not use an interactive script for the configuration as such it is also possible to call `make` directly without running `configure` first, but the contents of what `configure` would provide need to be added to the `make` call. For example both `make CONFIGURE_SUCCESS=1 WANT_COMPLEX=0 -mlong-double-64 EXTRA_CFLAGS="-DLIBMCS_LONG_DOUBLE_IS_64BITS"`, or `make CROSS_COMPILE=sparc-rtems- CONFIGURE_SUCCESS=1 WANT_COMPLEX=0 EXTRA_CFLAGS="-DLIBMCS_FPU_DAZ -DLIBMCS_LONG_DOUBLE_IS_64BITS -DLIBMCS_LONG_IS_32BITS -D__BYTE_ORDER__=__ORDER_BIG_ENDIAN__"` can be valid depending on your toolchain and target platform. Of considerable import to LibmCS are the following flags:

| Make Flag                         | Description                                                                                                                                 |
|-----------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------|
| `CROSS_COMPILE=<path>`            | Tells `make` which toolchain to use.                                                                                                        |
| `CONFIGURE_SUCCESS=1`             | Has to be set as otherwise `make` assumes `configure` has not been run successfully (or at all).                                            |
| `WANT_COMPLEX=0`                  | `0` results in all complex procedures not being compiled and thus not part of the built library, with `1` complex procedures are available. |
| `COVERAGE=1`                      | Builds the library for coverage generation with lcov/gcov.                                                                                  |
| `EXTRA_CFLAGS="<your flags>"`     | Used do define additional flags to the compiler. Takes both user and library specific flags/defines.                                        |

| Compilation Flag (`EXTRA_CFLAGS`) | Description                                                                                                                                 |
|-----------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------|
| `-DLIBMCS_FPU_DAZ`                | The library will assume the platform does not provide denormals and use the platform to convert denormal inputs/outputs to 0.               |
| `-DLIBMCS_LONG_DOUBLE_IS_64BITS`  | Should be set if the size of `long double` is 64bit. If this is not set, the library will not have `long double` procedures built.          |
| `-DLIBMCS_DOUBLE_IS_32BITS`       | Set if the size of `double` is 32bit. `double` procedures will use `float` implementations.                                                 |
| `-DLIBMCS_LONG_IS_32BITS`         | Set if the size of `long int` is 32bit. Concerns some return values and their boundaries.                                                   |

Of special note here is also that the library needs to know which endianness the platform uses. Most compilers use the define `__BYTE_ORDER__` with either `__ORDER_BIG_ENDIAN__` or `__ORDER_LITTLE_ENDIAN__` set, but if your toolchain does not provide this define you have to do it yourself (e.g. the EDISOFT RTEMS does not).

Note: `COVERAGE` is not set using `configure`, it should always be directly used with `make`.

### Make Targets

| Make Target    | Description                                                                                                                                 |
|----------------|---------------------------------------------------------------------------------------------------------------------------------------------|
| `all`          | Builds the library. This is the default target.                                                                                             |
| `debug`        | Builds the library. Currently equivalent to `all`.                                                                                          |
| `release`      | Builds the library. Equivalent to `all` with the additional flag `-DNDEBUG` set.                                                            |
| `clean`        | Removes the build directory of the library of the current ARCH. (ARCH can be set manually or is extracted from using the compiler)          |
| `cleanall`     | Removes all build directories of the library.                                                                                               |
| `distclean`    | Removes the `user_make.mk` file (and other files possibly created by `configure`).                                                          |

Note: LibmCS does not have an `install` target.
