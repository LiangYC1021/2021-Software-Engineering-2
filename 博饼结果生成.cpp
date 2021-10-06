#include<bits/stdc++.h>
#include<Windows.h>
#define inf 1e18+5
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const int N=1e5+5;
class Player;
class Game;
string its(int x){
	stringstream ss;
	string res;
	ss<<x;
	ss>>res;
	return res;
}

class Player{
private:
	int a[10],n,cnt[10],ID;
	int prize[10];
	int Best_Rank;
	//prize[1][2][3][4][5][6]
	//һ�� ���� �Ľ� ���� ���� ״Ԫ 
	string res;		
	friend class Game;
public:	
	Player(){
		for(int i=0;i<10;i++)a[i]=cnt[i]=prize[i]=0;
		Best_Rank=0;ID=0;
		n=6;res="";
	}
	void getnum()//һ��Ͷ���Ľ�� 
	{
		mt19937 myrand(time(0));
		rep(i,1,n){
			a[i]=myrand()%6 + 1; 
		}
	}
	string result(){
		int mx=0,tag=0;//����������������Ǹ�����
		memset(cnt,0,sizeof cnt);
		rep(i,1,n){
			cnt[a[i]]++;
			if(cnt[a[i]]>mx){
				tag=a[i];
				mx=cnt[a[i]];
			}
		}	
		if(mx==6){
			if(tag==4)return "������";
			else return "������";
		}
		if(mx==5){
			if(tag==4)return "���";
			else return "����";
		}
		if(mx==4){
			if(tag==4)return "״Ԫ";
			else return "�Ľ�"; 
		}
		if(mx==1)return "����";		
		if(cnt[4]==3)return "����";
		if(cnt[4]==2)return "����";
		if(cnt[4]==1)return "һ��";
		return "NULL"; 
	}	
	void Fetch_Prize(int i);
	void Get_Prize(){
		res=result();
		if(res=="NULL")return;
		if(res=="һ��")Fetch_Prize(1);
		else if(res=="����")Fetch_Prize(2);
		else if(res=="�Ľ�")Fetch_Prize(3);
		else if(res=="����")Fetch_Prize(4);
		else if(res=="����")Fetch_Prize(5);
		//����Ϊ״Ԫ		
		else {
			Fetch_Prize(6);
			int br=0;
			if(res=="״Ԫ"){
				rep(i,1,n)if(i!=4){
					br+=cnt[i]*i;
				}
				if(br==2){
					br+=1000;
					res+="���";
				}
				else res+="��"+its(br);
			} 
			else if(res=="���" || res=="����"){
				rep(i,1,n)if(cnt[i]==1){
					br+=i;
					break; 
				}
				res+="��"+its(br);
				if(res=="���")br+=600;
				else br+=500;				
			}
			else if(res=="������")br=888;
			Best_Rank=max(Best_Rank,br);
		} 		
	}	
	void Print_Prize(){
		cout<<"----------"<<endl;
		cout<<"��� "<<ID<<endl;
		for(int i=1;i<=6;i++)cout<<a[i]<<" ";
		cout<<endl;
		if(res=="NULL")cout<<"ʲôҲû��"<<endl;
		else cout<<res<<endl;
		cout<<"----------"<<endl;
	}
	
	void Play_One_Round(){
		getnum();	
		Get_Prize();
		Print_Prize();		
	}
	
}p,P[10];

class Game{
private:
	int PLAYER_NUM;//������� 
	int TOTAL_PRIZE[10];//ÿ����Ʒ������	
	friend class Player;
public:
	Game(){	}
	set(int num){
		PLAYER_NUM=num;
		for(int i=1;i<=num;i++)P[i].ID=i;
		TOTAL_PRIZE[1]=32;
		for(int i=2;i<=6;i++)TOTAL_PRIZE[i]=TOTAL_PRIZE[i-1]>>1;
		//Ĭ�Ͻ�Ʒ����Ϊ32 16 8 4 2 1 
	} 
	void Prize_Set(){
		
	}
	bool Prize_empty(){
		for(int i=1;i<=6;i++)if(TOTAL_PRIZE[i]>0)return false;
		return true; 
	}
	int Prize_Num(int i){//���ص�i�ֽ�Ʒ������ 
		return TOTAL_PRIZE[i];
	}
	void Give_Prize(int i){//ĳ�ֽ�Ʒ����-1 
		if(TOTAL_PRIZE[i]>0)TOTAL_PRIZE[i]--;
	}
	void Print_Currunt_Prize(){
		cout<<"--------------------------------"<<endl;
		cout<<"��ǰ��Ʒ��ʣ�� : "<<endl;
		cout<<"һ��  "<<TOTAL_PRIZE[1]<<endl; 
		cout<<"����  "<<TOTAL_PRIZE[2]<<endl; 
		cout<<"�Ľ�  "<<TOTAL_PRIZE[3]<<endl; 
		cout<<"����  "<<TOTAL_PRIZE[4]<<endl; 
		cout<<"����  "<<TOTAL_PRIZE[5]<<endl; 
		cout<<"״Ԫ  "<<TOTAL_PRIZE[6]<<endl; 
		cout<<"--------------------------------"<<endl;
	}
	void Gaming(){
		int cur=1;
		while(!Prize_empty()){
			P[cur].Play_One_Round();
			cur++;
			if(cur>PLAYER_NUM){
				cur=1;
				Print_Currunt_Prize();
			}
			Sleep(2007);
		}
	}	
}G;


void Player:: Fetch_Prize(int i){
	if(1<=i && i<=5){
		if(G.Prize_Num(i)>0){
			G.Give_Prize(i);
			this->prize[i]++;
		}
	}
	else if(i==6){
		int best=0,index=0;
		bool flag=1;
		for(int j=1;j<=G.PLAYER_NUM;j++)if(j!=ID){
			if(P[j].Best_Rank<Best_Rank){
				P[j].prize[6]=0;
			}
			else if(P[j].Best_Rank>Best_Rank){
				flag=0;
				break;
			}
		}
		if(flag){
			G.Give_Prize(6);
			this->prize[6]++;
		}
	}	
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	G.set(6);
	G.Gaming();
	system("pause");
	return 0;
}

