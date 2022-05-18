#include<iostream>
#include<map>
#include<string>
#include<stdio.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS // 为了优化Visual Studio对于scanf、freopen之类的函数报错
map<string, int> mp = { {"main", 2}, {"int", 3}, {"if", 4}, {"else", 5}, {"while", 6}, {"for", 7},
						{"map", 8}, {"string", 9}, {"double", 10}, {"float", 11}, {"char", 12}, {"const", 13}, 
						{"void", 14}, {"define", 15}, {"do", 16}, {"bool", 17}, {"return", 18}, {"include", 19}, 
						{"using", 20}, {"namespace", 21}, {"scanf", 22}, {"printf", 23}, {"cout", 24}, {"cin", 25}, 
						{"typedef", 26}, {"switch", 27}, {"std", 28}, {"long", 29}, {"+", 30}, {"-", 31}, {"*", 32},
						{"/", 33}, {"<", 34}, {"<=", 35}, {">", 36}, {">=", 37}, {"!=", 38}, {"==", 39}, {"||", 40}, 
						{"&&", 41}, {"=", 42}, {"!", 43}, {")", 44}, {",", 45}, {";", 46}, {"#", 47}, {"\"", 48}, 
						{"<<", 49}, {">>", 50}, {".", 51}, {"//", 52}, {"|", 53}, {"&", 54}, {"(", 55}, {"_", 56}, 
						{"\'", 57}, {"{", 58}, {"}", 59}, {"~", 60}, {":", 61}, {"[", 62}, {"]", 63} };
// 字符打表
int main() {
	char ch;
	string joint;
	bool sws = 'a' <= joint[0] && joint[0] <= 'z'; // 特判字符串的第一位，为了简化代码单独写出来
	bool swd = 'A' <= joint[0] && joint[0] <= 'Z';
	bool ss = '0' <= joint[0] && joint[0] <= '9';
	bool head = false, headf = false; // 头文件尖括号判断
	int xscnt = 0; // 小数点计数
	bool sps = false; // 特殊字符
	freopen("C:\\Users\\JiangShi\\Desktop\\yl\\10.in", "r", stdin); // 让scanf或cin从外部文件读入
	freopen("C:\\Users\\JiangShi\\Desktop\\yl\\10.out", "w", stdout);
	while (scanf("%c", &ch) != EOF) { // 按字符读入
		bool word = 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z'; // 判断是不是字母
		bool num = '0' <= ch && ch <= '9'; // 判断是不是数字
		bool jin16 = joint[0] == '0' && joint[1] == 'x' && (num || 'a' <= ch && ch <= 'f' || 'A' <= ch && ch <= 'F') && joint.size() >= 2;
		//cout << jin16 << endl;
		sws = 'a' <= joint[0] && joint[0] <= 'z'; // 重新判断
		swd = 'A' <= joint[0] && joint[0] <= 'Z';
		ss = '0' <= joint[0] && joint[0] <= '9';
		bool xs = ss && ch == '.'; //判断小数
		if (joint.size() > 0) {
			if (word && joint[joint.size() - 1] == '.' && ss && joint.size() > 0) {
				joint.pop_back();
				cout << "{ " << joint << "," << 1 << " }" << endl;
				joint.clear();
				joint.push_back('.');
				cout << "{ " << joint << "," << mp[joint] << " }" << endl;
				joint.clear();
			}
		}
		if (head == true && joint[0] == '<' && ch != '<' && ch != '=') { // 关键字左尖括号
			cout << "{ " << joint[0] << "," << 64 << " }" << endl;
			headf = true;
			joint.clear();
		}
		else if (head == true && headf == true && joint[0] == '>' && ch != '>' && ch != '=') { // 关键字右尖括号
			cout << "{ " << joint[0] << "," << 65 << " }" << endl;
			head = false;
			headf = false;
			joint.clear();
		}
		if (xs && joint.size() != 0) {
			joint.push_back(ch);
			xscnt++;
		}
		else if (word || num) { // 如果输入的是字母或者数字
			if (joint.size() != 0 && !sws && !ss && !swd) { // 如果joint中有残留并且不是字母或数字，输出并清空joint
				cout << "{ " << joint << "," << mp[joint] << " }" << endl;
				joint.clear();
			}
			joint.push_back(ch); // 将字母或数字压入joint
			if (ss && word && !(ch == 'x' && joint[0] == '0' || ch == 'e' && joint.size() == 2) && !jin16) { // 如果输入的是字母，并且可能目标输入是数字，检查输入是否合法，不合法报错
				cout << "Error: The Input \" " << joint << " \" Is Illegal" << endl;
				return 0;
			}
			if (ss && word && sps == false) sps = true; // 如果是特殊数字，sps标记为true
			else if (sps == true && word && !jin16) { //如果输入的是字母，并且是特殊数字，并且不是16进制，报错
				cout << "Error: The Input \" " << joint << " \" Is Illegal" << endl;
				return 0;
			}
		}
		sws = 'a' <= joint[0] && joint[0] <= 'z'; //由于上一步可能对字符串进行改变，重新判断
		swd = 'A' <= joint[0] && joint[0] <= 'Z';
		ss = '0' <= joint[0] && joint[0] <= '9';
		xs = ss && ch == '.';
		if (!word && !num && joint.size() != 0 && (sws || ss || swd) && !xs) { // 如果本次输入不是字母或者数字, 并且字符串不为空（代表一个单词已经输入完毕）
			if(joint == "true" || joint == "false") cout << "{ " << joint << "," << 1 << " }" << endl; // true,false是常数
			else if ((sws || swd) && mp.find(joint) != mp.end())  // 判断单词，并且map中有这个单词(这个单词是关键词)
				cout << "{ " << joint << "," << mp[joint] << " }" << endl;
			else if (ss && mp.find(joint) == mp.end()) { // 判断数字
				//cout << joint.size() << ' ' << xscnt << endl;
				if (!('0' <= joint[1] && joint[1] <= '9'|| joint[1] == 'x' && joint[0] == '0' || joint[1] == 'e' || joint[1] == '.') && joint.size() > 1 || xscnt > 1) { // 检查数字第二位是否合法，检查小数点是否只有一个（其他不合法情况上面已经检查完毕）
					cout << "Error: The Input \" " << joint << " \" Is Illegal" << endl;
					return 0;
				}
				else cout << "{ " << joint << "," << 1 << " }" << endl;
				sps = false; // 重置标记
				xscnt = 0;
			}
			else if (mp.find(joint) == mp.end()) // map中没有的单词肯定不是关键词
				cout << "{ " << joint << "," << "0" << " }" << endl;
			if (mp.find(joint) != mp.end()) head = true; // 如果是关键字，head标记为true
			else if (mp.find(joint) == mp.end() && headf == false) head = false;
			joint.clear(); // 清空字符串
		}
		if (!word && !num && !xs) { // 如果输入的是符号
			if (ch == ' ') { // 特判空格
				if (joint.size() != 0) {
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				continue;
			}
			else if (ch == '\n') { // 特判换行
				if (joint.size() != 0) {
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				continue;
			}
			else if (ch == '\t') { // 特判Tab空格
				if (joint.size() != 0) {
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				continue;
			}
			else if (joint.size() == 0 && ch != ' ') { // 由于可能会有组合字符，当字符串为空时，预存储一个字符
				joint.push_back(ch);
				if (mp.find(joint) == mp.end()) { // 如遇到map中没有的字符，报错
					cout << "Error: The Input \" " << joint << " \" Is NO Entry" << endl;
					joint.clear();
					continue;
				}
			}
			else if (ch != '=') { 
				if (ch == '<' && joint[0] == '<') { // 特判<<
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else if (ch == '>' && joint[0] == '>') { // 特判>>
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else if (ch == '/' && joint[0] == '/') { // 特判//
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else if (ch == '|' && joint[0] == '|') { // 特判||
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else if (ch == '&' && joint[0] == '&') { // 特判&&
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else { // 其他字符（不成对的）
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
			}
			else if (ch == '=') { // 特判类如<=、>=、==、!=等成对字符
				joint.push_back(ch);
				cout << "{ " << joint << "," << mp[joint] << " }" << endl;
				joint.clear();
			}
		}
	}
	sws = 'a' <= joint[0] && joint[0] <= 'z'; //处理当输入结束后的最后一个字符
	swd = 'A' <= joint[0] && joint[0] <= 'Z';
	ss = '0' <= joint[0] && joint[0] <= '9';
	if (joint.size() != 0) {
		if ((sws || swd) && mp.find(joint) != mp.end())  //如果是单词
			cout << "{ " << joint << "," << mp[joint] << " }" << endl;
		else if (ss && mp.find(joint) == mp.end()) // 如果是数字
			cout << "{ " << joint << "," << 1 << " }" << endl;
		else if (mp.find(joint) == mp.end()) // 其他map中没有的
			cout << "{ " << joint << "," << "0" << " }" << endl;
		else cout << "{ " << joint << "," << mp[joint] << " }" << endl; //其他
	}
	return 0;
}