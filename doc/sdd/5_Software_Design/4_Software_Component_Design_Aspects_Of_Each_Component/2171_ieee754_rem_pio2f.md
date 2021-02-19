### \_\_ieee754\_rem\_pio2f {#sec:component-ieee-rem-pio2f}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{\_\_int32\_t \_\_ieee754\_rem\_pio2f(float x, float *y)} \newline
		with \texttt{y} referring to an array of 2 \texttt{float} values that will be used to return the result of the procedure. \\ 
		
		Type & Internal Procedure    \\ 
		
		Files & \texttt{libm/math/ef\_rem\_pio2.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_ieee754\_rem\_pio2}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_ieee754\_rem\_pio2}.    \\ 
		
		References & \texttt{\_\_ieee754\_rem\_pio2} \ref{sec:component-ieee-rem-pio2}, \texttt{cosf} \ref{sec:component-cosf}, \texttt{sinf} \ref{sec:component-sinf}, \texttt{tanf} \ref{sec:component-tanf}, \texttt{fabsf} \ref{sec:component-fabsf}, \texttt{\_\_kernel\_rem\_pio2f} \ref{sec:component-kernel-rem-pio2f}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_ieee754\_rem\_pio2}, but several limits and scales are different:
\begin{compactenum}
	\item Replace constants with:
	\begin{compactitem}
		\item $invpio2$   = \texttt{0x3f22f984} (6.3661980629 $\cdot 10^{-1}$, equals first 24 bit of $\frac{2}{\pi}$)
		\item $pio2_1$    = \texttt{0x3fc90f80} (1.5707855225, equals first 16 bit of $\frac{\pi}{2}$)
		\item $pio2_{1t}$ = \texttt{0x37354443} (1.0804334124 $\cdot 10^{-5}$, equals $\frac{\pi}{2} - pio2_1$)
		\item $pio2_2$    = \texttt{0x37354400} (1.0804273188 $\cdot 10^{-5}$, equals second 16 bit of $\frac{\pi}{2}$)
		\item $pio2_{2t}$ = \texttt{0x2e85a308} (6.0770999344 $\cdot 10^{-11}$, equals $\frac{\pi}{2} - (pio2_1 + pio2_2)$)
		\item $pio2_3$    = \texttt{0x2e85a300} (6.0770943833 $\cdot 10^{-11}$, equals third 16 bit of $\frac{\pi}{2}$)
		\item $pio2_{3t}$ = \texttt{0x248d3132} (6.1232342629 $\cdot 10^{-17}$, equals $\frac{\pi}{2} - (pio2_1 + pio2_2 + pio2_3)$)
	\end{compactitem}
	\setcounter{enumi}{2}
	\item \begin{compactenum}
		\item \begin{compactenum}
			\item If the integer representation of x, with the last 17 bit masked off, is equal to \texttt{0x3FC80000} (this means x is close to $\frac{\pi}{2}$):
		\end{compactenum}
		Otherwise: \begin{compactenum}
			\item If the integer representation of x, with the last 17 bit masked off, is equal to \texttt{0x3FC80000} (this means x is close to $\frac{\pi}{2}$):
		\end{compactenum}
	\end{compactenum}
	\item If |x| < $2^{7} \cdot \frac{\pi}{2}$, an addition or subtraction of multiple $pio2$ is enough:
	\begin{compactenum}
		\setcounter{enumii}{5}
		\item If $i > 8$, a second iteration is necessary:
		\begin{compactenum}
			\setcounter{enumiii}{5}
			\item If $i > 25$, a second iteration is necessary:
		\end{compactenum}
	\end{compactenum}
	\setcounter{enumi}{5}
	\item Set $e0 = $ (exponent of |x|) $- 7$.
	\setcounter{enumi}{9}
	\item Set $z = (z-tx[0]) \cdot 2^{8}$.
	\setcounter{enumi}{11}
	\item Set $z = (z-tx[1]) \cdot 2^{8}$.
\end{compactenum}
