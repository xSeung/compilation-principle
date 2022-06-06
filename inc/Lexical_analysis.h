#pragma once
#include <fstream>
#include <map>
#include <string>
#include <utility>
class Analyser;

class Analyser {
private:
  std::ifstream in;
  std::map<std::string, int> k;             //�ؼ��ֱ�
  std::map<std::string, int> p;             //�ֽ����
  std::map<std::string, int> c;             //������
  std::map<std::string, int> i;             //��ʶ����
  std::map<std::string, int> const arit = { //�����������
      {"+", 1},  {"-", 2},  {"*", 3},  {"/", 4},   {"++", 5},  {"==", 6},
      {"+=", 7}, {"-=", 8}, {"*=", 9}, {"/=", 10}, {"--", 11}, {"=", 12}};
  std::map<std::string, int> const rela = { //��ϵ�������
      {">", 1},
      {"<", 2},
      {">=", 3},
      {"<=", 4},
      {"==", 5}};
  /*���ж��ļ�
  ���룺p�ļ���ַ��str�������
  ����ֵ�������ļ���û�ж��ɹ�
  */
  auto readline(char const *p, std::string &str) -> bool;
  auto is_number(char c) -> bool;
  auto is_character(char c) -> bool;
  /*
  ���룺
    �ַ����ĵ�����
  ����ֵ��
    ��Ԫ�飺<�ַ����������࣬������>
  */
  auto sub_program1(std::string::iterator &iter, std::string::iterator &end)
      -> std::pair<std::string, std::pair<std::string, int>>;
  /*
  ���룺
    �ַ����ĵ�����
  ����ֵ��
    ��Ԫ�飺<���֣����࣬���������루����0ʱΪError��>
  */
  auto sub_program2(std::string::iterator &iter, std::string::iterator &end)
      -> std::pair<std::string, std::pair<std::string, int>>;
  /*
  ���룺
    �ַ����ĵ�����
  ����ֵ��
    ��Ԫ�飺<���ţ����࣬�����루����0ʱΪError��>
  */
  auto sub_program3(std::string::iterator &iter, std::string::iterator &end)
      -> std::pair<std::string, std::pair<std::string, int>>;

public:
  Analyser() = default;
  //��k��
  auto read_k(char const *p) -> void;
  //��p��
  auto read_p(char const *p) -> void;
  //���÷���p·���ļ��Ľӿ�
  auto analyse(char const *p) -> void;
};
