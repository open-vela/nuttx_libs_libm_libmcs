### \_\_ieee754\_powf {#sec:component-ieee-powf}

\begin{sffamily}\small
	\begin{tabularx}{\dimexpr\textwidth-1\tabcolsep}{p{2.3cm}X}
		Interface       & \texttt{float \_\_ieee754\_powf(float x, float y)} \\ 
		
		Type & Internal procedure   \\ 
		
		Files & \texttt{libm/math/ef\_pow.c}    \\ 
		
		Subordinates and Superiors & Float-equivalent to \texttt{\_\_ieee754\_pow}.    \\ 
		
		Purpose & Float-equivalent to \texttt{\_\_ieee754\_pow}.    \\ 
		
		References & \texttt{\_\_ieee754\_pow} \ref{sec:component-ieee-pow}, \texttt{powf} \ref{sec:component-powf}, \texttt{\_\_ieee754\_sqrtf} \ref{sec:component-ieee-sqrtf}, \texttt{nanf} \ref{sec:component-nanf}, \texttt{fabsf} \ref{sec:component-fabsf}, \texttt{scalbnf} \ref{sec:component-scalbnf}, \texttt{\_\_ieee754\_logf} \ref{sec:component-ieee-logf}, \texttt{\_\_ieee754\_expf} \ref{sec:component-ieee-expf}    \\ 
	\end{tabularx}
\end{sffamily}

#### Procedure Design

Float-equivalent to \texttt{\_\_ieee754\_pow}, but several limits and scales are different:
\begin{compactenum}
	\item Replace constants with:
	\begin{compactitem}
		\item $lg2$      = \texttt{0x3F317218} (6.9314718246 $\cdot 10^{-1}$, equals $ln(2)$)
		\item $lg2_h$    = \texttt{0x3F317200} (6.93145752 $\cdot 10^{-1}$)
		\item $lg2_l$    = \texttt{0x35BFBE8C} (1.42860654 $\cdot 10^{-6}$)
		\item $invln2$   = \texttt{0x3FB8AA3B} (1.4426950216 $\cdot 10^{-1}$, equals $\frac{1}{ln(2)}$)
		\item $invln2_h$ = \texttt{0x3FB8AA00} (1.4426879883 $\cdot 10^{-1}$)
		\item $invln2_l$ = \texttt{0x36ECA570} (7.0526075433 $\cdot 10^{-6}$)
		\item $cp$       = \texttt{0x3F76384F} (9.6179670095 $\cdot 10^{-1}$, equals $\frac{2}{3 \cdot ln(2)}$)
		\item $cp_h$     = \texttt{0x3F764000} (9.6191406250 $\cdot 10^{-1}$)
		\item $cp_l$     = \texttt{0xB8F623C6} (-1.1736857402 $\cdot 10^{-4}$)
		\item $dp_h$     = \texttt{0x3F15C000} (5.84960938 $\cdot 10^{-1}$) %TODO what is this?
		\item $dp_l$     = \texttt{0x35D1CFDC} (1.56322085 $\cdot 10^{-6}$)
		\item $L1$       = \texttt{0x3F19999A} (6.0000002384 $\cdot 10^{-1}$)
		\item $L2$       = \texttt{0x3EDB6DB7} (4.2857143283 $\cdot 10^{-1}$)
		\item $L3$       = \texttt{0x3EAAAAAB} (3.3333334327 $\cdot 10^{-1}$)
		\item $L4$       = \texttt{0x3E8BA305} (2.7272811532 $\cdot 10^{-1}$)
		\item $L5$       = \texttt{0x3E6C3255} (2.3066075146 $\cdot 10^{-1}$)
		\item $L6$       = \texttt{0x3E53f142} (2.0697501302 $\cdot 10^{-1}$)
		\item $P1$       = \texttt{0x3E2AAAAB} (1.6666667163 $\cdot 10^{-1}$)
		\item $P2$       = \texttt{0xBB360B61} (-2.7777778450 $\cdot 10^{-3}$)
		\item $P3$       = \texttt{0x388AB355} (6.6137559770 $\cdot 10^{-5}$)
		\item $P4$       = \texttt{0xB5DDEA0E} (-1.6533901999 $\cdot 10^{-6}$)
		\item $P5$       = \texttt{0x3331BB4C} (4.1381369442 $\cdot 10^{-8}$)
	\end{compactitem}
	\setcounter{enumi}{4}
	\begin{compactenum}
		\item If integer representation of y >= \texttt{0x4B800000} \footnote{This means that y can only be even, as the exponent is so high that only integral values that are multiples of 2 are possible.}, set yisint to 2.
		\item If y >= 1:
		\begin{compactenum}
			\item Let k be the binary exponent of y.
			\item Set j to the integer representation of y shifted right by (23 - k).
			\item If (j shifted left by (23 - k)) equals the integer representation of y, set yisint to (2 - last bit of j).
		\end{compactenum}
		\item If yisint has not yet been set, set it to 0.
	\end{compactenum}
	\item Omit this if clause and always use its contents.
	\setcounter{enumi}{11}
	\item If |y| > $2^{27}$:
	\begin{compactenum}
		\item Omit this step.
		\item If integer representation of |x| < \texttt{0x3F7FFFF8} \footnote{This means that (1-x) >= $2^{-20}$.}:
		\begin{compactenum}
			\item If y < 0, return infinity with sign of $sn$, with overflow.
			\item Return 0 with sign of $sn$, with underflow.
		\end{compactenum}
		\item If integer representation of |x| > \texttt{0x3F800007} \footnote{This means that (1-x) <= $-2^{-20}$.}:
		\begin{compactenum}
			\item If y > 0, return infinity with sign of $sn$, with overflow.
			\item Return 0 with sign of $sn$, with underflow.
		\end{compactenum}
		\setcounter{enumii}{5}
		\item Set $t1 = invln2_{h} \cdot t + (t \cdot invln2_{l} - w \cdot invln2)$, with the 12 lowest bits masked to 0.
	\end{compactenum}
	\item Otherwise:
	\begin{compactenum}
		\item If x is subnormal, scale x and ax by multiplying them with $2^{24}$.
		\item Change to footnote: \footnote{This shall be the real binary exponent: subnormals have an exponent < -128.}.
		\item Change to footnote: \footnote{Set the three highest bytes of ix to \texttt{0x3F80}.}.
		\item Change to footnote: \footnote{This is when (ix with exponent masked) < \texttt{0x1CC471}.}.
		\item Change to footnote: \footnote{This is when (ix with exponent masked) < \texttt{0x5DB3D7}.}.
		\setcounter{enumii}{6}
		\item Set ix = ax.
		\item Replace intermediates with:
		\begin{align}
			s_{h} &= \bigg(\frac{ax-bp}{ax+bp}\bigg) with\ the\ lowest\ 12\ bits\ set\ to\ all\ zeroes \nonumber
		\end{align}
		with
		\begin{compactitem}
			\item $t_{h} = ax + bp$ with the lowest 12 bits set to all zeroes.
		\end{compactitem}
		\item Replace intermediates with:
		\begin{align}
			t_{h}  &= 3 + s_{h}^2 + r \quad \wedge \quad lowest\ 12\ bits\ of\ t_{h}\ set\ to\ all\ zeroes \nonumber \\
			p_{h}  &= s_{h} \cdot t_{h} + (s_{l} \cdot t_{h} + t_{l} \cdot s) \quad \wedge \quad lowest\ 12\ bits\ of\ p_{h}\ set\ to\ all\ zeroes \nonumber \\
		\end{align}
	\end{compactenum}
	\setcounter{enumi}{13}
	\item Split y into $y1+y2$:
	\begin{compactitem}
		\item $y1 = y$ with lowest 12 bits set to all zeroes.
		\item $y2 = y - y1$.
	\end{compactitem}
	\setcounter{enumi}{15}
	\item If $y \cdot log_2(x) >= 128$:
	\begin{compactenum}
		\item If $y \cdot log_2(x) > 128$ return infinity with the sign of $s$, with overflow.
		\item If $p_l + ovt > y \cdot log_2(x) - p_h$, with $ovt$ = 4.2995665694 $\cdot 10^{-8}$ \footnote{Which equals $-(128-log_2(overflow+0.5\ ULP))$.}, return infinity with the sign of $s$, with overflow.
	\end{compactenum}
	\item If $y \cdot log_2(x) <= -150$:
	\begin{compactenum}
		\item If $y \cdot log_2(x) < -150$ return zero with the sign of $s$, with underflow.
		\item If $p_l <= y \cdot log_2(x) - p_h$ return zero with the sign of $s$, with underflow.
	\end{compactenum}
	\item \begin{compactenum}
		\setcounter{enumii}{1}
		\item \begin{compactenum}
			\item Set $n = $ integer representation of $(y \cdot log_2(x) + 0.5)$.
			\setcounter{enumiii}{2}
			\item Set $t$ to a new float with (exponent of n including sign) right shifted by k.
			\item Replace the exponent of n with 1, then right shift n by (23-k).
		\end{compactenum}
		\item Replace intermediates with:
		\begin{align}
			t                     &= p_l + p_h \quad \wedge \quad lowest\ 12\ bits\ of\ t\ set\ to\ all\ zeroes \nonumber
		\end{align}
	\end{compactenum}
\end{compactenum}
