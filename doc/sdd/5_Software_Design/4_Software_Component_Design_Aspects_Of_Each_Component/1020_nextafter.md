### nextafter  {#sec:component-nextafter}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double nextafter(double x, double y)} \\ 
			
			Type &     \\ 
			
			Files &     \\ 
			
			Subordinates and Superiors &     \\ 
			
			Purpose & The \texttt{nextafter} function shall return the next representable floating-point number following argument \texttt{x} in direction of argument \texttt{y}. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-4700
				\item REQ-ML-4710
				\item REQ-ML-4720
				\item REQ-ML-4730
				\item REQ-ML-4731
				\item REQ-ML-4740
				\item REQ-ML-4741
			\end{compactitem}    \\ 
			
			References & \texttt{nextafterf} \ref{sec:component-nextafterf}, \texttt{nexttoward} \ref{sec:component-nexttoward}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design
