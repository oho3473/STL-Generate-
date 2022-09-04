#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<list>

//generate

using List = std::vector<std::string>;
using History = std::map<std::string, bool>;
using History_int = std::map<std::string, int>;
using result = std::list <std::list<std::string>>;
using History_result = std::map<std::string, result>;

bool CanGenerate(std::string target, const List& list)
{
	if (target == "")
		return true;

	for (auto e : list)
	{
		if (target.find(e) == 0)
		{
			const std::string subs = target.substr(e.length());

			if (CanGenerate(subs, list))
			{
				return true;
			}
		}
	}

	return false;
}

bool CanGenerate(std::string target, const List& list, History& h)
{
	if (h.count(target) == 1)
	{
		return h[target];
	}


	if (target == "")
		return true;

	for (auto e : list)
	{
		if(target.find(e) == 0)
		{
			const std::string subs = target.substr(e.length());

			if (CanGenerate(subs, list))
			{
				h[target] = true;
				return true;
			}
		}
	}

	h[target] = false;
	return h[target];
}

int HowManyGenrate(std::string target, List list)
{
	if (target == "")
	{
		return 1;
	}

	int count{ 0 };

	for (auto e : list)
	{
		if (target.find(e) == 0)
		{
			const std::string subs = target.substr(e.length());
			count += HowManyGenrate(subs, list);
		}
	}

	return count;
}

int HowManyGenerate(std::string target, List list, History_int& h)
{
	if(h.count(target) == 1)
	{
		return h[target];
	}

	if (target == "")
	{
		return 1;
	}

	int count{ 0 };

	for (auto e : list)
	{
		if (target.find(e) == 0)
		{
			const std::string subs = target.substr(e.length());
			count += HowManyGenerate(subs, list, h);
		}
	}

	h[target] = count;
	return count;
}

result FindGenerate(std::string target, const List& list)
{
	if(target == "")
	{
		return result{ {} };
	}

	result r;

	for (auto e : list)
	{
		if (target.find(e) == 0)
		{
			const std::string subs = target.substr(e.length());
			auto ret = FindGenerate(subs, list);

			for (auto e2 : ret)
			{
				e2.push_front(e);
				r.push_front(e2);
			}
		}
	}

	return r;
}

result FindGenerate(std::string target, const List& list, History_result h)
{
	if (h.count(target) == 1)
	{
		return h[target];
	}

	if (target == "")
	{
		return result{ {} };
	}

	result r;

	for (auto e : list)
	{
		if (target.find(e) == 0)
		{
			const std::string subs = target.substr(e.length());
			auto ret = FindGenerate(subs, list,h);

			for (auto e2 : ret)
			{
				e2.push_front(e);
				r.push_front(e2);
			}
		}
	}

	h[target] = r;
	return h[target];
}


void Print(const result& r)
{
	std::cout << "{" << std::endl;

	for (auto e1 : r)
	{
		std::cout << "\t{";
		for (auto e2 : e1)
		{
			std::cout << e2 << ", ";
		}
		std::cout << "}," << std::endl;
	}

	std::cout << "}" << std::endl;
}

bool CanGenerate2(std::string target, const List& list)
{
	std::vector<bool> table(target.length() + 1, false);
	table[0] = true;

	if (target == "")
		return true;

	for (int i = 0; i <= target.length(); ++i)
	{
		if (table[i] == true)
		{
			for (auto e : list)
			{
				if (target.substr(i,e.length()) == e)
				{
					if (i + e.length() <= target.length())
					{
						table[i + e.length()] = true;
					}
				}
			}
		}
	}
	
	return table[target.length()];
}

int HowManyGenerate2(std::string target, List list)
{
	std::vector<int> table(target.length() + 1, 0);
	table[0] = 1;

	for (int i = 0; i <= target.length(); ++i)
	{
		if (table[i] > 0)
		{
			for (auto e : list)
			{
				if (target.substr(i, e.length()) == e)
				{
					if (i + e.length() <= target.length())
					{
						table[i + e.length()] += table[i];
					}
				}
			}
		}
	}

	return table[target.length()];
}

result FindGenerate2(std::string target, const List& list)
{
	std::vector<std::list<std::list<std::string>>> table(target.length() + 1);
	table[0] = result{ {} };

	for (int i =0; i<=target.length(); ++i)
	{
		for (auto e : list)
		{
			if (target.substr(i, e.length()) == e)
			{
				if (i + e.length() <= target.length())
				{
					if (i + e.length() <= target.length())
					{
						for (auto e2 : table[i])
						{
							e2.push_back(e);
							table[i + e.length()].push_back(e2);
						}
					}
				}
			}
		}
	}

	return table[target.length()];
}

int main()
{
	History h;
	History_int hi;
	History_result hr;
	
	std::string target{"abcdef"};
	std::vector<std::string> list{"ab","abc","cd","def","abcd"};
	
	std::cout << CanGenerate(target, list, h) << std::endl;
	std::cout << HowManyGenerate(target, list, hi) << std::endl;
	
	Print(FindGenerate("hello", {"he","h","e", "llo","hell"},hr));
	
	std::string target2{"abcdef"};
	std::vector<std::string> list2{"ab","abc","cd","def","abcd","a","b","c","d"};
	
	std::cout << CanGenerate2(target2, list2) << std::endl;
	
	std::cout << HowManyGenerate2(target2, list2) << std::endl;
	
	Print(FindGenerate2(target2, list2));
}
