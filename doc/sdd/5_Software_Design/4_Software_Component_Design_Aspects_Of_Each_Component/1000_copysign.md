### copysign {#sec:component-copysign}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double copysign(double x, double y)} \\ 
			
			Type & Procedure    \\ 
			
			Files & \texttt{libm/common/s\_copysign.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-copysign.png}}    \\ 
			
			Purpose & The \texttt{copysign} function shall return the value with magnitude of x and sign of y. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-1380
				\item REQ-ML-1381
			\end{compactitem}    \\ 
			
			References & \texttt{copysignf} \ref{sec:component-copysignf}, \texttt{scalbn} \ref{sec:component-scalbn}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Return the value with the magnitude of x and sign of y.
\end{compactenum}

\begin{figure}[H]
	\begin{sffamily}\small
		\begin{center}
			\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{|c||c|c|}
				\hline
				$copysign(x, y)$ & \multicolumn{2}{c|}{$x$}                       \\ \hline
				$y$              & $\neq$NaN               & NaN                  \\ \hline \hline
				
				$-$NaN           & \multirow{4}{*}{$-|x|$} & \multirow{8}{*}{NaN} \\ \cline{1-1}
				$-$Inf           &                         &                      \\ \cline{1-1}
				$<0$             &                         &                      \\ \cline{1-1}
				$-0$             &                         &                      \\ \cline{1-2}
				$+0$             & \multirow{4}{*}{$|x|$}  &                      \\ \cline{1-1}
				$>0$             &                         &                      \\ \cline{1-1}
				$+$Inf           &                         &                      \\ \cline{1-1}
				$+$NaN           &                         &                      \\ \hline
				
				\caption{Outputs of copysign}\label{tab:copysign}
			\end{tabularx}
		\end{center}
	\end{sffamily}
\end{figure}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.5\textwidth]{./figure/Copysign_Flowchart.pdf}
	\caption{Flowchart copysign}
	\label{fig:flowchart-copysign}
\end{figure}