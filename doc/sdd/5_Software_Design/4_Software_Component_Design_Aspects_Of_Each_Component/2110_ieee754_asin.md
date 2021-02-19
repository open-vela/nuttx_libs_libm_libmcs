### \_\_ieee754\_asin {#sec:component-ieee-asin}

\begin{sffamily}\small
	\begin{center}
		\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
			Interface       & \texttt{double \_\_ieee754\_asin(double x)} \\ 
			
			Type & Internal Procedure    \\ 
			
			Files & \texttt{libm/math/e\_asin.c}    \\ 
			
			Subordinates and Superiors &
			\raisebox{-1\height}{\includegraphics[]{./figure/Declaration-__ieee754_asin.png}}    \\ 
			
			Purpose & 
			The internal \texttt{\_\_ieee754\_asin} function shall return the arcsine of x. \newline
			This component does not implement software requirements by itself.    \\ 
			
			References & \texttt{\_\_ieee754\_asinf} \ref{sec:component-ieee-asinf}, \texttt{asin} \ref{sec:component-asin}, \texttt{\_\_ieee754\_sqrt} \ref{sec:component-ieee-sqrt}, \texttt{fabs} \ref{sec:component-fabs}    \\ 
		\end{tabularx}
	\end{center}
\end{sffamily}

#### Procedure Design

\begin{compactenum}
	\item All the following return values shall have the same sign as the input value.
	\item If x is \texttt{NaN}, return \texttt{NaN}.
	\item If |x| > 1, return \texttt{NaN}.
	\item If |x| is 1, return x $\cdot \frac{\pi}{2}$.
	\item If |x| < $2^{-26}$, return x, with inexact except when x is 0.
	\item If |x| < 0.5:\footnote{This implementation of asin is a variation of the algorithm proposed by W. J. Cody, JR. and W. Waite in "Software Manual for the Elementary Functions"}
	\begin{compactenum}
		\item Use the identity
		\begin{align}
			sin^{-1}(x) &= x + \frac{1}{2} \frac{x^3}{3} + \frac{1 \cdot 3}{2 \cdot 4} \frac{x^5}{5} + ... \nonumber \\
			            &= \sum\limits_{i=0}^{\infty} \frac{\binom{2i}{i} \cdot x^{2i+1}}{4^i \cdot (2i+1)} \label{formula_asin_1}
		\end{align}
		to approximate asin as:
		\begin{align}
			asin(x) &= x + x \cdot x^2 \cdot R(x^2) \nonumber \\
			R(x^2)  &= \frac{asin(x)-x}{x^3} \label{formula_asin_2}
		\end{align}
		\item $R(x^2)$ can be rationally approximated with\footnote{Use Horner's method for implementation}:
		\begin{align}
			t &= x^2 \nonumber \\
			R(t) &\sim \frac{P0 \cdot t + P1 \cdot t^2 + P2 \cdot t^3 + P3 \cdot t^4 + P4 \cdot t^5 + P5 \cdot t^6}{1 + Q1 \cdot t + Q2 \cdot t^2 + Q3 \cdot t^3 + Q4 \cdot t^4} \label{formula_asin_3}
		\end{align}
		with
		\begin{compactitem}
			\item $P0$ = \texttt{0x3FC5555555555555} (1.66666666666666657415 $\cdot 10^{-1}$)
			\item $P1$ = \texttt{0xBFD4D61203EB6F7D} (-3.25565818622400915405 $\cdot 10^{-1}$)
			\item $P2$ = \texttt{0x3FC9C1550E884455} (2.01212532134862925881 $\cdot 10^{-1}$)
			\item $P3$ = \texttt{0xBFA48228B5688F3B} (-4.00555345006794114027 $\cdot 10^{-2}$)
			\item $P4$ = \texttt{0x3F49EFE07501B288} (7.91534994289814532176 $\cdot 10^{-4}$)
			\item $P5$ = \texttt{0x3F023DE10DFDF709} (3.47933107596021167570 $\cdot 10^{-5}$)
			\item $Q1$ = \texttt{0xC0033A271C8A2D4B} (-2.40339491173441421878)
			\item $Q2$ = \texttt{0x40002AE59C598AC8} (2.02094576023350569471)
			\item $Q3$ = \texttt{0xBFE6066C1B8D0159} (-6.88283971605453293030 $\cdot 10^{-1}$)
			\item $Q4$ = \texttt{0x3FB3B8C5B12E9282} (7.70381505559019352791 $\cdot 10^{-2}$)
		\end{compactitem}
		The error of this approximation is smaller than $2^{-58.75}$.
		\item Return $x + x \cdot R(t)$.
	\end{compactenum}
	\item Use the identity (set x = |x|, use \texttt{fabs} to calculate the absolute value\footnote{Remember that the final results still have the same sign as the initial x!})
	\begin{align}
		sin^{-1}(x) &= \frac{\pi}{2} - 2 \cdot sin^{-1}\bigg(\sqrt{\frac{1-x}{2}}\bigg) \label{formula_asin_4}
	\end{align}
	for range reduction purposes.
	\item Let $y = (1-x)$, $z = \frac{y}{2}$, $s = \sqrt{z}$, and split $\frac{\pi}{2}$ into $pio2_{hi}$ and $pio2_{lo}$ for more accuracy, then:
	\begin{compactenum}
		\item If |x| >= 0.975 \footnote{Use \texttt{highword} >= 0x3FEF3333.}, return
		\begin{align}
			asin(x) &= \frac{\pi}{2} - 2 \cdot (s + s \cdot z \cdot R(z)) \nonumber \\
			        &= pio2_{hi} - (2 \cdot (s + s \cdot z \cdot R(z)) - pio2_{lo}) \label{formula_asin_5}
		\end{align}
		with
		\begin{compactitem}
			\item $R(z)$ approximated as in formula \ref{formula_asin_3}
			\item Use \texttt{\_\_ieee754\_sqrt} to calculate the square root of $z$.
			\item $pio2_{hi}$ = \texttt{0x3FF921FB54442D18} (1.57079632679489655800)
			\item $pio2_{lo}$ = \texttt{0x3C91A62633145C07} (6.12323399573676603587 $\cdot 10^{-17}$)
		\end{compactitem}
		\item Otherwise, let $pio4_{hi} = \frac{pio2_{hi}}{2}$, $f =$ highword of $s$, $c = \sqrt{z} - f = \frac{z-f^2}{s+f}$, then return
		\begin{align}
			asin(x) &= \frac{\pi}{2} - 2 \cdot (s + s \cdot z \cdot R(z)) \nonumber \\
			        &= pio4_{hi} + (pio4_{hi} - 2s) - (2 \cdot s \cdot z \cdot R(z) - pio2_{lo}) \nonumber \\
			        &= pio4_{hi} - \Big(\big(2 \cdot s \cdot z \cdot R(z) - (pio2_{lo}+2c)\big) - (pio4_{hi} - 2f)\Big) \label{formula_asin_6}
		\end{align}
		with
		\begin{compactitem}
			\item $pio4_{hi}$ = \texttt{0x3FE921FB54442D18} (7.85398163397448278999 $\cdot 10^{-1}$)
		\end{compactitem}
	\end{compactenum}
\end{compactenum}

\begin{figure}[H]
	\centering
	\includegraphics[width=0.75\textwidth]{./figure/Ieee_Asin_Flowchart.pdf}
	\caption{Flowchart \_\_ieee754\_asin}
	\label{fig:flowchart-ieee_asin}
\end{figure}