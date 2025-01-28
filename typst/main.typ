#import "template.typ": *
#import "algorithms.typ": *
#import "data-structures.typ": *
#import "math.typ": *
#import "ideias.typ" as ideais

#show: project.with(
  title: "Apostila Puc-Rio",
authors: ("Thomaz Miranda", "Miguel Batista", "João Arthur Marques"),
)

#outline(
  title: "Contents",
  indent: 15pt
)


#section-break
= Informações Importantes
#import-code("src/template.cpp")
#colbreak()
#complexity-table

#section-break
= Ideias Gerais
#ideais.gerais
= Ideias de DP
#ideais.dp


#section-break
= Data Structures
#ds-section


#section-break
= Algorithms 
#algo-section


#section-break
= Mathematics
#math-section