### \_\_kernel\_sinf {#sec:component-kernel-sinf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{double \_\_kernel\_sinf(double x, double y)} \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/kf\_sin.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_kernel\_sin}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_kernel\_sin}.    \\ 
		
		References & \texttt{\_\_kernel\_sin} \ref{sec:component-kernel-sin}, cosf \ref{sec:component-cosf}, sinf \ref{sec:component-sinf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_kernel\_sin}, although the polynomial is shortened and different constants are used:
\begin{compactenum}
	\setcounter{enumi}{1}
	\item The sine is computed by evaluating the following polynomial of degree 9:
	
	\begin{align}
		r &= x^3 \cdot (S2+x^2 \cdot (S3+x^2 \cdot S4) \nonumber \\
		sin(x+y) &= x + (S1 \cdot x + ( x \cdot (r- \frac{y}{2}) + y))
	\end{align}
	with 
	\begin{compactitem}
		\item $S1$ = \texttt{0xBE2AAAAB} (-1.6666667163 $\cdot 10^{-1}$)
		\item $S2$ = \texttt{0x3C0888BB} (8.3333803341 $\cdot 10^{-3}$)
		\item $S3$ = \texttt{0xB9502DE1} (-1.9853517006 $\cdot 10^{-4}$)
		\item $S4$ = \texttt{0x363E6DBE} (2.8376084629 $\cdot 10^{-6}$)
	\end{compactitem}
\end{compactenum}
