## General
<!--
a. The SDD shall describe the software architectural design.
b. The architecture structure of the software item shall be described, identifying the software components, their hierarchical relationships, any dependency and interfaces between them.
c. For flight software, the design shall reflect in flight modification requirements.
d. The structure in <5.2> to <5.5> should be used.
-->

The herein described software is a mathematical library, not designed for independent execution, but for embedding into other software projects. This chapter describes the software design in a top-bottom approach: First in [@sec:software-design-overall-architecture] a common overview over the structure of the software is given. The section afterwards [@sec:software-design-software-component-design-general] identifies each component in the software. All components are described in [@sec:software-design-software-component-design-aspects-of-each-component]. The last section [@sec:software-design-internal-interface-design] gives an overview about the internal usage between the components.

The library is a reuse of the mathematical library contained in `newlib` called `libm`, specifically we use the `libm` contained in `newlib` v4.0.0.

In the process of improving the reused software several design and implementation changes have to be made to the library.

This document follows in structure and content the \gls{DRD} in ECSS-E-ST-40 \AD{01}, but because of the type of the reused software some required items have to be redefined for an appropriate design description or are not relevant. The reinterpreting/redefining of items is done at the start of each section. All items not relevant in this context are mentioned at the end of each section to be compliant with \gls{ECSS}.
