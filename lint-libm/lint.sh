#!/bin/bash

# Point to your pc-lint executeable
LINT=./lint-nt.exe

find ../libm/common -name  "*.c" | grep -v "fenv.c" > result/files.lnt
find ../libm/complexd -name  "*.c" >> result/files.lnt
find ../libm/complexf -name  "*.c" >> result/files.lnt
find ../libm/mathd -name  "*.c" >> result/files.lnt
find ../libm/mathf -name  "*.c" >> result/files.lnt

${LINT} std.lnt result/files.lnt | tr "\\\\" "/" | tr -d '\r' | sed 's/ \[MISRA/$ \[MISRA/' | tee result/lint.txt | grep -e "--- Module"
cat result/lint.txt | sort | uniq | grep mandatory > result/mandatory.txt
cat result/lint.txt | sort | uniq | grep required > result/required.txt
cat result/lint.txt | sort | uniq | grep advisory > result/advisory.txt
cat result/lint.txt | sort | uniq | grep -v 'required\|mandatory\|advisory' > result/other.txt

wc -l result/mandatory.txt result/required.txt result/advisory.txt result/other.txt
