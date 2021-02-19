### scalbnf {#sec:component-scalbnf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float scalbnf(float x, int n)} \\ 
		
		Type & Procedure    \\ 
		
		Files & \texttt{libm/common/sf\_scalbn.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{scalbn}.    \\ 
		
		Purpose & Float-equivalent to \texttt{scalbn}.    \\ 
		
		References & \texttt{scalbn} \ref{sec:component-scalbn}, \texttt{copysignf} \ref{sec:component-copysignf}, \texttt{\_\_ieee754\_powf} \ref{sec:component-ieee-powf}, \texttt{\_\_kernel\_rem\_pio2f} \ref{sec:component-kernel-rem-pio2f}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following return values shall have the same sign as the input value.
	\item If the input is zero, return a zero.
	\item If the input is not finite, return x+x.
	\item If the input is subnormal:
	\begin{compactenum}
		\item Scale up the input by multiplying with $2^{25}$.
		\item If n is < -50000 return a zero, with underflow.
	\end{compactenum}
	\item If the exponent + n is > 254, return an infinity, with overflow.
	\item If the exponent + n is > 0, return x with the exponent increased by n.
	\item If the exponent + n is >= -22, return x with the exponent increased by n and then multiplied with $2^{-25}$.
	\item If n is > 50000 return an infinity, with overflow.
	\item Return a zero, with underflow.
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.70\textwidth]{./figure/Scalbnf_Flowchart.pdf}
	\caption{Flowchart scalbnf}
	\label{fig:flowchart-scalbnf}
\end{figure}