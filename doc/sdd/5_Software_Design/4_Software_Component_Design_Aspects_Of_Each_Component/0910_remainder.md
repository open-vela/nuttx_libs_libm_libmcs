### remainder  {#sec:component-remainder}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double remainder(double x, double y)} \\ 
			
			Type & Procedure    \\ 
			
			Files &    \\ 
			
			Subordinates and Superiors &    \\ 
			
			Purpose & The \texttt{remainder} function shall return the  floating-point remainder $r = x − n \cdot y$ of \texttt{x} and \texttt{y}, where \texttt{n} is the integral value nearest to $\frac{x}{y}$. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-3900
				\item REQ-ML-3910
				\item REQ-ML-3920
				\item REQ-ML-3940
			\end{compactitem}    \\ 
			
			References & \texttt{remainderf} \ref{sec:component-remainderf}, \texttt{remquo} \ref{sec:component-remquo}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design
