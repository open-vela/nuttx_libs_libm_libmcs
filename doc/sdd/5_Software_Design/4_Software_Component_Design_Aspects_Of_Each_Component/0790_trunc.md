### trunc {#sec:component-trunc}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double trunc(double x)} \\ 
			
			Type & Procedure    \\ 
			
			Files & \texttt{libm/common/s\_trunc.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-trunc.png}}    \\ 
			
			Purpose & The \texttt{trunc} function shall return the input value rounded to the nearest integer value that is not greater in magnitude than the input value. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-1060
				\item REQ-ML-1070
				\item REQ-ML-1071
			\end{compactitem}    \\ 
			
			References & \texttt{truncf} \ref{sec:component-truncf}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following return values shall have the same sign as the input value.
	\item If the exponent is < 20, the integral part of x is in the double's highword:
	\begin{compactenum}
		\item If the exponent is < 0, there is no integral part, return a zero.
		\item Return x rounded to the nearest integer no greater in magnitude than x.
	\end{compactenum}
	\item If the exponent is > 51, there is no fractional part:
	\begin{compactenum}
		\item If the exponent is = 1024, x is \texttt{NaN} or infinite, return x+x.
		\item Return x.
	\end{compactenum}
	\item Return x rounded to the nearest integer no greater in magnitude than x.
\end{compactenum}

\begin{figure}[H]
	\begin{sffamily}\small
		\begin{center}
			\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{|c||c|c|c|c|c|c|c|}
				\hline
				$x$        & $-$Inf & $<0$             & $-0$ & $+0$              & $>0$               & $+$Inf & NaN \\ \hline
				$trunc(x)$ & $-$Inf & $\lceil x\rceil$ & \multicolumn{2}{c|}{$x$} & $\lfloor x\rfloor$ & $+$Inf & NaN \\ \hline
				
				\caption{Outputs of trunc}\label{tab:trunc}
			\end{tabularx}
		\end{center}
	\end{sffamily}
\end{figure}

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Trunc_Flowchart.pdf}
	\caption{Flowchart trunc}
	\label{fig:flowchart-trunc}
\end{figure}