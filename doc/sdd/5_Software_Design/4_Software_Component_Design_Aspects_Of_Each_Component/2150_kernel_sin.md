### \_\_kernel\_sin {#sec:component-kernel-sin}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double \_\_kernel\_sin(double x, double y, int iy)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/k\_sin.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__kernel_sin.png}}    \\ 
			
			Purpose & 
			The function \_\_kernel\_sin computes the sine of the input value. The sum of both input parameters \texttt{x} and \texttt{y} is bounded to $[\frac{-\pi}{4};\frac{\pi}{4}]$. The first parameter x is the requested value in raw precision while the second parameter contains a tail for higher precision. The third parameter iy signals, if the parameter y is 0. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_kernel\_sinf} \ref{sec:component-kernel-sinf}, cos \ref{sec:component-cos}, sin \ref{sec:component-sin}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item The input value x and y are interpreted in radians.
	\item The sine is computed by evaluating the following polynomial of degree 13:
	
	\begin{align}
		r &= x^3 \cdot (S2+x^2 \cdot (S3+x^2 \cdot (S4+x^2 \cdot (S5+x^2 \cdot S6)))) \nonumber \\
		sin(x+y) &= x + (S1 \cdot x + ( x \cdot (r- \frac{y}{2}) + y))
	\end{align}
	with:
	\begin{compactitem}
		\item $S1$ = \texttt{0xBFC5555555555549} ($-1.66666666666666324348 \cdot 10^{-01}$)
		\item $S2$ = \texttt{0x3F8111111110F8A6} ($8.33333333332248946124 \cdot 10^{-03}$)
		\item $S3$ = \texttt{0xBF2A01A019C161D5} ($-1.98412698298579493134 \cdot 10^{-04}$)
		\item $S4$ = \texttt{0x3EC71DE357B1FE7D} ($2.75573137070700676789 \cdot 10^{-06}$)
		\item $S5$ = \texttt{0xBE5AE5E68A2B9CEB} ($-2.50507602534068634195 \cdot 10^{-08}$)
		\item $S6$ = \texttt{0x3DE5D93A5ACFD57C} ($1.58969099521155010221 \cdot 10^{-10}$)
	\end{compactitem}
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.9\textwidth]{./figure/Sin_Kernel_Flowchart.pdf}
	\caption{Flowchart \_\_kernel\_sin}
	\label{fig:flowchart-kernel_sin}
\end{figure}