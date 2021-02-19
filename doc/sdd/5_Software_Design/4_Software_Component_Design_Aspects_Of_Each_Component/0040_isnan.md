### isnan {#sec:component-isnan}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{int isnan(double x)} \newline \texttt{int isnan(float x)} \\ 
			
			Type & Macro    \\ 
			
			Files & \texttt{include/math.h}    \\ 
			
			Subordinates and Superiors & \begin{minipage}[t]{1\linewidth} \begin{compactitem}
					\item Calls \texttt{fpclassify}.
				\end{compactitem} \end{minipage}    \\ 
				
			Purpose & The \texttt{isnan} macro shall return 1 if the input is infinite, 0 if not. \newline
			The macro shall be callable with both a float and a double input. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-1340
			\end{compactitem}    \\ 
			
			References & \texttt{fpclassify} \ref{sec:component-fpclassify}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Call \texttt{fpclassify}.
	\item Check that the return value of the \texttt{fpclassify} call is \texttt{FP\_NAN}, if so return 1, else return 0.
\end{compactenum}

\begin{figure}[H]
	\begin{sffamily}\small
		\begin{center}
			\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{|c||c|c|c|c|}
				\hline
				$x$        & $-$Inf & $\in \mathbb{R}$ & $+$Inf & NaN  \\ \hline
				$isnan(x)$ & $+0$   & $+0$             & $+0$   & $+1$ \\ \hline
				
				\caption{Outputs of isnan}\label{tab:isnan}
			\end{tabularx}
		\end{center}
	\end{sffamily}
\end{figure}

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Isnan_Flowchart.pdf}
	\caption{Flowchart isnan}
	\label{fig:flowchart-isnan}
\end{figure}