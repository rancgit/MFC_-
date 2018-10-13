// GetData.cpp : �������̨Ӧ�ó������ڵ㡣
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
//������Ŀǰ�ٶ���2010��2050
//#define MAXAGE 101
//�ٶ������������
//#define TODO 7
//�������ݵ�����������֮��ʼԤ�⣬����ǰ��ļ���������2010��2016�����ݣ���2017��ʼԤ��

PeopleData::PeopleData(int i)
{//������ֻ����Ҫ����ĳ���������ҪԤ�����ݲ�һ��
	//�ȰѴ��������е����ݶ�����
	//if(!InitiPeopleFromFile())cerr<<"InitiPeople����";
	//if(!InitiBirth()) cerr<<"InitiBirth����";
	//if(!InitiDeath()) cerr<<"InitiDeath����";
	//if(!ExtendDeath()) cerr<<"ExtendDeath����";
	if (!InitiPeopleFromFile()) AfxMessageBox("InitiPeopleFromFile");
	if (!InitiBirth())AfxMessageBox("InitiBirth����");
	if (!InitiDeath()) AfxMessageBox("InitiDeath����");
	if (!ExtendDeath()) AfxMessageBox("ExtendDeath����");


	if (i==1)
	{
		//����������ǵ�������
		Predict(1);

	}
	else if(i==2)
	{
		Predict(2);
		//�����������ȫ�����
	}

/*
	for (int i = 0; i < NYEAR; i++)
	{
		vector<NodeOfPeople> PeoTemp;
		//�ȶ�ÿһ��������ṹ��ʼ��
		for (int i = 0; i <= MAXAGE; i++)
		{
			NodeOfPeople temp(0, 0);
			PeoTemp.push_back(temp);
		}
		//Ȼ��������ṹ��ʼ��
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
	TXT�ļ���ʽ�涨��
	���� Ů����	Ů�Ա�
	�ļ����������
	��Ĭ��ʹ��2010��2016���ļ���ʼ��
	*/
	//ifstream opfile("E:\\VS\\GetData\\2010.txt",ios::in);
	//��ȫ����ʼ��Ϊ0��֮��ֱ�Ӳ��ø�ֵ�������ȽϺ����ڿ���
	
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
		//�����ע��·������
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
	//����1��ʼ��������������ģ�ͼ���,����Ҫ������ݺ��Ա��
	//������Ϊ����Ӥ������Ů�ȴ����114:100����һ����ݺ󣬽��ή��110:100;
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
	/*//ͬ�����ó�����ʼ���ˣ�����������ģ��
	for (int i = 0; i < NYEAR-TODO; i++)
	{
		vector<Node> temp;
		for (int i = 0; i < MAXAGE; i++)
		{
			temp.push_back(0);
		}
		Death.push_back(temp);
	}*/
	//�ȶ������ͦ£���Ů�ֿ����ʹ�
	vector<double> man_a, man_b, woman_a, woman_b;
	ifstream opmana("����������.txt", ios::in);
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

	ifstream opmanb("�б�¶ϵ��.txt", ios::in);
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

	ifstream opwomana("Ů��������.txt", ios::in);
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

	ifstream opwomanb("Ů��¶ϵ��.txt", ios::in);
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

	//��ʼ��ȡkֵ��������õ�������
	//��k   Ůk
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

		//����������,ע��������ͨ��k����������ȷ������ݣ�����Ҫȷ��kֵ������һ��
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
	//���ļ�����չ,�ļ��ṹ������ Ů��
	ifstream exdea("��������չ.txt", ios::in);
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

	/*//�����е����������
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
	//��TODO��ʼ����
	/*������ʵ����˹��ģ��
	�ٸ����ӣ�2017�������ε��˿�Ϊ2016����һ����ε��˿ڵĻ���������
	ע��0����˿�����������������ע��100�꼰���ϵĶ���ͬһ�������棬��������������
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
		//�ȼ���������100�����ϵģ�Ϊ��һ��99+����������100��������
		//����Ů��Ҫ�ֿ�����
		
		unsigned long olman = People[i - 1][MAXAGE].getman()*(1 - Death[i-TODO][MAXAGE].getman())+People[i-1][MAXAGE-1].getman()*(1-Death[i-TODO][MAXAGE-1].getman());
		unsigned long olwoman = People[i - 1][MAXAGE].getwoman()*(1 - Death[i - TODO][MAXAGE].getwoman()) + People[i - 1][MAXAGE - 1].getwoman()*(1 - Death[i-TODO][MAXAGE - 1].getwoman());
		NodeOfPeople Max(olman, olwoman);
		People[i][MAXAGE] = Max;

		//��������˿�
		//���Թ����������ó����ʻ�������������˵
		unsigned long babyboy=0;
		unsigned long babygirl=0;
		/*for (int j =MINI+1; j <=MAX+1; j++)
		{	
			//�Ȼ��ǰһ�������
			unsigned long sum = GetSumOfYear(i - 1);
			babyboy = Birth[i-TODO].getman();
			babygirl = Birth[i-TODO].getwoman();
			NodeOfPeople Min(babyboy, babyboy);
		}*/
		//���ó����ʣ�����ÿһ��������˿���
		unsigned long sum = GetSumOfYear(i - 1);
		babyboy = sum*Birth[i - TODO].getman();
		//cout << "babyboy" << babyboy << ends << Birth[i - TODO].getman() <<ends<<sum<< endl;
		babygirl = sum*Birth[i - TODO].getwoman();
	//	cout << "babygirl" << babygirl << ends << Birth[i - TODO].getwoman()<<ends<<sum<< endl;
		NodeOfPeople Min(babyboy, babygirl);
		People[i][0] = Min;

		//������������������������
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