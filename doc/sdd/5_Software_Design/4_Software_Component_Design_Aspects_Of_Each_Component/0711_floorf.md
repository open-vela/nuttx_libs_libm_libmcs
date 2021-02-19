### floorf {#sec:component-floorf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float floorf(float x)} \\ 
		
		Type & Procedure    \\ 
		
		Files & \texttt{libm/math/sf\_floor.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{floor}.    \\ 
		
		Purpose & Float-equivalent to \texttt{floor}.    \\ 
		
		References & \texttt{floor} \ref{sec:component-floor}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following return values shall have the same sign as the input value.
	\item If the exponent is < 23, there may be a fractional part:
	\begin{compactenum}
		\item If the exponent is < 0, there is no integral part:
		\begin{compactenum}
			\item If the input is >= 0, return a zero with inexact.
			\item Return -1 with inexact.
		\end{compactenum}
		\item If x is integral, return x.
		\item Return x rounded towards negative infinity with inexact.
	\end{compactenum}
	\item If the input is not finite, return x+x.
	\item Return x.
\end{compactenum}

Expected output table is equivalent to \texttt{floor}, \ref{tab:floor}.

\begin{figure}[H]
	\centering
	\includegraphics[width=0.7\textwidth]{./figure/Floorf_Flowchart.pdf}
	\caption{Flowchart floorf}
	\label{fig:flowchart-floorf}
\end{figure}