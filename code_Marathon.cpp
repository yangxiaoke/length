#include<iostream>
#include<map>
#include<cstring>
#include<fstream>
#include<stdio.h>
#include<iomanip>

using namespace std;

int main()
{
    //open the input file,and make sure the file is opened sucessfully
    ifstream openFile;
    openFile.open("D:\\input.txt",ios::in);
    if(!openFile)
    {
        cerr<<"error: unable to open input file: "<<openFile<<endl;
        return -1;
    }

    int lineno = 0;           //the number of the line in the inputfile
    string str;               //each line of the inputfile
    double result[12]={0.0};  //the result of each expression
    int num = 0;              //the index of the array
    map<string,double> pairMode;  //store the conversion rules

    //read the file line by line
    while(getline(openFile,str))
    {
        //read and store the conversion rules
        if(lineno<6)
        {
            int j=0,i=2,m=0;
            string str1;
            double data;

            for(i=2;str[i]!=' ';i++)
            {
                j++;
            }

            m = i+3;
            str1 = str.substr(2,j);
            j = 0;

            for(i = m;str[i]!=' ';i++)
            {
                j++;
            }
            //cout<<str.substr(m,j)<<"  ";
            const char *p = str.substr(m,j).c_str();
            sscanf(p,"%Lf",&data);
            //cout<<data<<endl;

            pairMode.insert(make_pair(str1,data));
            lineno++;

            //cout<<pair->first<<endl;
        }
        else if(lineno==6)
        {//skip the blank line
            lineno++;
            continue;
        }
        else if(lineno>6 && lineno <13)
        {//calculate the sample expressions
            double fir;
            char sec[10];
            const char* q = str.c_str();
            sscanf(q,"%Lf %s",&fir,sec);
            string secd = sec;

            if(secd=="inches")
            {
                secd = "inch";
            }
            else if(secd == "feet")
            {
                secd = "foot";
            }
            else if(secd == "faths")
            {
                secd = "fath";
            }
            else if(secd == "miles")
            {
                secd = "mile";
            }

            map<string,double>::const_iterator map_it = pairMode.begin();
            while(map_it != pairMode.end())
            {
                if(secd == map_it->first)
                {
                    result[num] = map_it->second * fir;
                    num++;
                }
                ++map_it;
            }
            lineno++;
        }
        else if(lineno == 13 || lineno == 14)
        {//calculate the next two expressions
            double a,b;
            double res1,res2;
            char ch1[10];
            char ch2[10];
            char c;
            const char* x = str.c_str();
            sscanf(x,"%Lf %s %c %Lf %s",&a,ch1,&c,&b,ch2);

            string str1 = ch1;
            string str2 = ch2;

            if(str2 =="inches")
            {
                str2 = "inch";
            }
            else if(str2 == "feet")
            {
                str2 = "foot";
            }
            else if(str2 == "faths")
            {
                str2 = "fath";
            }
            else if(str2 == "miles")
            {
                str2 = "mile";
            }
            map<string,double>::iterator map_it = pairMode.find(str1);
            if(map_it!=pairMode.end())
            {
                res1 = map_it->second * a;
            }
            map<string,double>::iterator map_it2 = pairMode.find(str2);
            if(map_it2!=pairMode.end())
            {
                res2 = map_it2->second * b;
            }
            if(c == '+')
            {
                result[num] = res1 + res2;
                num++;
            }
            else
            {
                result[num] = res1- res2;
                num++;
            }

            lineno++;

        }
        else if(lineno == 15 || lineno == 16)
        {//calculate the last three expressions
            double data1,data2,data3;
            double result1,result2,result3;
            char char1[10];
            char char2[10];
            char char3[10];
            char c1,c2;
            const char* strChar = str.c_str();
            sscanf(strChar,"%Lf %s %c %Lf %s %c %Lf %s",&data1,char1,&c1,&data2,char2,&c2,&data3,char3);

            string s1 = char1;
            string s2 = char2;
            string s3 = char3;

            if(s1=="faths" )
            {
                s1 = "fath";
            }
            else if(s1=="miles" )
            {
                s1 = "mile";
            }

            if(s2=="yards")
            {
                s2 = "yard";
            }

            if(s3=="inches")
            {
                s3 = "inch";
            }

            map<string,double>::iterator it = pairMode.find(s1);
            if(it!=pairMode.end())
            {
                result1 = it->second * data1;
            }

            map<string,double>::iterator it2 = pairMode.find(s2);
            if(it2!=pairMode.end())
            {
                result2 = it2->second * data2;
            }

            map<string,double>::iterator it3 = pairMode.find(s3);
            if(it3!=pairMode.end())
            {
                result3 = it3->second * data3;
            }

            if(c1 == '+')
            {
                result[num] = result1 + result2;
            }
            else
            {
                result[num] = result1 - result2;
            }

            if(c2=='+')
            {
                result[num] += result3;
                num++;
            }
            else
            {
                result[num] -=result3;
                num++;
            }
            lineno++;
        }
        else
        {
            break;
        }
    }

    openFile.close();

    //write the result to the output file
    ofstream outFile;
    outFile.open("D:\\outfile.txt",ofstream::out|ofstream::app);
    if(!outFile)
    {
        cerr<<"error: unable to open out file: "<<outFile<<endl;
        return -1;
    }

    outFile<<"yangxiaokegood@163.com"<<endl;
    outFile<<endl;
    for(int i=0;i<10;i++)
    {
        outFile<<setprecision(2)<<std::fixed<<result[i]<<" m"<<endl;
    }
    outFile.close();

    return 0;
}
