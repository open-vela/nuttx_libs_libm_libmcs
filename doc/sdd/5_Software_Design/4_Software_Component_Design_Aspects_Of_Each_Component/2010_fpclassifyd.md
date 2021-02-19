### \_\_fpclassifyd {#sec:component-fpclassifyd}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{int \_\_fpclassifyd(double x)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/common/s\_fpclassify.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__fpclassifyd.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_fpclassifyd} function shall return one of the macros \texttt{FP\_ZERO}, \texttt{FP\_NORMAL}, \texttt{FP\_SUBNORMAL}, \texttt{FP\_INFINITE}, or \texttt{FP\_NAN}, depending on whether the input is zero, a normal, a subnormal, infinite or NaN respectively. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_fpclassifyf} \ref{sec:component-fpclassifyf}, \texttt{fmax} \ref{sec:component-fmax}, \texttt{fmin} \ref{sec:component-fmin}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Return \texttt{FP\_ZERO} if the input value is -0 or +0.
	\item Return \texttt{FP\_NORMAL} if the input value is finite and not a subnormal or zero.
	\item Return \texttt{FP\_SUBNORMAL} if the input value is a subnormal.
	\item Return \texttt{FP\_INFINITE} if the input value is positive or negative infinity.
	\item Return \texttt{FP\_NAN} if the input value is \texttt{NaN}.
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.6\textwidth]{./figure/Fpclassifyd_Flowchart.pdf}
	\caption{Flowchart \_\_fpclassifyd}
	\label{fig:flowchart-fpclassifyd}
\end{figure}