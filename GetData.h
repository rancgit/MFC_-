#pragma once

#include <vector>

using namespace std;


#define  NYEAR 41
//������Ŀǰ�ٶ���2010��2050

#define MAXAGE 100
//�ٶ������������Ϊ100���������100��Ҳ����һ������

#define TODO 7
//��ʵ�����ݵ���ݣ�����֮��ʼԤ�⣬����ǰ��ļ��裬���Ǵ�2017�꿪ʼ��Ԥ��
//������2010������ݵ�2016�������

#define MINI 20
#define	MAX 60
//��������ָ���

#define GAP  5
//����μ��


//����Node�ڵ㣬���ڱ�ʾ�����ʺ�������
class Node
{
public:
	//���ֻ���ܵģ�����Ϊ��Ů�Ķ�һ��
	Node(double m_total):total(m_total),man(m_total/2),woman(m_total/2){}
	//���������ֱ�Ϊ�к�Ů��
	Node(double m_man, double m_woman) :man(m_man), woman(m_woman),total(m_man+m_woman) {};
	double getman() { return man; }
	double getwoman() { return woman; }
	double gettotal() { return total; }

private:
	double man = 0;
	double woman = 0;
	double total = 0;
};

//����ÿ������Ľڵ�ṹ����������������Ů����������������Ů��ռ��
class NodeOfPeople
{
public:
	//NodeOfPeople(unsigned long m_sum, double m_wp);
	NodeOfPeople(unsigned long m_man, unsigned long m_woman);
	NodeOfPeople(unsigned long m_man,unsigned long m_woman, double wp);
	~NodeOfPeople();
	unsigned long getsum() { return sum; }
	double getwp() {return wp;}
	unsigned long getman() { return man; }
	unsigned long getwoman() { return woman; }
private:
	unsigned long sum = 0;
	//������������������Ϊ��λ
	double wp = 0;
	//���������е��Ա�ȣ���Ů��100Ϊ�ο�
	unsigned long man = 0;//���Ա�����
	unsigned long woman = 0;
};

/*NodeOfPeople::NodeOfPeople(unsigned long m_sum,double m_wp)
{
	wp = m_wp;
	sum = m_sum;
	man = ((double)sum)*(m_wp / 100.0);
	woman = sum - man;
}
*/
 NodeOfPeople::NodeOfPeople(unsigned long m_man, unsigned long m_woman)
{
	 man = m_man;
	 woman = m_woman;
	 sum = m_man + m_woman;
	 if (woman==0)
	 {
		 wp = 0;
	 }
	 else
	 {
		 wp = (double)man / woman * 100;
	 }
}

NodeOfPeople::NodeOfPeople(unsigned long m_man,unsigned long m_woman, double m_wp)
{
	man = m_man;
	woman = m_woman;
	sum = man + woman;
	wp = m_wp;
}
NodeOfPeople::~NodeOfPeople()
{
}

class PeopleData
{
public:
	PeopleData() {}
	PeopleData(int i);//��i�ж��ǵ�����������ȫ�����
	~PeopleData();

	//�������е�People����
	vector<vector<NodeOfPeople>> GetPeople() {return People;}

	//����ĳһ����˿����ݣ������У�Ů���Ա��,iΪ����ڵ�һ���ƫ����
	//��������ļ��裬��i=1ʱ����2011��
	vector<NodeOfPeople> GetPeopleOfYear(int i);

	//����ĳһ��ķ�������˿���,iΪ����ڵ�һ���ƫ����
	vector<unsigned long> GetAgeGroupOfYear(int i);

	//����ĳһ��ķ������Ů���˿���   iΪ����ڵ�һ���ƫ����,����εļ��ΪGAP
	//���Ҫ֪��ĳһ�ε������˿��������������������ȥ���Ů���˿�������
	unsigned long GetWomanSumOfYear(int i);

	//����ĳһ�������ṹ    iΪ����ڵ�һ���ƫ����
	//����Ԫ�أ��ֱ��������˿������������˿������������˿�����
	vector<unsigned long> GetStrOfYear(int i);

	//����ĳһ����˿�����
	unsigned long GetSumOfYear(int i);
	
private:
	vector<vector<NodeOfPeople>> People;	//���ڴ洢���˿ڵ�����
	vector<Node> BirthOfTwo;		//������
	vector<Node> BirthOfOne;
	vector<vector<Node>> Death;		//�����ʽṹ

	double CalDea(double a, double b, double k);//����������
	//���ļ���ʼ��People��Ĭ��Excel�ļ�����->��ΪTXT�ļ�
	bool InitiPeopleFromFile();

	//���ļ���ʼ��Birth��Ĭ��Excel�ļ�->��ΪTXT�ļ�
	bool InitiBirth();

	//���ļ���ʼ��Death��Ĭ��TXT�ļ�
	bool InitiDeath();

	//��չ�����ʣ�����������չ��100��+��
	bool ExtendDeath();

	//����Ԥ����㣬��ݴ�TODO��ʼ
	void Predict(int i);

};




