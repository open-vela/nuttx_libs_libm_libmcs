### round {#sec:component-round}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double round(double x)} \\ 
			
			Type & Procedure    \\ 
			
			Files & \texttt{libm/common/s\_round.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-round.png}}    \\ 
			
			Purpose & The \texttt{round} function shall return the input value rounded to the nearest integer value; rounding halfway cases away from zero. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-1020
				\item REQ-ML-1031
				\item REQ-ML-1032
			\end{compactitem}    \\ 
			
			References & \texttt{roundf} \ref{sec:component-roundf}, \texttt{lround} \ref{sec:component-lround}, \texttt{llround} \ref{sec:component-llround}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following return values shall have the same sign as the input value.
	\item If the exponent is < 20, the integral part of x is in the double's highword:
	\begin{compactenum}
		\item If the exponent is < 0, there is no integral part:
		\begin{compactenum}
			\item If the exponent is -1, return a zero.
			\item Return a one.
		\end{compactenum}
		\item If the input is integral, return x.
		\item Return x rounded to the nearest integer, with halfway cases rounded away from zero, regardless of the current rounding direction.
	\end{compactenum}
	\item If the exponent is > 51, there is no fractional part:
	\begin{compactenum}
		\item If the exponent is = 1024, x is \texttt{NaN} or infinite, return x+x.
		\item Return x.
	\end{compactenum}
	\item If the input is integral, return x.
	\item Return x rounded to the nearest integer, with halfway cases rounded away from zero, regardless of the current rounding direction.
\end{compactenum}

\begin{figure}[H]
	\begin{sffamily}\small
		\begin{center}
			\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{|c||c|c|c|c|c|c|c|}
				\hline
				$x$        & $-$Inf & $<0$                   & $-0$ & $+0$              & $>0$                     & $+$Inf & NaN \\ \hline
				$round(x)$ & $-$Inf & $\lceil x - 0.5\rceil$ & \multicolumn{2}{c|}{$x$} & $\lfloor x + 0.5\rfloor$ & $+$Inf & NaN \\ \hline
				
				\caption{Outputs of round}\label{tab:round}
			\end{tabularx}
		\end{center}
	\end{sffamily}
\end{figure}

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Round_Flowchart.pdf}
	\caption{Flowchart round}
	\label{fig:flowchart-round}
\end{figure}