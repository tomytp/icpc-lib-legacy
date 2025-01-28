#import "template.typ": import-code

#let algo-section = [
  == Sparse Dijkstra
  #import-code("src/sparse_dijkstra.cpp")

  #colbreak()
  == Dense Dijkstra
  #import-code("src/dense_dijkstra.cpp")
]
