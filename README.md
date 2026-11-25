# MA429 Cybersecurity Assignments: Solutions



---

## p1: Password

Flipping a segment only changes the *difference array* at two spots, exactly `a` apart. So the task becomes: take the positions where the difference array is 1 (at most 20 of them), find the cheapest way to pair them up, where the cost of a pair is the shortest number of moves of length `a_i` to get from one to the other (BFS). Then a bitmask DP finds the minimum-cost perfect matching. If any pair is unreachable, the answer is -1.

## p2: Hidden bit (interactive, AND/OR)

We don't know whether the interactor uses `&` or `|`, so we pick `x` with exactly half its bits set and read the response `o`. Then we send `m0 = 0` and `m1 = D`, where `D` has bits both inside and outside `x`. From the reply `r`, we check which of `r` or `r ^ D` is a value `v` that could have produced `o`. Whichever fits is the real `b`. If both fit, we guess. This one is randomised, so a rare unlucky run is possible.

## p3: Tanya and the password

Treat every 2-character pair as a node and every 3-letter substring as an edge from its first pair to its second pair. The password exists exactly when this graph has an Euler path. Check in/out degrees, build the path with Hierholzer's algorithm (iterative, so no stack overflow), and make sure the path uses all `n` edges.

## p4: Network safety

For an edge `(u, v)`, the virus value `x` breaks it only if `c_u ^ c_v = x` and exactly one of `u`, `v` is infected. So group edges by `c_u ^ c_v`. For each group, the edges force their endpoints to be infected together, which is a DSU, and the number of valid subsets is `2^(components)`. Values of `x` that appear on no edge give `2^n` each. Reset the DSU only on the touched nodes so it stays fast.

## p5: Spy Syndrome 2

Put every word into a trie, lowercased and reversed, since the cipher reverses each word. Then do a DP from the end of the ciphered string: `can[i]` is true if the suffix starting at `i` can be split into words. Walking the trie from position `i` gives all words that match there. Rebuild the sentence by following the stored choices and print the original-cased words.

## p6: Sherlock and the encrypted data

Each operation moves one unit from one letter to its neighbour, so **word length and the sum of letter values never change**. And any word with the same length and sum is reachable. So the answer is the number of strings with that length and sum, minus 1 (the word itself). Precompute that count once with a DP over (length, sum).

## p7: Xenon's attack

The optimal labelling puts `0, 1, 2, ...` along one growing path. Let `dp[u][v]` be the best score when the path between `u` and `v` holds the smallest labels. Extending the path by one end adds `size(u side) * size(v side)`. So `dp[u][v] = sub[v][u] * sub[u][v] + max(dp[parent of v][u]..., dp[u][...])`. To get the subtree sizes and parents for every root in O(1), run a BFS from every node (O(n²) total, fine for n ≤ 3000). The answer is the max over all pairs.

## p8: Bipartite checking

Offline dynamic connectivity. Work out the time interval each edge exists, then add it to a segment tree over time. DFS the segment tree with a DSU that stores parity and supports rollback. If an edge closes an odd cycle, every query under that node is "NO". Otherwise carry on down and roll back on the way out.

## p9: Bubbleland contacts

Same offline trick as p8, but simpler. An edge added on day `d` stays valid until `k` day-changes have passed. Time is indexed by the type-2 queries only, so each edge covers a range of queries. Add each edge to a segment tree over that range, DFS with a rollback DSU (union by size), and each query's answer is the size of its component.

## p10: Hash fixed point (interactive)

`f^n(1)` always lands on a cycle, so call that node `x`. Use baby-step giant-step to find the cycle length `L` using about `2 * sqrt(n)` queries (well under 1000). Then choose `c = x` and `r = f^m(x)` with `m ≡ -x (mod L)`. Going around the cycle `x + m` steps from `x` gets back to `x`, so `f^c(r) = c`.
