# Intermediate code

The compiler uses an intermediate code representation. It isn't written in a string, but instead is represented in a vector of operation classes. These classes are represented with an enum of types.

## Types

This table represent the different token type

| type | meaning |
| --- | --- |
|declaration| declaration operation |
| assignment | variable assignment operation |
