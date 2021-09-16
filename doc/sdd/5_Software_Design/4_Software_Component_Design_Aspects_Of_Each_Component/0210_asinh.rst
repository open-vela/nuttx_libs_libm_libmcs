asinh
~~~~~

.. c:autodoc:: ../libm/mathd/asinhd.c

Special cases
^^^^^^^^^^^^^

+--------------------------+--------------------------+
| x                        | Result                   |
+==========================+==========================+
| :math:`±0`               | :math:`x`                |
+--------------------------+--------------------------+
| :math:`±Inf`             | :math:`x`                |
+--------------------------+--------------------------+
| :math:`NaN`              | :math:`qNaN`             |
+--------------------------+--------------------------+

Mathematical Approach
^^^^^^^^^^^^^^^^^^^^^

Here there be dragons. (TODO)

Requirements
^^^^^^^^^^^^

* REQ-ML-2900
* REQ-ML-2910
* REQ-ML-2920
* REQ-ML-2940

Source Code Files
^^^^^^^^^^^^^^^^^

* libm/include/math.h
* libm/mathd/asinhd.c
* libm/mathf/asinhf.c

References
^^^^^^^^^^

* :ref:`fabs`
* :ref:`log`
* :ref:`log1p`
* :ref:`sqrt`
