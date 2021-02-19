### frexp  {#sec:component-frexp}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double frexp(double value, double *exp)} \\ 
			
			Type &     \\ 
			
			Files &     \\ 
			
			Subordinates and Superiors &     \\ 
			
			Purpose & The \texttt{frexp} function shall return the mantissa of the floating-point number \texttt{value} and place its exponent in \texttt{*exp}. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-4000
				\item REQ-ML-4010
				\item REQ-ML-4020
				\item REQ-ML-4040
			\end{compactitem}    \\ 
			
			References & \texttt{frexpf} \ref{sec:component-frexpf}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design
