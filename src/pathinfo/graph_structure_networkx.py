import matplotlib.pyplot as plt
import networkx as nx
G=nx.DiGraph()
G.add_node("a")
G.add_node("b")
G.add_node("c")
G.add_node("d")
G.add_node("e")
G.add_node("f")
G.add_node("g")
G.add_node("h")
G.add_node("i")
G.add_node("j")
G.add_node("k")
G.add_node("l")
G.add_node("m")
G.add_node("n")
G.add_node("o")
G.add_node("p")
G.add_node("q")
G.add_node("r")
G.add_node("s")
G.add_node("t")
G.add_node("u")
G.add_node("v")
G.add_node("w")
G.add_node("x")
G.add_node("y")
G.add_node("z")
G.add_edge("a", "z")
G.add_edge("a", "y")
G.add_edge("a", "v")
G.add_edge("a", "r")
G.add_edge("a", "q")
G.add_edge("a", "m")
G.add_edge("a", "k")
G.add_edge("a", "g")
G.add_edge("a", "f")
G.add_edge("a", "e")
G.add_edge("b", "z")
G.add_edge("b", "y")
G.add_edge("b", "x")
G.add_edge("b", "s")
G.add_edge("b", "r")
G.add_edge("b", "q")
G.add_edge("b", "o")
G.add_edge("b", "n")
G.add_edge("b", "l")
G.add_edge("b", "e")
G.add_edge("c", "y")
G.add_edge("c", "x")
G.add_edge("c", "w")
G.add_edge("c", "s")
G.add_edge("c", "l")
G.add_edge("c", "k")
G.add_edge("c", "j")
G.add_edge("c", "i")
G.add_edge("c", "g")
G.add_edge("c", "f")
G.add_edge("d", "z")
G.add_edge("d", "x")
G.add_edge("d", "u")
G.add_edge("d", "t")
G.add_edge("d", "q")
G.add_edge("d", "m")
G.add_edge("d", "l")
G.add_edge("d", "i")
G.add_edge("d", "g")
G.add_edge("d", "f")
G.add_edge("e", "z")
G.add_edge("e", "u")
G.add_edge("e", "t")
G.add_edge("e", "o")
G.add_edge("e", "l")
G.add_edge("e", "k")
G.add_edge("e", "j")
G.add_edge("e", "g")
G.add_edge("e", "b")
G.add_edge("e", "a")
G.add_edge("f", "y")
G.add_edge("f", "w")
G.add_edge("f", "v")
G.add_edge("f", "u")
G.add_edge("f", "t")
G.add_edge("f", "m")
G.add_edge("f", "i")
G.add_edge("f", "d")
G.add_edge("f", "c")
G.add_edge("f", "a")
G.add_edge("g", "z")
G.add_edge("g", "x")
G.add_edge("g", "v")
G.add_edge("g", "q")
G.add_edge("g", "i")
G.add_edge("g", "h")
G.add_edge("g", "e")
G.add_edge("g", "d")
G.add_edge("g", "c")
G.add_edge("g", "a")
G.add_edge("h", "v")
G.add_edge("h", "u")
G.add_edge("h", "s")
G.add_edge("h", "r")
G.add_edge("h", "q")
G.add_edge("h", "n")
G.add_edge("h", "m")
G.add_edge("h", "l")
G.add_edge("h", "k")
G.add_edge("h", "g")
G.add_edge("i", "u")
G.add_edge("i", "s")
G.add_edge("i", "p")
G.add_edge("i", "n")
G.add_edge("i", "l")
G.add_edge("i", "k")
G.add_edge("i", "g")
G.add_edge("i", "f")
G.add_edge("i", "d")
G.add_edge("i", "c")
G.add_edge("j", "y")
G.add_edge("j", "w")
G.add_edge("j", "v")
G.add_edge("j", "r")
G.add_edge("j", "p")
G.add_edge("j", "o")
G.add_edge("j", "m")
G.add_edge("j", "k")
G.add_edge("j", "e")
G.add_edge("j", "c")
G.add_edge("k", "w")
G.add_edge("k", "u")
G.add_edge("k", "t")
G.add_edge("k", "l")
G.add_edge("k", "j")
G.add_edge("k", "i")
G.add_edge("k", "h")
G.add_edge("k", "e")
G.add_edge("k", "c")
G.add_edge("k", "a")
G.add_edge("l", "y")
G.add_edge("l", "x")
G.add_edge("l", "o")
G.add_edge("l", "k")
G.add_edge("l", "i")
G.add_edge("l", "h")
G.add_edge("l", "e")
G.add_edge("l", "d")
G.add_edge("l", "c")
G.add_edge("l", "b")
G.add_edge("m", "z")
G.add_edge("m", "y")
G.add_edge("m", "x")
G.add_edge("m", "v")
G.add_edge("m", "o")
G.add_edge("m", "j")
G.add_edge("m", "h")
G.add_edge("m", "f")
G.add_edge("m", "d")
G.add_edge("m", "a")
G.add_edge("n", "y")
G.add_edge("n", "x")
G.add_edge("n", "v")
G.add_edge("n", "t")
G.add_edge("n", "r")
G.add_edge("n", "q")
G.add_edge("n", "p")
G.add_edge("n", "i")
G.add_edge("n", "h")
G.add_edge("n", "b")
G.add_edge("o", "z")
G.add_edge("o", "x")
G.add_edge("o", "w")
G.add_edge("o", "v")
G.add_edge("o", "q")
G.add_edge("o", "m")
G.add_edge("o", "l")
G.add_edge("o", "j")
G.add_edge("o", "e")
G.add_edge("o", "b")
G.add_edge("p", "y")
G.add_edge("p", "w")
G.add_edge("p", "v")
G.add_edge("p", "u")
G.add_edge("p", "t")
G.add_edge("p", "s")
G.add_edge("p", "r")
G.add_edge("p", "n")
G.add_edge("p", "j")
G.add_edge("p", "i")
G.add_edge("q", "x")
G.add_edge("q", "t")
G.add_edge("q", "s")
G.add_edge("q", "o")
G.add_edge("q", "n")
G.add_edge("q", "h")
G.add_edge("q", "g")
G.add_edge("q", "d")
G.add_edge("q", "b")
G.add_edge("q", "a")
G.add_edge("r", "x")
G.add_edge("r", "w")
G.add_edge("r", "v")
G.add_edge("r", "s")
G.add_edge("r", "p")
G.add_edge("r", "n")
G.add_edge("r", "j")
G.add_edge("r", "h")
G.add_edge("r", "b")
G.add_edge("r", "a")
G.add_edge("s", "z")
G.add_edge("s", "y")
G.add_edge("s", "u")
G.add_edge("s", "r")
G.add_edge("s", "q")
G.add_edge("s", "p")
G.add_edge("s", "i")
G.add_edge("s", "h")
G.add_edge("s", "c")
G.add_edge("s", "b")
G.add_edge("t", "z")
G.add_edge("t", "w")
G.add_edge("t", "u")
G.add_edge("t", "q")
G.add_edge("t", "p")
G.add_edge("t", "n")
G.add_edge("t", "k")
G.add_edge("t", "f")
G.add_edge("t", "e")
G.add_edge("t", "d")
G.add_edge("u", "w")
G.add_edge("u", "t")
G.add_edge("u", "s")
G.add_edge("u", "p")
G.add_edge("u", "k")
G.add_edge("u", "i")
G.add_edge("u", "h")
G.add_edge("u", "f")
G.add_edge("u", "e")
G.add_edge("u", "d")
G.add_edge("v", "r")
G.add_edge("v", "p")
G.add_edge("v", "o")
G.add_edge("v", "n")
G.add_edge("v", "m")
G.add_edge("v", "j")
G.add_edge("v", "h")
G.add_edge("v", "g")
G.add_edge("v", "f")
G.add_edge("v", "a")
G.add_edge("w", "z")
G.add_edge("w", "u")
G.add_edge("w", "t")
G.add_edge("w", "r")
G.add_edge("w", "p")
G.add_edge("w", "o")
G.add_edge("w", "k")
G.add_edge("w", "j")
G.add_edge("w", "f")
G.add_edge("w", "c")
G.add_edge("x", "r")
G.add_edge("x", "q")
G.add_edge("x", "o")
G.add_edge("x", "n")
G.add_edge("x", "m")
G.add_edge("x", "l")
G.add_edge("x", "g")
G.add_edge("x", "d")
G.add_edge("x", "c")
G.add_edge("x", "b")
G.add_edge("y", "s")
G.add_edge("y", "p")
G.add_edge("y", "n")
G.add_edge("y", "m")
G.add_edge("y", "l")
G.add_edge("y", "j")
G.add_edge("y", "f")
G.add_edge("y", "c")
G.add_edge("y", "b")
G.add_edge("y", "a")
G.add_edge("z", "w")
G.add_edge("z", "t")
G.add_edge("z", "s")
G.add_edge("z", "o")
G.add_edge("z", "m")
G.add_edge("z", "g")
G.add_edge("z", "e")
G.add_edge("z", "d")
G.add_edge("z", "b")
G.add_edge("z", "a")
layout = nx.circular_layout(G)
nx.draw_networkx(G, pos=layout, with_labels=True)
plt.show()