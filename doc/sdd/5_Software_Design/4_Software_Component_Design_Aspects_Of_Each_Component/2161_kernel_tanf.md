### \_\_kernel\_tanf {#sec:component-kernel-tanf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{double \_\_kernel\_tanf(float x, float y, int k)} \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/kf\_tan.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_kernel\_tan}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_kernel\_tan}.    \\ 
		
		References & \texttt{\_\_kernel\_tan} \ref{sec:component-kernel-tan}, \texttt{tanf} \ref{sec:component-tanf}, \texttt{fabsf} \ref{sec:component-fabsf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_kernel\_tan}, but several limits and scales are different:
\begin{compactenum}
	\item Replace constants with:
	\begin{compactitem}
		\item $PIo4$ = \texttt{0x3F490FDA} (7.8539812565 $\cdot 10^{-1}$)
		\item $PIo4_{lo}$ = \texttt{0x33222168} (3.7748947079 $\cdot 10^{-8}$)
	\end{compactitem}
	\setcounter{enumi}{3}
	\item Change to footnote\footnote{This is when integer representation of x < \texttt{0x3F2CA140}.}
	\begin{compactenum}
		\item Replace constants with:
		\begin{compactitem}
			\item $T0$ = \texttt{0x3EAAAAAB} (3.3333334327 $\cdot 10^{-1}$)
			\item $T1$ = \texttt{0x3E088889} (1.3333334029 $\cdot 10^{-1}$)
			\item $T2$ = \texttt{0x3D5D0DD1} (5.3968254477 $\cdot 10^{-2}$)
			\item $T3$ = \texttt{0x3CB327A4} (2.1869488060 $\cdot 10^{-2}$)
			\item $T4$ = \texttt{0x3C11371F} (8.8632395491 $\cdot 10^{-3}$)
			\item $T5$ = \texttt{0x3B6B6916} (3.5920790397 $\cdot 10^{-3}$)
			\item $T6$ = \texttt{0x3ABEDE48} (1.4562094584 $\cdot 10^{-3}$)
			\item $T7$ = \texttt{0x3A1A26C8} (5.8804126456 $\cdot 10^{-4}$)
			\item $T8$ = \texttt{0x398137B9} (2.4646313977 $\cdot 10^{-4}$)
			\item $T9$ = \texttt{0x38A3F445} (7.8179444245 $\cdot 10^{-5}$)
			\item $T10$ = \texttt{0x3895C07A} (7.1407252108 $\cdot 10^{-5}$)
			\item $T11$ = \texttt{0xB79BAE5F} (-1.8558637748 $\cdot 10^{-5}$)
			\item $T12$ = \texttt{0x37D95384} (2.5907305826 $\cdot 10^{-5}$)
		\end{compactitem}
		\setcounter{enumii}{3}
		\item \begin{compactitem}
			\item $z = tan(x+y)$ with the last 12 bits masked to zero.
			\item $t = a$ with the last 12 bits masked to zero.
		\end{compactitem}
	\end{compactenum}
\end{compactenum}