trunc
~~~~~

.. c:autodoc:: ../libm/mathd/truncd.c

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

   #. If the exponent is :math:`< 0`, there is no integral part, return a zero.
   #. Return :math:`x` rounded to the nearest integer no greater in magnitude than :math:`x`.

#. If the exponent is :math:`> 51`, there is no fractional part:

   #. If the exponent is :math:`= 1024`, :math:`x` is :math:`NaN` or infinite, return :math:`x+x`.
   #. Return :math:`x`.

#. Return :math:`x` rounded to the nearest integer no greater in magnitude than :math:`x`.

For the float version the approach can be shortened:

#. All the following return values shall have the same sign as the input value.
#. If the exponent is :math:`< 23`, there may be a fractional part:

   #. If the exponent is :math:`< 0`, there is no integral part, return a zero.
   #. Return :math:`x` rounded to the nearest integer no greater in magnitude than :math:`x`.

#. If the exponent is :math:`= 128`, :math:`x` is :math:`NaN` or infinite, return :math:`x+x`.
#. Return :math:`x`.

Requirements
^^^^^^^^^^^^

* REQ-ML-1060
* REQ-ML-1070
* REQ-ML-1071

Source Code Files
^^^^^^^^^^^^^^^^^

* libm/include/math.h
* libm/mathd/truncd.c
* libm/mathf/truncf.c

References
^^^^^^^^^^

* :ref:`round`
