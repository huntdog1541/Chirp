# Parsing

This uses a Recursive descent parser, creating a tree from the top. It will analyze the tokens provided by the lexer until it runs out of those. When finished it will procced to do semantic analysis.

## Tree

The parser will generate a parse tree, each statements is a node with the type of the statement as a child. Below is an example of the resulting parse tree from this code.

```chirp
int: a
```

![This image was generated with mshang's syntax tree generator](https://i.ibb.co/2sGdLFW/download-1.png)