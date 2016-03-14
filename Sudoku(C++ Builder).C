#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>

#define ENTER 0x0d
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define ESC 0x1b
#define ListLeft 10
#define ListRight 54
#define ListTop 1
#define ListBottom 27

int PosX;
int PosY;
int CurrPage;
int level;
int NumList[3][9][9]={0};
int LoadPos;
int Load[5];
int Pos1,Pos4,Pos5,Pos7,Pos8;



int Las_vegas(int completed[9][9],int n);
int Judge(int array[9][9],int i,int j,int current);
int solve(int completed[9][9],int flag[][2],int n);
int dig(int uncompleted[9][9],int level);
void next(int *p1,int *p2);
int initialize(void);
void save(void);
int check(void);
void state_1(void);
void plot_1(void);
void fill_1(int flag);
void state_2(void);
void fill_2(int flag);
int state_3(int flag);
void fill_3(int flag);
void state_4(void);
void fill_4(int flag);
void state_5(void);
void fill_5(int flag);
void state_6(int flag);
void Page(int pagenum);
void fill_6(int flag);
int state_7(void);
void fill_7(int flag);
int state_8(void);
void fill_8(int flag);
void state_9(int flag);

int Las_vegas(int completed[9][9],int n){
  int i,j,m,temp;
  int a,b;
  int flag[81][2];
  for(i=0;i<9;i++)
    for(j=0;j<9;j++)
      completed[i][j]=0;
  randomize();
  for(m=0;m<n;){
    i=rand()%9;
    j=rand()%9;
    temp=rand()%9+1;
    if(completed[i][j]==0)
    {
      if(!Judge(completed,i,j,temp))continue;
      completed[i][j]=temp;
      m++;
    }
  }
  m=0;
  a=rand()%9;
  b=rand()%9;
  for(i=a;i<9+a;i++){
    for(j=b;j<9+b;j++){
      if(completed[i%9][j%9]==0){
        flag[m][0]=i%9;
        flag[m][1]=j%9;
        m++;
      }
    }
  }
  return solve(completed,flag,m)==1;
}

int Judge(int array[9][9],int i,int j,int current){
  int m,n;
  for(n=0;n<9;n++){
    if(n==j)continue;
    if(array[i][n]==current)
      return 0;
  }
  for(m=0;m<9;m++){
    if(m==i)continue;
    if(array[m][j]==current)
	  return 0;
  }
  for(m=i/3*3;m<(i/3+1)*3;m++){
    for(n=j/3*3;n<(j/3+1)*3;n++){
      if(m==i&&n==j)continue;
      if(array[m][n]==current)
        return 0;
    }
  }
  return 1;
}

int solve(int completed[9][9],int flag[][2],int n){
  int i,temp;
  long count;
  for(i=0,count=0;i<n&&count<1000000;){
    if(i<0)break;
    if((temp=completed[flag[i][0]][flag[i][1]])==0){
      temp=1;
      if(Judge(completed,flag[i][0],flag[i][1],temp)){
        completed[flag[i][0]][flag[i][1]]=temp;
        i++;
        continue;
      }
    }
    temp++;
    for(;temp<10;){
      if(Judge(completed,flag[i][0],flag[i][1],temp)){
        completed[flag[i][0]][flag[i][1]]=temp;
        i++;
        break;
      }
      temp++;
    }
    if(temp==10){
      completed[flag[i][0]][flag[i][1]]=0;
      i--;
    }
  count++;
  }
  if(i==n&&count<1000000)return 1;
  else if(i<0&&count<1000000)return 0;
  else return 2;
}
int dig(int uncompleted[9][9],int level){
  int flag[81][2],count_line[2][9]={0},num[2];
  int i,j,k,count,temp,n,t,m;
  randomize();
  i=rand()%9;
  j=rand()%9;
  num[0]=rand()%4+(level==1?31:(level==2?36:(level==3?40:(level==4?48:52))));
  num[1]=level==1?4:(level<=3?5:(level<=4?6:7));
  for(count=0,m=0;count<num[0]&&m<200;){
    m++;
    if(count_line[0][i]==num[1]||count_line[1][j]==num[1]||uncompleted[i][j]==0){
	  next(&i,&j);
      continue;
    }
    if(count==0){
      uncompleted[i][j]=0;
      flag[count][0]=i;
      flag[count][1]=j;
      count++;
      count_line[0][i]++;
      count_line[1][j]++;
      next(&i,&j);
      continue;
    }
    temp=uncompleted[i][j];
	for(k=1;k<=9;k++){
	  if(k==temp||!Judge(uncompleted,i,j,k))continue;
      uncompleted[i][j]=k;
      t=solve(uncompleted,flag,count);
      for(n=0;n<count;n++)
         uncompleted[flag[n][0]][flag[n][1]]=0;
      if(t==2)
        return 0;
      if(t==1)break;
    }
    if(k==10){
      uncompleted[i][j]=0;
	  flag[count][0]=i;
      flag[count][1]=j;
	  count++;
      count_line[0][i]++;
      count_line[1][j]++;
    }
    else uncompleted[i][j]=temp;
	  next(&i,&j);
  }
  if(count<num[0])return 0;
  return 1;
}

void next(int *p1,int *p2){
  ++(*p2)>8?(*p1)++:1;*p1=*p1%9;*p2=*p2%9;
}

int initialize(void){
  FILE *fp;
  int data1[2][9][9];
  int i,j,k,n;
  fp=fopen("data1","wb");
  if(fp==NULL)return 0;
  for(k=1;k<=5;){
    while(!Las_vegas(data1[0],11));
    n=0;
    do{
      for(i=0;i<9;i++)
        for(j=0;j<9;j++)
          data1[1][i][j]=data1[0][i][j];
      n++;
      if(n>40)break;
    }while(!dig(data1[1],k));
    if(n<=40){
      k++;
      for(i=0;i<9;i++){
        for(j=0;j<9;j++){
          fwrite(*(data1[0]+i)+j,sizeof(int),1,fp);
          if(ferror(fp))return 0;
        }
      }
      for(i=0;i<9;i++){
        for(j=0;j<9;j++){
          fwrite(*(data1[1]+i)+j,sizeof(int),1,fp);
          if(ferror(fp))return 0;
        }
      }
    }
  }
  fclose(fp);
  fp=fopen("data2","wb");
  if(fp==NULL)return 0;
  n=0;
  for(k=1;k<=5;k++){
    fwrite(&n,sizeof(int),1,fp);
    if(ferror(fp))return 0;
  }
  fclose(fp);
  fp=fopen("data3","wb");
  if(fp==NULL)return 0;
  fclose(fp);
  return 1;
}


void save(void){
  FILE *fp;
  int i,j,k;
  Load[LoadPos-1]=level;
  fp=fopen("data2","rb+");
  fseek(fp,(LoadPos-1)*sizeof(int),0);
  fwrite(Load+LoadPos-1,sizeof(int),1,fp);
  fclose(fp);
  fp=fopen("data3","rb+");
  fseek(fp,243*sizeof(int)*(LoadPos-1),0);
  for(i=0;i<3;i++)
    for(j=0;j<9;j++)
      for(k=0;k<9;k++)
        fwrite(*(NumList[i]+j)+k,sizeof(int),1,fp);
  fclose(fp);
}
int check(void){
  int i,j;
  for(i=0;i<9;i++)
    for(j=0;j<9;j++)
      if(NumList[0][i][j]!=NumList[2][i][j])return 0;
  return 1;
}
void state_1(void){
  char ch;
  Pos1=1;
  plot_1();
  while(1){
	fill_1(1);
    if((ch=getch())==0)
	   ch=getch();
	switch(ch){
    case UP:if(Pos1>=2)fill_1(0),Pos1--;break;
    case DOWN:if(Pos1<=3)fill_1(0),Pos1++;break;
    case ENTER:switch(Pos1){
               case 1:state_2();plot_1();break;
               case 2:state_3(1);plot_1();break;
               case 3:state_4();plot_1();break;
               case 4:state_5();plot_1();break;
               }break;
    }
  }
}

void plot_1(void){
  window(1,1,80,25);
  textbackground(WHITE);
  clrscr();
  window(21,2,60,23);
  textbackground(GREEN);
  textcolor(WHITE);
  clrscr();
  gotoxy(18,4);
  cprintf("Sudoku");
  textcolor(WHITE);
  gotoxy(16,10);
  cprintf("Start game");
  gotoxy(17,13);
  cprintf("Continue");
  gotoxy(18,16);
  cprintf("Reset");
  gotoxy(19,19);
  cprintf("Exit");
}

void fill_1(int flag){
  window(35,Pos1*3+7,46,Pos1*3+9);
  textbackground(flag?WHITE:GREEN);
  textcolor(flag?BLACK:WHITE);
  clrscr();
  switch(Pos1){
  case 1:gotoxy(2,2);cprintf("Start game");break;
  case 2:gotoxy(3,2);cprintf("Continue");break;
  case 3:gotoxy(4,2);cprintf("Reset");break;
  case 4:gotoxy(5,2);cprintf("Exit");break;
  }
  window(80,25,80,25);
  textbackground(WHITE);
  clrscr();
}
void state_2(void){
  int i;
  char ch;
  level=1;
  window(31,7,50,23);
  textbackground(BROWN);
  textcolor(WHITE);
  clrscr();
  for(i=1;i<=5;i++){
    gotoxy(7,3*i);
    cprintf("Level  %d",i);
  }
  while(1){
	fill_2(1);
	if((ch=getch())==0)
	   ch=getch();
    switch(ch){
    case UP:if(level>=2)fill_2(0),level--;break;
    case DOWN:if(level<=4)fill_2(0),level++;break;
    case ENTER:switch(level){
               case 1:
               case 2:
               case 3:
               case 4:
               case 5:state_6(1);return;
               }break;
    case ESC:return;
    }
  }
}

void fill_2(int flag){
  window(35,level*3+5,46,level*3+7);
  textbackground(flag?CYAN:BROWN);
  textcolor(flag?BLACK:WHITE);
  clrscr();
  gotoxy(3,2);
  cprintf("Level  %d",level);
  window(80,25,80,25);
  textbackground(WHITE);
  clrscr();
}
int state_3(int flag){
  int i;
  char ch;
  LoadPos=1;
  window(31,7,50,23);
  textbackground(BROWN);
  textcolor(WHITE);
  clrscr();
  for(i=1;i<=5;i++){
    gotoxy(6,3*i);
    if(Load[i-1]==0)
      cprintf("%d  Empty",i);
    else
      cprintf("%d  Level %d",i,Load[i-1]);
  }
  while(1){
	fill_3(1);
	if((ch=getch())==0)
	   ch=getch();
	switch(ch){
    case UP:if(LoadPos>=2)fill_3(0),LoadPos--;break;
    case DOWN:if(LoadPos<=4)fill_3(0),LoadPos++;break;
    case ENTER:switch(LoadPos){
               case 1:
               case 2:
               case 3:
               case 4:
               case 5:if(flag==1&&Load[LoadPos-1]){state_6(2);return;}
                      if(flag==2&&Load[LoadPos-1])return state_8();
                      if(flag==2&&!Load[LoadPos-1]){for(;Load[LoadPos-1]==0&&LoadPos>=2;LoadPos--);if(Load[LoadPos-1]!=0)LoadPos++;save();return 1;}
               }break;
    case ESC:return 0;
    }
  }
}

void fill_3(int flag){
  window(34,LoadPos*3+5,47,LoadPos*3+7);
  textbackground(flag?CYAN:BROWN);
  textcolor(flag?BLACK:WHITE);
  clrscr();
  gotoxy(3,2);
  if(Load[LoadPos-1]==0)
    cprintf("%d  Empty",LoadPos);
  else
    cprintf("%d  Level %d",LoadPos,Load[LoadPos-1]);
  window(80,25,80,25);
  textbackground(WHITE);
  clrscr();
}
void state_4(void){
  char ch;
  Pos4=2;
  window(26,12,55,19);
  textbackground(YELLOW);
  textcolor(WHITE);
  clrscr();
  gotoxy(8,2);
  cprintf("Are you sure you");
  gotoxy(6,4);
  cprintf("want to reset game ?");
  gotoxy(9,7);
  cprintf("Yes");
  gotoxy(20,7);
  cprintf("No");
  while(1){
	fill_4(1);
	if((ch=getch())==0)
	   ch=getch();
	switch(ch){
    case LEFT:if(Pos4==2)fill_4(0),Pos4--;break;
    case RIGHT:if(Pos4==1)fill_4(0),Pos4++;break;
    case ENTER:if(Pos4==1){initialize();Load[0]=Load[1]=Load[2]=Load[3]=Load[4]=0;}
    case ESC:return;
    }
  }
}

void fill_4(int flag){
  if(Pos4==1)
    window(33,18,37,18);
  else
    window(45,18,49,18);
  textbackground(flag?WHITE:YELLOW);
  textcolor(flag?BLACK:WHITE);
  clrscr();
  gotoxy(2,1);
  if(Pos4==1)
    cprintf("Yes");
  else
    cprintf("No");
  window(80,25,80,25);
  textbackground(WHITE);
  clrscr();
}

void state_5(void){
  char ch;
  Pos5=2;
  window(26,12,55,19);
  textbackground(YELLOW);
  textcolor(WHITE);
  clrscr();
  gotoxy(8,2);
  cprintf("Are you sure you");
  gotoxy(9,4);
  cprintf("want to quit ?");
  gotoxy(9,7);
  cprintf("Yes");
  gotoxy(20,7);
  cprintf("No");
  while(1){
	fill_5(1);
	if((ch=getch())==0)
	   ch=getch();
    switch(ch){
    case LEFT:if(Pos5==2)fill_5(0),Pos5--;break;
    case RIGHT:if(Pos5==1)fill_5(0),Pos5++;break;
    case ENTER:if(Pos5==1)exit(1);
    case ESC:return;
    }
  }
}

void fill_5(int flag){
  if(Pos5==1)
    window(33,18,37,18);
  else
    window(45,18,49,18);
  textbackground(flag?WHITE:YELLOW);
  textcolor(flag?BLACK:WHITE);
  clrscr();
  gotoxy(2,1);
  if(Pos5==1)
    cprintf("Yes");
  else
    cprintf("No");
  window(80,25,80,25);
  textbackground(WHITE);
  clrscr();
}

void state_6(int flag){
  char ch;
  int i,j,k;
  FILE *fp;
  if(flag==1){
	fp=fopen("data1","rb");
	fseek(fp,162*sizeof(int)*(level-1),0);
	for(i=0;i<2;i++)
	  for(j=0;j<9;j++)
		for(k=0;k<9;k++)
		  fread(*(NumList[i]+j)+k,sizeof(int),1,fp);
	for(i=0;i<9;i++)
	  for(j=0;j<9;j++)
		NumList[2][i][j]=NumList[1][i][j];
  }
  else{
    level=Load[LoadPos-1];
	fp=fopen("data3","rb");
	fseek(fp,243*sizeof(int)*(LoadPos-1),0);
	for(i=0;i<3;i++)
	  for(j=0;j<9;j++)
		for(k=0;k<9;k++)
		  fread(*(NumList[i]+j)+k,sizeof(int),1,fp);
  }
  CurrPage=1;
  Page(CurrPage);
  PosX=1;
  PosY=1;
  while(1){
	fill_6(1);
	if((ch=getch())==0)
	   ch=getch();
	switch(ch){
	case LEFT:if(PosX>=2)fill_6(0),PosX--;break;
    case RIGHT:if(PosX<=8)fill_6(0),PosX++;break;
    case UP:fill_6(0);
            if(CurrPage==2&&PosY==2)CurrPage=1,Page(CurrPage),PosY--;
            else if(PosY>=2)PosY--;break;
    case DOWN:fill_6(0);
              if(CurrPage==1&&PosY==8)CurrPage=2,Page(CurrPage),PosY++;
              else if(PosY<=8)PosY++;break;
	case 49:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=1;break;
	case 50:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=2;break;
	case 51:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=3;break;
	case 52:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=4;break;
	case 53:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=5;break;
	case 54:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=6;break;
	case 55:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=7;break;
	case 56:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=8;break;
	case 57:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=9;break;
	case 48:if(NumList[1][PosY-1][PosX-1]==0)NumList[2][PosY-1][PosX-1]=0;break;
    case ENTER:if(check()){state_9(1);return;}state_9(2);Page(CurrPage);break;
    case ESC:if(state_7())return;Page(CurrPage);
    }
  }
}
void Page(int pagenum){
  int i,j,t;
  window(1,1,80,25);
  textbackground(WHITE);
  clrscr();
  window(ListLeft-2,1,ListLeft-1,25);
  textcolor(BLACK);
  clrscr();
  for(i=1;i<=8;i++){
    gotoxy(1,i*3-(pagenum==1));
    cprintf("%d",i+(pagenum==2));
  }
  for(i=0;i<8;i++){
    for(j=0;j<9;j++){
      window(ListLeft+j*5,(pagenum==2)+1+i*3,ListLeft+4+j*5,(pagenum==2)+3+i*3);
      if(i+(pagenum==2)>=3&&i+(pagenum==2)<=5&&!(j>=3&&j<=5)||!(i+(pagenum==2)>=3&&i+(pagenum==2)<=5)&&j>=3&&j<=5)
        textbackground(GREEN);
	  else
        textbackground(CYAN);
      textcolor(NumList[1][i+(pagenum==2)][j]==0?RED:WHITE);
      clrscr();
      gotoxy(3,2);
      cprintf("%c",(t=NumList[2][i+(pagenum==2)][j])==0?32:t+'0');
    }
  }
  window(ListRight+1,1,80,25);
  textbackground(WHITE);
  textcolor(BLUE);
  clrscr();
  gotoxy(8,5);
  cprintf("Up:      \x18");
  gotoxy(8,7);
  cprintf("Down:    \x19");
  gotoxy(8,9);
  cprintf("LEFT:    \x1B");
  gotoxy(8,11);
  cprintf("Right:   \x1A");
  gotoxy(8,13);
  cprintf("Fill:    1-9");
  gotoxy(8,15);
  cprintf("Delete:  0");
  gotoxy(8,17);
  cprintf("Check:   Enter");
  gotoxy(8,19);
  cprintf("Quit:    Esc");
  for(j=0;j<9;j++)
    switch(pagenum){
    case 1:window(ListLeft+j*5,25,ListLeft+4+j*5,25);textbackground(j>=3&&j<=5?GREEN:CYAN);clrscr();break;
    case 2:window(ListLeft+j*5,1,ListLeft+4+j*5,1);textbackground(j>=3&&j<=5?GREEN:CYAN);clrscr();break;
    }
  window(80,25,80,25);
}


void fill_6(int flag){
  int t;
  window((PosX-1)*5+ListLeft,(PosY-1)*3+1-(CurrPage==2)*2,PosX*5+ListLeft-1,PosY*3-(CurrPage==2)*2);
  textbackground(flag?BROWN:(PosX>=4&&PosX<=6&&!(PosY>=4&&PosY<=6)||!(PosX>=4&&PosX<=6)&&PosY>=4&&PosY<=6)?GREEN:CYAN);
  textcolor(NumList[1][PosY-1][PosX-1]==0?RED:(flag?BLACK:WHITE));
  clrscr();
  gotoxy(3,2);
  cprintf("%c",(t=NumList[2][PosY-1][PosX-1])==0?32:t+'0');
  window(80,25,80,25);
  textbackground(WHITE);
  clrscr();
}

int state_7(void){
  char ch;
  Pos7=2;
  window(26,12,55,19);
  textbackground(YELLOW);
  textcolor(WHITE);
  clrscr();
  gotoxy(11,2);
  cprintf("Do you want");
  gotoxy(10,4);
  cprintf("to save it ?");
  gotoxy(9,7);
  cprintf("Yes");
  gotoxy(20,7);
  cprintf("No");
  while(1){
	fill_7(1);
	if((ch=getch())==0)
	   ch=getch();
	switch(ch){
	case LEFT:if(Pos7==2)fill_7(0),Pos7--;break;
	case RIGHT:if(Pos7==1)fill_7(0),Pos7++;break;
    case ENTER:if(Pos7==1){Page(CurrPage);return state_3(2);}return 1;
    case ESC:return 0;
    }
  }
}

void fill_7(int flag){
  if(Pos7==1)
    window(33,18,37,18);
  else
    window(45,18,49,18);
  textbackground(flag?WHITE:YELLOW);
  textcolor(flag?BLACK:WHITE);
  clrscr();
  gotoxy(2,1);
  if(Pos7==1)
    cprintf("Yes");
  else
    cprintf("No");
  window(80,25,80,25);
  textbackground(WHITE);
  clrscr();
}

int state_8(void){
  char ch;
  Pos8=2;
  window(26,12,55,19);
  textbackground(YELLOW);
  textcolor(WHITE);
  clrscr();
  gotoxy(8,2);
  cprintf("Are you sure you");
  gotoxy(7,4);
  cprintf("want to cover it ?");
  gotoxy(9,7);
  cprintf("Yes");
  gotoxy(20,7);
  cprintf("No");
  while(1){
	fill_8(1);
	if((ch=getch())==0)
	   ch=getch();
	switch(ch){
	case LEFT:if(Pos8==2)fill_8(0),Pos8--;break;
	case RIGHT:if(Pos8==1)fill_8(0),Pos8++;break;
    case ENTER:if(Pos8==1){save();return 1;}
    case ESC:return 0;
    }
  }
}

void fill_8(int flag){
  if(Pos8==1)
    window(33,18,37,18);
  else
    window(45,18,49,18);
  textbackground(flag?WHITE:YELLOW);
  textcolor(flag?BLACK:WHITE);
  clrscr();
  gotoxy(2,1);
  if(Pos8==1)
    cprintf("Yes");
  else
    cprintf("No");
  window(80,25,80,25);
  textbackground(WHITE);
  clrscr();
}

void state_9(int flag){
  window(31,11,50,17);
  textbackground(YELLOW);
  textcolor(WHITE);
  clrscr();
  if(flag==1){
    gotoxy(6,3);
    cprintf("Succeeded !");
  }
  else{
    gotoxy(7,3);
    cprintf("Failed !");
  }
  getch();
}

int main(void){
  FILE *fp1,*fp2;
  int i;
  textmode(C80);
  textbackground(WHITE);
  clrscr();
  window(21,6,60,20);
  textbackground(GREEN);
  textcolor(WHITE);
  clrscr();
  gotoxy(18,4);
  cprintf("Sudoku");
  fp1=fopen("data1","rb");
  if(fp1==NULL){
    textattr(WHITE+(GREEN<<4));
    gotoxy(13,11);
    cprintf("Initializing...");
    if(!initialize()){
      gotoxy(13,10);
      cprintf("Initialization failed!");
      gotoxy(10,12);
      cprintf("Press any key to quit");
      getch();
      return 0;
    }
    gotoxy(13,11);
    delline();
  }
  fclose(fp1);
  textattr(WHITE+(GREEN<<4));
  gotoxy(13,10);
  cprintf("Loading...      ");
  fp2=fopen("data2","rb");
  for(i=0;i<5;i++)
    fread(Load+i,sizeof(int),1,fp2);
  fclose(fp2);
  delline();
  gotoxy(10,12);
  cprintf("Press any key to start");
  getch();
  state_1();
  return 0;
}
