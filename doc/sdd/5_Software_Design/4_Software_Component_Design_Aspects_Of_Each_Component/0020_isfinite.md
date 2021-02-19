### isfinite {#sec:component-isfinite}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{int isfinite(double x)} \newline \texttt{int isfinite(float x)} \\ 
			
			Type & Macro    \\ 
			
			Files & \texttt{include/math.h}    \\ 
			
			Subordinates and Superiors & \begin{minipage}[t]{1\linewidth} \begin{compactitem}
				\item Calls \texttt{fpclassify}.
			\end{compactitem} \end{minipage}    \\ 
			
			Purpose & The \texttt{isfinite} macro shall return 1 if the input is finite, 0 if not. \newline
			The macro shall be callable with both a float and a double input. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-1300
			\end{compactitem}    \\ 
			
			References & \texttt{fpclassify} \ref{sec:component-fpclassify}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Call \texttt{fpclassify}.
	\item Check that the return value of the \texttt{fpclassify} call is neither \texttt{FP\_INFINITE} nor \texttt{FP\_NAN}, if so return 1, else return 0.
\end{compactenum}

\begin{figure}[H]
	\begin{sffamily}\small
		\begin{center}
			\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{|c||c|c|c|c|}
				\hline
				$x$           & $-$Inf & $\in \mathbb{R}$ & $+$Inf & NaN  \\ \hline
				$isfinite(x)$ & $+0$   & $+1$             & $+0$   & $+0$ \\ \hline
				
				\caption{Outputs of isfinite}\label{tab:isfinite}
			\end{tabularx}
		\end{center}
	\end{sffamily}
\end{figure}

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Isfinite_Flowchart.pdf}
	\caption{Flowchart isfinite}
	\label{fig:flowchart-isfinite}
\end{figure}