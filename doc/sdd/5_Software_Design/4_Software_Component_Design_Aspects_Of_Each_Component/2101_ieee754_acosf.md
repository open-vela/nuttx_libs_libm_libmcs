### \_\_ieee754\_acosf {#sec:component-ieee-acosf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float \_\_ieee754\_acosf(float x)} \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/ef\_acos.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_ieee754\_acos}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_ieee754\_acos}.    \\ 
		
		References & \texttt{\_\_ieee754\_acos} \ref{sec:component-ieee-acos}, \texttt{\_\_ieee754\_asinf} \ref{sec:component-ieee-asinf}, \texttt{acosf} \ref{sec:component-acosf}, \texttt{\_\_ieee754\_sqrtf} \ref{sec:component-ieee-sqrtf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_ieee754\_acos}, with the constants taken from \texttt{\_\_ieee754\_asinf}, additional constant:
\begin{compactitem}
	\item $PI$ = \texttt{0x40490FDA} (3.1415925026)
\end{compactitem}

In step 11.a) $f$ changes to: $f =$ integer representation of $s$ with the last 12 bits masked to 0.