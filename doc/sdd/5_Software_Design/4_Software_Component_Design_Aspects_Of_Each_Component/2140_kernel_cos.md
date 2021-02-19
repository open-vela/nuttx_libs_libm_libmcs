### \_\_kernel\_cos {#sec:component-kernel-cos}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double \_\_kernel\_cos(double x, double y)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/k\_cos.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__kernel_cos.png}}    \\ 
			
			Purpose & 
			The function \_\_kernel\_cos computes the cosine of the input value. The sum of both input parameters \texttt{x} and \texttt{y} is bounded to $[\frac{-\pi}{4};\frac{\pi}{4}]$. The first parameter x is the requested value in raw precision while the second parameter contains a tail for higher precision. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_kernel\_cosf} \ref{sec:component-kernel-cosf}, cos \ref{sec:component-cos}, sin \ref{sec:component-sin}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{enumerate}
	\item The input value x and y are interpreted in radians.
	\item The cosine is computed by evaluating the following polynomial of degree 14:
	
	\begin{align}
		r &= C1\cdot x^2 + C2\cdot x^4 + C3\cdot x^6 + C4\cdot x^{8} + C5\cdot x^{10} + C6\cdot x^{12} \\
		cos(x+y) &= w + (((1 - w) - hz) + (x^2 \cdot r - x \cdot y))
	\end{align}
	with:
	\begin{compactitem}
		\item $hz = 0.5 \cdot x^2$
		\item $w = 1 - hz$
	\end{compactitem}
	and 
	\begin{compactitem}
		\item $C1$ = \texttt{0x3FA555555555554C} (4.16666666666666019037 $\cdot 10^{-02}$)
		\item $C2$ = \texttt{0xBF56C16C16C15177} (-1.38888888888741095749 $\cdot 10^{-03}$)
		\item $C3$ = \texttt{0x3EFA01A019CB1590} (2.48015872894767294178 $\cdot 10^{-05}$)
		\item $C4$ = \texttt{0xBE927E4F809C52AD} (-2.75573143513906633035 $\cdot 10^{-07}$)
		\item $C5$ = \texttt{0x3E21EE9EBDB4B1C4} (2.08757232129817482790 $\cdot 10^{-09}$)
		\item $C6$ = \texttt{0xBDA8FAE9BE8838D4} (-1.13596475577881948265 $\cdot 10^{-11}$)
	\end{compactitem}
\end{enumerate}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.4\textwidth]{./figure/Cos_Kernel_Flowchart.pdf}
	\caption{Flowchart \_\_kernel\_cos}
	\label{fig:flowchart-kernel_cos}
\end{figure}