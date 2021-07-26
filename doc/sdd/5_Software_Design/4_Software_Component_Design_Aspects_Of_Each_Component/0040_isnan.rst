isnan
~~~~~

.. c:autodoc:: ../libm/common/isnan.c

Special cases
^^^^^^^^^^^^^

This macro does not have special cases.

Mathematical Approach
^^^^^^^^^^^^^^^^^^^^^

The approach is to call ``fpclassify`` and decide on the return value depending on the result:

#. Call ``fpclassify`` with input :math:`x`, return :math:`1` if the call returned ``FP_NAN``.
#. Else return :math:`0`.

Requirements
^^^^^^^^^^^^

* REQ-ML-1340

References
^^^^^^^^^^

* :ref:`fpclassify`
* :ref:`nexttowardf <nexttoward>`
