#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 14348907
typedef struct name{
    char name[10];
}name;
int n,k;
name *person;
int *tag;
int *tag1;
long int map(int mappednumber){
    char *s=person[mappednumber].name;
    long int sum=0;
    for(int i=0;i<strlen(s);i++){
        sum=sum*26;
        sum=sum+s[i]-'a'+1;
    }
    return sum;
}
int main(){
    int count=0;
    int countqueue1=0,countqueue2=0;
    int queuehead1=1,starthead2=1;
    int publicend=0;
    tag=(int *)malloc(sizeof(int)*MAX);
    tag1=(int *)malloc(sizeof(int)*MAX);
    memset(tag,0,MAX);
    memset(tag1,0,MAX);
    scanf("%d%d",&n,&k);
    person=(name*)malloc(sizeof(name)*(n+1));
    for(int i=1;i<=n;i++){
        scanf("%s",person[i].name);
        getchar();
    }
    while(countqueue1<k){
        publicend++;
        if(tag[map(publicend)]==0){
            countqueue1++;
            countqueue2++;
        }
        tag[map(publicend)]++;
        tag1[map(publicend)]++;
    }
    while(publicend<=n){
        if(countqueue1==k&&countqueue2==k){
            tag1[map(starthead2)]--;
            if(tag1[map(starthead2)]==0)
                countqueue2--;
            else ;
            starthead2++;
        }
        else if(countqueue1==k&&countqueue2==k-1){
            count+=starthead2-queuehead1;
            if(publicend==n)
                break;
            publicend++;
            if(tag[map(publicend)]==0)
                countqueue1++;
            if(tag1[map(publicend)]==0)
                countqueue2++;
            tag[map(publicend)]++;
            tag1[map(publicend)]++;
        }
        else if(countqueue1==k+1&&countqueue2==k){
            {
                tag[map(queuehead1)]--;
                if(tag[map(queuehead1)]==0)
                    countqueue1--;
                queuehead1++;
            }
        }
    }
    printf("  %d",count);

}