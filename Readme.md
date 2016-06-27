Square and multiply
===================
This small software tries to solve exponential expressions modulo X in short time. (As of the form x^y (mod z)). I don't recommend using it in real world applications since it is open for side channel attacks.

Compile
-------
`gcc -Wall sam.c -o sam -std=c99`
The sam_pretty.c is ment for a more verbose output of the math behind it.
Please note that it uses the gcc builtin function for cnz (count leading zeros) and hence will be much faster with a processor with ABM instruction set extension enabled (for the LZCNT instruction).

Usage
-----
Given the above formula: `./sam x y z` 
