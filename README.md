# Confluently Persistent Array
Supports the following operations:
- Cut(A, i, j) extracts A[i:j] (Python-style indexing; extracted part is length j - i) and returns it; A[i:j] is now removed from A (so A is now A[:i] + A[j:]
- Paste(A, B, i): pastes B into A such that the first element of B is index i in in the result
- Create(x): return an array storing just x
- Get(A, i): return A[i]

Implemented with a functionally persistent treap; all operations above are expected log n time. Since this structure is pointer based, it's possible to store an array of length <i>l</i> in far less than <i>l</i> memory (in fact, it can take as little as O(log <i>l</i>) space).

I'm not quite sure whether functional persistence plays well with the randomization of a treap; if you ever get unlucky and happen to have a deep tree, you could keep applying operations to the same tree and get slow operations.
