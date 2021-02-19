### lround  {#sec:component-lround}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{long int lround(double x)} \\ 
			
			Type & Procedure    \\ 
			
			Files &     \\ 
			
			Subordinates and Superiors &    \\ 
			
			Purpose & The \texttt{lround} function shall return the input value rounded to the nearest integer value; rounding halfway cases away from zero. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-8300
				\item REQ-ML-8310
				\item REQ-ML-8320
				\item REQ-ML-8330
				\item REQ-ML-8340
			\end{compactitem}    \\ 
			
			References & \texttt{lroundf} \ref{sec:component-lroundf}, \texttt{round} \ref{sec:component-round}, \texttt{llround} \ref{sec:component-llround}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design
