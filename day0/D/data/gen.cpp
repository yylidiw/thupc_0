#include <cstdio>
#include <cstdlib>
#include <random>
#include <cassert>
#include <algorithm>
using namespace std;
namespace Generator {
	#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
	#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
	#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
	#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
	char s[10000008], command[180], prefix[36], inname[36];
	random_device rd;
	mt19937 randgen(rd());
	FILE *log;
	void output(int index, int isdown = 0) {
		int i, sum;
		for (i = 1, sum = 0; s[i]; ++i) sum += (s[i] == '(' ? 1 : -1);
		assert(sum == 0);
		if (isdown) sprintf(prefix, "../down/%d", index);
		else sprintf(prefix, "%d", index);
		fprintf(log, "Output to %s.in:\n", prefix);
		sprintf(inname, "%s.in", prefix);
		FILE *p = fopen(inname, "w");
		fprintf(p, "%s\n", s + 1);
		fclose(p);
		fprintf(log, "Output Done.\nRun std to get %s.ans.\n", prefix);
		fclose(log);
		sprintf(command, "(time ../AnalogueHeart/fla < %s.in > %s.ans) 2>> gen.log", prefix, prefix);
		system(command);
		log = fopen("gen.log", "a");
		fprintf(log, "Answer done.\n");
		return ;
	}
	int randint(int lbd, int rbd, int interval = 1) {
		uniform_int_distribution<> gen(0, (rbd - lbd) / interval);
		return lbd + gen(randgen) * interval;
	}
	void genseq_shuffle(int nmin = 2, int nmax = 10000000, int shuffrom = 0) {
		assert(nmin % 2 == 0 && nmax % 2 == 0 && nmin >= 2 && nmax <= 10000000 && nmin <= nmax);
		int n = randint(nmin, nmax, 2), i;
		for (i = 1; i <= n / 2; ++i) s[i] = '(';
		for (; i <= n; ++i) s[i] = ')';
		if (shuffrom <= n) shuffle(s + 1 + shuffrom, s + n + 1, randgen);
		s[n + 1] = 0;
		return ;
	}
	void fillup(int first, int last, int lim = 10000000) {
		assert(first % 2 == last % 2);
		int i, len;
		while (first < last) {
			len = randint(1, dmin((last - first) / 2, lim));
			for (i = 1; i <= len; ++i) s[first++] = '(';
			for (i = 1; i <= len; ++i) s[first++] = ')';
		}
		return ;
	}
	void filldown(int first, int last, int lim = 10000000) {
		assert(first % 2 == last % 2);
		int i, len;
		while (first < last) {
			len = randint(1, dmin((last - first) / 2, lim));
			for (i = 1; i <= len; ++i) s[first++] = ')';
			for (i = 1; i <= len; ++i) s[first++] = '(';
		}
		return ;
	}
	void genseq_table(int nmin = 2, int nmax = 10000000, int slope_min = 0, int slope_max = 10000000, int hill_lim = 10000000) {
		assert(nmin % 2 == 0 && nmax % 2 == 0 && nmin >= 2 && nmax <= 10000000 && nmin <= nmax);
		int n = randint(nmin, nmax, 2), i, slope;
		slope = randint(dmin(slope_min, n / 2), dmin(slope_max, n / 2));
		for (i = 1; i <= slope; ++i) {
			s[i] = '(';
			s[n - i + 1] = ')';
		}
		assert(hill_lim);
		if (hill_lim > 0) fillup(slope + 1, n - slope + 1, hill_lim);
		else filldown(slope + 1, n - slope + 1, -hill_lim);
		s[n + 1] = 0;
		return ;
	}
	void genseq_elbat(int nmin = 2, int nmax = 10000000, int slope_min = 0, int slope_max = 10000000, int hill_lim = 10000000) {
		assert(nmin % 2 == 0 && nmax % 2 == 0 && nmin >= 2 && nmax <= 10000000 && nmin <= nmax);
		int n = randint(nmin, nmax, 2), i, slope;
		slope = randint(dmin(slope_min, n / 2), dmin(slope_max, n / 2));
		for (i = 1; i <= slope; ++i) {
			s[i] = ')';
			s[n - i + 1] = '(';
		}
		assert(hill_lim);
		if (hill_lim > 0) fillup(slope + 1, n - slope + 1, hill_lim);
		else filldown(slope + 1, n - slope + 1, -hill_lim);
		s[n + 1] = 0;
		return ;
	}
	void genseq_valley(int nmin = 2, int nmax = 10000000, int slope_min = 0, int slope_max = 10000000) {
		assert(nmin % 2 == 0 && nmax % 2 == 0 && nmin >= 2 && nmax <= 10000000 && nmin <= nmax);
		int n = randint(nmin, nmax, 2), i, out_slope;
		out_slope = randint(dmin(slope_min, n / 2), dmin(slope_max, n / 2));
		for (i = 1; i <= out_slope; ++i) {
			s[i] = '(';
			s[n - i + 1] = ')';
		}
		for (i = out_slope + 1; i <= n / 2; ++i) {
			s[i] = ')';
			s[n - i + 1] = '(';
		}
		s[n + 1] = 0;
		return ;
	}
	void genseq_peak(int nmin, int nmax, int slope_min, int slope_max, int plain_min, int plain_max, int hills_lim) {
		assert(nmin % 2 == 0 && nmax % 2 == 0 && nmin >= 2 && nmax <= 10000000 && nmin <= nmax);
		int n = randint(nmin, nmax, 2), i, out_slope, plain, lbd, rbd;
		out_slope = randint(dmin(slope_min, n / 2), dmin(slope_max, n / 2));
		plain = randint(dmin(plain_min, out_slope), dmin(plain_max, out_slope));
		for (i = 1; i <= out_slope; ++i) s[i] = '(';
		lbd = out_slope, rbd = n + 1;
		if (plain >= 0) {
			for (i = 1; i <= plain; ++i) s[--rbd] = ')';
			for (; i <= out_slope; ++i) s[++lbd] = ')';
		}
		else {
			for (i = 1; i <= out_slope; ++i) s[++lbd] = ')';
			for (i = -1; i >= plain; --i) {
				s[++lbd] = ')';
				s[--rbd] = '(';
			}
			assert(lbd < rbd);
		}
		fillup(lbd + 1, rbd, hills_lim);
		s[n + 1] = 0;
		return ;
	}
	void main() {
		int caseid;
		log = fopen("gen.log", "a");
		fprintf(log, "Generating test data:\n");
		for (caseid = 31; caseid <= 34; ++caseid) {
			fprintf(log, "Generating testcase #%d:\n", caseid);
			switch (caseid) {
				case 1:
				case 2:
					genseq_shuffle(9999990, 10000000, 0); break;
				case 3:
				case 4:
					genseq_shuffle(9999990, 10000000, 1000); break;
				case 5:
				case 6:
					genseq_table(9999990, 10000000, 1000, 3000, 10); break;
				case 7:
				case 8:
					genseq_table(9999990, 10000000, 1000, 3000, 1000000); break;
				case 9:
				case 10:
					genseq_table(9999990, 10000000, 1000, 3000, -10); break;
				case 11:
				case 12:
					genseq_table(9999990, 10000000, 1000, 3000, -12000); break;
				case 13:
				case 14:
					genseq_elbat(9999990, 10000000, 1000, 3000, 10); break;
				case 15:
				case 16:
					genseq_elbat(9999990, 10000000, 1000, 3000, -10); break;
				case 17:
				case 18:
					genseq_elbat(9999990, 10000000, 1000, 3000, 12000); break;
				case 19:
				case 20:
					genseq_elbat(9999990, 10000000, 1000, 3000, -12000); break;
				case 21:
				case 22:
					genseq_table(9999990, 10000000, 0, 0, 8); break;
				case 23:
				case 24:
					genseq_table(9999990, 10000000, 0, 0, -8); break;
				case 25:
					genseq_table(9999990, 10000000, 10000000, 10000000); break;
				case 26:
					genseq_elbat(9999990, 10000000, 10000000, 10000000); break;
				case 27:
				case 28:
					genseq_valley(9999990, 10000000, 100000, 200000); break;
				case 29:
				case 30:
					genseq_valley(9999990, 10000000, 300000, 400000); break;
				case 31:
				case 32:
					genseq_peak(9999990, 10000000, 1000, 3000, -3000, -1000, 10); break;
				case 33:
				case 34:
					genseq_peak(9999990, 10000000, 50000, 100000, -300, -100, 10); break;
				case 35:
				case 36:
					genseq_peak(9999990, 10000000, 50000, 100000, 100, 300, 10); break;
					
				default: fprintf(log, "[Warning] Skipping testcase #%d.\n", caseid); continue;
			}
			output(caseid);
		}
		fprintf(log, "Test data 31 - 34 re-generated.\n");
		fclose(log);
		return ;
		fprintf(log, "Test data done.\nGenerating down:\n");
		for (caseid = 1; caseid <= 3; ++caseid) {
			fprintf(log, "Generating down case #%d:\n", caseid);
			switch (caseid) {
				case 1: sprintf(s + 1, "()()()"); break;
				case 2: sprintf(s + 1, "(()))()()("); break;
				case 3: genseq_shuffle(210222, 210222, 2021); break;
				default: fprintf(log, "[Error] No config for down case #%d.\n", caseid);
			}
			output(caseid, 1);
		}
		fclose(log);
		return ;
	}
	#undef cmax
	#undef cmin
	#undef dmax
	#undef dmin
}
int main(){
	Generator::main();
	return 0;
}