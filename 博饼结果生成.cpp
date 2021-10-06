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
	//一秀 二举 四进 三红 对堂 状元 
	string res;		
	friend class Game;
public:	
	Player(){
		for(int i=0;i<10;i++)a[i]=cnt[i]=prize[i]=0;
		Best_Rank=0;ID=0;
		n=6;res="";
	}
	void getnum()//一次投掷的结果 
	{
		mt19937 myrand(time(0));
		rep(i,1,n){
			a[i]=myrand()%6 + 1; 
		}
	}
	string result(){
		int mx=0,tag=0;//最大数量的数量和那个点数
		memset(cnt,0,sizeof cnt);
		rep(i,1,n){
			cnt[a[i]]++;
			if(cnt[a[i]]>mx){
				tag=a[i];
				mx=cnt[a[i]];
			}
		}	
		if(mx==6){
			if(tag==4)return "六博红";
			else return "六博黑";
		}
		if(mx==5){
			if(tag==4)return "五红";
			else return "五子";
		}
		if(mx==4){
			if(tag==4)return "状元";
			else return "四进"; 
		}
		if(mx==1)return "对堂";		
		if(cnt[4]==3)return "三红";
		if(cnt[4]==2)return "二举";
		if(cnt[4]==1)return "一秀";
		return "NULL"; 
	}	
	void Fetch_Prize(int i);
	void Get_Prize(){
		res=result();
		if(res=="NULL")return;
		if(res=="一秀")Fetch_Prize(1);
		else if(res=="二举")Fetch_Prize(2);
		else if(res=="四进")Fetch_Prize(3);
		else if(res=="三红")Fetch_Prize(4);
		else if(res=="对堂")Fetch_Prize(5);
		//以下为状元		
		else {
			Fetch_Prize(6);
			int br=0;
			if(res=="状元"){
				rep(i,1,n)if(i!=4){
					br+=cnt[i]*i;
				}
				if(br==2){
					br+=1000;
					res+="插金花";
				}
				else res+="带"+its(br);
			} 
			else if(res=="五红" || res=="五子"){
				rep(i,1,n)if(cnt[i]==1){
					br+=i;
					break; 
				}
				res+="带"+its(br);
				if(res=="五红")br+=600;
				else br+=500;				
			}
			else if(res=="六博红")br=888;
			Best_Rank=max(Best_Rank,br);
		} 		
	}	
	void Print_Prize(){
		cout<<"----------"<<endl;
		cout<<"玩家 "<<ID<<endl;
		for(int i=1;i<=6;i++)cout<<a[i]<<" ";
		cout<<endl;
		if(res=="NULL")cout<<"什么也没有"<<endl;
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
	int PLAYER_NUM;//玩家人数 
	int TOTAL_PRIZE[10];//每个奖品总数量	
	friend class Player;
public:
	Game(){	}
	set(int num){
		PLAYER_NUM=num;
		for(int i=1;i<=num;i++)P[i].ID=i;
		TOTAL_PRIZE[1]=32;
		for(int i=2;i<=6;i++)TOTAL_PRIZE[i]=TOTAL_PRIZE[i-1]>>1;
		//默认奖品个数为32 16 8 4 2 1 
	} 
	void Prize_Set(){
		
	}
	bool Prize_empty(){
		for(int i=1;i<=6;i++)if(TOTAL_PRIZE[i]>0)return false;
		return true; 
	}
	int Prize_Num(int i){//返回第i种奖品的数量 
		return TOTAL_PRIZE[i];
	}
	void Give_Prize(int i){//某种奖品数量-1 
		if(TOTAL_PRIZE[i]>0)TOTAL_PRIZE[i]--;
	}
	void Print_Currunt_Prize(){
		cout<<"--------------------------------"<<endl;
		cout<<"当前奖品还剩下 : "<<endl;
		cout<<"一秀  "<<TOTAL_PRIZE[1]<<endl; 
		cout<<"二举  "<<TOTAL_PRIZE[2]<<endl; 
		cout<<"四进  "<<TOTAL_PRIZE[3]<<endl; 
		cout<<"三红  "<<TOTAL_PRIZE[4]<<endl; 
		cout<<"对堂  "<<TOTAL_PRIZE[5]<<endl; 
		cout<<"状元  "<<TOTAL_PRIZE[6]<<endl; 
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

