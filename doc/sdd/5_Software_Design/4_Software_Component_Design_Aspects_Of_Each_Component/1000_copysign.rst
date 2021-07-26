copysign
~~~~~~~~

.. c:autodoc:: ../libm/mathd/copysignd.c

Special cases
^^^^^^^^^^^^^

+-----------------------------+-----------------------------+-----------------------------+
| x                           | y                           | Result                      |
+=============================+=============================+=============================+
| :math:`NaN`                 | :math:`\in \mathbb{F}`      | :math:`qNaN`                |
+-----------------------------+-----------------------------+-----------------------------+

Mathematical Approach
^^^^^^^^^^^^^^^^^^^^^

Return the value with the magnitude of :math:`x` and sign of :math:`y`.

Requirements
^^^^^^^^^^^^

* REQ-ML-1380
* REQ-ML-1381

References
^^^^^^^^^^

* :ref:`cproj`
