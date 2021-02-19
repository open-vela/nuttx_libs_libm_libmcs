### ceilf {#sec:component-ceilf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float ceilf(float x)} \\ 
		
		Type & Procedure    \\ 
		
		Files & \texttt{libm/math/sf\_ceil.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{ceil}.    \\ 
		
		Purpose & Float-equivalent to \texttt{ceil}.    \\ 
		
		References & \texttt{ceil} \ref{sec:component-ceil}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following return values shall have the same sign as the input value.
	\item If the exponent is < 23, there may be a fractional part:
	\begin{compactenum}
		\item If the exponent is < 0, there is no integral part:
		\begin{compactenum}
			\item If the input is <= 0, return a zero with inexact.
			\item Return 1 with inexact.
		\end{compactenum}
		\item If x is integral, return x.
		\item Return x rounded towards positive infinity with inexact.
	\end{compactenum}
	\item If the input is not finite, return x+x.
	\item Return x.
\end{compactenum}

Expected output table is equivalent to \texttt{ceil}, \ref{tab:ceil}.

\begin{figure}[H]
	\centering
	\includegraphics[width=0.7\textwidth]{./figure/Ceilf_Flowchart.pdf}
	\caption{Flowchart ceilf}
	\label{fig:flowchart-ceilf}
\end{figure}