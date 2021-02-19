### hypot {#sec:component-hypot}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double hypot(double x, double y)} \\ 
			
			Type & Wrapper for procedure    \\ 
			
			Files & \texttt{libm/math/w\_hypot.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-hypot.png}}    \\ 
			
			Purpose & The \texttt{hypot} function shall return the square root of $x^2+y^2$. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-1260
				\item REQ-ML-1270
				\item REQ-ML-1271
			\end{compactitem}    \\ 
			
			References & \texttt{hypotf} \ref{sec:component-hypotf}, \texttt{\_\_ieee754\_hypot} \ref{sec:component-ieee-hypot}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Call \texttt{\_\_ieee754\_hypot} with x, y as input and return the result.
\end{compactenum}

\begin{figure}[H]
	\begin{sffamily}\small
		\begin{center}
			\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{|c||c|c|c|c|c|}
				\hline
				$hypot(x, y)$    & \multicolumn{4}{c|}{$x$}                                                        \\ \hline
				$y$              & $-$Inf                  & $\in \mathbb{R}$   & $+$Inf                  & NaN    \\ \hline \hline
				
				$-$Inf           & \multirow{4}{*}{$+$Inf} & $+$Inf             & \multirow{4}{*}{$+$Inf} & $+$Inf \\ \cline{1-1} \cline{3-3} \cline{5-5} 
				$\in \mathbb{R}$ &                         & $\sqrt{x^2 + y^2}$ &                         & NaN    \\ \cline{1-1} \cline{3-3} \cline{5-5} 
				$+$Inf           &                         & $+$Inf             &                         & $+$Inf \\ \cline{1-1} \cline{3-3} \cline{5-5} 
				NaN              &                         & NaN                &                         & NaN    \\ \hline
				
				\caption{Outputs of hypot}\label{tab:hypot}
			\end{tabularx}
		\end{center}
	\end{sffamily}
\end{figure}