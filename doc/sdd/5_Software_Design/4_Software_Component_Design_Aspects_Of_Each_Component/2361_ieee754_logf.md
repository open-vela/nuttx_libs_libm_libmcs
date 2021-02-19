### \_\_ieee754\_logf {#sec:component-ieee-logf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float \_\_ieee754\_logf(float x)} \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/ef\_log.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_ieee754\_log}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_ieee754\_log}.    \\ 
		
		References & \texttt{\_\_ieee754\_log} \ref{sec:component-ieee-log}, \texttt{logf} \ref{sec:component-logf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_ieee754\_log}, but several limits and scales are different:
\begin{compactenum}
	\setcounter{enumi}{3}
	\item If x is subnormal, scale up by multiplying with $2^{25}$.
	\item Change to footnote\footnote{Use \texttt{mantissa part of integer representation} + (\texttt{0x95f64} << 3) to find k.}. Decrease k by 25 if x was subnormal in the previous step.
	\item Replace constants with:
	\begin{compactitem}
		\item $L1$ = \texttt{0x3F2AAAAB} (6.6666668653 $\cdot 10^{-1}$)
		\item $L2$ = \texttt{0x3ECCCCCD} (4.0000000596 $\cdot 10^{-1}$)
		\item $L3$ = \texttt{0x3E924925} (2.8571429849 $\cdot 10^{-1}$)
		\item $L4$ = \texttt{0x3E638E29} (2.2222198546 $\cdot 10^{-1}$)
		\item $L5$ = \texttt{0x3E3A3325} (1.8183572590 $\cdot 10^{-1}$)
		\item $L6$ = \texttt{0x3E1CD04F} (1.5313838422 $\cdot 10^{-1}$)
		\item $L7$ = \texttt{0x3E178897} (1.4798198640 $\cdot 10^{-1}$)
	\end{compactitem}
	Change to footnote\footnote{f is too large when (0x6147A << 3) < mantissa part of integer representation < (0x6B851 << 3).}.
	\setcounter{enumi}{7}
	\item Replace constants with:
	\begin{compactitem}
		\item $Ln2_{hi}$ = \texttt{0x3F317180} (6.9313812256 $\cdot 10^{-1}$)
		\item $Ln2_{lo}$ = \texttt{0x3717F7D1} (9.0580006145 $\cdot 10^{-6}$)
	\end{compactitem}
\end{compactenum}
