### \_\_kernel\_log {#sec:component-kernel-log}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double \_\_kernel\_log(double f)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/k\_log.h}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__kernel_log.png}}    \\ 
			
			Purpose & 
			The kernel \texttt{\_\_kernel\_log} function shall return $\log{f}$ to help with the implementation of the \_\_ieee754\_log10 procedure. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_kernel\_logf} \ref{sec:component-kernel-logf}, \texttt{\_\_ieee754\_log10} \ref{sec:component-ieee-log10}, \texttt{\_\_ieee754\_log} \ref{sec:component-ieee-log}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item This procedure shall always be inlined, as such it is part of the \texttt{\_\_ieee754\_log10} procedure.
	\item Calculate r:
	\begin{align}
		s &= \frac{f}{2+f} \nonumber \\
		R &= L1 \cdot s^2 + L2 \cdot s^4 + L3 \cdot s^6 + L4 \cdot s^8 + L5 \cdot s^{10} +L6 \cdot s^{12} + L7 \cdot s^{14} \nonumber \\
		r &= s \cdot \Big(\frac{f^2}{2} + R\Big) \label{formula_kernel_log_1}
	\end{align}
	with
	\begin{compactitem}
		\item $L1$ = \texttt{0x3FE5555555555593} (6.666666666666735130 $\cdot 10^{-1}$)
		\item $L2$ = \texttt{0x3FD999999997FA04} (3.999999999940941908 $\cdot 10^{-1}$)
		\item $L3$ = \texttt{0x3FD2492494229359} (2.857142874366239149 $\cdot 10^{-1}$)
		\item $L4$ = \texttt{0x3FCC71C51D8E78AF} (2.222219843214978396 $\cdot 10^{-1}$)
		\item $L5$ = \texttt{0x3FC7466496CB03DE} (1.818357216161805012 $\cdot 10^{-1}$)
		\item $L6$ = \texttt{0x3FC39A09D078C69F} (1.531383769920937332 $\cdot 10^{-1}$)
		\item $L7$ = \texttt{0x3FC2F112DF3E5244} (1.479819860511658591 $\cdot 10^{-1}$)
	\end{compactitem}
	This calculation is a simplification of the theory employed and described in \texttt{\_\_ieee754\_log} and omits the considerations regarding extra precision, as this is done by the upper level \texttt{\_\_ieee754\_log10} procedure.
	\item Return r.
\end{compactenum}
