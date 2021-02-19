### \_\_ieee754\_rem\_pio2 {#sec:component-ieee-rem-pio2}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface & \texttt{\_\_int32\_t \_\_ieee754\_rem\_pio2(double x, double *y)} \newline
			with \texttt{y} referring to an array of 2 \texttt{double} values that will be used to return the result of the procedure. \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/e\_rem\_pio2.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__ieee754_rem_pio2.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_ieee754\_rem\_pio2} function shall return the quadrant the input angle lies in, and place the remainder of x divided by $\frac{\pi}{4}$ in the output array (which consists of 2 values, the remainder and its tail, hereafter called $y_0$ and $y_1$). \newline
			The return value can be converted to the angle quadrant by taking just its last two bits. If the last two bits are 00, the input value is represented in $[-45^{\circ}, 45^{\circ}]$, if they are 01, it is in $[45^{\circ}, 135^{\circ}]$, if they are 10, it is in $[135^{\circ}, 225^{\circ}]$, and if they are 11, it is in $[225^{\circ}, 315^{\circ}]$. The last two bits of the return value are the only relevant part. In some cases the return value also equals the number of reductions (by $2\pi$) necessary to reduce the value - this is not always the case, as the return value would often overflow due to the limited size of \texttt{\_\_int32\_t}. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_ieee754\_rem\_pio2f} \ref{sec:component-ieee-rem-pio2f}, \texttt{cos} \ref{sec:component-cos}, \texttt{sin} \ref{sec:component-sin}, \texttt{tan} \ref{sec:component-tan}, \texttt{fabs} \ref{sec:component-fabs}, \texttt{\_\_kernel\_rem\_pio2} \ref{sec:component-kernel-rem-pio2}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Use the following constants throughout the implementation of the internal remainder of $\frac{x}{\frac{\pi}{4}}$ function:
	\begin{compactitem}
		\item $invpio2$   = \texttt{0x3FE45F306DC9C883} (6.36619772367581382433 $\cdot 10^{-1}$, equals first 53 bit of $\frac{2}{\pi}$)
		\item $pio2_1$    = \texttt{0x3FF921FB54400000} (1.57079632673412561417, equals first 33 bit of $\frac{\pi}{2}$)
		\item $pio2_{1t}$ = \texttt{0x3DD0B4611A626331} (6.07710050650619224932 $\cdot 10^{-11}$, equals $\frac{\pi}{2} - pio2_1$)
		\item $pio2_2$    = \texttt{0x3DD0B4611A600000} (6.07710050630396597660 $\cdot 10^{-11}$, equals second 33 bit of $\frac{\pi}{2}$)
		\item $pio2_{2t}$ = \texttt{0x3BA3198A2E037073} (2.02226624879595063154 $\cdot 10^{-21}$, equals $\frac{\pi}{2} - (pio2_1 + pio2_2)$)
		\item $pio2_3$    = \texttt{0x3BA3198A2E000000} (2.02226624871116645580 $\cdot 10^{-21}$, equals third 33 bit of $\frac{\pi}{2}$)
		\item $pio2_{3t}$ = \texttt{0x397B839A252049C1} (8.47842766036889956997 $\cdot 10^{-32}$, equals $\frac{\pi}{2} - (pio2_1 + pio2_2 + pio2_3)$)
	\end{compactitem}
	\item If |x| < $\frac{\pi}{4}$, there is no need for reduction: Set $y_0 = x$ and $y_1 = 0$, and return 0.
	\item If |x| < $3 \cdot \frac{\pi}{4}$, one addition or subtraction of $pio2$ is enough:
	\begin{compactenum}
		\item If x is positive:
		\begin{compactenum}
			\item If the \texttt{highword} of x is \texttt{0x3FF921FB} (this means x is close to $\frac{\pi}{2}$):
			\begin{compactenum}
				\item Set $y_0 = x - pio2_1 - pio2_2 - pio2_{2t}$.
				\item Set $y_1 = (x - pio2_1 - pio2_2 - y_0) - pio2_{2t}$.
			\end{compactenum}
			Otherwise a less precise $pio2$ is sufficient:
			\begin{compactenum}
				\item Set $y_0 = x - pio2_1 - pio2_{1t}$.
				\item Set $y_1 = (x - pio2_1 - y_0) - pio2_{1t}$.
			\end{compactenum}
			\item Return 1.
		\end{compactenum}
		Otherwise, when x is negative:
		\begin{compactenum}
			\item If the \texttt{highword} of x is \texttt{0x3FF921FB} (this means x is close to $\frac{\pi}{2}$):
			\begin{compactenum}
				\item Set $y_0 = x + pio2_1 + pio2_2 + pio2_{2t}$.
				\item Set $y_1 = (x + pio2_1 + pio2_2 - y_0) + pio2_{2t}$.
			\end{compactenum}
			Otherwise a less precise $pio2$ is sufficient:
			\begin{compactenum}
				\item Set $y_0 = x + pio2_1 + pio2_{1t}$.
				\item Set $y_1 = (x + pio2_1 - y_0) + pio2_{1t}$.
			\end{compactenum}
			\item Return -1.
		\end{compactenum}
	\end{compactenum}
	\item If |x| < $2^{19} \cdot \frac{\pi}{2}$, an addition or subtraction of multiple $pio2$ is enough:
	\begin{compactenum}
		\item $n$ shall be an integer. Set $n = |x| \cdot invpio2 + 0.5$ (use \texttt{fabs} to calculate the absolute value of x).
		\item Set $r = |x| - n \cdot pio2_1$.
		\item Set $w = n \cdot pio2_{1t}$.
		\item Set $y_0 = r - w$.
		\item Set $i = exponent\ bits\ of\ x - exponent\ bits\ of\ y_0$.
		\item If $i > 16$, a second iteration is necessary:
		\begin{compactenum}
			\item Set $t = r$.
			\item Set $r = r - n \cdot pio2_{2}$.
			\item Set $w = n \cdot pio2_{2t} - ((t - r) - n \cdot pio2_{2})$.
			\item Set $y_0 = r - w$.
			\item Set $i = exponent\ bits\ of\ x - exponent\ bits\ of\ y_0$.
			\item If $i > 49$, a third iteration is necessary:
			\begin{compactenum}
				\item Set $t = r$.
				\item Set $r = r - n \cdot pio2_{3}$.
				\item Set $w = n \cdot pio2_{3t} - ((t - r) - n \cdot pio2_{3})$.
				\item Set $y_0 = r - w$.
			\end{compactenum}
		\end{compactenum}
		\item Set $y_1 = (r - y_0) - w$.
		\item If x is negative, negate $y_0$ and $y_1$, and return -n.
		\item Return n.
	\end{compactenum}
	\item If x is infinite or \texttt{NaN}, set both $y_0$ and $y_1$ to \texttt{NaN}, and return 0.
	\item Set $e0 = $ (exponent of |x|) $- 23$.
	\item Set $z = |x|\ with\ exponent\ set\ to\ e0$.
	\item Create array $tx$ for three values.
	\item Set $tx[0] =$ the integer part of $z$.
	\item Set $z = (z-tx[0]) \cdot 2^{24}$.
	\item Set $tx[1] =$ the integer part of $z$.
	\item Set $z = (z-tx[1]) \cdot 2^{24}$.
	\item Set $tx[2] = z$.
	\item Loop over the array $tx$ from back to front, break the loop if the element is equal to zero. Set $nx$ to the index of the element that caused the break, or 0 if no break was triggered.
	\item Call \_\_kernel\_rem\_pio2 with arguments $tx$, $y$, $e0$, and $nx$. Save the return value in $n$.
	\item If x is negative, negate $y_0$ and $y_1$, and return -n.
	\item Return n.
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.82\textwidth]{./figure/Ieee_Rem_pio2_Flowchart.pdf}
	\caption{Flowchart \_\_ieee754\_rem\_pio2}
	\label{fig:flowchart-ieee_rem_pio2}
\end{figure}