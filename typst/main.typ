#import "utils.typ": *
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
#complexity-table

#section-break
= Ideias Gerais
#ideais.gerais
= Ideias de DP
#ideais.dp

#pagebreak()

#let structure = yaml.decode(read("structure.yaml"))
#process-structure(structure)