Reference Manual
================

This chapter provides the detailed documentation of all the procedures (C functions and macros) listed in chapter :ref:`Purpose of the Software`.

Each procedure is described in a separate subsection with the style similar to the documentation of the procedures in the ISO C and POSIX standards. Each subsection starts with a synopsis specifying the
procedure’s signature, followed by a short description of the evaluated mathematical function and its return value. Further the raised exceptions are noted.

Classification Macros
"""""""""""""""""""""

fpclassify
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/internal/fpclassifyd.c

isfinite
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/isfinite.c

isinf
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/isinf.c

isnan
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/isnan.c

isnormal
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/isnormal.c

signbit
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/internal/signbitd.c

Trigonometric Functions
"""""""""""""""""""""""

acos
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/acosd.c

asin
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/asind.c

atan
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/atand.c

atan2
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/atan2d.c

cos
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/cosd.c

sin
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/sind.c

tan
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/tand.c

Hyperbolic Functions
""""""""""""""""""""

acosh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/acoshd.c

asinh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/asinhd.c

atanh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/atanhd.c

cosh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/coshd.c

sinh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/sinhd.c

tanh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/tanhd.c

Exponential and Logarithmic Functions
"""""""""""""""""""""""""""""""""""""

exp
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/expd.c

exp2
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/exp2d.c

expm1
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/expm1d.c

frexp
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/frexpd.c

ilogb
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/ilogbd.c

ldexp
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/ldexpd.c

log
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/logd.c

log10
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/log10d.c

log1p
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/log1pd.c

log2
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/log2d.c

logb
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/logbd.c

modf
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/modfd.c

scalbn
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/scalbnd.c

scalbln
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/scalblnd.c

Power and Absolute-value Functions
""""""""""""""""""""""""""""""""""

cbrt
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/cbrtd.c

fabs
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/fabsd.c

hypot
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/hypotd.c

pow
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/powd.c

sqrt
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/sqrtd.c

Error and Gamma Functions
"""""""""""""""""""""""""

erf
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/erfd.c

erfc
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/erfcd.c

lgamma
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/lgammad.c

tgamma
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/tgammad.c

signgam
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/signgam.c

Nearest Integer Functions
"""""""""""""""""""""""""

ceil
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/ceild.c

floor
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/floord.c

nearbyint
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/nearbyintd.c

rint
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/rintd.c

lrint
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/lrintd.c

llrint
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/llrintd.c

round
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/roundd.c

lround
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/lroundd.c

llround
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/llroundd.c

trunc
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/truncd.c

Remainder Functions
"""""""""""""""""""

fmod
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/fmodd.c

remainder
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/remainderd.c

remquo
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/remquod.c

Manipulation Functions
""""""""""""""""""""""

copysign
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/copysignd.c

nan
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/nand.c

nextafter
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/nextafterd.c

nexttoward
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/nexttowardd.c

Maximum, Minimum and Positive Difference Functions
""""""""""""""""""""""""""""""""""""""""""""""""""

fdim
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/fdimd.c

fmax
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/fmaxd.c

fmin
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/fmind.c

Floating Multiply-Add
"""""""""""""""""""""

fma
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/fmad.c

Comparison Macros
"""""""""""""""""

isgreater
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/isgreater.c

isgreaterequal
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/isgreaterequal.c

isless
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/isless.c

islessequal
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/islessequal.c

islessgreater
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/islessgreater.c

isunordered
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/isunordered.c

Bessel Functions (POSIX)
""""""""""""""""""""""""

j0
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/j0d.c

j1
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/j1d.c

jn
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/jnd.c

y0
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/y0d.c

y1
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/y1d.c

yn
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/mathd/ynd.c

Complex Trigonometric Functions
"""""""""""""""""""""""""""""""

cacos
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/cacosd.c

casin
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/casind.c

catan
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/catand.c

ccos
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/ccosd.c

csin
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/csind.c

ctan
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/ctand.c

Complex Hyperbolic Functions
""""""""""""""""""""""""""""

cacosh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/cacoshd.c

casinh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/casinhd.c

catanh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/catanhd.c

ccosh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/ccoshd.c

csinh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/csinhd.c

ctanh
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/ctanhd.c

Complex Exponential and Logarithmic Functions
"""""""""""""""""""""""""""""""""""""""""""""

cexp
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/cexpd.c

clog
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/clogd.c

Complex Power and Absolute-value Functions
""""""""""""""""""""""""""""""""""""""""""

cabs
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/cabsd.c

cpow
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/cpowd.c

csqrt
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/csqrtd.c

Complex Manipulation Functions
""""""""""""""""""""""""""""""

carg
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/cargd.c

cimag
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/cimagd.c

CMPLX
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/common/cmplx.c

conj
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/conjd.c

cproj
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/cprojd.c

creal
~~~~~~~~~~~~~~~

.. c:autodoc:: ../libm/complexd/creald.c
