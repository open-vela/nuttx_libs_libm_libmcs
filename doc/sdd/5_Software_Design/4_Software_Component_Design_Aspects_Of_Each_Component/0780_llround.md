### llround  {#sec:component-llround}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{long long int llround(double x)} \\ 
			
			Type & Procedure    \\ 
			
			Files &     \\ 
			
			Subordinates and Superiors &    \\ 
			
			Purpose & The \texttt{llround} function shall return the input value rounded to the nearest integer value; rounding halfway cases away from zero. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-8400
			\end{compactitem}    \\ 
			
			References & \texttt{llroundf} \ref{sec:component-llroundf}, \texttt{round} \ref{sec:component-round}, \texttt{lround} \ref{sec:component-lround}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design
