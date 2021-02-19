### atanf {#sec:component-atanf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float atanf(float x)} \\ 
		
		Type & Procedure    \\ 
		
		Files & \texttt{libm/math/sf\_atan.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{atan}.    \\ 
		
		Purpose & Float-equivalent to \texttt{atan}.    \\ 
		
		References & \texttt{atan} \ref{sec:component-atan}, \texttt{\_\_ieee754\_atan2f} \ref{sec:component-ieee-atan2f}, \texttt{fabsf} \ref{sec:component-fabsf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{atan}, but several limits and scales are different:
\begin{compactenum}
	\setcounter{enumi}{1}
	\item Replace constants with:
	\begin{compactitem}
		\item $atan0.5_{hi}$ = \texttt{0x3EED6338} (4.6364760399 $\cdot 10^{-1}$)
		\item $atan0.5_{lo}$ = \texttt{0x31AC3769} (5.0121582440 $\cdot 10^{-9}$)
		\item $atan1_{hi}$ = \texttt{0x3F490FDA} (7.8539812565 $\cdot 10^{-1}$)
		\item $atan1_{lo}$ = \texttt{0x33222168} (3.7748947079 $\cdot 10^{-8}$)
		\item $atan1.5_{hi}$ = \texttt{0x3F7B985E} (9.8279368877 $\cdot 10^{-1}$)
		\item $atan1.5_{lo}$ = \texttt{0x33140FB4} (3.4473217170 $\cdot 10^{-8}$)
		\item $atanInf_{hi}$ = \texttt{0x3FC90FDA} (1.5707962513)
		\item $atanInf_{lo}$ = \texttt{0x33A22168} (7.5497894159 $\cdot 10^{-8}$)
	\end{compactitem}
	\item If |x| > $2^{34}$, return $atanInf_{hi} + atanInf_{lo}$ with the sign of x.
	\setcounter{enumi}{5}
	\item Change to footnote\footnote{Test with integer representation < \texttt{0x3EE00000}.}. Replace constants with:
	\begin{compactitem}
		\item $A0$ = \texttt{0x3EAAAAAA} (3.3333334327 $\cdot 10^{-1}$)
		\item $A1$ = \texttt{0xBE4CCCCD} (-2.0000000298 $\cdot 10^{-1}$)
		\item $A2$ = \texttt{0x3E124925} (1.4285714924 $\cdot 10^{-1}$)
		\item $A3$ = \texttt{0xBDE38E38} (-1.1111110449 $\cdot 10^{-1}$)
		\item $A4$ = \texttt{0x3DBA2E6E} 9.0908870101 $\cdot 10^{-2}$)
		\item $A5$ = \texttt{0xBD9D8795} (-7.6918758452 $\cdot 10^{-2}$)
		\item $A6$ = \texttt{0x3D886B35} (6.6610731184 $\cdot 10^{-2}$)
		\item $A7$ = \texttt{0xBD6EF16B} (-5.8335702866 $\cdot 10^{-2}$)
		\item $A8$ = \texttt{0x3D4BDA59} (4.9768779427 $\cdot 10^{-2}$)
		\item $A9$ = \texttt{0xBD15A221} (-3.6531571299 $\cdot 10^{-2}$)
		\item $A10$ = \texttt{0x3C8569D7} (1.6285819933 $\cdot 10^{-2}$)
	\end{compactitem}
	\item Change to footnote\footnote{Test with integer representation < \texttt{0x3F300000}.}.
	\item Change to footnote\footnote{Test with integer representation < \texttt{0x3F980000}.}.
	\item Change to footnote\footnote{Test with integer representation < \texttt{0x401C0000}.}.
\end{compactenum}