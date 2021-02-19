### \_\_kernel\_rem\_pio2 {#sec:component-kernel-rem-pio2}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{\_\_int32\_t \_\_kernel\_rem\_pio2(double *x, double *y, \_\_int32\_t e0, \_\_int32\_t nx)} \newline
			with \texttt{x} referring to an array of 3 \texttt{double} values used as an input, and \texttt{y} referring to an array of 2 \texttt{double} values that will be used to return the result of the procedure. \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/k\_rem\_pio2.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__kernel_rem_pio2.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_kernel\_rem\_pio2} function shall return the quadrant the input angle lies in (see \texttt{\_\_ieee754\_rem\_pio2} on how to convert the return value into the quadrant), and place the remainder of x (scaled x which consists of 3 values, hereafter called $x_0$, $x_1$ and $x_2$, original x $= x_0 \cdot 2^{e0} + x_1 \cdot 2^{e0-24} + x_2 \cdot 2^{e0-48}$) divided by $\frac{\pi}{4}$ in the output array (which consists of 2 values, the remainder and its tail, hereafter called $y_0$ and $y_1$). \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_kernel\_rem\_pio2f} \ref{sec:component-kernel-rem-pio2f}, \texttt{floor} \ref{sec:component-floor}, \texttt{scalbn} \ref{sec:component-scalbn}, \texttt{\_\_ieee754\_rem\_pio2} \ref{sec:component-ieee-rem-pio2}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

Use Payne and Hanek's method for range reduction as described in the article \textit{Radian reduction for trigonometric functions}\footnote{By Mary H. Payne and Robert N. Hanek.} and referenced by the paper \textit{A New Range-Reduction Algorithm}\footnote{By N. Brisebarre, D. Defour, P. Kornerup, J.-M Muller and R. Revol.}. The description in the article is quite extensive and should be sufficient to implement the algorithm (refer to §3.0 of the article for a step by step outline), therefore its contents will not be repeated here.

<!--\begin{figure}[H]
	\centering
	\includegraphics[width=0.82\textwidth]{./figure/Kernel_Rem_pio2_Flowchart.pdf}
	\caption{Flowchart \_\_kernel\_rem\_pio2}
	\label{fig:flowchart-kernel_rem_pio2}
\end{figure}-->