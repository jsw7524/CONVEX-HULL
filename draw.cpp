#include<afxwin.h>
#include<math.h>
#include<stdlib.h>
#define speed 0
struct Mydot
{
	int Mx;
	int My;
	int flag;
}Dot_table[256];
int dotnumber=0,Leftmost=0,Rightmost=0,min=0,max=0;
class myframe : public CFrameWnd
{
public:
	myframe()
	{
		Create(NULL,"CONVEX HULL #This program is writed by 吳嘉森");
		ShowWindow(SW_SHOWMAXIMIZED);	
		tagRECT gg={30,30,500,50};
		CClientDC a(this);
		a.DrawText("請按滑鼠左鍵產生節點  請按滑鼠右鍵產生CONVEX HULL  ",&gg,DT_LEFT);

	}


	void Quick_Hull()
	{
		HWND jk;
		float IR=((float)Dot_table[Rightmost].My-Dot_table[Leftmost].My)/((float)Dot_table[Rightmost].Mx-Dot_table[Leftmost].Mx);
		float C = -IR*Dot_table[Leftmost].Mx+Dot_table[Leftmost].My;
		float hvalue=0,tc;		
		int peaknb=0;

		for (int t =0 ;t < dotnumber ;t ++)
		{
			if ( Dot_table[t].flag != -1)
			{
				if (((tc=Dot_table[t].My-IR*Dot_table[t].Mx-C) <= 0)  )
				{
					Dot_table[t].flag=-1;
					
				}
				else
				{
					if (tc > hvalue )
					{
						hvalue = tc;
						peaknb = t;
					}

				}
			}
		}
		if (hvalue > 0)
		{
			upper_hull(Leftmost,peaknb,Dot_table);
			upper_hull(peaknb,Rightmost,Dot_table);

		}
		for ( t =0 ;t < dotnumber ;t ++)
		{
			
			if ( Dot_table[t].flag != 1)
			{
				tc=Dot_table[t].My-IR*Dot_table[t].Mx-C;
				if ( tc > 0  )
				{
					Dot_table[t].flag=1;	
				}
				else if (tc <= 0)
				{

					if (tc < hvalue  )
					{				
						hvalue = tc;
						peaknb = t;
					}

				}
			}
		}
		if (hvalue < 0)
		{
			lower_hull(Leftmost,peaknb,Dot_table);
			lower_hull(peaknb,Rightmost,Dot_table);
		}
	}
	void upper_hull(int D1 ,int D2, Mydot * Dot_table)
	{
	/*
					CClientDC a(this);
			CPen mypen(PS_SOLID,1,RGB(0,0,0));	
			a.SelectObject(&mypen);
			a.MoveTo(Dot_table[D1].Mx,Dot_table[D1].My);
			a.LineTo(Dot_table[D2].Mx,Dot_table[D2].My);
			_sleep(speed);
*/
		Mydot local_table[256];
		for (int rr =0 ; rr < 256 ; rr++)
		{
			local_table[rr] = Dot_table[rr];
		}

		Dot_table[D1].flag=-1;
		Dot_table[D2].flag=-1;

		float IR=((float)Dot_table[D2].My-Dot_table[D1].My)/((float)Dot_table[D2].Mx-Dot_table[D1].Mx);
		float C = -IR*Dot_table[D1].Mx+Dot_table[D1].My;
		float hvalue=0,tc;		
		int peaknb=0;
//////////////
		for (int t =0 ;t < dotnumber ;t ++)
		{
			
			if ( Dot_table[t].flag != -1)
			{
				tc=Dot_table[t].My-IR*Dot_table[t].Mx-C;
				if ( tc <= 0  )
				{
					local_table[t].flag=-1;	
				}
				else if (tc > 0)
				{

					if (tc > hvalue  )
					{
						
						hvalue = tc;
						peaknb = t;
					}

				}
			}
		}
		if (hvalue > 0)
		{
			upper_hull(D1,peaknb,local_table);
			upper_hull(peaknb,D2,local_table);
		}
		else
		{
			
			CClientDC a(this);
			CPen mypen(PS_SOLID,1,RGB(0,0,0));	
			a.SelectObject(&mypen);
			a.MoveTo(Dot_table[D1].Mx,Dot_table[D1].My);
			a.LineTo(Dot_table[D2].Mx,Dot_table[D2].My);
			_sleep(speed);
			
		}
////////////
	}
	void lower_hull(int D1 ,int D2, Mydot * Dot_table)
	{
/*
					CClientDC a(this);
			CPen mypen(PS_SOLID,1,RGB(0,0,0));	
			a.SelectObject(&mypen);
			a.MoveTo(Dot_table[D1].Mx,Dot_table[D1].My);
			a.LineTo(Dot_table[D2].Mx,Dot_table[D2].My);*/
		Mydot local_table[256];
		_sleep(speed);
		for (int rr =0 ; rr < 256 ; rr++)
		{
			local_table[rr] = Dot_table[rr];
		}
		Dot_table[D1].flag=1;
		Dot_table[D2].flag=1;

		float IR=((float)Dot_table[D2].My-Dot_table[D1].My)/((float)Dot_table[D2].Mx-Dot_table[D1].Mx);
		float C = -IR*Dot_table[D1].Mx+Dot_table[D1].My;
		float hvalue=0,tc;		
		int peaknb=0;
//////////////
		for (int t =0 ;t < dotnumber ;t ++)
		{
			
			if ( Dot_table[t].flag != 1)
			{
				tc=Dot_table[t].My-IR*Dot_table[t].Mx-C;
				if ( tc > 0  )
				{
					local_table[t].flag=1;	
				}
				else if (tc <= 0)
				{

					if (tc < hvalue  )
					{				
						hvalue = tc;
						peaknb = t;
					}

				}
			}
		}
		if (hvalue < 0)
		{
			lower_hull(D1,peaknb,local_table);
			lower_hull(peaknb,D2,local_table);
		}
		else
		{
			
			CClientDC a(this);
			CPen mypen(PS_SOLID,1,RGB(0,0,0));	
			a.SelectObject(&mypen);
			a.MoveTo(Dot_table[D1].Mx,Dot_table[D1].My);
			a.LineTo(Dot_table[D2].Mx,Dot_table[D2].My);
			_sleep(speed);
			
		}
	}
/////////////
	char * myitoa(int a,char *b,int base)
	{
		char * temp=b;
		if (a / base != 0)
		{
			temp=myitoa(a/base,b,base);
		}
		*(temp) = (base > 10 && a%base > 9 )?55+a%base:48+a%base;
		*(temp+1) = '\0';
		return (temp+ 1);
	}

	afx_msg void OnLButtonDown(UINT k,int x , int y)//左鍵事件 
	{

		Dot_table[dotnumber].flag = 1;
		Dot_table[dotnumber].Mx=x;
		Dot_table[dotnumber].My=y;

		if (dotnumber==0) //initial
		{
			min =Dot_table[dotnumber].Mx;
			max =Dot_table[dotnumber].Mx;
		}
		else if(dotnumber>0)
		{
			if (Dot_table[dotnumber].Mx > max)
			{
				Rightmost = dotnumber;
				max =Dot_table[dotnumber].Mx;
			//	MessageBox("Max");
			}
			if (Dot_table[dotnumber].Mx < min)
			{
				Leftmost = dotnumber;
				min =Dot_table[dotnumber].Mx;
			//	MessageBox("Min");
			}

		}

		char hh[66]; ;
		char* temp;
		temp=myitoa(dotnumber,hh,10);
		* temp =' ';
		temp=myitoa(x,temp+1,10);
		* temp =' ';
		myitoa(y,temp+1,10);
		
		tagRECT gg={x-50,y-20,x+50,y+20};
		CClientDC a(this);	
		CBrush mybrush(RGB(255,0,0));
		a.SelectObject(&mybrush);
		a.Ellipse(x-2,y-2,x+2,y+2);
		a.DrawText(hh,&gg,DT_CENTER);
		//SetPixel(x,y,RGB(255,0,0));
		/*		
		itoa(Leftmost,hh,10);
		MessageBox(hh);
		*/
		dotnumber++;		
	}

	afx_msg void OnRButtonDown(UINT k,int x , int y)//右鍵事件
	{
		Quick_Hull();
	}

	DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(myframe,CFrameWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()
class mywin :public CWinApp
{
public:
	BOOL InitInstance()
	{
		myframe  * ff = new myframe ;
		m_pMainWnd = ff ;
		return 1;
	}
}player; 
