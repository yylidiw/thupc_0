{{ self.title() }}

{{ s('description') }}

给定一个长为 $n$ 的序列 $a$。

有 $m$ 次询问，每次询问给定一个区间 $[l,r]$，求 $|{(a_i,a_j)：l\le i<j\le r \wedge a_i>a_j}|$。

$1\le n\le 10^5$，$1\le m\le 5\times 10^5$。

{{ s('input format') }}

{{ self.input_file() }}

第一行一个正整数 $n$。

第二行 $n$ 个正整数，其中第 $i$ 个数 $a_i$ 表示序列第 $i$ 个位置的值，保证$1\leq a_i \leq n$。

第三行一个正整数 $m$。

之后 $m$ 行，每行用两个空格隔开的正整数，分别表示 $l,r$，表示一次询问，保证 $1\leq l\le r \leq n$。

{{ s('output format') }}

{{ self.output_file() }}

输出 $m$ 行，第 $i$ 行输出一行一个整数，表示第 $i$ 次询问的答案。

{{ s('sample') }}

{{ self.sample_text() }}

