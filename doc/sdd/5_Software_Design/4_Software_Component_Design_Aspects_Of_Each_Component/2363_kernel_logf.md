### \_\_kernel\_logf {#sec:component-kernel-logf}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{float \_\_kernel\_logf(float f)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/kf\_log.h}    \\ 
			
			Subordinates and Superiors & Float-equivalent to \texttt{\_\_kernel\_log10}.    \\ 
			
			Purpose & Float-equivalent to \texttt{\_\_kernel\_log10}.    \\ 
			
			References & \texttt{\_\_kernel\_log} \ref{sec:component-kernel-log}, \texttt{\_\_ieee754\_log10f} \ref{sec:component-ieee-log10f}, \texttt{\_\_ieee754\_logf} \ref{sec:component-ieee-logf}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item This procedure shall always be inlined, as such it is part of the \texttt{\_\_ieee754\_log10f} procedure.
	\item Calculate r:
	\begin{align}
		s &= \frac{f}{2+f} \nonumber \\
		R &= L1 \cdot s^2 + L2 \cdot s^4 + L3 \cdot s^6 + L4 \cdot s^8 \nonumber \\
		r &= s \cdot \Big(\frac{f^2}{2} + R\Big) \label{formula_kernel_logf_1}
	\end{align}
	with
	\begin{compactitem}
		\item $L1$ = \texttt{0x3F2AAAAA} (6.6666662693 $\cdot 10^{-1}$)
		\item $L2$ = \texttt{0x3ECCCE13} (4.0000972152 $\cdot 10^{-1}$)
		\item $L3$ = \texttt{0x3E91E9EE} (2.8498786688 $\cdot 10^{-1}$)
		\item $L4$ = \texttt{0x3E789E26} (2.4279078841 $\cdot 10^{-1}$)
	\end{compactitem}
	This calculation is a simplification of the theory employed and described in \texttt{\_\_ieee754\_logf} and omits the considerations regarding extra precision, as this is done by the upper level \texttt{\_\_ieee754\_log10f} procedure.
	\item Return r.
\end{compactenum}
