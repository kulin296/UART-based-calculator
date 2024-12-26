	#include<LPC21XX.H>
	#include"header.h"
	main()
	{
		unsigned int a[16],b[16],k,i,s,temp,c,e,l;
		int j,flag=0;
		uart0_init(9600);	
		while(1)
		{
			uart0_tx_string("\r\nEnter exp: ");
			i=0;
			while(uart0_rx()!='\r')
			{
				a[i]=uart0_rx();
				uart0_tx(a[i]);
				i++;
			}
			for(j=0,s=0,k=0;j<i;j++)
			{
				if(a[j]>='0' && a[j]<='9')
					s=(s*10)+(a[j]-48);
				else 
				{
					if(s>0)
					{
						b[k]=s;
						if(b[k]!=a[j])
						{
							b[k+1]=a[j];
							k=k+2;
						}
						else
							k++;
						s=0;
					}
					else
					{
						if(b[k-1]!=a[j])
						{
							b[k]=a[j];
							k++;
						}
					}
				}
			}
			b[k]=s;
			temp=0;
			c=0;
			/////////////////////////////////////
			while(1)
			{
				flag=0;
			for(i=0;i<=k;i++)
			{
				if(b[i]=='(' || b[i]==')')
				{
					flag=1;
					break;
				}
			}
			/////////////////////////////////////
			if(flag==1)
			{
			for(i=0;i<=k;i++)
			{
				if(b[i]=='(')
				{
					s=i;
				}
				else if(b[i]==')')
				{
						e=i;
						break;
				}
			}
				for(j=s+1;j<e;j++)
				{
				if(b[j]=='/')
				{
					temp=b[j-1]/b[j+1];
					b[j-1]=temp;
					for(l=j;l<=k;l++)
						b[l]=b[l+2];
					k=k-2;
					j=s;
					e=e-2;
				}
				else if(b[j]=='*')
				{
					temp=b[j-1]*b[j+1];
					b[j-1]=temp;
					for(l=j;l<=k;l++)
						b[l]=b[l+2];
					k=k-2;
					j=s+1;
					e=e-2;
				}

				else if(b[j]=='%')
				{
					temp=b[j-1]%b[j+1];
					b[j-1]=temp;
					for(l=j;l<=k;l++)
						b[l]=b[l+2];
					k=k-2;
					j=s+1;
					e=e-2;
				}
				}
				for(j=s+1;j<e;j++)
				{
				if(b[j]=='+')
				{
					temp=b[j-1]+b[j+1];
					b[j-1]=temp;
					for(l=j;l<=k;l++)
						b[l]=b[l+2];
					k=k-2;
					j=s+1;
					e=e-2;
				}
				else if(b[j]=='-')
				{
					temp=b[j-1]-b[j+1];
					b[j-1]=temp;
					for(l=j;l<=k;l++)
						b[l]=b[l+2];
					k=k-2;
					j=s+1;
					e=e-2;
				}
				}
			for(i=0;i<=k;i++)
			{
				if(b[i]=='(' )
				{
					for(j=i;j<=k;j++)
						b[j]=b[j+1];
					k--;
				}
				else if(b[i]==')' )
				{
					for(j=i;j<=k;j++)
						b[j]=b[j+1];
					k--;
					break;
				}
			}
			}
			else if(flag==0)
				break;
		}
//				for(i=0;i<=k;i++)
//				{
//					if(b[i]=='(' || b[i]==')')
//					{
//						for(j=i;j<=k;j++)
//							b[j]=b[j+1];
//						k--;
//					}
//				}
//		for(i=0;i<=k;i++)
//		{
//			uart0_tx_string("\r\n");
//			uart0_tx_integer(b[i]);
//		}
//		uart0_tx_string("\r\n");
//			uart0_tx_integer(k);
		
			
			///////////////////////////////////////////
		for(i=0;i<=k;i++)
		{
			if(b[i]=='/')
			{
				temp=b[i-1]/b[i+1];
				b[i-1]=temp;
				for(j=i;j<=k;j++)
					b[j]=b[j+2];
				k=k-2;
			}
			else if(b[i]=='*')
			{
				temp=b[i-1]*b[i+1];
				b[i-1]=temp;
				for(j=i;j<=k;j++)
					b[j]=b[j+2];
				k=k-2;
			}
			else if(b[i]=='%')
			{
				temp=b[i-1]%b[i+1];
				b[i-1]=temp;
				for(j=i;j<=k;j++)
					b[j]=b[j+2];
				k=k-2;
			}
		}

		for(i=0;i<=k;i++)
		{
			if(b[i]=='+')
			{
				if(c==0)
				{
					temp=b[i-1]+b[i+1];
					c++;
				}
				else
				{
						temp+=b[i+1];
				}
			}		
			else if(b[i]=='-')
			{
				if(c==0)
				{
					temp=b[i-1]-b[i+1];
					c++;
				}
				else
				{
						temp-=b[i+1];
				}
			}		
		}
		
		uart0_tx_string("\r\nResult: ");
		uart0_tx_integer(temp);
		}
}
