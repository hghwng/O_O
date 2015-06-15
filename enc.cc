#include <iostream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
static const string kStub =
  "/* O_O Generator by Hugh Wang. http://github.com/hghwng/O_O */\n"
  "#include \"stdio.h\"\n"
  "#define o_O +\n"
  "#define O_o <<\n"
  "#define o (\n"
  "#define O )\n"
  "#define oo if\n"
  "#define oO int\n"
  "#define Oo char\n"
  "#define OO return\n"
  "#define _ 1\n"
  "#define __ o _ O_o _ O\n"
  "#define ___ o __ O_o _ O\n"
  "#define ooo oo (OoO == -_) OO 0; }\n"
  "#define o_o oO main o oO OoO, Oo **Ooo O {\n"
  "#define O_O(OOO, OOOO, OOOOO) oo o OOO == OoO O fputc o OOOO, stdout O , main o OOOOO , 0 O ;\n";

int encode_by_sum(size_t v, string &ret) {
  if (v == 0) {
    ret = "0";
    return 0;
  }
  int num_parts = 0;

  string s;
  while (v) {
    if (num_parts++) s += " o_O ";

    for (;;) {
      auto r = rand() % 3;
      switch (r) {
        case 0: // 1
          s += "_";
          v -= 1;
          goto exit;
        case 1: // 2
          if (v < 2) break;
          s += "__";
          v -= 2;
          goto exit;
        case 2: // 4
          if (v < 4) break;
          s += "___";
          v -= 4;
          goto exit;
      }
    }
exit:
      continue;
  }

  if (num_parts == 1) {
    ret = s;
  } else {
    ret = "o " + s + " O";
  }

  return num_parts;
}

void encode_part(size_t lhs_val, size_t rhs_val, string &part_str) {
  string lhs_str, rhs_str;
  int lhs_part = encode_by_sum(lhs_val, lhs_str);
  int rhs_part = encode_by_sum(rhs_val, rhs_str);

  if (lhs_part == 0) {
    // 0 << x -> nothing, ""
    part_str.clear();
  }

  if (rhs_part == 0) {
    // lhs << 0 -> "lhs"
    part_str = lhs_str;
  } else {
    // lhs << rhs -> "lhs << rhs"
    part_str = "o " + lhs_str + " O_o " + rhs_str + " O";
  }
}

string encode_num(size_t v) {
  // x = ((a + b + c + d) << (e + f)) + (x << y)
  size_t prev_bits = 0;
  size_t cur_bits;
  int part_num = 0;
  string s;

  for (auto t = v; t; prev_bits += cur_bits) {
    int r = rand();
    cur_bits = r % 3 + 1; // 1 to 4
    size_t mask = (1 << cur_bits) - 1;

    string part_str;
    encode_part(t & mask, prev_bits, part_str);
    if (part_num++) s += " o_O ";
    s += part_str;

    t >>= cur_bits;
  }

  return s;
}

string encode_string(string s) {
  string ret;
  size_t size = s.size();

  // random cond value
  vector<size_t> cond_vals;
  cond_vals.resize(size);
  cond_vals[0] = rand() % 10 + 2; // >= 2
  for (size_t i = 1; i < size; ++i) {
    cond_vals[i] = cond_vals[i - 1] + rand() % 10 + 1;
  }
  random_shuffle(cond_vals.begin(), cond_vals.end());
  cond_vals[0] = 1;

  // random output sequences
  vector<size_t> out_seqs;
  out_seqs.resize(size);
  for (size_t i = 0; i < size; ++i) {
    out_seqs[i] = i;
  }
  random_shuffle(out_seqs.begin(), out_seqs.end());

  for (size_t n = 0; n < size; ++n) {
    size_t i = out_seqs[n];
    string val_str = encode_num(s[i]);
    string cond_str = encode_num(cond_vals[i]);
    string goto_str;
    if (i == size - 1) {
      // last one, goto -1
      goto_str = "-_";
    } else {
      goto_str = encode_num(cond_vals[i + 1]);
    }

    ret += "O_O(" + cond_str + ", "
                 + val_str + ", "
                 + goto_str + ")\n";
  }
  return ret;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage:" << argv[0] << "string_to_encode" << endl;
    return -1;
  }

  srand(time(0));
  string src = argv[1];
  string dst = encode_string(src);
  cout << kStub;
  cout << "o_o" << endl;
  cout << dst;
  cout << "ooo" << endl;

  return 0;
}
