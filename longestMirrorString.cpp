string longestMirrorString(string strs) {
	//初始化哈希表，便于查询
	unordered_map<char, char> mir_table;
	mir_table['A'] = 'A';
	mir_table['E'] = '3';
	mir_table['3'] = 'E';
	mir_table['H'] = 'H';
	mir_table['I'] = 'I';
	mir_table['J'] = 'L';
	mir_table['L'] = 'J';
	mir_table['M'] = 'M';
	mir_table['O'] = 'O';
	mir_table['S'] = '2';
	mir_table['2'] = 'S';
	mir_table['T'] = 'T';
	mir_table['V'] = 'V';
	mir_table['U'] = 'U';
	mir_table['W'] = 'W';
	mir_table['X'] = 'X';
	mir_table['Y'] = 'Y';
	mir_table['Z'] = '5';
	mir_table['5'] = 'Z';
	mir_table['0'] = '0';
	mir_table['1'] = '1';
	mir_table['8'] = '8';
	
	int sz = strs.size();
	vector<string> ans;
	string tmp_odd, tmp_even;
	for (int i = 0; i < sz; i++)//假设子串以strs[i]为中心
	{
		if (mir_table.count(strs[i]) == 0) continue;

		//----------------------------------------
		//镜像串长度为奇数的情况：
		//----------------------------------------
		int l = i - 1, r = i + 1;
		if (i != 0 && i != sz - 1)
		{
			while (l >= 0 && r < sz)
			{
				if (mir_table[strs[l]] == strs[r])
				{
					l--; r++;
				}
				else break;
			}
		}
		tmp_odd = strs.substr(l + 1, r-l-1);

		//-----------------------------------------
		//镜像串长度为偶数的情况：
		//-----------------------------------------
		int l_e = i, r_e = i + 1;
		if (i != sz - 1)
		{
			while (l_e >= 0 && r_e < sz)
			{
				if (mir_table[strs[l_e]] == strs[r_e])
				{
					l_e--; r_e++;
				}
				else break;
			}
		}

		//-------------------------------------
		//进行奇偶比较，取最大值
		//-------------------------------------
		tmp_even = strs.substr(l_e + 1, r_e - l_e - 1);
		if (tmp_even.empty() && tmp_odd.empty()) continue;
		if (tmp_even.size() > tmp_odd.size())
			ans.push_back(tmp_even);
		else if (tmp_odd.size() > tmp_even.size()) ans.push_back(tmp_odd);
		else {
			ans.push_back(tmp_even);
			ans.push_back(tmp_odd);
		}
	}
	//---------------------------------------
	//find maxlen strings in vector ans
	//---------------------------------------
	if (ans.empty()) return "";
	vector<string> res;
	int max_len = ans[0].size();
	for (auto x : ans)
	{
		if (x.size() > max_len)
			max_len = x.size();
	}
	for (auto x : ans) {
		if (x.size() == max_len)
			res.push_back(x);
	}
	//------------------------------------------
	//把所有最长镜像子串放在一起，用、隔开
	//------------------------------------------
	string real_ans = "";
	for (auto x : res) {
		real_ans += x;
		real_ans += "、";
	}
	real_ans.pop_back();
	real_ans.pop_back();
	return real_ans;
}
//命名属实有点随意.jpg

