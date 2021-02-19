### floor {#sec:component-floor}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double floor(double x)} \\ 
			
			Type & Procedure    \\ 
			
			Files & \texttt{libm/math/s\_floor.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-floor.png}}    \\ 
			
			Purpose & The \texttt{floor} function shall return the largest integral value not greater than the input value. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-1040
				\item REQ-ML-1051
				\item REQ-ML-1052
			\end{compactitem}    \\ 
			
			References & \texttt{floorf} \ref{sec:component-floorf}    \\ 
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
			\item If the input is >= 0, return a zero, with inexact.
			\item Return -1 with inexact.
		\end{compactenum}
		\item If x is integral, return x.
		\item Return x rounded towards negative infinity, with inexact.
	\end{compactenum}
	\item If the exponent is > 51, there is no fractional part:
	\begin{compactenum}
		\item If the exponent is = 1024, x is \texttt{NaN} or infinite, return x+x.
		\item Return x.
	\end{compactenum}
	\item If x is integral, return x.
	\item Return x rounded towards negative infinity, with inexact.
\end{compactenum}

\begin{figure}[H]
	\begin{sffamily}\small
		\begin{center}
			\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{|c||c|c|c|c|c|c|c|}
				\hline
				$x$        & $-$Inf & $<0$               & $-0$ & $+0$              & $>0$               & $+$Inf & NaN \\ \hline
				$floor(x)$ & $-$Inf & $\lfloor x\rfloor$ & \multicolumn{2}{c|}{$x$} & $\lfloor x\rfloor$ & $+$Inf & NaN \\ \hline
				
				\caption{Outputs of floor}\label{tab:floor}
			\end{tabularx}
		\end{center}
	\end{sffamily}
\end{figure}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.7\textwidth]{./figure/Floor_Flowchart.pdf}
	\caption{Flowchart floor}
	\label{fig:flowchart-floor}
\end{figure}