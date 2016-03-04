## Input format
~~~
<n> <m>
<c11> <c12> .. <c1k1>
<c21> <c22> .. <c2k2>
..
<cm1> <c22> .. <cmkm>
~~~

Where `n` is the number of vertices, `m` is the number of constraints, `ci` is
the `i`:th constraint, and `cij` is the `j`:th vertex in the `i`:th constraint.

Say we have 10 vertices, and it is forbidden to include all of `0`, `1` and `2`
and it is forbidden to include both of `8` and `9`. Then the input should look
as follows:

~~~
10 2
0 1 2
8 9
~~~
