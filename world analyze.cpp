#include<iostream>
#include<map>
#include<string>
#include<stdio.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS // Ϊ���Ż�Visual Studio����scanf��freopen֮��ĺ�������
map<string, int> mp = { {"main", 2}, {"int", 3}, {"if", 4}, {"else", 5}, {"while", 6}, {"for", 7},
						{"map", 8}, {"string", 9}, {"double", 10}, {"float", 11}, {"char", 12}, {"const", 13}, 
						{"void", 14}, {"define", 15}, {"do", 16}, {"bool", 17}, {"return", 18}, {"include", 19}, 
						{"using", 20}, {"namespace", 21}, {"scanf", 22}, {"printf", 23}, {"cout", 24}, {"cin", 25}, 
						{"typedef", 26}, {"switch", 27}, {"std", 28}, {"long", 29}, {"+", 30}, {"-", 31}, {"*", 32},
						{"/", 33}, {"<", 34}, {"<=", 35}, {">", 36}, {">=", 37}, {"!=", 38}, {"==", 39}, {"||", 40}, 
						{"&&", 41}, {"=", 42}, {"!", 43}, {")", 44}, {",", 45}, {";", 46}, {"#", 47}, {"\"", 48}, 
						{"<<", 49}, {">>", 50}, {".", 51}, {"//", 52}, {"|", 53}, {"&", 54}, {"(", 55}, {"_", 56}, 
						{"\'", 57}, {"{", 58}, {"}", 59}, {"~", 60}, {":", 61}, {"[", 62}, {"]", 63} };
// �ַ����
int main() {
	char ch;
	string joint;
	bool sws = 'a' <= joint[0] && joint[0] <= 'z'; // �����ַ����ĵ�һλ��Ϊ�˼򻯴��뵥��д����
	bool swd = 'A' <= joint[0] && joint[0] <= 'Z';
	bool ss = '0' <= joint[0] && joint[0] <= '9';
	bool head = false, headf = false; // ͷ�ļ��������ж�
	int xscnt = 0; // С�������
	bool sps = false; // �����ַ�
	freopen("C:\\Users\\JiangShi\\Desktop\\yl\\10.in", "r", stdin); // ��scanf��cin���ⲿ�ļ�����
	freopen("C:\\Users\\JiangShi\\Desktop\\yl\\10.out", "w", stdout);
	while (scanf("%c", &ch) != EOF) { // ���ַ�����
		bool word = 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z'; // �ж��ǲ�����ĸ
		bool num = '0' <= ch && ch <= '9'; // �ж��ǲ�������
		bool jin16 = joint[0] == '0' && joint[1] == 'x' && (num || 'a' <= ch && ch <= 'f' || 'A' <= ch && ch <= 'F') && joint.size() >= 2;
		//cout << jin16 << endl;
		sws = 'a' <= joint[0] && joint[0] <= 'z'; // �����ж�
		swd = 'A' <= joint[0] && joint[0] <= 'Z';
		ss = '0' <= joint[0] && joint[0] <= '9';
		bool xs = ss && ch == '.'; //�ж�С��
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
		if (head == true && joint[0] == '<' && ch != '<' && ch != '=') { // �ؼ����������
			cout << "{ " << joint[0] << "," << 64 << " }" << endl;
			headf = true;
			joint.clear();
		}
		else if (head == true && headf == true && joint[0] == '>' && ch != '>' && ch != '=') { // �ؼ����Ҽ�����
			cout << "{ " << joint[0] << "," << 65 << " }" << endl;
			head = false;
			headf = false;
			joint.clear();
		}
		if (xs && joint.size() != 0) {
			joint.push_back(ch);
			xscnt++;
		}
		else if (word || num) { // ������������ĸ��������
			if (joint.size() != 0 && !sws && !ss && !swd) { // ���joint���в������Ҳ�����ĸ�����֣���������joint
				cout << "{ " << joint << "," << mp[joint] << " }" << endl;
				joint.clear();
			}
			joint.push_back(ch); // ����ĸ������ѹ��joint
			if (ss && word && !(ch == 'x' && joint[0] == '0' || ch == 'e' && joint.size() == 2) && !jin16) { // ������������ĸ�����ҿ���Ŀ�����������֣���������Ƿ�Ϸ������Ϸ�����
				cout << "Error: The Input \" " << joint << " \" Is Illegal" << endl;
				return 0;
			}
			if (ss && word && sps == false) sps = true; // ������������֣�sps���Ϊtrue
			else if (sps == true && word && !jin16) { //������������ĸ���������������֣����Ҳ���16���ƣ�����
				cout << "Error: The Input \" " << joint << " \" Is Illegal" << endl;
				return 0;
			}
		}
		sws = 'a' <= joint[0] && joint[0] <= 'z'; //������һ�����ܶ��ַ������иı䣬�����ж�
		swd = 'A' <= joint[0] && joint[0] <= 'Z';
		ss = '0' <= joint[0] && joint[0] <= '9';
		xs = ss && ch == '.';
		if (!word && !num && joint.size() != 0 && (sws || ss || swd) && !xs) { // ����������벻����ĸ��������, �����ַ�����Ϊ�գ�����һ�������Ѿ�������ϣ�
			if(joint == "true" || joint == "false") cout << "{ " << joint << "," << 1 << " }" << endl; // true,false�ǳ���
			else if ((sws || swd) && mp.find(joint) != mp.end())  // �жϵ��ʣ�����map�����������(��������ǹؼ���)
				cout << "{ " << joint << "," << mp[joint] << " }" << endl;
			else if (ss && mp.find(joint) == mp.end()) { // �ж�����
				//cout << joint.size() << ' ' << xscnt << endl;
				if (!('0' <= joint[1] && joint[1] <= '9'|| joint[1] == 'x' && joint[0] == '0' || joint[1] == 'e' || joint[1] == '.') && joint.size() > 1 || xscnt > 1) { // ������ֵڶ�λ�Ƿ�Ϸ������С�����Ƿ�ֻ��һ�����������Ϸ���������Ѿ������ϣ�
					cout << "Error: The Input \" " << joint << " \" Is Illegal" << endl;
					return 0;
				}
				else cout << "{ " << joint << "," << 1 << " }" << endl;
				sps = false; // ���ñ��
				xscnt = 0;
			}
			else if (mp.find(joint) == mp.end()) // map��û�еĵ��ʿ϶����ǹؼ���
				cout << "{ " << joint << "," << "0" << " }" << endl;
			if (mp.find(joint) != mp.end()) head = true; // ����ǹؼ��֣�head���Ϊtrue
			else if (mp.find(joint) == mp.end() && headf == false) head = false;
			joint.clear(); // ����ַ���
		}
		if (!word && !num && !xs) { // ���������Ƿ���
			if (ch == ' ') { // ���пո�
				if (joint.size() != 0) {
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				continue;
			}
			else if (ch == '\n') { // ���л���
				if (joint.size() != 0) {
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				continue;
			}
			else if (ch == '\t') { // ����Tab�ո�
				if (joint.size() != 0) {
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				continue;
			}
			else if (joint.size() == 0 && ch != ' ') { // ���ڿ��ܻ�������ַ������ַ���Ϊ��ʱ��Ԥ�洢һ���ַ�
				joint.push_back(ch);
				if (mp.find(joint) == mp.end()) { // ������map��û�е��ַ�������
					cout << "Error: The Input \" " << joint << " \" Is NO Entry" << endl;
					joint.clear();
					continue;
				}
			}
			else if (ch != '=') { 
				if (ch == '<' && joint[0] == '<') { // ����<<
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else if (ch == '>' && joint[0] == '>') { // ����>>
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else if (ch == '/' && joint[0] == '/') { // ����//
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else if (ch == '|' && joint[0] == '|') { // ����||
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else if (ch == '&' && joint[0] == '&') { // ����&&
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
				else { // �����ַ������ɶԵģ�
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
					joint.push_back(ch);
					cout << "{ " << joint << "," << mp[joint] << " }" << endl;
					joint.clear();
				}
			}
			else if (ch == '=') { // ��������<=��>=��==��!=�ȳɶ��ַ�
				joint.push_back(ch);
				cout << "{ " << joint << "," << mp[joint] << " }" << endl;
				joint.clear();
			}
		}
	}
	sws = 'a' <= joint[0] && joint[0] <= 'z'; //�����������������һ���ַ�
	swd = 'A' <= joint[0] && joint[0] <= 'Z';
	ss = '0' <= joint[0] && joint[0] <= '9';
	if (joint.size() != 0) {
		if ((sws || swd) && mp.find(joint) != mp.end())  //����ǵ���
			cout << "{ " << joint << "," << mp[joint] << " }" << endl;
		else if (ss && mp.find(joint) == mp.end()) // ���������
			cout << "{ " << joint << "," << 1 << " }" << endl;
		else if (mp.find(joint) == mp.end()) // ����map��û�е�
			cout << "{ " << joint << "," << "0" << " }" << endl;
		else cout << "{ " << joint << "," << mp[joint] << " }" << endl; //����
	}
	return 0;
}