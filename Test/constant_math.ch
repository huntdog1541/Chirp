###
This tests constant math, this is actually a big part
of the optimisation process. Because the result is always the same
the compiler will actually do the math instead of generating the assembly code
to do the math.
###

entry()
{
  int: add = 123 + 321
  int: sub = 321 - 123
  int: div = 100 / 10
  int: mul = 321 * 123
}
