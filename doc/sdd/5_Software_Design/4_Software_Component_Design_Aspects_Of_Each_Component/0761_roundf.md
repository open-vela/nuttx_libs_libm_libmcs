### roundf {#sec:component-roundf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float roundf(float x)} \\ 
		
		Type & Procedure    \\ 
		
		Files & \texttt{libm/common/sf\_round.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{round}.    \\ 
		
		Purpose & Float-equivalent to \texttt{round}.    \\ 
		
		References & \texttt{round} \ref{sec:component-round}, \texttt{lroundf} \ref{sec:component-lroundf}, \texttt{llroundf} \ref{sec:component-llroundf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following return values shall have the same sign as the input value.
	\item If the exponent is < 23, there may be a fractional part:
	\begin{compactenum}
		\item If the exponent is < 0, there is no integral part:
		\begin{compactenum}
			\item If the exponent is -1, return a zero.
			\item Return a one.
		\end{compactenum}
		\item If the input is integral, return x.
		\item Return x rounded to the nearest integer, with halfway cases rounded away from zero, regardless of the current rounding direction.
	\end{compactenum}
	\item If the exponent is = 128, x is \texttt{NaN} or infinite, return x+x.
	\item Return x.
\end{compactenum}

Expected output table is equivalent to \texttt{round}, \ref{tab:round}.

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Roundf_Flowchart.pdf}
	\caption{Flowchart roundf}
	\label{fig:flowchart-roundf}
\end{figure}