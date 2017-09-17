/* L-R Flow
 * for each edge a->b whose capacity is [l, r]
 * 1) a->b with capacity l, cost -1 and with capacity r-l, cost 0
 * 2) new source -> b with capacity l, a -> new sink with capacity l, a->b with capacity r-l, sink->source with capacity INF
 */
