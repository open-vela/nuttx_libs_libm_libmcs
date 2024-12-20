floor
~~~~

.. c:autodoc:: ../libm/mathd/floord.c

Special cases
^^^^^^^^^^^^^

+--------------------------+--------------------------+
| x                        | Result                   |
+==========================+==========================+
| :math:`±0`               | :math:`x`                |
+--------------------------+--------------------------+
| :math:`±Inf`             | :math:`x`                |
+--------------------------+--------------------------+
| :math:`NaN`              | :math:`NaN`              |
+--------------------------+--------------------------+

Mathematical Approach
^^^^^^^^^^^^^^^^^^^^^

The approach is to first check whether the input is fractional, then remove the fraction and round in the correct direction.

#. All the following return values shall have the same sign as the input value.
#. If the exponent is :math:`< 20`, the integral part of :math:`x` is in the double's highword:

   #. If the exponent is :math:`< 0`, there is no integral part:

      #. If the input is :math:`>= 0`, return a zero.
      #. Return :math:`-1`.

   #. If :math:`x` is integral, return :math:`x`.
   #. Return :math:`x` rounded towards negative infinity.

#. If the exponent is :math:`> 51`, there is no fractional part:

   #. If the exponent is :math:`= 1024`, :math:`x` is :math:`NaN` or infinite, return :math:`x+x`.
   #. Return :math:`x`.

#. If :math:`x` is integral, return :math:`x`.
#. Return :math:`x` rounded towards negative infinity.

For the float version the approach can be shortened:

#. All the following return values shall have the same sign as the input value.
#. If the exponent is :math:`< 23`, there may be a fractional part:

   #. If the exponent is :math:`< 0`, there is no integral part:

      #. If the input is :math:`>= 0`, return a zero.
      #. Return :math:`-1`.

   #. If :math:`x` is integral, return :math:`x`.
   #. Return :math:`x` rounded towards negative infinity.

#. If the input is not finite, return :math:`x+x`.
#. Return :math:`x`.

Requirements
^^^^^^^^^^^^

* REQ-ML-1040
* REQ-ML-1051
* REQ-ML-1052

Source Code Files
^^^^^^^^^^^^^^^^^

* libm/include/math.h
* libm/mathd/floord.c
* libm/mathf/floorf.c

References
^^^^^^^^^^

* :ref:`ceil`
