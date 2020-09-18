#include <stdio.h>
#include <math.h>                                                                                    
#include <stdlib.h>
#define DEG_2_KM  111.194926644558550
#define DEG_2_RAD 0.017453292519943
#define RAD_2_DEG 57.295779513082323
double dmstodecimaldegree(double degree,double minute,double second,char letter){

    int sign=1;
    if(letter=='S'|| letter=='W') sign=-1;
    else sign=1;
    return sign*(degree+(minute/60.0)+(second/3600.0));
}
double greatcircledistance(double s1,double lambda1,double s2,double lambda2){ 
    return fabs(DEG_2_KM*RAD_2_DEG*acos(cos(s1)*cos(s2)*cos(lambda1-lambda2)+sin(s1)*sin(s2)));

}
void sort(double arr1[],int arr2[],double arr3[],double arr4[],double arr5[],double arr6[],double arr7[],double arr8[],char arr9[],char arr10[],int size1){
    int i,j;
    int smallest;
    for(i=0; i<size1; ++i){
        smallest=i;
    for(j=i+1; j<size1; ++j){
        if(arr1[j]<arr1[smallest]){
            smallest=j;
        }
    }
     double temp=arr1[i];
      arr1[i]=arr1[smallest];
      arr1[smallest]=temp;
       int temp2=arr2[i];
       arr2[i]=arr2[smallest];
       arr2[smallest]=temp2;
       //
       double temp3=arr3[i];
       arr3[i]=arr3[smallest];
       arr3[smallest]=temp3;
       //
       double temp4=arr4[i];
       arr4[i]=arr4[smallest];
       arr4[smallest]=temp4;
       //
       double temp5=arr5[i];
       arr5[i]=arr5[smallest];
       arr5[smallest]=temp5;
       //
       double temp6=arr6[i];
       arr6[i]=arr6[smallest];
       arr6[smallest]=temp6;
       //
       double temp7=arr7[i];
       arr7[i]=arr7[smallest];
       arr7[smallest]=temp7;
       //
       double temp8=arr8[i];
       arr8[i]=arr8[smallest];
       arr8[smallest]=temp8;
        //
       char temp9=arr9[i];
       arr9[i]=arr9[smallest];
       arr9[smallest]=temp9;
        //
       char temp10=arr10[i];
       arr10[i]=arr10[smallest];
       arr10[smallest]=temp10;

    }

}
int main(int argc,char* argv[]){
double longitude;
sscanf(argv[1],"%lf",&longitude);
double latitude;
sscanf(argv[2],"%lf",&latitude);
double  searchrange;
sscanf(argv[3],"%lf",&searchrange);
FILE *readed=fopen(argv[4],"r");
FILE *readed2;
FILE *writed=fopen(argv[5],"w");  
 char NO[30],LONDEG[30],LONMIN[30],LONSEC[30],LONEW[2],LATDEG[30],LATMIN[30],LATSEC[30],LATNS[2],CITY_NAME[50],CNTRY_NAME[50],POP[30]; //12 string
 int no;
 double londeg,lonmin,lonsec,latdeg,latmin,latsec;
 int nos[2540];
 double londegs[2540],lonmins[2540],lonsecs[2540],latdegs[2540],latmins[2540],latsecs[2540],distances[2540];
 char lonews[2543], latns[2543];
 int size=0;
 int i=0;
 int j=0;

 char alllines[2541][250];

fscanf(readed,"%s %s %s %s %s %s %s %s %s %s %s %s ",NO,LONDEG,LONMIN,LONSEC,LONEW,LATDEG,LATMIN,LATSEC,LATNS,CITY_NAME,CNTRY_NAME,POP);
while( fscanf(readed,"%s %s %s %s %s %s %s %s %s %s %s %s ",NO,LONDEG,LONMIN,LONSEC,LONEW,LATDEG,LATMIN,LATSEC,LATNS,CITY_NAME,CNTRY_NAME,POP)==12)
{  no=atoi(NO);
    londeg=atof(LONDEG);
    lonmin=atof(LONMIN);
    lonsec=atof(LONSEC);
    latdeg=atof(LATDEG);
    latmin=atof(LATMIN);
    latsec=atof(LATSEC);
   double ddlon=dmstodecimaldegree(londeg,lonmin,lonsec,LONEW[0]);
    double ddlat=dmstodecimaldegree(latdeg,latmin,latsec,LATNS[0]);
    double distancetry=greatcircledistance(latitude*DEG_2_RAD,longitude*DEG_2_RAD,ddlat*DEG_2_RAD,ddlon*DEG_2_RAD);
    if(distancetry<=searchrange){
      nos[size]=no;
      londegs[size]=londeg;
      lonmins[size]=lonmin;
      lonsecs[size]=lonsec;
      latdegs[size]=latdeg;
      latmins[size]=latmin;
      latsecs[size]=latsec;
      lonews[size]=LONEW[0];
      latns[size]=LATNS[0];
      distances[size]=distancetry;

      ++size;
    }


}
fclose(readed);
readed2=fopen(argv[4],"r");
fscanf(readed2,"%[^\n]\n",alllines[i]);
++i;
while(i<2541){
fscanf(readed2,"%s %s %s %s %s %s %s %s %s %[^\n]\n",NO,LONDEG,LONMIN,LONSEC,LONEW,LATDEG,LATMIN,LATSEC,LATNS,alllines[i]);
++i;
}
fclose(readed2);
sort(distances,nos,londegs,lonmins,lonsecs,latdegs,latmins,latsecs,lonews,latns,size);


for(j=0; j<size; ++j){
fprintf(writed, "%d %.0lf° %.0lf' %7.4lf\" %c %.0lf° %.0lf' %7.4lf\" %c %s %.2lf\n",nos[j],londegs[j],lonmins[j],lonsecs[j],lonews[j],latdegs[j],latmins[j],latsecs[j],latns[j],alllines[nos[j]],distances[j]);
}

fclose(writed);


return 0;
}
