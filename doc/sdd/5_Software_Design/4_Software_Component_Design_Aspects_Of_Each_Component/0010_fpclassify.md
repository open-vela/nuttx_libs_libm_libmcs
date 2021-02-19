### fpclassify {#sec:component-fpclassify}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{int fpclassify(double x)} \newline \texttt{int fpclassify(float x)} \\ 
			
			Type & Macro    \\ 
			
			Files & \texttt{include/math.h}    \\ 
			
			Subordinates and Superiors & \begin{minipage}[t]{1\linewidth} \begin{compactitem}
				\item Calls \texttt{\_\_builtin\_fpclassify}.
				\item Calls \texttt{\_\_fpclassifyf}.
				\item Calls \texttt{\_\_fpclassifyd}.
				\item Called by \texttt{isfinite}.
				\item Called by \texttt{isinf}.
				\item Called by \texttt{isnan}.
			\end{compactitem} \end{minipage}    \\ 
			
			Purpose & 
			The internal \texttt{fpclassify} macro shall return one of the macros \texttt{FP\_ZERO}, \texttt{FP\_NORMAL}, \texttt{FP\_SUBNORMAL}, \texttt{FP\_INFINITE}, or \texttt{FP\_NAN}, depending on whether the input is zero, a normal, a subnormal, infinite or NaN respectively. \newline
			The macro shall be callable with both a float and a double input. \newline
			This component implements the following software requirements:
			\begin{compactitem}
				\item REQ-ML-5700
			\end{compactitem}    \\ 
			
			References & \texttt{\_\_fpclassifyd} \ref{sec:component-fpclassifyd}, \texttt{\_\_fpclassifyf} \ref{sec:component-fpclassifyf}, \texttt{isfinite} \ref{sec:component-isfinite}, \texttt{isinf} \ref{sec:component-isinf}, \texttt{isnan} \ref{sec:component-isnan}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Call \texttt{\_\_fpclassifyf} if the input was a float and return its result.
	\item Call \texttt{\_\_fpclassifyd} and return its result.
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Fpclassify_Flowchart.pdf}
	\caption{Flowchart fpclassify}
	\label{fig:flowchart-fpclassify}
\end{figure}