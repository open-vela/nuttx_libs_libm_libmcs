### truncf {#sec:component-truncf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float truncf(float x)} \\ 
		
		Type & Procedure    \\ 
		
		Files & \texttt{libm/common/sf\_trunc.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{trunc}.    \\ 
		
		Purpose & Float-equivalent to \texttt{trunc}.    \\ 
		
		References & \texttt{trunc} \ref{sec:component-trunc}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following return values shall have the same sign as the input value.
	\item If the exponent is < 23, there may be a fractional part:
	\begin{compactenum}
		\item If the exponent is < 0, there is no integral part, return 0.
		\item Return x rounded to the nearest integer no greater in magnitude than x.
	\end{compactenum}
	\item If the exponent is = 128, x is \texttt{NaN} or infinite, return x+x.
	\item Return x.
\end{compactenum}

Expected output table is equivalent to \texttt{trunc}, \ref{tab:trunc}.

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Truncf_Flowchart.pdf}
	\caption{Flowchart truncf}
	\label{fig:flowchart-truncf}
\end{figure}