### \_\_signbitd {#sec:component-signbitd}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{int \_\_signbitd(double x)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/common/s\_signbit.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__signbitd.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_signbitd} function shall return 1 if the input is signed, 0 if not. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_signbitf} \ref{sec:component-signbitf}, \texttt{signbit} \ref{sec:component-signbit}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Use a mask to get the sign bit of the input value.
	\item If the sign bit is set, return 1, else return 0.
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.6\textwidth]{./figure/Signbitd_Flowchart.pdf}
	\caption{Flowchart \_\_signbitd}
	\label{fig:flowchart-signbitd}
\end{figure}