#pragma once
#include <array>
#include <map>
#include <string>
#include <vector>

class LR1 {
private:
  static const int maxSize = 15; //��������������С
  std::array<std::array<std::string, LR1::maxSize>, LR1::maxSize>
      table;     //������ľ��������
  int tNum = 6;  //�����ս��������
  int nNum = 3;  //������ս��������
  int sNum = 12; //����״̬��

  std::map<char, int> tSet{
      {'i', 1}, {'+', 2}, {'*', 3}, {'(', 4},
      {')', 5}, {'#', 6}}; //�ս���ļ��ϣ���map ӳ���ʾ�ڷ�����ĵڼ���

  std::map<char, int> nSet{
      {'E', 1},
      {'T', 2},
      {'F', 3}}; //���ս���ļ��ϣ���map ӳ���ʾ�ڷ�����ĵڼ���

  std::map<int, std::string> g{{1, "E->E+T"}, {2, "E->T"},
                               {3, "T->T*F"}, {4, "T->F"},
                               {5, "F->(E)"}, {6, "F->i"}}; //����ʽ����
  
  std::vector<char> aStack;                                 //����ջ
  std::vector<int> sStack;                                  //״̬ջ

public:
  void fun(std::string &str); //�������������LL1Ԥ���������з���
  void init();                //���ݷ������ʼ��
};