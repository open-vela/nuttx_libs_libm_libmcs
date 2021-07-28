General Behaviour
=================

All procedures can handle all input values of its respective types, including special values such as NaNs or infinities. Pointers used to output additional return values are under the user’s control, using misplaced or ``NULL`` pointers may cause unwanted behaviour or even a crash of the system. The ``NULL`` pointers are handled appropriately by the library, but no action can be taken against using misplaced pointers.

NaN Types
~~~~~~~~~

Subnormal Values
~~~~~~~~~~~~~~~~

Exceptions
~~~~~~~~~~

Exceptions raised by the procedures are listed in the :ref:`Reference Manual`. These are in accordance with the ISO C, IEEE-754 and POSIX standards. The :ref:`Reference Manual` will only list the exceptions ``invalid operation``, ``divide by zero`` and ``overflow`` while not stating ``underflow`` and ``inexact``. These are the three exceptions deemed as important in *IEEE 754 Error Handling and Programming Languages* [NM]_.

The POSIX standard does not define errors/exceptions for complex procedures. The implementations however make use of multiple non-complex procedures which do raise exceptions. As such the :ref:`Reference Manual` does not list the exceptions thrown by complex procedures, it is assumed that the exceptions of their underlying procedures apply.

All procedures raise ``invalid operation`` exception when the input argument is ``sNaN`` unless stated otherwise in the :ref:`Reference Manual`.

.. [NM] *IEEE 754 Error Handling and Programming Languages* by Nick Maclaren.

Limitations of the Libm
~~~~~~~~~~~~~~~~~~~~~~~

fenv.h
^^^^^^

The mathematical library contains the header file ``fenv.h``. It declares - but does not implement - the functionalities listed in this section. The ``fenv.h`` header does not contain type definitions nor macros. This header file is only provided as the starting point for the user of the library to implement their own ``fenv.h`` as it is highly hardware dependent. Inclusion of the ``fenv.h`` file in an unmodified version produces an error at compile time, which should be removed by the user after implementing their own procedures. The library also provides an implementation file ``fenv.c`` which contains stub implementations for all procedures in ``fenv.h`` which simply return :math:`-1` which is a valid return value for all procedures and denotes that an error has accured while calling said procedure. User software will have to check for negative output values anyway as this is how the procedures are defined to give notice of errors. As such this is a reliable way to tell the user that an implementation of the procedures still needs to be provided.

A custom ``fenv.h`` file needs to contain the type definition of ``fenv_t`` and ``fexcept_t`` provided by the user:

* ``fenv_t`` represents the entire state of the floating-point environment including its status flags and control modes.
* ``fexcept_t`` represents the state of all floating-point status flags collectively, including the active floating-point exceptions along with additional information the implementation associates with their status.

A custom ``fenv.h`` file needs to contain the following defines and constants:

* Constants which need to contain the position of their respective exception flag in the given hardware environment in the form of a bitmask (and as such be easily combineable), their type is ``int`` and should be used by the functions ``feclearexcept``, ``feraiseexcept``, ``fegetexceptflag`` and ``fesetexceptflag``:

   * ``FE_DIVBYZERO``
   * ``FE_INEXACT``
   * ``FE_INVALID``
   * ``FE_OVERFLOW``
   * ``FE_UNDERFLOW``
   * ``FE_ALL_EXCEPT``

* Constants which need to represent the given rounding mode in the given hardware environment, their type is ``int`` and should be used by the functions ``fegetround`` and ``fesetround``:

   * ``FE_DOWNWARD``
   * ``FE_TONEAREST``
   * ``FE_TOWARDSZERO``
   * ``FE_UPWARD``
   
* Constant pointer to access the environment in the given hardware environment, the type is ``fenv_t*`` and should be used as input for the functions ``fesetenv`` and ``fegetenv``:

   * ``FE_DFL_ENV``

These are the expected procedures of a proper ``fenv.h`` implementation:

* Floating-point Exceptions

   #. Clear floating-point exceptions

      * ``int feclearexcept(int excepts)``

   #. Raise floating-point exceptions

      * ``int feraiseexcept(int excepts)``

   #. Get floating-point exception flags

      * ``int fegetexceptflag(fexcept_t* flagp, int excepts)``

   #. Set floating-point exception flags

      * ``int fesetexceptflag(const fexcept_t* flagp, int excepts)``

* Rounding Direction

   #. Get rounding direction mode

      * ``int fegetround(void)``

   #. Set rounding direction mode

      * ``int fesetround(int rdir)``

* Entire Environment

   #. Get floating-point environment

      * ``int fegetenv(fenv_t* envp)``

   #. Set floating-point environment

      * ``int fesetenv(const fenv_t* envp)``

   #. Hold floating-point exceptions

      * ``int feholdexcept(fenv_t* envp)``

   #. Update floating-point environment

      * ``int feupdateenv(const fenv_t* envp)``

* Other

   #. Test for floating-point exceptions

      * ``int fetestexcept(int excepts)``

tgmath.h
^^^^^^^^

The mathematical library contains the header file ``tgmath.h`` which except for adding an error message upon compilation has not been changed from its ``Newlib`` state. ``tgmath.h`` procedures are not qualified.

Inclusion of the ``tgmath.h`` file produces an intentional error at compile time. Contrary to the ``fenv.h`` header file we descourage any use of the ``tgmath.h`` header and suggest users to not create their own. Type generic function calls should never be used in critical software.

Thread Safety and Reentrancy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The library is thread safe and reentrant. For software that is using the library it has to be noted that usage of the ``signgam`` variable is not thread safe when executing the ``lgamma`` procedures on
multiple threads at once, as each procedure call operates on the same variable. This is a limitation forced on the library by the POSIX standard that demands the availability of the ``signgam`` global variable.

Modular Arithmetic Procedures
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Side Effects
~~~~~~~~~~~~

This library does not produce any side effects, apart from the exceptions that have been described,

* to the software that uses the library,
* nor to the hardware,

as it does not configure any hardware.
