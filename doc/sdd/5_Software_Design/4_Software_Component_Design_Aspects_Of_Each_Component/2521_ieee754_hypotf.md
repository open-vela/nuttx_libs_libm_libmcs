### \_\_ieee754\_hypotf {#sec:component-ieee-hypotf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float \_\_ieee754\_hypotf(float x, float y)} \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/ef\_hypot.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_ieee754\_hypot}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_ieee754\_hypot}.    \\ 
		
		References & \texttt{\_\_ieee754\_hypot} \ref{sec:component-ieee-hypot}, \texttt{hypotf} \ref{sec:component-hypotf}, \texttt{\_\_ieee754\_sqrtf} \ref{sec:component-ieee-sqrtf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_ieee754\_hypot}, but several limits and scales are different:
\begin{compactenum}
	\setcounter{enumi}{4}
	\item If $\frac{x}{y} > 2^{30}$, return x with inexact.
	\item If x > $2^{50}$, scale down x and y by multiplying them with $2^{-68}$.
	\item If y < $2^{-50}$, scale up x and y by multiplying them with $2^{80}$.
	\item The calculation values are split at the 12th instead of the 32nd bit (e.g.  $x_1 = x$ with the lower 12bits cleared and $x_2 = x - x_1$).
\end{compactenum}
