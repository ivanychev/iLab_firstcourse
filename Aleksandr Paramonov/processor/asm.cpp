//0-exit
//1-push   //0-number 1-register
//2-pop
//4-add
//3-ja
//5-mul
//6-jmp
//7-sqrt
//8-div
//10-crash
//11-call
//12-ret
#include <stdlib.h>
#include <stdio.h>
const double FAIL=666.666;
int labels[10];
int main()
{

    FILE *F;
    FILE *F2;
    int i,j,commandnumber=0;
    double forpush;
    double forpop=999;
    char command[7];
    //char* command=new char;
    char c;


    for(int a=0; a<2; a++)
    {
        commandnumber=0;
        F=fopen("1.txt","r");
        F2=fopen("2.txt","w");
        do
        {
            forpush=FAIL;
            command[0]='\0';
            command[1]='\0';
            command[2]='\0';
            command[3]='\0';
            command[4]='\0';
            command[5]='\0';
            command[6]='\0';
            for (i=0; i<7; i++)
            {

                //scanf("%c",&c);
                c=getc(F);
                // if (c==':'){command[i]=c;}
                //  if (c==':')break;
                command[i]=c;
                if((c!='\n')&&(c!=' '))
                {

                }
                else break;

                if (c==':')break;

            }


            if(command[0]==':')
            {
                fscanf(F,"%lg",&forpush);

                labels[(int)forpush]=commandnumber;

                //  fprintf(F2,":%lg  %d\n",forpush,commandnumber);//commandnumber--;commandnumber--;
            }

            if(command[0]=='p'&&command[1]=='u'&&command[2]=='s'&&command[3]=='h')
            {
                commandnumber+=1;
                if(fscanf(F,"%lg",&forpush)==0)fscanf(F,"%c",&c);
                if (c>='a'&&c<='d')fprintf(F2,"1 1 %c\n",c);  //if second argument=1 then we sent register,otherway we send number
                if (forpush!=FAIL)fprintf(F2,"1 0 %lg\n",forpush);

            }



            if(command[0]=='a'&&command[1]=='d'&&command[2]=='d')
            {
                commandnumber+=1;
                fprintf(F2,"4\n");
            }
            if(command[0]=='m'&&command[1]=='u'&&command[2]=='l')
            {
                commandnumber+=1;
                fprintf(F2,"5\n");
            }
            if(command[0]=='d'&&command[1]=='i'&&command[2]=='v')
            {
                commandnumber+=1;
                fprintf(F2,"8\n");
            }
            if(command[0]=='r'&&command[1]=='e'&&command[2]=='t')
            {
                commandnumber+=1;
                fprintf(F2,"12\n");
            }
            if(command[0]=='s'&&command[1]=='q'&&command[2]=='r'&&command[3]=='t')
            {
                commandnumber+=1;
                fprintf(F2,"7\n");
            }
            if(command[0]=='j'&&command[1]=='m'&&command[2]=='p')
            {
                commandnumber+=1;
                fprintf(F2,"6 ");
                if (fscanf(F,"%d",&j)==0)
                {
                    fscanf(F,":%d",&j);
                    fprintf(F2,"%d\n",labels[j]);
                }
                else fprintf(F2,"%d\n",j);
            }
            if(command[0]=='c'&&command[1]=='a'&&command[2]=='l'&&command[3]=='l')
            {
                commandnumber+=1;
                fprintf(F2,"11 ");
                if (fscanf(F,"%d",&j)==0)
                {
                    fscanf(F,":%d",&j);
                    fprintf(F2,"%d\n",labels[j]);
                }
                else fprintf(F2,"%d\n",j);
            }
            if(command[0]=='j'&&command[1]=='a')
            {
                commandnumber+=1;
                fprintf(F2,"3 ");
                if (fscanf(F,"%d",&j)==0)
                {
                    fscanf(F,":%d",&j);
                    fprintf(F2,"%d\n",labels[j]);
                }
                else fprintf(F2,"%d\n",j);


            }


            if(command[0]=='e'&&command[1]=='x'&&command[2]=='i'&&command[3]=='t')
            {
                commandnumber+=1;
                fprintf(F2,"0\n");
            }

            if(command[0]=='c'&&command[1]=='r'&&command[2]=='a'&&command[3]=='s'&&command[4]=='h')
            {
                commandnumber+=1;
                fprintf(F2,"10\n");
            }

            if((command[0]=='p'&&command[1]=='o'&&command[2]=='p')||(command[0]=='o'&&command[1]=='u'&&command[2]=='t'))
            {
                commandnumber+=1;
                if (command[i]!='\n')
                {
                    if(fscanf(F,"%c",&c)==1)

                        if(c>='a'&&c<='d')fprintf(F2,"2 %c\n",c);
                }

                else
                    fprintf(F2,"2\n");



            }
            //if(command[0]=='o'&&command[1]=='k')printf("%s\n",(stack_ok(st)==0)?"OK":"STACK DOESN'T EXIST!");
            //if(command[0]=='c'&&command[1]=='r'&&command[2]=='e'&&command[3]=='a'&&command[4]=='t'&&command[5]=='e')stack_ctor(st);
            //if(command[0]=='d'&&command[1]=='e'&&command[2]=='s'&&command[3]=='t'&&command[4]=='r'&&command[5]=='o'&&command[6]=='y')stack_dtor(st);
            //if(command[0]=='p'&&command[1]=='r'&&command[2]=='i'&&command[3]=='n'&&command[4]=='t')stack_print(st);


        }
        while(command[0]!='e'||command[1]!='x'||command[2]!='i'||command[3]!='t');
        fclose(F);
        fclose(F2);
    }

}
