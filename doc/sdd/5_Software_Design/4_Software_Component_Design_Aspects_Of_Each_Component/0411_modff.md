### modff {#sec:component-modff}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float modff(float value, float *iptr)} \newline
		with \texttt{iptr} referring to a pointer to a \texttt{float} value that will be used to return one part of the result of the procedure. \\ 
		
		Type & Procedure    \\ 
		
		Files & \texttt{libm/common/sf\_modf.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{modf}.    \\ 
		
		Purpose & Float-equivalent to \texttt{modf}.    \\ 
		
		References & \texttt{modf} \ref{sec:component-modf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following outputs (both return value and out-pointer) shall have the same sign as the input value.
	\item If the argument \texttt{iptr} is a NULL-pointer replace the pointer internally with a valid one. At the end place a NULL-pointer to the out-pointer regardless of what is otherwise stated at that branch. The return value remains unchanged.
	\item Return \texttt{NaN} to both outputs if the input value is \texttt{NaN}.
	\item Return a zero if the input value is infinite, and place the infinity to the out-pointer.
	\item If the exponent is < 23, there may be a fractional part:
	\begin{compactenum}
		\item If the exponent is < 0, there is no integral part, return the input and place a zero to the out-pointer.
		\item If the input is integral, return a zero and place the input value to the out-pointer.
		\item Return the fractional part of the input and place the integral part to the out-pointer.
	\end{compactenum}
	\item Return a zero and place the input value to the out-pointer.
\end{compactenum}

Expected output table is equivalent to \texttt{modf}, \ref{tab:modf}.

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Modff_Flowchart.pdf}
	\caption{Flowchart modff}
	\label{fig:flowchart-modff}
\end{figure}