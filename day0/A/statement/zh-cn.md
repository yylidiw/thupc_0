{{ self.title() }}

{{ s('description') }}

给定两个序列 $a_1,\dots,a_n$，$b_1,\dots,b_n$，一开始 $b_i=0$；

你需要进行 $m$ 次操作：

每次操作，给出 $l,r,L$，需要对于$k\in[l,r]$，将 $b_{L+k-l}$ 增加 $a_k$；

最后输出经过所有操作后的序列 $b_1,\dots,b_n$。

$0\le a_i\le 1000$；

$1\le n\le 10^5$；

$1\le m\le 10^6$。

{{ s('input format') }}

{{ self.input_file() }}

第一行一个整数 $n$；

第二行 $n$ 个整数 $a_1,\dots,a_n$；

第三行一个整数 $m$；

之后 $m$ 行每行三个整数 $l\;r\;L$，表示一个询问。

{{ s('output format') }}

{{ self.output_file() }}

输出 $m$ 行，表示操作后的 $b_1,\dots,b_m$。

{{ s('sample') }}

{{ self.sample_text() }}
