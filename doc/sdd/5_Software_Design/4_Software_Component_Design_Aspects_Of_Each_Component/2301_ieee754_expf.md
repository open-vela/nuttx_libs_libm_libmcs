### \_\_ieee754\_expf {#sec:component-ieee-expf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float \_\_ieee754\_expf(float x)} \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/ef\_exp.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_ieee754\_exp}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_ieee754\_exp}.    \\ 
		
		References & \texttt{\_\_ieee754\_exp} \ref{sec:component-ieee-exp}, \texttt{expf} \ref{sec:component-expf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_ieee754\_exp}. \\
The constants in step 8 change to:
\begin{compactitem}
	\item $P1$ = \texttt{0x3E2AAAAB} (1.6666667163 $\cdot 10^{-1}$)
	\item $P2$ = \texttt{0xBB360B61} (-2.7777778450 $\cdot 10^{-3}$)
	\item $P3$ = \texttt{0x388AB355} (6.6137559770 $\cdot 10^{-5}$)
	\item $P4$ = \texttt{0xB5DDEA0E} (-1.6533901999 $\cdot 10^{-6}$)
	\item $P5$ = \texttt{0x3331BB4C} (4.1381369442 $\cdot 10^{-8}$)
\end{compactitem}
