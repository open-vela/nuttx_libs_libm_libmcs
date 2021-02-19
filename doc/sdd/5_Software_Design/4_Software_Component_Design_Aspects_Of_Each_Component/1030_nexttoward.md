### nexttoward  {#sec:component-nexttoward}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double nexttoward(double x, long double y)} \\ 
			
			Type &     \\ 
			
			Files &     \\ 
			
			Subordinates and Superiors &     \\ 
			
			Purpose & The \texttt{nexttoward} function shall return the next representable floating-point number following argument \texttt{x} in direction of argument \texttt{y}. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-4750
			\end{compactitem}    \\ 
			
			References & \texttt{nexttowardf} \ref{sec:component-nexttowardf}, \texttt{nextafter} \ref{sec:component-nextafter}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design
