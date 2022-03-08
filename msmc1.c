#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<stdlib.h>

struct medicine
{
    int id,price,quantity;
    char name[50],company_name[50],mfg_date[11],exp_date[11];
}m;


void addmedicine()
{
    FILE *fp;
    fp=fopen("medi","a");

    printf("\nEnter ID:");
    scanf("%d",&m.id);

    printf("\nEnter the Name of Medicine:");
    scanf("%s",m.name);

    printf("\nEnter the Company name:");
    scanf("%s",m.company_name);

    printf("\nEnter Price:");
    scanf("%ld",&m.price);

    printf("\nEnter the no. of Quantity:");
    scanf("%d",&m.quantity);
    
    printf("\nEnter Mfg date:");
    scanf("%s",m.mfg_date);

    printf("\nEnter Exp date:");
    scanf("%s",m.exp_date);

    fprintf(fp,"\n%d %s %s %ld %d %s %s",m.id,m.name,m.company_name,m.price,m.quantity,m.mfg_date,m.exp_date);

    fclose(fp);
}

void displaymedicine()
{
    struct medicine m;
    FILE *fp;
    
    fp=fopen("medi","r");
    printf("===========================================================================================");
    printf("\n|ID \t|Medicine Name \t|Company Name \t|Price \t|Quantity \t|Mfg Date \t|Exp Date");
    printf("\n===========================================================================================");
    while(fscanf(fp,"\n%d\t%s\t%s\t%d\t%d\t%s\t%s",&m.id,&m.name,&m.company_name,&m.price,&m.quantity,&m.mfg_date,&m.exp_date)!=EOF)
    {
        printf("\n%d \t%s \t\t%s \t\t%d \t%d \t\t%s \t%s",m.id,m.name,m.company_name,m.price,m.quantity,m.mfg_date,m.exp_date);
    }
        printf("\n===========================================================================================");
    fclose(fp);
}

int avlName(char str[])
{
    struct medicine m;
    FILE *fp;
    fp=fopen("medi","r");

    while(!feof(fp))
    {
        fscanf(fp,"\n%d\t%s\t%s\t%d\t%d\t%s\t%s",&m.id,&m.name,&m.company_name,&m.price,&m.quantity,&m.mfg_date,&m.exp_date);

        if(strcmp(str,m.name)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void search()
{
    struct medicine m;
    FILE *fp;
    int a;
    char str[50];

    printf("\nEnter the name to be search:");
    scanf("%s",str);

    fp=fopen("medi","r");
    a=avlName(str);
    if(a==1)
    {
        printf("===========================================================================================");
        printf("\n|ID \t|Medicine Name \t|Company Name \t|Price \t|Quantity \t|Mfg Date \t|Exp Date");  
        printf("\n===========================================================================================");
        while(fscanf(fp,"\n%d\t%s\t%s\t%d\t%d\t%s\t%s",&m.id,&m.name,&m.company_name,&m.price,&m.quantity,&m.mfg_date,&m.exp_date)!=EOF)
        {
            if(strcmp(str,m.name)==0)
            {
                printf("\n%d \t%s \t\t%s \t\t%d \t%d \t\t%s \t%s",m.id,m.name,m.company_name,m.price,m.quantity,m.mfg_date,m.exp_date); 
                fclose(fp);
            }
        }
        printf("\n===========================================================================================");

    }
    else
    {
        printf("\nThe searched Medicine does not exist.");
    }
    fclose(fp);
}

void display(struct medicine me)
{
            printf("\n ID of Medicine:%d",me.id);
            printf("\n Name of Medicine:%s",me.name);
            printf("\n Company Name:%s",me.company_name);
            printf("\n Price:%d",me.price);
            printf("\n Quantity:%d",me.quantity);
            printf("\n Mfg Date:%S",me.mfg_date);
            printf("\n Exp Date:%s",me.exp_date);
}

void input(struct medicine *medi)
{
            printf("\n ID of Medicine:");
            scanf("%d",&medi->id);
            printf("\n Enter the new name of Medicine:");
            gets(medi->name);
            printf("\n Enter the new Company Name:");
            scanf("%s",medi->company_name);
            printf("\n Enter the new Price:");
            scanf("%d",&medi->price);
            printf("\n Enter teh new Quantity:");
            scanf("%d",&medi->quantity);
            printf("\n Enter new Mfg Date:");
            scanf("%s",&medi->mfg_date);
            printf("\n Enter new Exp Date:");
            scanf("%s",&medi->exp_date);    
}

void update()
{
    FILE *fp;
    struct medicine m;
    int n,found=0;  
    
    printf("\n To Update");
    printf("\n Enter the ID of medicine:");
    scanf("%d",&n);
    fp=fopen("update","r");
    while((fread(&m,sizeof(m),1,fp))>0 && found==0)
    {
        if (m.id==n)
        {
            display(m);
            printf("Enter new details of Medicine\n");
            input(&m);
            fseek(fp,-(long)sizeof(m),1);
            fwrite(&m,sizeof(m),1,fp);
            printf("\n Record Updated");
            found=1;
        }
    }
    fclose(fp);
    if (found==0)
    printf("\n Record Not Found");
}

void delete()
{
    struct medicine m;
    FILE *f1;
    FILE *f2;
    char str[30];

    printf("\nEnter the Medicine name u want to delete:");
    scanf("%s",str);

    f1=fopen("medi","r");
    f2=fopen("medi1","w");

    while(fscanf(f1,"\n%d\t%s\t%s\t%d\t%d\t%s\t%s",&m.id,&m.name,&m.company_name,&m.price,&m.quantity,&m.mfg_date,&m.exp_date)!=EOF)
    {
        if(strcmp(str,m.name)!=0)
        {
            fprintf(f2,"\n%d\t%s\t%s\t%d\t%d\t%s\t%s",m.id,m.name,m.company_name,m.price,m.quantity,m.mfg_date,m.exp_date);
        }
    }
    fclose(f1);
    fclose(f2);

    f1=fopen("medi","w");
    f2=fopen("medi1","r");

    while(fscanf(f2,"\n%d\t%s\t%s\t%d\t%d\t%s\t%s",&m.id,&m.name,&m.company_name,&m.price,&m.quantity,&m.mfg_date,&m.exp_date)!=EOF)
    {
        fprintf(f1,"\n%d\t%s\t%s\t%d\t%d\t%s\t%s",m.id,m.name,m.company_name,m.price,m.quantity,m.mfg_date,m.exp_date);
    }

    fclose(f1);
    fclose(f2);

    printf("\nRecord Deleted");
}

void purchase()
{
    struct medicine m;
    FILE *f,*fp;
    fp=fopen("bill.txt","w");
    int n,i,o,p=0;
    do
    {
    printf("enter medicin id for purchase = ");
    scanf("%d",&n);
    f=fopen("medi","r");
    while(fscanf(f,"\n%d\t%s\t%s\t%d\t%d\t%s\t%s",&m.id,&m.name,&m.company_name,&m.price,&m.quantity,&m.mfg_date,&m.exp_date)!=EOF)
    {
        if(n==m.id)
        {
            printf("how many quantity you want to buy = ");
            scanf("%d",&i);
            fprintf(fp,"\t%d\t=",m.id);
            fprintf(fp,"\t[%s]\t",m.name);
            fprintf(fp,"\t%d\t*",i);
            fprintf(fp,"\t%d\t=",m.price);
            m.price=m.price*i;
            fprintf(fp,"\t%d\n",m.price);
            p=p+m.price;
        }
    }
    fclose(f);
    printf("for more purchase enter 1 = ");
    scanf("%d",&o);
    }while(o==1);
    fprintf(fp,"\n\ttotal price is = %d",p);
    fclose(fp);
    
}

int main()
{
    int ch1,ch2;

    do
    {
        printf("\n1.Add Medicine");
        printf("\n2.Display Medicine");
        printf("\n3.Search");
        printf("\n4.Purchase Medicine");
        printf("\n5.Update");
        printf("\n6.Bill");
        printf("\n7.Delete");
        printf("\n8.Exit");

        printf("\nEnter the choice:");
        scanf("%d",&ch1);

        switch(ch1)
        {
            case 1:
                addmedicine();
                break;

            case 2:
                displaymedicine();
                break;

            case 3:
                search();
                break;

            case 4:
                purchase();
                break;

            case 5:
                update();
                break;

            case 6:
                system("bill.txt");
                break;
                
            case 7:
                delete();
                break;
                    
            case 8:
                printf("\nThank You...");
                return 0;

            default:
                printf("\nWrong choice.");
                break;
        }
        printf("\nDo you want to continue yes=1 and no=0");
        scanf("%d",&ch2);
    }
    while(ch2==1);

    return 0;
}
