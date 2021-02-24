Special cases
^^^^^^^^^^^^^

This macro does not have special cases.

Mathematical Approach
^^^^^^^^^^^^^^^^^^^^^

The approach is to call one of two internal procedures named ``__signbitd`` or ``__signbitf`` depending on the type of the input. These procedures follow the following approach:

#. Use a mask to get the sign bit of the input value.
#. If the sign bit is set, return :math:`1`, else return :math:`0`.

Requirements
^^^^^^^^^^^^

* REQ-ML-1360

References
^^^^^^^^^^
