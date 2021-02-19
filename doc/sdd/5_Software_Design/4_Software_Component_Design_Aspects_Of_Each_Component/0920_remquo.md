### remquo  {#sec:component-remquo}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double remquo(double x, double y, int *quo)} \\ 
			
			Type & Procedure    \\ 
			
			Files &    \\ 
			
			Subordinates and Superiors &    \\ 
			
			Purpose & The \texttt{remquo} function shall return the  floating-point remainder $r = x − n \cdot y$ of \texttt{x} and \texttt{y}, where \texttt{n} is the integral value nearest to $\frac{x}{y}$. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-5600
				\item REQ-ML-5601
				\item REQ-ML-5610
				\item REQ-ML-5620
				\item REQ-ML-5640
			\end{compactitem}    \\ 
			
			References & \texttt{remquof} \ref{sec:component-remquof}, \texttt{remainder} \ref{sec:component-remainder}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design
