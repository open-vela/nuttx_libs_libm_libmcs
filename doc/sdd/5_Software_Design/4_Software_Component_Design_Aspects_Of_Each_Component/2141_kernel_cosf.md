### \_\_kernel\_cosf {#sec:component-kernel-cosf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{double \_\_kernel\_cosf(double x, double y)} \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/kf\_cos.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_kernel\_cos}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_kernel\_cos}.    \\ 
		
		References & \texttt{\_\_kernel\_cos} \ref{sec:component-kernel-cos}, cosf \ref{sec:component-cosf}, sinf \ref{sec:component-sinf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_kernel\_cos}, although the polynomial is shortened and different constants are used:
\begin{compactenum}
	\setcounter{enumi}{1}
	\item The cosine is computed by evaluating the following polynomial of degree 8:
	
	\begin{align}
		r &= C1\cdot x^2 + C2\cdot x^4 + C3\cdot x^6 \\
		cos(x+y) &= w + (((1 - w) - hz) + (x^2 \cdot r - x \cdot y))
	\end{align}
	with
	\begin{compactitem}
		\item $hz = 0.5 \cdot x^2$
		\item $w = 1 - hz$
	\end{compactitem}
	and 
	\begin{compactitem}
		\item $C1$ = \texttt{0x3D2AAAA5} (4.1666645556 $\cdot 10^{-2}$)
		\item $C2$ = \texttt{0xBAB60615} (-1.3887310633 $\cdot 10^{-3}$)
		\item $C3$ = \texttt{0x37CCF47C} (2.4432542886 $\cdot 10^{-5}$)
	\end{compactitem}
\end{compactenum}
