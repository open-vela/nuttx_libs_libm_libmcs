frexp
~~~~~

.. c:autodoc:: ../libm/mathd/frexpd.c

Special cases
^^^^^^^^^^^^^

+------------------------------+------------------------------+--------------------------+
| x                            | :math:`*eptr`                | Result                   |
+==============================+==============================+==========================+
| :math:`±0`                   | :math:`0`                    | :math:`±0`               |
+------------------------------+------------------------------+--------------------------+
| :math:`±Inf`                 | :math:`0`                    | :math:`qNaN`             |
+------------------------------+------------------------------+--------------------------+
| :math:`NaN`                  | :math:`0`                    | :math:`qNaN`             |
+------------------------------+------------------------------+--------------------------+

Mathematical Approach
^^^^^^^^^^^^^^^^^^^^^

Implement based on bit-fiddling.

.. Here there be dragons. (TODO)

Requirements
^^^^^^^^^^^^

* REQ-ML-4000
* REQ-ML-4010
* REQ-ML-4020
* REQ-ML-4040

Source Code Files
^^^^^^^^^^^^^^^^^

* libm/include/math.h
* libm/mathd/frexpd.c
* libm/mathf/frexpf.c

References
^^^^^^^^^^
