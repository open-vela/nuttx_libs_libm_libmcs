ilogb
~~~~~

.. c:autodoc:: ../libm/mathd/ilogbd.c

Special cases
^^^^^^^^^^^^^

+--------------------------+--------------------------+
| x                        | Result                   |
+==========================+==========================+
| :math:`±0`               | min :math:`\mathbb{I}`   |
+--------------------------+--------------------------+
| :math:`±Inf`             | max :math:`\mathbb{I}`   |
+--------------------------+--------------------------+
| :math:`NaN`              | max :math:`\mathbb{I}`   |
+--------------------------+--------------------------+

Mathematical Approach
^^^^^^^^^^^^^^^^^^^^^

Here there be dragons. (TODO)

Requirements
^^^^^^^^^^^^

* REQ-ML-4300
* REQ-ML-4310
* REQ-ML-4320
* REQ-ML-4340

References
^^^^^^^^^^

* :numref:`Tbl. %s <List of math constants>`
* :ref:`logb`