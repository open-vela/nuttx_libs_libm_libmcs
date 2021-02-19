### \_\_ieee754\_hypot {#sec:component-ieee-hypot}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double \_\_ieee754\_hypot(double x, double y)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/e\_hypot.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__ieee754_hypot.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_ieee754\_hypot} function shall return $\sqrt{x^2+y^2}$. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_ieee754\_hypotf} \ref{sec:component-ieee-hypotf}, \texttt{hypot} \ref{sec:component-hypot}, \texttt{\_\_ieee754\_sqrt} \ref{sec:component-ieee-sqrt}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item If either x or y is \texttt{NaN}, return NaN.
	\item If either x or y is positive or negative infinity, return positive infinity.
	\item Remove the sign of both x and y.
	\item Assume x > y, otherwise replace x with y and y with x.
	\item If $\frac{x}{y} > 2^{60}$, y is too small to matter when the result is represented with double precision, return x, with inexact.
	\item If x > $2^{500}$, scale down x and y by multiplying them with $2^{-600}$, otherwise their combined squares will overflow the double range.
	\item If y < $2^{-500}$, scale up x and y by multiplying them with $2^{600}$, otherwise their combined squares will underflow the double range.
	\item If $z = x \cdot x + y \cdot y$ has an error of less than $\frac{\sqrt{2}}{2}$ \glspl{ULP}, then $\sqrt{z}$ has an error of less than 1 \gls{ULP}. Using this relation calculate $\sqrt{x \cdot x + y \cdot y}$ as follows:
	\begin{compactenum}
		\item If $x > 2y$ use the following to replace $x \cdot x + y \cdot y$:
		\begin{gather}
			x_1 \cdot x_1 + (y \cdot y + (x_2 \cdot (x+x_1))) \label{formula_hypot_1}
		\end{gather}
		with $x_1 = x$ with the lower 32bits cleared and $x_2 = x - x_1$.
		\item Otherwise use:
		\begin{gather}
			t_1 \cdot y_1 + ((x-y) \cdot (x-y)+(t_1 \cdot y_2 + t_2 \cdot y)) \label{formula_hypot_2}
		\end{gather}
		with $t_1 = 2x$ with the lower 32bits cleared and $t_2 = 2x - t_1$, and $y_1 = y$ with the lower 32bits cleared and $y_2 = y - y_1$.
		\item Use \texttt{\_\_ieee754\_sqrt} to calculate the square root of the replacement \ref{formula_hypot_1} or \ref{formula_hypot_2}.
	\end{compactenum}
	\item Revert the scaling on the resulting square root if any was done in an earlier step.
	\item Return the calculated square root.
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.57\textwidth]{./figure/Ieee_Hypot_Flowchart.pdf}
	\caption{Flowchart \_\_ieee754\_hypot}
	\label{fig:flowchart-ieee_hypot}
\end{figure}