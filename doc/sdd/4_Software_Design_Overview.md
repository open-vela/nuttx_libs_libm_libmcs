# Software Design Overview

## Software Static Architecture
<!--
a. The SDD shall describe the architecture of the software item, as well as the main relationship with the major components identified.
b. The SDD shall also describe any system state or mode in which the software operates.
c. The SDD shall describe the separated mission and configuration data.
    NOTE: Data can be classified in the following categories:
        * data resulting from the mission analysis and which thus vary from one mission to another;
        * reference data which are specific to a family of software product;
        * reference data which never change;
        * data depending only on the specific mission requirements (e.g. calibration of sensors);
        * data required for the software operation which only vary the higher level system design (in which is embedded the software) is changed;
-->

The mathematical library is a software library. The library is a fully passive library and provides solutions for mathematical procedures to the calling software. As such it can be seen as a replacement of the `libm` standard library. The procedures the library implements are listed in [@sec:software-design-overall-architecture].

The library has no separate operational modes or states, it simply provides the above mentioned procedures.

Further the library does not store data of any kind.


## Software Dynamic Architecture
<!--
a. The SDD shall describe the design choices to cope with the real time constraints (e.g. selection and description of the computational model).
-->

The library has no real-time constraints, all procedures provided calculate a response right away. Each procedure however has a bounded execution time (refer to \gls{SRS} \RD{01} §5.3).


## Software Behaviour

As previously noted, the library's behaviour is that of a passive library. It never executes code of any kind without being explicitly called by another program.

## Interfaces Context
<!--
a. The SDD shall identify all the external interfaces or refer to the ICD.
b. The description in <4.4>a. should be based on system block diagram or context diagram to illustrate the relationship between this system and other systems.
-->

The \gls{ICD} \RD{02} provides information on the function signatures of all library procedures. The library is meant to be included in other software projects.

The interface provided is that of a C library that can be compiled to an object file to be statically or dynamically linked to the calling software.

## Long Lifetime Software
<!--
a. The SDD shall describe the design choices to cope with the long planned lifetime of the software, in particular minimum dependency on the operating system and the hardware to improve portability.
-->

The library does not cause restrictions regarding the longevity of the operating software. It does not depend on a particular operating system or hardware setup.

## Memory and CPU Budget
<!--
a. The SDD shall document and summarize the allocation of memory and processing time to the software components.
-->

The library uses 100\% of available processing time while executing a procedure and 0\% while it doesn't. This is due to the library not having any tasks that run continuously or periodically. It simply executes one function, returns its result and stops.

The static memory needed for the library differs depending on the used toolchain and on which procedures are used by the user (due to `gc-sections` flags to the compiler). Still the library targets to use as little static memory as possible while providing its functionality. The library's allocation of dynamic memory is marginal - each procedure only requires several bytes to save intermediate variables. This however is only stack memory, no \texttt{malloc} is used, therefore no memory will be allocated from heap.

## Design Standards, Conventions and Procedures
<!--
a. The SDD shall summarize (or reference in the SDP) the software methods adopted for the architectural and the detailed design.
    NOTE: A design method offers often the following characteristics:
        * decomposition of the software architecture in design objects having integral parts that communicate with each other and with the outside environment
        * explicit recognition of typical activities of real‐time systems (i.e. cyclic and sporadic threads, protected resources)
        * integration of appropriate scheduling paradigms with the design process
        * explicit definition of the application timing requirements for each activity
        * static verification of processor allocation, schedulability and timing analysis
        * consistent code generation
b. The following information shall be summarized:
    1. software architectural design method;
    2. software detailed design method;
    3. code documentation standards;
    4. naming conventions;
    5. programming standards;
    6. intended list of reuse components
    7. main design trade‐off.
-->

The main design method of this project is 'reuse', therefore the design of the functions highly depends on the already existing implementation, which in turn causes this \gls{SDD} to be more of a description of an existing design rather than a design produced before implementation. However the procedures and their designs may be improved during this project, turning the design method into 'reuse with improvements'.

Source code documentation is done using the restructured text format for file, procedure and variable documentation, it will then be interpreted by Sphinx to generate HTML/PDF documents. Additionally the software engineer may use further comments within the code to describe parts of their implementation.

All aspects regarding the design that are not explicitly stated shall remain as they were in newlib's libm.

The library will guarantee thread safety and reentrancy for all procedures unless explicitly stated otherwise. The only exception will be the `lgamma` procedures due to the requirement to have the global variable `signgam`, as such the content of the variable is not thread safe when `lgamma` procedures are executed in multiple threads at the same time.
