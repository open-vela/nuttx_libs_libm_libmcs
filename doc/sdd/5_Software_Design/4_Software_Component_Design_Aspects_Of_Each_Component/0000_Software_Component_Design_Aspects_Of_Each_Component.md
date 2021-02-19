## Software Components Design – Aspects of Each Component  {#sec:software-design-software-component-design-aspects-of-each-component}
<!--
### General
a. This part of the DRD, as well as <5.5>, may be produced as the detailed design model of a tool, if agreed with the customer.

### <Component Identifier>
a. Each component should have a unique identifier.
b. The component should be named according to the rules of the programming language or operating system to be used.
c. A hierarchical naming scheme should be used that identifies the parent of the component (e.g. ParentName_ChildName).

### <Type>
a. Component type should be described by stating its logical and physical characteristics.
b. The logical characteristics should be described by stating the package, library or class that the component belongs to.
c. The physical characteristics should be described by stating the type of component, using the implementation terminology (e.g. task, subroutine, subprogram, package and file).
    NOTE: The contents of some components description clauses depend on the component type. For the purpose of this guide, the following categories are used: executable (i.e. contains computer instructions) or non–executable (i.e. contains only data).

### <Purpose>
a. The purpose of a component should describe its trace to the software requirements that it implements.
    NOTE: Backward traceability depends upon each component description explicitly referencing the requirements that justify its existence.

### <Function>
a. The function of a component shall be described in the software architectural design.
b. The description specified in <5.4.5>a. should be done by stating what the component does.
    NOTE 1: The function description depends upon the component type. Therefore, it can be a description of the process.
    NOTE 2: Process descriptions can use such techniques as structured English, precondition–postcondition specifications and state–transition diagrams.

### <Subordinates>
a. The subordinates of a component should be described by listing the immediate children.
    NOTE 1: The subordinates of a unit are the units that are ’called by’ it. The subordinates of a database can be the files that ’compose’ it.
    NOTE 2: The subordinates of an object are the objects that are ’used by’ it.

### <Dependencies>
a. The dependencies of a component should be described by listing the constraints upon its use by other components.
    NOTE: Examples are:
        * Operations to take place before this component is called,
        * Operations that are excluded when this operation takes place.

### <Interfaces>
a. Both control flow and data flow aspects of an interface shall be described for each “executable” component.
b. Data aspects of ’non executable’ components should be described.
c. The control flow to and from a component should be described in terms of how to start (e.g. subroutine call) and terminate (e.g. return) the execution of the component.
d. If the information in <5.4.8>c. is implicit in the definition of the type of component, a description need not be done.
e. If control flows take place during execution (e.g. interrupt), they should be described.
f. The data flow input to and output from each component shall be described.
g. It should be ensured that data structures:
    1. are associated with the control flow (e.g. call argument list);
    2. interface components through common data areas and files.

### <Resources>
a. The resources’ needs of a component should be described by itemising what the component needs from its environment to perform its function.
    NOTE 1: Items that are part of the component interface are excluded.
    NOTE 2: Examples of resources’ needs of a component are displays, printers and buffers.

### <References>
a. Explicit references should be inserted where a component description uses or implies material from another document.

### <Data>
a. The data internal to a component should be described.
    NOTE: The amount of details to be provided depends strongly on the type of the component.
b. The data structures internal to a program or subroutine should also be described.
c. Data structure definitions shall include the:
    1. description of each element (e.g. name, type, dimension);
    2. relationships between the elements (i.e. the structure);
    3. range of possible values of each element;
    4. initial values of each element.
-->
