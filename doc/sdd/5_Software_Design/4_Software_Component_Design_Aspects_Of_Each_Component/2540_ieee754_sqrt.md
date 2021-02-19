### \_\_ieee754\_sqrt {#sec:component-ieee-sqrt}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double \_\_ieee754\_sqrt(double x)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/e\_sqrt.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__ieee754_sqrt.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_ieee754\_sqrt} function shall return $\sqrt{x}$. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_ieee754\_sqrtf} \ref{sec:component-ieee-sqrtf}, \texttt{sqrt} \ref{sec:component-sqrt}, \texttt{\_\_ieee754\_asin} \ref{sec:component-ieee-asin}, \texttt{\_\_ieee754\_acos} \ref{sec:component-ieee-acos}, \texttt{\_\_ieee754\_pow} \ref{sec:component-ieee-pow}, \texttt{\_\_ieee754\_hypot} \ref{sec:component-ieee-hypot}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item If x is \texttt{NaN}, return \texttt{NaN}.
	\item If x is positive infinity, return positive infinity.
	\item If x is negative infinity, return \texttt{NaN}.\footnote{The first three steps can be combined by checking that x is not finite and returning x$\cdot$x+x, which returns the correct value for all three cases}
	\item If x is a zero, return the zero with the same sign.
	\item If x is negative, return NaN.
	\item Given x find y and integer k such that the formula
	\begin{align}
		y &= x \cdot 2 ^ {-2k} \label{formula_sqrt_1} \\ \nonumber
		\Leftrightarrow \qquad \sqrt{x} &= 2^{k} \cdot \sqrt{y}
	\end{align}
	with $y \in [1.0, 4.0)$\footnote{With this trick one can ensure that $\sqrt{y}$ truncates to 1.} \\
	holds true.\footnote{Take special care with subnormal numbers.}
	\item Compute the square root bit by bit\footnote{As shown in John von Neumann's \textit{First Draft of a Report on the EDVAC} in §10.1}:
	\begin{compactenum}
		\item Let $q_i$ be $\sqrt{y}$ truncated to $i$ bit after the binary point ($q_0 = 1$), then
		\begin{align}
			y_i &= 2 ^ {i+1} \cdot (y - q_i^2) \label{formula_sqrt_2}
		\end{align}
		\item To compute $q_{i+1}$ from $q_i$, check whether
		\begin{align}
			(q_i + 2^{-(i+1)})^2 <= y \label{formula_sqrt_3}
		\end{align}
		is false, if yes $q_{i+1} = q_i$, else $q_{i+1} = q_i + 2^{-(i+1)}$.
		\item With $s_i = 2 q_i$ formula \ref{formula_sqrt_3} is equivalent to \footnotemark
		\begin{align}
			s_i + 2^{-(i+1)} <= y_i \label{formula_sqrt_4}
		\end{align}
		\footnotetext{Since the left hand side of this formula only contains i+2 bits it is not necessary to do a full (53-bit) comparison.}
		\item With formula \ref{formula_sqrt_4} one can compute $s_i$ and $y_i$ with the following recurrence formula: \\
		If formula \ref{formula_sqrt_4} is false:
		\begin{align}
			s_{i+1} = s_i \wedge y_{i+1} = y_i \label{formula_sqrt_5}
		\end{align}
		otherwise:
		\begin{align}
			s_{i+1} = s_i + 2^{-i} \wedge y_{i+1} = y_i - s_i - 2^{-(i+1)} \label{formula_sqrt_6}
		\end{align}
	\end{compactenum}
	\item When done with computing the 53-bit result in the previous step, compute another bit. Use this bit added to the remainder to correctly round the calculated square root.
	\item Use formula \ref{formula_sqrt_1} to return y to x.
	\item Return x.
\end{compactenum}

#### Hardware Version for SPARC V8

The \texttt{\_\_ieee754\_sqrt} procedure can be replaced by the hardware version of the sqrt procedure. For SPARC V8 this implementation can be found in file \texttt{libm/machine/sparc\_v8/e\_sqrt.c}.

The sole function of the replacement is to directly call the \gls{FPU}'s sqrt instruction.

\begin{figure}[H]
	\centering
	\includegraphics[width=0.75\textwidth]{./figure/Ieee_Sqrt_Flowchart.pdf}
	\caption{Flowchart \_\_ieee754\_sqrt}
	\label{fig:flowchart-ieee_sqrt}
\end{figure}