#pragma once

#include <vector>

using namespace std;


#define  NYEAR 41
//年数，目前假定是2010到2050

#define MAXAGE 100
//假定的最大年龄组为100，年龄大于100的也在这一类里面

#define TODO 7
//有实际数据的年份，从这之后开始预测，基于前面的假设，就是从2017年开始做预测
//我们有2010年的数据到2016年的数据

#define MINI 20
#define	MAX 60
//定义年龄分隔，

#define GAP  5
//年龄段间隔


//定义Node节点，用于表示出生率和死亡率
class Node
{
public:
	//如果只有总的，则认为男女的都一样
	Node(double m_total):total(m_total),man(m_total/2),woman(m_total/2){}
	//两个参数分别为男和女的
	Node(double m_man, double m_woman) :man(m_man), woman(m_woman),total(m_man+m_woman) {};
	double getman() { return man; }
	double getwoman() { return woman; }
	double gettotal() { return total; }

private:
	double man = 0;
	double woman = 0;
	double total = 0;
};

//这是每个年龄的节点结构，包括男性人数，女性人数，总人数，女性占比
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
	//该年龄组人数，以人为单位
	double wp = 0;
	//该年龄组中的性别比，以女性100为参考
	unsigned long man = 0;//分性别人数
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
	PeopleData(int i);//用i判断是单独二孩还是全面二孩
	~PeopleData();

	//返回类中的People数据
	vector<vector<NodeOfPeople>> GetPeople() {return People;}

	//返回某一年的人口数据，包括男，女，性别比,i为相对于第一年的偏移量
	//基于上面的假设，当i=1时就是2011年
	vector<NodeOfPeople> GetPeopleOfYear(int i);

	//返回某一年的分年龄段人口数,i为相对于第一年的偏移量
	vector<unsigned long> GetAgeGroupOfYear(int i);

	//返回某一年的分年龄段女性人口数   i为相对于第一年的偏移量,年龄段的间隔为GAP
	//如果要知道某一段的男性人口数，用上面的总人数减去这个女性人口数即可
	unsigned long GetWomanSumOfYear(int i);

	//返回某一年的年龄结构    i为相对于第一年的偏移量
	//三个元素，分别是少年人口总数，中年人口总数，老年人口总数
	vector<unsigned long> GetStrOfYear(int i);

	//返回某一年的人口总数
	unsigned long GetSumOfYear(int i);
	
private:
	vector<vector<NodeOfPeople>> People;	//用于存储总人口的数据
	vector<Node> BirthOfTwo;		//出生率
	vector<Node> BirthOfOne;
	vector<vector<Node>> Death;		//死亡率结构

	double CalDea(double a, double b, double k);//返回死亡率
	//从文件初始化People，默认Excel文件？？->改为TXT文件
	bool InitiPeopleFromFile();

	//从文件初始化Birth，默认Excel文件->改为TXT文件
	bool InitiBirth();

	//从文件初始化Death，默认TXT文件
	bool InitiDeath();

	//拓展死亡率，将死亡率拓展到100岁+，
	bool ExtendDeath();

	//进行预测计算，年份从TODO开始
	void Predict(int i);

};




