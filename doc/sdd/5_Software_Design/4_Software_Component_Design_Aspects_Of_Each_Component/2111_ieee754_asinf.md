### \_\_ieee754\_asinf {#sec:component-ieee-asinf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float \_\_ieee754\_asinf(float x)} \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/ef\_asin.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_ieee754\_asin}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_ieee754\_asin}.    \\ 
		
		References & \texttt{\_\_ieee754\_asin} \ref{sec:component-ieee-asin}, \texttt{asinf} \ref{sec:component-asinf}, \texttt{\_\_ieee754\_sqrtf} \ref{sec:component-ieee-sqrtf}, \texttt{fabsf} \ref{sec:component-fabsf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_ieee754\_asin}, but several limits and scales are different:
\begin{compactenum}
	\setcounter{enumi}{5}
	\item Replace constants with:
	\begin{compactitem}
		\item $P0$ = \texttt{0x3E2AAAAB} (1.6666667163 $\cdot 10^{-1}$)
		\item $P1$ = \texttt{0xBEA6B090} (-3.2556581497 $\cdot 10^{-1}$)
		\item $P2$ = \texttt{0x3E4E0AA8} (2.0121252537 $\cdot 10^{-1}$)
		\item $P3$ = \texttt{0xBD241146} (-4.0055535734 $\cdot 10^{-2}$)
		\item $P4$ = \texttt{0x3A4F7F04} (7.9153501429 $\cdot 10^{-4}$)
		\item $P5$ = \texttt{0x3811EF08} (3.4793309169 $\cdot 10^{-5}$)
		\item $Q0$ = \texttt{0xC019D139} (-2.4033949375)
		\item $Q1$ = \texttt{0x4001572D} (2.0209457874)
		\item $Q2$ = \texttt{0xBF303361} (-6.8828397989 $\cdot 10^{-1}$)
		\item $Q3$ = \texttt{0x3D9DC62E} (7.7038154006 $\cdot 10^{-2}$)
	\end{compactitem}
	\setcounter{enumi}{7}
	\item
	\begin{compactenum}
		\item Change to footnote\footnote{Use integer representation of x >= 0x3F79999A.}, and replace constants with:
		\begin{compactitem}
			\item $pio2_{hi}$ = \texttt{0x3FC90FDB} (1.57079637050628662109375)
			\item $pio2_{lo}$ = \texttt{0xC08BE05E} (-4.37113900018624283 $\cdot 10^{-8}$)
		\end{compactitem}
		\item $f =$ integer representation of $s$ with the last 12 bits masked to 0, and replace constant with:
		\begin{compactitem}
			\item $pio4_{hi}$ = \texttt{0x3F490FDB} (0.785398185253143310546875 $\cdot 10^{-1}$)
		\end{compactitem}
	\end{compactenum}
\end{compactenum}
