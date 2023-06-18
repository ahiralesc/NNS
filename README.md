# Nearest neighbor search (NNS) : Locality Sensitive Hashing

[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fahchash%2Fhit-counter&count_bg=%2301167A&title_bg=%23000000&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)

In 1999 Gionis et. al $^1$ addressed the Nearest Neighbors Search (NNS) problem as a mapping problem in associative memory (hashing). Their strategy is referred to as Locality Sensitive Hashing (LSH). Although a formal proof establishing an equivalence between both classes of problems was not given,   

presented an equivalence between the Nearest Neighbors Search (NNS) and data mapping in associative memory, referred to Locality Sensitive Hashing (LSH), by designing a family $\mathbb{H}= \left \{ h : S \mapsto U  \right \}$ of functions $h$ such that given any two vectors $v, q \in S$ the following holds: 

1. if $v \in B \left ( q, r_1 \right )$ then $Pr_H \left [ h\left ( q \right ) = h\left ( v \right ) \right ] \geq p_1$
2. if $v \notin B \left ( q, r_2 \right )$ then $Pr_H \left [ h\left ( q \right ) = h\left ( v \right ) \right ] \leq p_2$

With $r_1, r_2, c \in \mathbb{R}^{+}, c \neq 0, r_2 = c r_1$, $p_1$ and $p_2$ probabilities with $p_2 < p_1$, and $B$ a balls of radius $r_1$ and $r_2$. Note $S \subset \mathbb{R}^{d}$. 

In simple terms, 1 and 2 state that if $v$ and $q$ are close in the Euclidean space, then they will fall in the same slot with high probability. On the other hand, if they are distance then the probability that they fall in the same slot is small. 

<p><small>
$^1$ Gionis, A., Indyk, P. and Motwani, R. <i>Similarity Search in High Dimensions via Hashing</i>. Proceedings of the 25th International Conference on Very Large Data Bases (San Francisco, CA, USA, 1999), 518–529. <b>1999</b>.
</small></p>




This repository aggregated many NLP (Natural Language Processing) constructs for:
- Text normalization.
- Text fingerprint generation.
- And similarity search.

Similarity search is based on works from:
- Datar, M., Immorlica, N., Indyk, P. and Mirrokni, V.S. 2004. Locality-sensitive hashing scheme based on p-stable distributions. Proceedings of the twentieth annual symposium on Computational geometry (Jun. 2004)
- Gionis, A., Indyk, P. and Motwani, R. 1999. Similarity Search in High Dimensions via Hashing. Proceedings of the 25th International Conference on Very Large Data Bases (San Francisco, CA, USA, 1999), 518–529.
