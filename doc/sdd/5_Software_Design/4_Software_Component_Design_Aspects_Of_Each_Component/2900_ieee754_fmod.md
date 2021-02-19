### \_\_ieee754\_fmod {#sec:component-ieee-fmod}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double \_\_ieee754\_fmod(double x)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/e\_fmod.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__ieee754_fmod.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_ieee754\_fmod} function shall return the floating point remainder of $\frac{x}{y}$. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_ieee754\_fmodf} \ref{sec:component-ieee-fmodf}, \texttt{fmod} \ref{sec:component-fmod}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All return values mentioned hereafter shall have the same sign as x at this point.
	\item If x is not finite, or y is NaN or zero, return NaN.
	\item If |x| < |y|, return x.
	\item If |x| equals |y|, return a zero.
	\item Remove the sign bits from x and y.
	\item Extract the binary exponents of x and y into ix and iy respectively.\footnote{Take care with subnormals.}
	\item Normalize x and y by replacing their exponent with 1.\footnote{Subnormal x or y instead need to be shifted left until the exponent is 1.}
	\item Loop for ix - iy steps, add an additional step if x is > y at the end:
	\begin{compactenum}
		\item Set x to x - y.
		\item If x is 0, return a zero.
	\end{compactenum}
	\item If the exponent of x is < 1, normalize x by shifting left until the exponent is 1. While doing so decrease iy once for every necessary shifting step.
	\item Set iy as the new exponent of x.\footnote{If iy is <= -1023 (this means the result is subnormal), x needs to be shifted right while increasing iy for every step until iy is -1022.}
	\item Return x.
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.65\textwidth]{./figure/Ieee_Fmod_Flowchart.pdf}
	\caption{Flowchart \_\_ieee754\_fmod}
	\label{fig:flowchart-ieee_fmod}
\end{figure}