### isnormal  {#sec:component-isnormal}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{int isnormal(double x)} \newline \texttt{int isnormal(float x)} \\ 
			
			Type & Macro    \\ 
			
			Files & \texttt{include/math.h}    \\ 
			
			Subordinates and Superiors & \begin{minipage}[t]{1\linewidth} \begin{compactitem}
				\item Calls \texttt{fpclassify}.
			\end{compactitem} \end{minipage}    \\ 
			
			Purpose & The \texttt{isnormal} macro shall return 1 if the input is normal, 0 if not. \newline
			The macro shall be callable with both a float and a double input. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-5500
			\end{compactitem}    \\ 
			
			References & \texttt{fpclassify} \ref{sec:component-fpclassify}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design
