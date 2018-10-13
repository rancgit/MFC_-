// GetData.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include	"GetData.h"
#include	<fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

//#define  NYEAR 41
//年数，目前假定是2010到2050
//#define MAXAGE 101
//假定的最大年龄组
//#define TODO 7
//已有数据的年数，从这之后开始预测，基于前面的假设则是有2010到2016的数据，从2017开始预测

PeopleData::PeopleData(int i)
{//这两者只是需要处理的出生率与需要预测的年份不一样
	//先把磁盘上已有的数据读出来
	//if(!InitiPeopleFromFile())cerr<<"InitiPeople出错";
	//if(!InitiBirth()) cerr<<"InitiBirth出错";
	//if(!InitiDeath()) cerr<<"InitiDeath出错";
	//if(!ExtendDeath()) cerr<<"ExtendDeath出错";
	if (!InitiPeopleFromFile()) AfxMessageBox("InitiPeopleFromFile");
	if (!InitiBirth())AfxMessageBox("InitiBirth出错");
	if (!InitiDeath()) AfxMessageBox("InitiDeath出错");
	if (!ExtendDeath()) AfxMessageBox("ExtendDeath出错");


	if (i==1)
	{
		//这种情况下是单独二孩
		Predict(1);

	}
	else if(i==2)
	{
		Predict(2);
		//这种情况下是全面二孩
	}

/*
	for (int i = 0; i < NYEAR; i++)
	{
		vector<NodeOfPeople> PeoTemp;
		//先对每一年的向量结构初始化
		for (int i = 0; i <= MAXAGE; i++)
		{
			NodeOfPeople temp(0, 0);
			PeoTemp.push_back(temp);
		}
		//然后对整个结构初始化
		People.push_back(PeoTemp);
	}
	*/
}

PeopleData::~PeopleData()
{
}

double PeopleData::CalDea(double a, double b, double k)
{

	return exp(a+b*k);
}


bool PeopleData::InitiPeopleFromFile()
{
	/*
	TXT文件格式规定：
	男人 女人数	女性比
	文件名则是年份
	先默认使用2010到2016的文件初始化
	*/
	//ifstream opfile("E:\\VS\\GetData\\2010.txt",ios::in);
	//先全部初始化为0，之后直接采用赋值法操作比较好现在看来
	
	for (int i = 0; i < NYEAR; i++)
	{
		vector<NodeOfPeople> yeartemp;
		for (int i = 0; i <= MAXAGE; i++)
		{
			NodeOfPeople tmp(0, 0, 0);
			yeartemp.push_back(tmp);
		}
		People.push_back(yeartemp);
	}

	ifstream opfile;
	vector<string> filename = { "2010.txt","2011.txt","2012.txt","2013.txt","2014.txt","2015.txt","2016.txt" };
	for (int i = 0; i < TODO; i++)
	{
		
		 opfile.open(filename[i], ios::in);
		//这里的注意路径问题
		unsigned long m_man=0;
		unsigned long	m_woman = 0;
		double m_wp=0;
		int j = 0;
		if (!opfile.is_open())
		{
			opfile.close();
			return false;
		}
		//vector<NodeOfPeople> yeartemp;
		while (1)
		{
			opfile >> m_man >> m_woman >> m_wp; 
	
				
				NodeOfPeople tmp(m_man,m_woman,m_wp);
				People[i][j]=tmp;
				//yeartemp.push_back(tmp);
				j++;
				//cout << << ends;
			if (opfile.eof())
			{
				opfile.clear();
				opfile.close();
				break;
			}
		
		}
		//People.push_back(yeartemp);
	}

	
	//cout << "InitiPeople" << endl;
	return true;
}



bool PeopleData::InitiBirth()
{
	//先用1初始化，后面再引入模型计算,这里要考虑年份和性别比
	//我们认为出生婴儿的男女比大概是114:100，在一定年份后，将会降到110:100;
	double ra1 = 114.0 / 214;
	double ra2 = 110.0 / 210;
	//srand(time(NULL));
	double r = 0.01283;
	double ro = 0.0123;
	for (int i = 0; i < NYEAR-TODO; i++)
	{
		//double r = rand()%(13.1 - 12 +1)+ 12;

		double manb = r*ra1;
		double manbo = ro*ra1;
		double womanb = r*(1-ra1);
		double womanbo = ro*(1 - ra1);
		Node tmp(manb, womanb);
		Node tmpo(manbo, womanbo);
		if (i==10)
		{
			ra1 = ra2;
			r = 0.011;
			ro=0.01;
		}
		if (i>10)
		{
			r -= 0.00001;
			ro -= 0.00001;
		}
		BirthOfTwo.push_back(tmp);
		BirthOfOne.push_back(tmpo);
		//Birth.push_back(temp);

	}
	//cout << "InitiBirth" << endl;
	return true;
}


bool PeopleData::InitiDeath()
{
	/*//同样先用常量初始化了，后面再引入模型
	for (int i = 0; i < NYEAR-TODO; i++)
	{
		vector<Node> temp;
		for (int i = 0; i < MAXAGE; i++)
		{
			temp.push_back(0);
		}
		Death.push_back(temp);
	}*/
	//先读出α和β，男女分开读和存
	vector<double> man_a, man_b, woman_a, woman_b;
	ifstream opmana("男年龄因素.txt", ios::in);
	if (!opmana.is_open())
	{
		opmana.close();
		return false;
	}
	while (true)
	{
		double temp = 0;
		opmana >> temp;
		man_a.push_back(temp);
		if (opmana.eof())
		{
			break;
		}
	}
	opmana.close();

	ifstream opmanb("男暴露系数.txt", ios::in);
	if (!opmanb.is_open())
	{
		opmanb.close();
		return false;
	}
	while (true)
	{
		double temp = 0;
		opmanb >> temp;
		man_b.push_back(temp);
		if (opmanb.eof())
		{
			break;
		}
	}
	opmanb.close();

	ifstream opwomana("女年龄因素.txt", ios::in);
	if (!opwomana.is_open())
	{
		opwomana.close();
		return false;
	}
	while (true)
	{
		double temp;
		opwomana >> temp;
		woman_a.push_back(temp);
		if (opwomana.eof())
		{
			break;
		}
	}
	opwomana.close();

	ifstream opwomanb("女暴露系数.txt", ios::in);
	if (!opwomanb.is_open())
	{
		opwomanb.close();
		return false;
	}
	while (true)
	{
		double temp;
		opwomanb >> temp;
		woman_b.push_back(temp);
		if (opwomanb.eof())
		{
			break;
		}
	}
	opwomanb.close();

	//开始读取k值，并计算得到死亡率
	//男k   女k
	double mk = 0, wk = 0;
	ifstream opk("k.txt", ios::in);
	if (!opk.is_open())
	{
		opk.close();
		return false;
	}
	int num = NYEAR-TODO;
	while (true)
	{
		
		opk >> mk >> wk;
		num--;

		//计算死亡率,注意这里是通过k的数量多少确定的年份，所以要确保k值数量的一致
		double md = 0, wd = 0;
		vector<Node> tempofyear;
		for (unsigned int i = 0; i < woman_a.size(); i++)
		{
			md = CalDea(man_a[i], man_b[i], mk);
			wd = CalDea(woman_a[i], woman_b[i], wk);
			Node tmp(md, wd);
			tempofyear.push_back(tmp);
		}
		Death.push_back(tempofyear);
		if (num==0)
		{
			break;
		}
		if (opk.eof())
		{
			break;
		}
	
	}
	opk.close();
	//cout << "initideath" << endl;
	return true;
}

bool PeopleData::ExtendDeath()
{
	//cout << "extenddeath" << endl;
	//从文件中扩展,文件结构，男性 女性
	ifstream exdea("死亡率拓展.txt", ios::in);
	if (!exdea.is_open())
	{
		exdea.close();
		return false;
	}
	double md = 0, wd = 0; 
	while (true)
	{
		exdea >> md >> wd;
		for (unsigned int i = 0; i < NYEAR-TODO; i++)
		{
			wd -= 0.001; md -= 0.001;
			Node tmp(md, wd);
			Death[i].push_back(tmp);
		}
		if (exdea.eof())
		{
			break;
		}
	}
	exdea.clear();
	exdea.close();
	return true;

	/*//把所有的死亡率输出
	cout << "shujuxieru" << endl;
	ofstream opfile("death.txt");
	if (!opfile.is_open())
	{
		return false;
	}
	
	for (int i = 0; i < Death.size(); i++)
	{
		for (int j = 0; j < Death[i].size(); j++)
		{
			double md = Death[i][j].getman();
			double wd = Death[i][j].getwoman();
			opfile << md << "    " << "    " << endl;
		}
		opfile << endl << endl << endl;
	}
	opfile.close();
	cout << "shujuxieruwanchen" << endl;
	*/
}

void PeopleData::Predict(int i)
{
	//从TODO开始计算
	/*在这里实现莱斯利模型
	举个例子：2017年各年龄段的人口为2016年上一年龄段的人口的活来的人数
	注意0岁的人口则是生育的人数，注意100岁及以上的都在同一个组里面，这两个单独处理
	*/
	vector<Node> Birth;
	if (i==1)
	{
		 Birth = BirthOfOne;
	}
	else
	{
		Birth = BirthOfTwo;
	}
	for (int i = TODO; i < NYEAR; i++)
	{
		//先计算年龄在100岁以上的，为上一年99+存活的人数和100存活的人数
		//男性女性要分开计算
		
		unsigned long olman = People[i - 1][MAXAGE].getman()*(1 - Death[i-TODO][MAXAGE].getman())+People[i-1][MAXAGE-1].getman()*(1-Death[i-TODO][MAXAGE-1].getman());
		unsigned long olwoman = People[i - 1][MAXAGE].getwoman()*(1 - Death[i - TODO][MAXAGE].getwoman()) + People[i - 1][MAXAGE - 1].getwoman()*(1 - Death[i-TODO][MAXAGE - 1].getwoman());
		NodeOfPeople Max(olman, olwoman);
		People[i][MAXAGE] = Max;

		//计算出生人口
		//先略过，决定采用出生率还是生育率了再说
		unsigned long babyboy=0;
		unsigned long babygirl=0;
		/*for (int j =MINI+1; j <=MAX+1; j++)
		{	
			//先获得前一年的人数
			unsigned long sum = GetSumOfYear(i - 1);
			babyboy = Birth[i-TODO].getman();
			babygirl = Birth[i-TODO].getwoman();
			NodeOfPeople Min(babyboy, babyboy);
		}*/
		//采用出生率，计算每一年出生的人口数
		unsigned long sum = GetSumOfYear(i - 1);
		babyboy = sum*Birth[i - TODO].getman();
		//cout << "babyboy" << babyboy << ends << Birth[i - TODO].getman() <<ends<<sum<< endl;
		babygirl = sum*Birth[i - TODO].getwoman();
	//	cout << "babygirl" << babygirl << ends << Birth[i - TODO].getwoman()<<ends<<sum<< endl;
		NodeOfPeople Min(babyboy, babygirl);
		People[i][0] = Min;

		//最后计算其余各个年龄组的人数
		for (int j = 1; j <= MAXAGE-1; j++)
		{
			unsigned long man, woman;
			man = People[i - 1][j - 1].getman()*(1 - Death[i-TODO][j].getman());
			woman = People[i - 1][j - 1].getwoman()*(1 - Death[i-TODO][j].getwoman());
			NodeOfPeople node(man, woman);
			People[i][j] = node;
		}
	}


}

vector<NodeOfPeople> PeopleData::GetPeopleOfYear(int i)
{

	return People[i];
}


vector<unsigned long> PeopleData::GetAgeGroupOfYear(int i)
{
	vector<unsigned long> group;
	unsigned long sum=0;
	for (int j = 0; j <= MAXAGE; j++)
	{
		sum += People[i][j].getsum();
		if(j%GAP==0)
		{
			group.push_back(sum);
			sum = 0;
		}
	}
	return group;
}

unsigned long PeopleData::GetWomanSumOfYear(int i)
{
	unsigned long sum = 0;
	for (int j = 0; j <= MAXAGE; j++)
	{
		sum += People[i][j].getwoman();
	
	}
	return sum;
}


vector<unsigned long> PeopleData::GetStrOfYear(int i)
{
	vector<unsigned long> str;
	unsigned long sum=0;
	for (int j = 0; j < MINI; j++)
	{
		sum += People[i][j].getsum();
	}
	str.push_back(sum);
	sum = 0;
	for (int j = MINI	; j < MAX; j++)
	{
		sum += People[i][j].getsum();
	}
	str.push_back(sum);
	sum = 0;
	for (int j = MAX; j <= MAXAGE; j++)
	{
		sum += People[i][j].getsum();
	}
	str.push_back(sum);
	return str;
}

unsigned long PeopleData::GetSumOfYear(int i)
{
	unsigned long sum = 0;
	for (int j = 0; j <= MAXAGE;j++)
	{
		sum += People[i][j].getsum();
	}
	return sum;
}