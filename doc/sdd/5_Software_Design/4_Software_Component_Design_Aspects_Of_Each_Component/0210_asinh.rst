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

* REQ-ML-2620
* REQ-ML-2630
* REQ-ML-2640
* REQ-ML-2700

References
^^^^^^^^^^

* :ref:`fabs`
* :ref:`log`
* :ref:`log1p`
* :ref:`sqrt`
