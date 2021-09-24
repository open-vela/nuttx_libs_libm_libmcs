atanh
~~~~~

.. c:autodoc:: ../libm/mathd/atanhd.c

Special cases
^^^^^^^^^^^^^

+--------------------------+--------------------------+
| x                        | Result                   |
+==========================+==========================+
| :math:`±0`               | :math:`x`                |
+--------------------------+--------------------------+
| :math:`\notin [-1, 1]`   | :math:`qNaN`             |
+--------------------------+--------------------------+
| :math:`±1`               | :math:`±Inf`             |
+--------------------------+--------------------------+
| :math:`±Inf`             | :math:`qNaN`             |
+--------------------------+--------------------------+
| :math:`NaN`              | :math:`qNaN`             |
+--------------------------+--------------------------+

Mathematical Approach
^^^^^^^^^^^^^^^^^^^^^

Here there be dragons. (TODO)

Requirements
^^^^^^^^^^^^

* REQ-ML-3100
* REQ-ML-3110
* REQ-ML-3120
* REQ-ML-3121
* REQ-ML-3140
* REQ-ML-3141

Source Code Files
^^^^^^^^^^^^^^^^^

* libm/include/math.h
* libm/mathd/atanhd.c
* libm/mathf/atanhf.c

References
^^^^^^^^^^

* :ref:`log1p`
