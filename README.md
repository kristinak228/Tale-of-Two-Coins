# Tale-of-Two-Coins

Alice has two coins that she can flip at any time. The two coins have distinct probabilities of showing Heads/Tails. Bob observes the outcomes of Alice's coin tosses but unfortunately he does not which coin Alice is tossing at any time (since both coins look alike). We assume Alice knows which coin is which at all times.
But Bob knows Alice's tendencies in choosing the coins. For example, suppose the coins are called coins X and Y, respectively. If Alice tosses coin X in the current step, then in the next step she will toss X again with probability 0.75 and will toss coin Y otherwise (with probability 0.25). On the other hand, if she tosses coin Y, she will choose to toss coin X in the next step with probability 0.9 and toss coin Y again with probability only 0.1. This can be represented as a probability transition matrix:

0.75  0.9
0.25  0.1
where the first row and column is indexed by X and the second row/column is indexed by Y.
Bob also knows the "biases" of the two coins (although he can not tell them apart). For example, coin X shows Heads (H) or Tails (T) with equal probabilities 0.4 and 0.6, respectively. But coin Y shows Heads (H) with probability 0.8 and shows Tails (T) with probability 0.2. This can be represented as two sequences (or vectors):

0.4  0.8
Note: we need only record the probabilities of showing Heads for each coin.
Now, suppose Bob observed a sequence of tosses, say:

HTHTHHHHTHTTHTHTHHTHHHHTHHTHTHHTTTH
His goal is to determine how Alice had chosen her sequence of coins. Or rather find the sequence of choices made by Alice that is most likely. For example,
XYXYXYXXXYXYXYYYYXYXYXYXYXYXYYYYXXX
is a particular sequence of choices that could have been made by Alice (but this might not be the most likely sequence).
