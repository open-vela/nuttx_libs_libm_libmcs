### scalbn {#sec:component-scalbn}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double scalbn(double x, int n)} \\ 
			
			Type & Procedure    \\ 
			
			Files & \texttt{libm/common/s\_scalbn.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-scalbn.png}}    \\ 
			
			Purpose & 
			The \texttt{scalbn} function shall scale x by $2^n$. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-4200
				\item REQ-ML-4210
				\item REQ-ML-4220
				\item REQ-ML-4230
				\item REQ-ML-4240
			\end{compactitem}    \\ 
			
			References & \texttt{scalbnf} \ref{sec:component-scalbnf}, \texttt{copysign} \ref{sec:component-copysign}, \texttt{\_\_ieee754\_pow} \ref{sec:component-ieee-pow}, \texttt{\_\_kernel\_rem\_pio2} \ref{sec:component-kernel-rem-pio2}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following return values shall have the same sign as the input value.
	\item If the input is subnormal or zero:
	\begin{compactenum}
		\item If the input is zero, return a zero.
		\item Scale up the input by multiplying with $2^{54}$.
		\item If n is < -50000 return a zero, with underflow.
	\end{compactenum}
	\item If the exponent of x is 1024, x is \texttt{NaN} or infinite, return x+x.
	\item If the exponent of x + n is > 1023, return an infinity, with overflow.
	\item If the exponent of x + n is > 0, return x with the exponent increased by n.
	\item If the exponent of x + n is > -54, return x with the exponent increased by n and then multiplied with $2^{-54}$.
	\item If n is > 50000 return an infinity, with overflow.
	\item Return a zero, with underflow.
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.88\textwidth]{./figure/Scalbn_Flowchart.pdf}
	\caption{Flowchart scalbn}
	\label{fig:flowchart-scalbn}
\end{figure}