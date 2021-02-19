### signbit {#sec:component-signbit}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{int signbit(double x)} \newline \texttt{int signbit(float x)} \\ 
			
			Type & Macro    \\ 
			
			Files & \texttt{include/math.h}    \\ 
			
			Subordinates and Superiors & \begin{minipage}[t]{1\linewidth} \begin{compactitem}
					\item Calls \texttt{\_\_signbitd}.
					\item Calls \texttt{\_\_signbitf}.
					\item Called by \texttt{trunc}.
					\item Called by \texttt{truncf}.
				\end{compactitem} \end{minipage}    \\ 
				
			Purpose & The \texttt{signbit} macro shall return 1 if the signbit of the input is set to 1, 0 if not. \newline
			The macro shall be callable with both a float and a double input. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-1360
			\end{compactitem}    \\ 
			
			References & \texttt{\_\_signbitd} \ref{sec:component-signbitd}, \texttt{\_\_signbitf} \ref{sec:component-signbitf}, \texttt{trunc} \ref{sec:component-trunc}, \texttt{truncf} \ref{sec:component-truncf}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Call \texttt{\_\_signbitf} if the input was a float and return its result.
	\item Call \texttt{\_\_signbitd} and return its result.
\end{compactenum}

\begin{figure}[H]
	\begin{sffamily}\small
		\begin{center}
			\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{|c||c|c|c|c|c|c|c|c|}
				\hline
				$x$          & $-$NaN & $-$Inf & $<0$ & $-0$ & $+0$ & $>0$ & $+$Inf & $+$NaN \\ \hline
				$signbit(x)$ & \multicolumn{4}{c|}{$+1$} 	 & \multicolumn{4}{c|}{$+0$}     \\ \hline
				
				\caption{Outputs of signbit}\label{tab:signbit}
			\end{tabularx}
		\end{center}
	\end{sffamily}
\end{figure}

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Signbit_Flowchart.pdf}
	\caption{Flowchart signbit}
	\label{fig:flowchart-signbit}
\end{figure}