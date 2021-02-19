### isinf {#sec:component-isinf}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{int isinf(double x)} \newline \texttt{int isinf(float x)} \\ 
			
			Type & Macro    \\ 
			
			Files & \texttt{include/math.h}    \\ 
			
			Subordinates and Superiors & \begin{minipage}[t]{1\linewidth} \begin{compactitem}
					\item Calls \texttt{fpclassify}.
				\end{compactitem} \end{minipage}    \\ 
				
			Purpose & The \texttt{isinf} macro shall return 1 if the input is infinite, 0 if not. \newline
			The macro shall be callable with both a float and a double input. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-1320
			\end{compactitem}    \\ 
			
			References & \texttt{fpclassify} \ref{sec:component-fpclassify}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Call \texttt{fpclassify}.
	\item Check that the return value of the \texttt{fpclassify} call is \texttt{FP\_INFINITE}, if so return 1, else return 0.
\end{compactenum}

\begin{figure}[H]
	\begin{sffamily}\small
		\begin{center}
			\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{|c||c|c|c|c|}
				\hline
				$x$        & $-$Inf & $\in \mathbb{R}$ & $+$Inf & NaN  \\ \hline
				$isinf(x)$ & $+1$   & $+0$             & $+1$   & $+0$ \\ \hline
				
				\caption{Outputs of isinf}\label{tab:isinf}
			\end{tabularx}
		\end{center}
	\end{sffamily}
\end{figure}

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Isinf_Flowchart.pdf}
	\caption{Flowchart isinf}
	\label{fig:flowchart-isinf}
\end{figure}