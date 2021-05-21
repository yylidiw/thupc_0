#include <cstdio>
#include <cstring>
using namespace std;
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
struct Node {
	int val, sum;
	Node *old, *cur, *pre;
	//			|-> old
	// pre <- this -> cur
} t[10000008], *now, *brancharr[10000008], **branch = brancharr + 5000004;
int delta[10000008], sum[10000008], stk[10000008], tot, stktop, nowindex;
char s[10000008];
void addleft(int val){					// +1
	++tot;
	t[tot].val = t[tot].sum = val;
	t[tot].old = t[tot].cur = t;
	t[tot].pre = now;
	if (now -> cur != t) { 				// build a new branch
		now -> old = now -> cur;
		++stktop;
	}
	now -> cur = t + tot;
	branch[++nowindex] = now = t + tot;
	stk[stktop] = nowindex;
	return ;
}
void addright(){						// -1
	if (now -> pre == t) { 				// into negative
		++tot;
		t[tot].cur = now;
		t[tot].pre = t[tot].old = t;
		now -> pre = t + tot;
		now = t + tot;
	}
	else if (now -> pre -> old != t) {	// merge branches
		Node *old = now -> pre -> old, *cur = now;
		while (old -> cur != t && cur -> cur != t) {
			cur -> val += old -> val;
			cur -> sum += old -> sum;
			cur = cur -> cur;
			old = old -> cur;
		}
		cur -> val += old -> val;
		cur -> sum += old -> sum;
		if (cur -> cur == t) {			// current branch is shorter, use old branch
			cur -> cur = old -> cur;
			old -> cur -> pre = cur;
		}
		now -> pre -> cur = now;
		now = now -> pre;
		now -> old = t;
		if (stk[stktop] > stk[stktop - 1]) stk[stktop - 1] = stk[stktop];
		--stktop;
	}
	else now = now -> pre;				// no merge
	now -> sum = now -> val + now -> cur -> sum;
	branch[--nowindex] = now;
	return ;
}
int query(int pos){
	if (pos > stk[stktop]) return 0;
	return branch[pos] -> sum;
}
int main(){
	int n, i, sufmin, insertlim;
	long long ans = 0;
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (i = 1; i <= n; ++i) sum[i] = sum[i - 1] + (s[i] == '(' ? 1 : -1);
	sufmin = 0;
	insertlim = n - 1;
	for (i = n; i; --i) {
		if (sum[i] < 0) insertlim = i - 1;
		cmin(sufmin, sum[i]);
		delta[i] = sum[i] - sufmin;
	}
	tot = 1;
	t[tot].val = t[tot].sum = 1;
	t[tot].cur = t[tot].old = t[tot].pre = t;
	branch[0] = now = t + tot;
	stk[stktop = 0] = nowindex = 0;
	for (i = 1; i < n; ++i) {
		if (s[i] == '(') addleft(i <= insertlim ? 1 : 0);
		else {
			addright();
			ans += query(delta[i]);
			if (i <= insertlim) {
				++ (now -> val);
				++ (now -> sum);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}