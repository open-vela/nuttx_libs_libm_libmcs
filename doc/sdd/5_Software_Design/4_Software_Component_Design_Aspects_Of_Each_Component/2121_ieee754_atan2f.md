### \_\_ieee754\_atan2f {#sec:component-ieee-atan2f}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float \_\_ieee754\_atan2f(float y, float x)} \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/ef\_atan2.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_ieee754\_atan2}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_ieee754\_atan2}.    \\ 
		
		References & \texttt{\_\_ieee754\_atan2} \ref{sec:component-ieee-atan2}, \texttt{atan2f} \ref{sec:component-atan2f}, \texttt{atanf} \ref{sec:component-atanf}, \texttt{fabsf} \ref{sec:component-fabsf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_ieee754\_atan2}. Replace constants with:
\begin{compactitem}
	\item $PI$ = \texttt{0x40490FDB} (3.1415927410)
	\item $PI_{lo}$ = \texttt{0xB3BBBD2E} (-8.7422776573 $\cdot 10^{-8}$)
	\item $PIo2$ = \texttt{0x3FC90FDB} (1.5707963705)
	\item $PIo4$ = \texttt{0x3F490FDB} (7.8539818525 $\cdot 10^{-1}$)
\end{compactitem}

Additionally replace the limits in steps 9. and 10.a) with $2^{26}$ and $2^{-26}$ respectively.