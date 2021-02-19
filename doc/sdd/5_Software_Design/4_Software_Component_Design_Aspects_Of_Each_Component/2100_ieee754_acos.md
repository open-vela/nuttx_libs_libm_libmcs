### \_\_ieee754\_acos {#sec:component-ieee-acos}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double \_\_ieee754\_acos(double x)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/e\_acos.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__ieee754_acos.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_ieee754\_acos} function shall return the arccosine of x. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_ieee754\_acosf} \ref{sec:component-ieee-acosf}, \texttt{\_\_ieee754\_asin} \ref{sec:component-ieee-asin}, \texttt{acos} \ref{sec:component-acos}, \texttt{\_\_ieee754\_sqrt} \ref{sec:component-ieee-sqrt}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

The \texttt{\_\_ieee754\_acos} functionality is highly similar to the \texttt{\_\_ieee754\_asin} function, therefore it will be heavily referenced here even though it is not called. Assume all mentioned constants that are not expressed here, are taken from \texttt{\_\_ieee754\_asin}.
\begin{compactenum}
	\item All the following return values shall have no sign as they are positive.
	\item If x is \texttt{NaN}, return \texttt{NaN}.
	\item If |x| > 1, return \texttt{NaN}.
	\item If x is 1, return 0.
	\item If x is -1, return $\pi$, with $\pi$ being represented with the constant
	\begin{compactitem}
		\item $PI$ = \texttt{0x400921FB54442D18} (3.14159265358979311600).
	\end{compactitem}
	\item If |x| < $2^{-57}$, return $\frac{\pi}{2}$, represented with $pio2_{hi}$ + $pio2_{lo}$.
	\item The following identity provides the reason \texttt{\_\_ieee754\_acos} and \texttt{\_\_ieee754\_asin} are so closely related:
	\begin{align}
		cos^{-1}(x)                &= \frac{\pi}{2} - sin^{-1}(x) \label{formula_acos_0} \\
		\wedge \qquad cos^{-1}(-x) &= \frac{\pi}{2} + sin^{-1}(x) \label{formula_acos_1}
	\end{align}
	\item If |x| < 0.5:
	\begin{compactenum}
		\item Using the identity shown in formula \ref{formula_acos_1} and converting the approximation of asin shown in formula \ref{formula_asin_2} to approximate acos as:
		\begin{align}
			acos(x) &= \frac{\pi}{2} - (x + x \cdot x^2 \cdot R(x^2)) \label{formula_acos_2}
		\end{align}
		\item Return\footnote{Formula \ref{formula_acos_2} with some accuracy improvements} $pio2_{hi} - (x - (pio2_{lo} - x \cdot R(x^2)))$.
	\end{compactenum}
	\item For the following steps use formula \ref{formula_asin_4} to reduce the range.
	\item If x < -0.5:
	\begin{compactenum}
		\item With formula \ref{formula_acos_1} and \ref{formula_acos_2}, as well as applying the range reduction, the approximation of acos changes to:
		\begin{align}
			acos(x) &= \pi - 2 \cdot (s + s \cdot z \cdot R(z)) \nonumber \\
			        &= PI - 2 \cdot (s+s \cdot z \cdot R(z) - pio2_{lo}) \label{formula_acos_3}
		\end{align}
		with
		\begin{compactitem}
			\item $z = \frac{1-|x|}{2}$
			\item $s = \sqrt{z}$
		\end{compactitem}
		\item Return the result of the approximation.
	\end{compactenum}
	\item Otherwise (x > 0.5):
	\begin{compactenum}
		\item With formula \ref{formula_acos_0} and \ref{formula_acos_2}, as well as applying the range reduction, the approximation of acos changes to:
		\begin{align}
			acos(x) &= \frac{\pi}{2} - \Big(\frac{\pi}{2} - 2 \cdot \big(s + s \cdot z \cdot R(z)\big)\Big) \nonumber \\
			        &= 2 \cdot (s + s \cdot z \cdot R(z)) \nonumber \\
			        &= 2s + 2s \cdot z \cdot R(z) \nonumber \\
			        &= (2f + 2c) + (2s \cdot z \cdot R(z)) \nonumber \\
			        &= 2 \cdot (f + (c + s \cdot z \cdot R(z))) \label{formula_acos_4}
		\end{align}
		with
		\begin{compactitem}
			\item $f =$ \texttt{highword} of $s$
			\item $c = \frac{z-f^2}{s+f}$, which is the correction term for $f$ so that $f+c \sim \sqrt{z}$
		\end{compactitem}
		\item Return the result of the approximation.
	\end{compactenum}
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.75\textwidth]{./figure/Ieee_Acos_Flowchart.pdf}
	\caption{Flowchart \_\_ieee754\_acos}
	\label{fig:flowchart-ieee_acos}
\end{figure}