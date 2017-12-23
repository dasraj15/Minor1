#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<graphics.h>

/*int searchUser(char key[20])
{
	int i,j=0;
	for(i=0;i<5;i++)
	{
		if(strcmp(key,list[i]))
		{
			return officialType[i];
		}
	}
}*/

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 20*number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}
void frontPage();
void startPage();
void loginPage();
void signUp();
int dijikstra(int source,int sink,int d1,int d2,int d3,int d4,int d5,int d6);
int fordFulkerson(int source,int sink,int w1,int w2,int w3,int w4,int w5,int w6);

void frontPage()
{
	int node1,node2,d1,d2,d3,d4,d5,d6,w1,w2,w3,w4,w5,w6;
	system("cls");
	//printf("This is Front Page.\nThis page will be developed soon!!");
	printf("Dear Admin!!The flow will happen between Exploration Sites and Refineries\n");
	printf("Enter Exploration Site ID");
	printf("\nID's are:\n");
	printf("1. ES1\n");
	printf("\n2. ES2\n");
	printf("\n3. ES3\n");
	scanf("%d",&node1);
	printf("Enter Refinery ID");
	printf("\nID's are:\n");
	printf("4. REFINERY1");
	printf("\n5. REFINERY2\n");
	scanf("%d",&node2);
	printf("Enter the values of the length of paths as instructed!!");
	printf("\nd1:");
	scanf("%d",&d1);
	printf("d2:");
	scanf("%d",&d2);
	printf("d3:");
	scanf("%d",&d3);
	printf("d4:");
	scanf("%d",&d4);
	printf("d5:");
	scanf("%d",&d5);
	printf("d6:");
	scanf("%d",&d6);
	printf("Enter the values of weight of paths as instructed!!");
	printf("\nw1:");
	scanf("%d",&w1);
	printf("w2:");
	scanf("%d",&w2);
	printf("w3:");
	scanf("%d",&w3);
	printf("w4:");
	scanf("%d",&w4);
	printf("w5:");
	scanf("%d",&w5);
	printf("w6:");
	scanf("%d",&w6);

	//Dijikstra Algorithm Essentials
	clrscr();
	printf("\nDijikstra algorithm(according to lenght of the paths you entered)!!\n");
	dijikstra(node1,node2,d1,d2,d3,d4,d5,d6);

	//Ford-fulkerson Algorithm Essentials
	printf("\n\n\nFord-fulkerson algorithm(according to the weights you entered)!!\n");
	fordFulkerson(node1,node2,w1,w2,w3,w4,w5,w6);
	getch();
}

int minLen1(int k1,int k2,int k3)
{
	if(k1<k2&&k1<k3)
	{
		return k1;
	}
	else
	{
		if(k2<k1&&k2<k3)
		return k2;
		else
		{
			if(k3<k1&&k3<k2)
			return k3;
		}
	}
}


int minLen(int k1,int k2)
{
	if(k1<k2)
	return k1;
	else
	return k2;
}

int fordFulkerson(int source,int sink,int w1,int w2,int w3,int w4,int w5,int w6)
{
	int totalFlow=0,w4Rev=w4,bottleNeck1,bottleNeck2,bottleNeck4,bottleNeck5;
	//Working on model 1
	bottleNeck1=minLen(w1,w6);
	w1-=bottleNeck1;
	w6-=bottleNeck1;
	totalFlow+=bottleNeck1;

	//Working on model 2
	bottleNeck2=minLen1(w1,w4,w5);
	w1-=bottleNeck2;
	w4-=bottleNeck2;
	w5-=bottleNeck2;
	totalFlow+=bottleNeck2;
	w4Rev-=w4;

	//Working on model 3
	totalFlow+=w2;

	//Working on model 4
	bottleNeck4=minLen1(w3,w4Rev,w6);
	w3-=bottleNeck4;
	w4Rev-=bottleNeck4;
	w6-=bottleNeck4;
	totalFlow+=bottleNeck4;

	//Working on model 5
	bottleNeck5=minLen(w3,w5);
	w3-=bottleNeck5;
	w5-=bottleNeck5;
	totalFlow+=bottleNeck5;

	printf("The paths used for the flow are:");
	if(bottleNeck1!=0)
	printf("\nd1,d6.");
	if(bottleNeck2!=0)
	printf("\nd1,d4,d5.");
	if(w2!=0)
	printf("\nd2.");
	if(bottleNeck4!=0)
	printf("\nd3,d4,d6.");
	if(bottleNeck5!=0)
	printf("\nd3,d5.");
	printf("\nTotal flow throughout the network is:%d",totalFlow);
}

int dijikstra(int source1,int sink1,int d1,int d2,int d3,int d4,int d5,int d6)
{
	int n=0,i=0,select,pathSelected[6],pathLength=0,t1=0,choice,nedges,count;
	char snode,enode,source,sink,curr_node,ch1,lenedge;
	char path[6][2],arrayNodeData[100][4],route[100];
	int arrayLengthData[100],minlen,index,t_length=0,rind=0;
	FILE *fp,*fp1;


	printf("\nProceeding for your distances with either manual entry or the static model!");
	printf("\n1.Manual Entry\n[Invalid choice makes you out]:");
	scanf("%d",&select);


	if(select==1)
	{
		fp=fopen("Update1.txt","w");
		printf("\nEnter the number of edges in your model:");
		scanf("%d",&nedges);

		printf("\nEnter the source node:");
		source=getche();
		route[rind]=source;
		rind++;
		printf("\nEnter the sink node:");
		sink=getche();


		//Edges have been entered!!
		for(count=0;count<nedges;count++)
		{
			printf("\nEnter start node %d:",count+1);
			snode=getche();
			printf("\nEnter end node %d:",count+1);
			enode=getche();
			printf("\nEnter edge length:");
			lenedge=getche();
			fprintf(fp,"%c,%c,%c.",snode,enode,lenedge);
		}
		fclose(fp);

		fp1=fopen("Update1.txt","r");

		i=0;
		//Read data from file and peform dijikstra algorithm on that read elements
		while((ch1=getc(fp1))!=EOF)
		{
			//t1 is used to get Username
			if((t1==0)&&(ch1!=','))
			arrayNodeData[i][0]=ch1;
			else if(t1==0&&ch1==',')
			t1++;
			else if(t1==1&&(ch1!=','))
			arrayNodeData[i][1]=ch1;
			else if(t1==1&&ch1==',')
			t1++;
			else if(t1==2&&ch1!='.')
			arrayNodeData[i][2]=ch1;
			else if(ch1=='.')
			{
				t1=0;
				i++;
				arrayNodeData[i][3]='\0';
			}
		}
		fclose(fp1);
		/*for(i=0;i<nedges;i++)
		{
			printf("\n%c,%c,%c.",arrayNodeData[i][0],arrayNodeData[i][1],arrayNodeData[i][2]);
		}*/
		//Data stored to arrayNodeData
		//Let's apply Dijikstra
		curr_node=source;
		while(curr_node!=sink)
		{
			for(i=0;i<nedges;i++)
			{
				if(arrayNodeData[i][0]==curr_node)
				{
					minlen=(int)arrayNodeData[i][2];
					index=i;
					goto t;
				}
				//One length is achieved
			}
			t:
			for(i=0;i<nedges;i++)
			{
				//Comparig the achieved length with all the other legths
				//which has same startig node as in it
				if(arrayNodeData[i][0]==curr_node)
				{
					if((int)arrayNodeData[i][2]<minlen)
					{
						minlen=(int)arrayNodeData[i][2];
						index=i;
					}
				}
			}
			t_length+=(int)(arrayNodeData[index][2]-'0');
			curr_node=arrayNodeData[index][1];
			route[rind]=curr_node;
			rind++;
		}
		route[rind]='\0';

		printf("\nThe route travelled is:");
		for(i=0;i<rind;i++)
		printf("%c  ",route[i]);
		printf("\nTotal length covered is %d.",t_length);
		return t_length;
	}
	else if(select==2)
	     {
		pathSelected[0]=minLen1(d1,d2,d3);
		if(pathSelected[0]==d1)
		{
			pathLength+=d1;
			strcpy(path[0],"d1");
			n++;
			pathSelected[1]=minLen(d6,d4);
			if(pathSelected[1]==d6)
			{
				pathLength+=d6;
				strcpy(path[1],"d6");
				n++;
			}
			else
			{
				pathLength+=d4;
				strcpy(path[1],"d4");
				n++;
				pathLength+=d5;
				strcpy(path[2],"d5");
				n++;
			}
		}
		else if(pathSelected[0]==d2)
		{
			pathLength+=d2;
			strcpy(path[0],"d2");
			n++;
		}
		else
		{
			pathLength+=d3;
			strcpy(path[0],"d3");
			n++;
			pathSelected[1]=minLen(d4,d5);
			if(pathSelected[1]==d4)
			{
				pathLength+=d4;
				strcpy(path[1],"d4");
				n++;
				pathLength+=d6;
				strcpy(path[2],"d6");
				n++;
			}
			else
			{
				pathLength+=d5;
				strcpy(path[1],"d5");
				n++;
			}
		}

		if(source1>=1&&source1<=3&&sink1>=4&&sink1<=5)
		{
			char node1[10],node2[10];
			switch(source)
			{
				case 1:strcpy(node1,"ES1");
				break;
				case 2:strcpy(node1,"ES2");
				break;
				case 3:strcpy(node1,"ES3");
				break;
				default:printf("INVALID CHOICE");
				exit(0);
			}

			switch(sink)
			{
				case 4:strcpy(node2,"REFINERY1");
				break;
				case 5:strcpy(node2,"REFINERY2");
				break;
				default:printf("INVALID CHOICE");
				exit(0);
			}
			printf("Flow between %s(Source) & %s(Sink) will be done using:\n",node1,node2);
		}

		printf("%s.",path[i]);
		printf("\nThe total length covered is:%d",pathLength);
		return pathLength;
	    }
	    else
	    {
		printf("INVALID CHOICE");
		exit(0);
	    }
}

void startPage()
{
	//Page 1(Starting Page)

	char ch;


	clrscr();
	printf("Dear user, please Login/SignUp.\n");
	printf("1. Login\n2. SignUp\n");
	printf("Please enter your choice!\nInvalid choice will make you out of the program:");
	scanf("%c",&ch);
	if(ch=='1')
	loginPage();   //Directed to the Login Page
	else if(ch=='2')
	signUp();      //Directed to the Signup Page
	else
	{
	    clrscr();
	    printf("Invalid choice!!\n");//Terminating the Application here
	    getch();
	    exit(0);
	}
}

void loginPage()
{
	//Page 2.1(Login Page)
	char username[40],password[40],testing,ch;
	char arrayUsername[40][100],arrayPassword[40][100],ch1;
	int t1=0,i=0,j=0,k=0,n=0;
	FILE *fp;

	//File Handling concept is used to authenticate the users who tries to Login
	fp=fopen("ValidUsers.txt","r");
	while((ch1=getc(fp))!=EOF)
	{
	//t1 is used to get Username
	if((t1!=1)&&(ch1!=':'))
	{
		arrayUsername[i][j]=ch1;
		j++;
	}
	else if(ch1==':')
	{
		t1++;
		arrayUsername[i][j]='\0';
	}

	if((t1==1)&&(ch1!='.')&&(ch1!=':'))
	{
		arrayPassword[i][k]=ch1;
		k++;
	}
	else if(ch1=='.')
	{
		arrayPassword[i][k]='\0';
		i++;
		t1=0;
		j=0;
		k=0;
		n++;
	}
}
	clrscr();
	printf("Username:");
	scanf("%s",&username);
	printf("Password:");
	i=0;
	while (1) {
		if (i < 0) {
		i = 0;
	}
	ch = getch();

	if (ch == 13)
	 break;
	if (ch == 8) /*ASCII value of BACKSPACE*/
	{
	 putch('b');
	 putch(NULL);
	 putch('b');
	 i--;
	 continue;
	}

	password[i++] = ch;
	ch = '*';
	putch(ch);
	}

	password[i] = '\0';

	system("cls");

	n=i;
	//Comparing username of users and then validating
	for(i=0;i<=n;i++)
	{
		if(strcmp(arrayUsername[i],username)==0)
		{
			//compare for password
			if(strcmp(arrayPassword[i],password)==0)
			{
				//Page 2.1.1(Splash Screen for 3 seconds)
				printf("Logging you in, wait....");
				delay(3);
				frontPage();
			}
			else
			{
				printf("Invalid username or password!!");
				getch();
				exit(0);
			}
		}
	}
}


void signUp()
{
	//Page 2.2(SignUp)
	int i=0,j=0,k=0,t1=0,n=0,choice;
	char ch,ch1,existingUsers[100][40],existPass[100][40],name[40],mobile[10],emailId[40],city[40],password[40],confPassword[40];
	FILE *fp;
	clrscr();
	fp=fopen("ValidUsers.txt","a+");
	printf("Dear User!!\n");

	while((ch1=getc(fp))!=EOF)
	{
	//t1 is used to get Username
	if((t1!=1)&&(ch1!=':'))
	{
		existingUsers[i][j]=ch1;
		j++;
	}
	else if(ch1==':')
	{
		t1++;
		existingUsers[i][j]='\0';
	}

	if((t1==1)&&(ch1!='.')&&(ch1!=':'))
	{
		existPass[i][k]=ch1;
		k++;
	}
	else if(ch1=='.')
	{
		existPass[i][k]='\0';
		i++;
		t1=0;
		j=0;
		k=0;
		n++;
	}
}

	X:
	printf("Enter a username:");
	scanf("%s",&emailId);
	fprintf(fp,"%s:",emailId);
	for(i=0;i<n;i++)
	{
		if(strcmp(existingUsers[i],emailId)==0)
		{
			printf("Username already exists!!");
			printf("Would you like to retry\n1.Yes\n2.No\n");
			scanf("%d",&choice);
			if(choice==1)
			goto X;
			else
			{
				clrscr();
				printf("\nThank You!!");
			}
			getch();
			exit(0);
		}
	}
	system("cls");
	//Uploading email-id as username to the file named "ValidUsers.txt".

	//Page 2.2.1(Password Entry Page)
	printf("Enter Password:");

	i=0;
	while (1) {
		if (i < 0) {
		i = 0;
	}
	ch = getch();

	if (ch == 13)
	 break;
	if (ch == 8) /*ASCII value of BACKSPACE*/
	{
	 putch('b');
	 putch(NULL);
	 putch('b');
	 i--;
	 continue;
	}

	password[i++] = ch;
	ch = '*';
	putch(ch);
	}

	password[i] = '\0';


	printf("\nConfirm Password:");

	i=0;
	while (1) {
		if (i < 0) {
		i = 0;
	}
	ch = getch();

	if (ch == 13)
	 break;
	if (ch == 8) /*ASCII value of BACKSPACE*/
	{
	 putch('b');
	 putch(NULL);
	 putch('b');
	 i--;
	 continue;
	}

	confPassword[i++] = ch;
	ch = '*';
	putch(ch);
	}

	confPassword[i] = '\0';


	if(strcmp(password,confPassword)==0)
	{
		//means the password is matching so upload the password to our file named "ValidUsers.txt"
		fprintf(fp,"%s.",password);
	}
	fclose(fp);
	system("cls");

	//Page 2.2.2(Splash Screen with certain information for 3 seconds)
	printf("Dear User! For future reference..\n");
	printf("Your Username is your username and your Password is the one you entered in the previous page");
	printf("\nThank You for Signing Up!");
	printf("\n\n\n\nTaking you to the Main Page....");
	delay(3);
	frontPage();
}

int main()
{
	startPage();
	return 0;
}