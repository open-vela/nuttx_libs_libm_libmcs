### \_\_kernel\_tan {#sec:component-kernel-tan}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double \_\_kernel\_tan(double x, double y, int k)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/k\_tan.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__kernel_tan.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_kernel\_tan} function shall return the tangent of $x$, which is represented by $x + y$. If the additional input variable $k$ is -1, the function shall return the negative inverse tangent of x. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_kernel\_tanf} \ref{sec:component-kernel-tanf}, \texttt{tan} \ref{sec:component-tan}, \texttt{fabs} \ref{sec:component-fabs}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item Use the following constants throughout the implementation of tan:
	\begin{compactitem}
		\item $PIo4$ = \texttt{0x3FE921FB54442D18} (7.8539816339744827900 $\cdot 10^{-1}$)
		\item $PIo4_{lo}$ = \texttt{0x3C81A62633145C07} (3.06161699786838301793 $\cdot 10^{-17}$)
	\end{compactitem}
	\item The identity $tan(-x) = -tan(x)$ can be used to reduce x to positive.
	\item The tangent of an argument can be calculated with:
	\begin{align}
		tan(x) &= x + \frac{1}{3}x^3 + \frac{2}{15}x^5 + \frac{17}{315}x^7 + ... \nonumber \\
			   &= \sum\limits_{i=1}^{\infty} \frac{(-1)^{i-1} \cdot 2^{2i} \cdot (2^{2i}-1) \cdot B_{2i} \cdot x^{2i-1}}{(2i)!} \label{formula_tan_1}
	\end{align}
	with $B_{n}$ being the $n$th Bernoulli number.
	\item If |x| < $0.67434$ (\footnote{This is when \texttt{highword} < \texttt{0x3FE59428}.}):
	\begin{compactenum}
		\item Use a polynomial approximation of formula \ref{formula_tan_1} to calculate tan\footnote{The error of this approximation is less than $2^{-59.2}$.}:
		\begin{align}
			tan(x) &\sim x \cdot (T0 \cdot x + T1 \cdot x^3 + T2 \cdot x^5 + ... + T12 \cdot x^{27}) \label{formula_tan_2}
		\end{align}
		with
		\begin{compactitem}
			\item $T0$ = \texttt{0x3FD5555555555563} (3.33333333333334091986 $\cdot 10^{-1}$)
			\item $T1$ = \texttt{0x3FC111111110FE7A} (1.33333333333201242699 $\cdot 10^{-1}$)
			\item $T2$ = \texttt{0x3FABA1BA1BB341FE} (5.39682539762260521377 $\cdot 10^{-2}$)
			\item $T3$ = \texttt{0x3F9664F48406D637} (2.18694882948595424599 $\cdot 10^{-2}$)
			\item $T4$ = \texttt{0x3F8226E3E96E8493} (8.86323982359930005737 $\cdot 10^{-3}$)
			\item $T5$ = \texttt{0x3F6D6D22C9560328} (3.59207910759131235356 $\cdot 10^{-3}$)
			\item $T6$ = \texttt{0x3F57DBC8FEE08315} (1.45620945432529025516 $\cdot 10^{-3}$)
			\item $T7$ = \texttt{0x3F4344D8F2F26501} (5.88041240820264096874 $\cdot 10^{-4}$)
			\item $T8$ = \texttt{0x3F3026F71A8D1068} (2.46463134818469906812 $\cdot 10^{-4}$)
			\item $T9$ = \texttt{0x3F147E88A03792A6} (7.81794442939557092300 $\cdot 10^{-5}$)
			\item $T10$ = \texttt{0x3F12B80F32F0A7E9} (7.14072491382608190305 $\cdot 10^{-5}$)
			\item $T11$ = \texttt{0xBEF375CBDB605373} (-1.85586374855275456654 $\cdot 10^{-5}$)
			\item $T12$ = \texttt{0x3EFB2A7074BF7AD4} (2.59073051863633712884 $\cdot 10^{-5}$)
		\end{compactitem}
		\item To increase the accuracy make use of the identity
		\begin{align}
			tan(x+y) &= tan(x) + tan'(x) \cdot y \nonumber \\
			         &\sim tan(x) + (1+ x^2) \cdot y  \label{formula_tan_3}
		\end{align}
		to change the approximation to:
		\begin{align}
			r(x)     &= x^3 \cdot (T1 + x \cdot (T2 + x \cdot (... + x \cdot (T11 + x \cdot T12)))) \label{formula_tan_4} \\
			R(x)     &= T0 \cdot x^3 + (x^2 \cdot (r(x)+y) +y) \label{formula_tan_5} \\
			tan(x+y) &= x + R(x) \label{formula_tan_6}
		\end{align}
		\item If k is 1, return the result of the approximation.
		\item Return $-\frac{1}{tan(x+y)}$, to not loose precision on this arithmetic operation, use this formula to create the return value:
		\begin{align}
			-\frac{1}{tan(x+y)} &= t + a \cdot (s + t \cdot v) \label{formula_tan_7}
		\end{align}
		with
		\begin{compactitem}
			\item $z = tan(x+y)$ with the \texttt{lowword} masked to zero.
			\item $v = R(x) - (z - x)$.
			\item $a = -\frac{1}{tan(x+y)}$.
			\item $t = a$ with the \texttt{lowword} masked to zero.
			\item $s = 1 + t \cdot z$.
		\end{compactitem}
	\end{compactenum}
	\item As the approximation in formula \ref{formula_tan_2} is only reliable for |x| < $0.67434$, make use of the identity
	\begin{align}
		tan(x) &= tan\bigg(\frac{\pi}{4}-f\bigg) \nonumber \\
		       &= \frac{1-tan(f)}{1+tan(f)} \nonumber \\
		       &= 1-2 \cdot \bigg(tan(f) - \frac{tan(f)^2}{1+tan(f)}\bigg) \label{formula_tan_8}
	\end{align}
	with
	\begin{compactitem}
		\item If x is negative, replace x with $x = -x$ and y with $y = -y$.
		\item $f = \frac{\pi}{4} - x$.
	\end{compactitem}
	to change the approximation of the tangent.
	\item Let $f = \frac{\pi}{4} - x = PIo4 - x + (PIo4_{lo} - y)$.
	\item Calculate tan(f) as in formula \ref{formula_tan_6}, with $f$ as x and $0$ as y.
	\item Use formula \ref{formula_tan_8} to calculate tan(x):
	\begin{align}
		tan(x) &= k - 2 \cdot \bigg(f-\Big(\frac{tan(f)^2}{tan(f)+k}-R(f)\Big)\bigg) \label{formula_tan_9}
	\end{align}
	\item Return tan(x) with the sign of the original x.
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=\textwidth]{./figure/Kernel_Tan_Flowchart.pdf}
	\caption{Flowchart \_\_kernel\_tan}
	\label{fig:flowchart-kernel_tan}
\end{figure}