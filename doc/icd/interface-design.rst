Interface design
================

This chapter describes the includes needed to use the library, the signatures of the procedures,
the existing defines and constants, and possible side effects to software and hardware.

C: math.h
---------

To include the Mathematical Library one has to include ``math.h`` . It declares the functionalities
listed in the following section.

Type Definitions
^^^^^^^^^^^^^^^^

The ``math.h`` file includes the type definition of ``double_t`` and ``float_t`` (floating types at least as
wide as ``double`` and ``float`` respectively).

Global Variables
^^^^^^^^^^^^^^^^

The ``math.h`` file includes the external variable ``signgam`` as integer type.
This variable is required by POSIX standard.

Defines and Constants
^^^^^^^^^^^^^^^^^^^^^

