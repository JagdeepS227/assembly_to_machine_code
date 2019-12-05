#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>
#include<bitset>
#include <bits/stdc++.h> 

using namespace std;
int line_no=0,line_no_label=0,line_bck=0,no_of_machinecodes=0 ;
ofstream myfile;
int linn,linn2=0;
int ident(string sed){
    if(sed=="x0"){return 0;}if(sed=="x1"){return 1;}if(sed=="x2" || sed=="sp"){return 2;}if(sed=="x3"){return 3;}if(sed=="x4"){return 4;}if(sed=="x5"){return 5;}
    if(sed=="x6"){return 6;}if(sed=="x7"){return 7;}if(sed=="x8"){return 8;}if(sed=="x9"){return 9;}if(sed=="x10"){return 10;}if(sed=="x11"){return 11;}if(sed=="x12"){return 12;}if(sed=="x13"){return 13;}
    if(sed=="x14"){return 14;}if(sed=="x15"){return 15;}if(sed=="x16"){return 16;}if(sed=="x17"){return 17;}if(sed=="x18"){return 18;}if(sed=="x19"){return 19;}if(sed=="x20"){return 20;}if(sed=="x21"){return 21;}
if(sed=="x22"){return 22;}if(sed=="x23"){return 23;}if(sed=="x24"){return 24;}if(sed=="x25"){return 25;}
    if(sed=="x26"){return 26;}if(sed=="x27"){return 27;}if(sed=="x28"){return 28;}if(sed=="x29"){return 29;}if(sed=="x30"){return 30;}if(sed=="x31"){return 31;}
}

int label_lineno(string abc){
    line_no_label=0;
string abd=":";
if( abc!=".text" && abc!=".data")
{abc=abc+abd;}
int r3=0;string line;
     ifstream fin1("assem_code.asm");
    while( getline(fin1,line)){line_no_label++;
        std::  istringstream iss(line); 
        do { string ter; iss >> ter; 
            if(ter==abc){r3=1;return line_no_label;}
        } while (iss);  
    }
}


string dectohex(int xixi)
{
    int xix=xixi;
    char hexaDeciNum[100];int i =0;
    string sdr;
     while(xix!=0){    
        int tempe  = 0; 
        tempe = xix % 16; 
        if(tempe < 10) { 
            hexaDeciNum[i] = tempe + 48; 
            i++; 
        } 
        else{ 
            hexaDeciNum[i] = tempe + 55; 
            i++; 
        } 
        xix = xix/16; 
    } 
    if(xixi==0)
    {
        sdr='0';
    }
    for(int pp=0;pp<i;pp++){
 sdr=sdr+hexaDeciNum[i-pp-1];}
 return sdr;
}

char id_hex(string axz)
{
    if(axz=="0000"){return '0';}
    if(axz=="0001"){return '1';}
    if(axz=="0010"){return '2';}
    if(axz=="0011"){return '3';}
    if(axz=="0100"){return '4';}
    if(axz=="0101"){return '5';}
    if(axz=="0110"){return '6';}
    if(axz=="0111"){return '7';}
    if(axz=="1000"){return '8';}
    if(axz=="1001"){return '9';}
    if(axz=="1010"){return 'A';}
    if(axz=="1011"){return 'B';}
    if(axz=="1100"){return 'C';}
    if(axz=="1101"){return 'D';}
    if(axz=="1110"){return 'E';}
    if(axz=="1111"){return 'F';}
} 



void bin_hex(bitset<32> bset1)
{
    char aqd[8][4];
    for(int frf=0;frf<8;frf++){
        for(int grg=0;grg<4;grg++){
            if(bset1[(frf*4)+grg]==1){aqd[frf][grg]='1';}
            else{        aqd[frf][grg]='0';
            }
        }
    }string huh[8];
    for(int dsd=0;dsd<8;dsd++){
    huh[dsd]=aqd[dsd][3];       huh[dsd]=huh[dsd]+aqd[dsd][2];   huh[dsd]=huh[dsd]+aqd[dsd][1];    huh[dsd]=huh[dsd]+aqd[dsd][0];
    }char res[10];
    res[0]='0';
    res[1]='x';
    for(int fvf=0;fvf<8;fvf++)
    {
        res[9-fvf]=id_hex(huh[fvf]);
    }
    line_no++;
    no_of_machinecodes++;
      myfile << "0x";
    myfile << dectohex((line_no-1)*4) << " " << res << "\n" ;
}





void r_code(bitset<7> opcode,bitset<7> f7,bitset<3> f3,string rs1,string rs2,string rd){   //00000000100000010000000010010011
    int rss1,rss2,rdd;rss1=ident(rs1);rss2=ident(rs2);rdd=ident(rd);
    bitset<5> rs11(rss1);bitset<5> rs22(rss2);bitset<5> rddd(rdd);bitset<32> mach ;int zey=0;
    for(zey=0;zey<32;zey++){
        if(zey<7){mach[zey]=opcode[zey];}
        if(zey>6 && zey<12){mach[zey]=rddd[zey-7];}
        if(zey>11 && zey<15){mach[zey]=f3[zey-12];}
        if(zey>14 && zey<20){mach[zey]=rs11[zey-15];}
        if(zey>19 && zey<25){mach[zey]=rs22[zey-20];}
        if(zey>24 && zey<32){mach[zey]=f7[zey-25];}
    }    
    bin_hex(mach);
}
void i_code(bitset<7> opcode,bitset<12> immed,bitset<3> f3,string rs1,string rd){   
    int rss1,rdd;rss1=ident(rs1);rdd=ident(rd);bitset<5> rs11(rss1);bitset<5> rddd(rdd);
    bitset<32> mach ;int zey=0;
    for(zey=0;zey<32;zey++){
        if(zey<7){mach[zey]=opcode[zey];}
        if(zey>6 && zey<12){mach[zey]=rddd[zey-7];}
        if(zey>11 && zey<15){mach[zey]=f3[zey-12];}
        if(zey>14 && zey<20){mach[zey]=rs11[zey-15];}
        if(zey>19){mach[zey]=immed[zey-20];}
    }
    bin_hex(mach);
}
void s_code(bitset<7> opcode,bitset<12> immed,bitset<3> f3,string rs1,string rs2){   
    int rss1,rss2;rss1=ident(rs1);rss2=ident(rs2);bitset<5> rs11(rss1);bitset<5> rs22(rss2);
    bitset<32> mach ;int zey=0;
    for(zey=0;zey<32;zey++){
        if(zey<7){mach[zey]=opcode[zey];}
        if(zey>6 && zey<12){mach[zey]=immed[zey-7];}
        if(zey>11 && zey<15){mach[zey]=f3[zey-12];}
        if(zey>14 && zey<20){mach[zey]=rs11[zey-15];}
        if(zey>19 && zey<25){mach[zey]=rs22[zey-15];}
        if(zey>24){mach[zey]=immed[zey-20];}
    }
        bin_hex(mach);
}
void sb_code(bitset<7> opcode,bitset<13> immed,bitset<3> f3,string rs1,string rs2){   
    int rss1,rss2;rss1=ident(rs1);rss2=ident(rs2);bitset<5> rs11(rss1);bitset<5> rs22(rss2);
    bitset<32> mach ;int zey=0;
    for(zey=0;zey<32;zey++){
        if(zey<7){mach[zey]=opcode[zey];}
        if(zey==7){mach[zey]=immed[11];}
        if(zey>7 && zey<12){mach[zey]=immed[zey-7];}
        if(zey>11 && zey<15){mach[zey]=f3[zey-12];}
        if(zey>14 && zey<20){mach[zey]=rs11[zey-15];}
        if(zey>19 && zey<25){mach[zey]=rs22[zey-20];}
        if(zey>24 && zey <31){mach[zey]=immed[zey-20];}
        if(zey==31){mach[zey]=immed[12];}
    }
        bin_hex(mach);
}
void u_code(bitset<7> opcode,bitset<20> immed,string rd){   
    int rdd=ident(rd);bitset<5> rddd(rdd);bitset<32> mach ;int zey=0;
    for(zey=0;zey<32;zey++){
        if(zey<7){mach[zey]=opcode[zey];}
        if(zey>6 && zey<12){mach[zey]=rddd[zey-7];}
        if(zey>11){mach[zey]=immed[zey-12];}
    }    
        bin_hex(mach);
}
void uj_code(bitset<7> opcode,bitset<20> immed,string rd){   
    int rdd=ident(rd);bitset<5> rddd(rdd);bitset<32> mach ;int zey=0;
    for(zey=0;zey<32;zey++){
        if(zey<7){mach[zey]=opcode[zey];}
        if(zey>6 && zey<12){mach[zey]=rddd[zey-7];}
        if(zey>11 && zey<20){mach[zey]=immed[zey];}
        if(zey==20){mach[zey]=immed[11];}
        if(zey>20 && zey<31){mach[zey]=immed[zey-20];}
        if(zey==31){mach[zey]=immed[20];}
    }    
        bin_hex(mach);
}




int con = 0;
void extract_terms(string line1){
    int rj=0,hj=0,err=0;string terms[100];
    std::  istringstream iss(line1); 
      do { 
        string term; 
        iss >> term; 
        terms[rj]=term;
        rj++;
    } while (iss); 
    string rs1,rs2,rd;
    //####################################R-FORMAT############################
    if(terms[0]=="add"){
        rd=terms[1];
        rs1=terms[2];
        rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0000000");bitset<3> f3("000");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="sub"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0100000");bitset<3> f3("000");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="sll"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0000000");bitset<3> f3("001");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="slt"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0000000");bitset<3> f3("010");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="sltu"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0000000");bitset<3> f3("011");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="xor"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0000000");bitset<3> f3("100");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="srl"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0000000");bitset<3> f3("101");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="sra"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0100000");bitset<3> f3("101");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="or"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0000000");bitset<3> f3("110");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="and"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0110011");bitset<7> f7("0000000");bitset<3> f3("111");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="addw"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0111011");bitset<7> f7("0000000");bitset<3> f3("000");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="subw"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0111011");bitset<7> f7("0100000");bitset<3> f3("000");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="sllw"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0111011");bitset<7> f7("0000000");bitset<3> f3("001");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="srlw"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0111011");bitset<7> f7("0000000");bitset<3> f3("101");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="sraw"){
        rd=terms[1];rs1=terms[2];rs2=terms[3];
        bitset<7> opc("0111011");bitset<7> f7("0100000");bitset<3> f3("101");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }
    if(terms[0]=="mul"){//00000010001100010000000010110011
        rd=terms[1];rs2=terms[3];rs1=terms[2];
        bitset<7> opc("0110011");bitset<3> f3("000");bitset<7> f7("0000001");
        r_code(opc,f7,f3,rs1,rs2,rd);
    }

    if(terms[0]=="div"){//00000010001100010000000010110011
        rd=terms[1];rs2=terms[3];rs1=terms[2];
        bitset<7> opc("0110011");bitset<3> f3("100");bitset<7> f7("0000001");
        r_code(opc,f7,f3,rs1,rs2,rd);}
    //############################IMMEdIATE FORMAT#########################
  if(terms[0]=="lb")
    {  
                int gp=0,sum=0,kp=0,mp=0,t1=0,t2;
                string hi;
                char rsr[3];
                hi=terms[2];
                int linn3=0;
                char fed[21],fed1[21];
                int prod,tkt=0;
                if((int)hi[0]<60)
                {tkt=1;}
            if(tkt==0)
            {
                rd=terms[1];
                bitset<20> immed1(65536);bitset<7> opc1("0010111");
                u_code(opc1,immed1,rd); 
                rs1=terms[1];          
                linn3=label_lineno(hi);
                int offset=(linn3-no_of_machinecodes-1)*4 ;
                int gvg=0;
                if(offset<0){gvg=1;
                offset=offset*(-1);offset=offset;
                }bitset<12> immed(offset);
                if(gvg==1)
                {int brk=0;
                    for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
                    for(int zuz=0;zuz<13 && brk==0;zuz++)
                    {
                        if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                    else{
                        immed[zuz]=0;
                    }
                    }
                }                
                bitset<7> opc("0000011");bitset<3> f3("000");
                i_code(opc,immed,f3,rs1,rd);

            }
            if(tkt==1){
                        string hi = terms[2];
                        int gp=0,sum=0,kp=0,mp=0,t1,t2;
                        char fed[21],fed1[21];
                        int prod;
                        while(hi[gp]!='('){
                                fed[20-gp]=hi[gp];                            
                                gp++;
                            }
                            while(hi[kp]!=')'){
                                    if(t1==1){
                                        rsr[mp]=hi[kp];                                    
                                        mp++;
                                    }
                                    if(hi[kp]=='('){
                                        t1=1;
                                    }
                                    kp++;
                                }
                                rsr[mp]=NULL;
                                rs1=rsr;
                            for(int kk=21-gp;kk<21 ;kk++)
                            {
                                prod=pow(10,kk+gp-21);
                                if(fed[kk]!='-')
                                sum=sum+(((int)fed[kk]-48)*prod);
                            }bitset<12> immed(sum);
                             if((int)hi[0]=='-')
                            {int brk=0;
                                for(int vuv=0;vuv<12;vuv++){immed[vuv]=1-immed[vuv];}
                                for(int zuz=0;zuz<12 && brk==0;zuz++)
                                {
                                    if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                                    else{
                                        immed[zuz]=0;
                                    }
                                }
                            }
                                    rd=terms[1];     
                                        rd=terms[1];bitset<7> opc("0000011");bitset<3> f3("000");
                                        i_code(opc,immed,f3,rs1,rd);
            }
    }




if(terms[0]=="lh")
    {  
                int gp=0,sum=0,kp=0,mp=0,t1=0,t2;
                string hi;
                char rsr[3];
                hi=terms[2];
                int linn3=0;
                char fed[21],fed1[21];
                int prod,tkt=0;
                if((int)hi[0]<60)
                {tkt=1;}
            if(tkt==0)
            {
                rd=terms[1];
                bitset<20> immed1(65536);bitset<7> opc1("0010111");
                u_code(opc1,immed1,rd); 
                rs1=terms[1];          
                linn3=label_lineno(hi);
                int offset=(linn3-no_of_machinecodes-1)*4 ;
                int gvg=0;
                if(offset<0){gvg=1;
                offset=offset*(-1);offset=offset;
                }bitset<12> immed(offset);
                if(gvg==1)
                {int brk=0;
                    for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
                    for(int zuz=0;zuz<13 && brk==0;zuz++)
                    {
                        if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                    else{
                        immed[zuz]=0;
                    }
                    }
                }                
                bitset<7> opc("0000011");bitset<3> f3("001");
                i_code(opc,immed,f3,rs1,rd);

            }
            if(tkt==1){
                        string hi = terms[2];
                        int gp=0,sum=0,kp=0,mp=0,t1,t2;
                        char fed[21],fed1[21];
                        int prod;
                        while(hi[gp]!='('){
                                fed[20-gp]=hi[gp];                            
                                gp++;
                            }
                            while(hi[kp]!=')'){
                                    if(t1==1){
                                        rsr[mp]=hi[kp];                                    
                                        mp++;
                                    }
                                    if(hi[kp]=='('){
                                        t1=1;
                                    }
                                    kp++;
                                }
                                rsr[mp]=NULL;
                                rs1=rsr;
                            for(int kk=21-gp;kk<21 ;kk++)
                            {
                                prod=pow(10,kk+gp-21);
                                if(fed[kk]!='-')
                                sum=sum+(((int)fed[kk]-48)*prod);
                            }bitset<12> immed(sum);
                             if((int)hi[0]=='-')
                            {int brk=0;
                                for(int vuv=0;vuv<12;vuv++){immed[vuv]=1-immed[vuv];}
                                for(int zuz=0;zuz<12 && brk==0;zuz++)
                                {
                                    if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                                    else{
                                        immed[zuz]=0;
                                    }
                                }
                            }
                                    rd=terms[1];     
                                        rd=terms[1];bitset<7> opc("0000011");bitset<3> f3("001");
                                        i_code(opc,immed,f3,rs1,rd);
            }
    }


    if(terms[0]=="lw")
    {  
                int gp=0,sum=0,kp=0,mp=0,t1=0,t2;
                string hi;
                char rsr[3];
                hi=terms[2];
                int linn3=0;
                char fed[21],fed1[21];
                int prod,tkt=0;
                if((int)hi[0]<60)
                {tkt=1;}
            if(tkt==0)
            {
                rd=terms[1];
                bitset<20> immed1(65536);bitset<7> opc1("0010111");
                u_code(opc1,immed1,rd); 
                rs1=terms[1];          
                linn3=label_lineno(hi);
                int offset=(linn3-no_of_machinecodes-1)*4 ;
                int gvg=0;
                if(offset<0){gvg=1;
                offset=offset*(-1);offset=offset;
                }bitset<12> immed(offset);
                if(gvg==1)
                {int brk=0;
                    for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
                    for(int zuz=0;zuz<13 && brk==0;zuz++)
                    {
                        if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                    else{
                        immed[zuz]=0;
                    }
                    }
                }                
                bitset<7> opc("0000011");bitset<3> f3("010");
                i_code(opc,immed,f3,rs1,rd);

            }
            if(tkt==1){
                        string hi = terms[2];
                        int gp=0,sum=0,kp=0,mp=0,t1,t2;
                        char fed[21],fed1[21];
                        int prod;
                        while(hi[gp]!='('){
                                fed[20-gp]=hi[gp];                            
                                gp++;
                            }
                            while(hi[kp]!=')'){
                                    if(t1==1){
                                        rsr[mp]=hi[kp];                                    
                                        mp++;
                                    }
                                    if(hi[kp]=='('){
                                        t1=1;
                                    }
                                    kp++;
                                }
                                rsr[mp]=NULL;
                                rs1=rsr;
                            for(int kk=21-gp;kk<21 ;kk++)
                            {
                                prod=pow(10,kk+gp-21);
                                if(fed[kk]!='-')
                                sum=sum+(((int)fed[kk]-48)*prod);
                            }bitset<12> immed(sum);
                             if((int)hi[0]=='-')
                            {int brk=0;
                                for(int vuv=0;vuv<12;vuv++){immed[vuv]=1-immed[vuv];}
                                for(int zuz=0;zuz<12 && brk==0;zuz++)
                                {
                                    if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                                    else{
                                        immed[zuz]=0;
                                    }
                                }
                            }
                                    rd=terms[1];     
                                        rd=terms[1];bitset<7> opc("0000011");bitset<3> f3("010");
                                        i_code(opc,immed,f3,rs1,rd);
            }
    }


   
   
if(terms[0]=="lbu")
    {  
                int gp=0,sum=0,kp=0,mp=0,t1=0,t2;
                string hi;
                char rsr[3];
                hi=terms[2];
                int linn3=0;
                char fed[21],fed1[21];
                int prod,tkt=0;
                if((int)hi[0]<60)
                {tkt=1;}
            if(tkt==0)
            {
                rd=terms[1];
                bitset<20> immed1(65536);bitset<7> opc1("0010111");
                u_code(opc1,immed1,rd); 
                rs1=terms[1];          
                linn3=label_lineno(hi);
                int offset=(linn3-no_of_machinecodes-1)*4 ;
                int gvg=0;
                if(offset<0){gvg=1;
                offset=offset*(-1);offset=offset;
                }bitset<12> immed(offset);
                if(gvg==1)
                {int brk=0;
                    for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
                    for(int zuz=0;zuz<13 && brk==0;zuz++)
                    {
                        if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                    else{
                        immed[zuz]=0;
                    }
                    }
                }                
                bitset<7> opc("0000011");bitset<3> f3("100");
                i_code(opc,immed,f3,rs1,rd);

            }
            if(tkt==1){
                        string hi = terms[2];
                        int gp=0,sum=0,kp=0,mp=0,t1,t2;
                        char fed[21],fed1[21];
                        int prod;
                        while(hi[gp]!='('){
                                fed[20-gp]=hi[gp];                            
                                gp++;
                            }
                            while(hi[kp]!=')'){
                                    if(t1==1){
                                        rsr[mp]=hi[kp];                                    
                                        mp++;
                                    }
                                    if(hi[kp]=='('){
                                        t1=1;
                                    }
                                    kp++;
                                }
                                rsr[mp]=NULL;
                                rs1=rsr;
                            for(int kk=21-gp;kk<21 ;kk++)
                            {
                                prod=pow(10,kk+gp-21);
                                if(fed[kk]!='-')
                                sum=sum+(((int)fed[kk]-48)*prod);
                            }bitset<12> immed(sum);
                             if((int)hi[0]=='-')
                            {int brk=0;
                                for(int vuv=0;vuv<12;vuv++){immed[vuv]=1-immed[vuv];}
                                for(int zuz=0;zuz<12 && brk==0;zuz++)
                                {
                                    if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                                    else{
                                        immed[zuz]=0;
                                    }
                                }
                            }
                                    rd=terms[1];     
                                        rd=terms[1];bitset<7> opc("0000011");bitset<3> f3("100");
                                        i_code(opc,immed,f3,rs1,rd);
            }
    }


    

    if(terms[0]=="lhu")
    {  
                int gp=0,sum=0,kp=0,mp=0,t1=0,t2;
                string hi;
                char rsr[3];
                hi=terms[2];
                int linn3=0;
                char fed[21],fed1[21];
                int prod,tkt=0;
                if((int)hi[0]<60)
                {tkt=1;}
            if(tkt==0)
            {
                rd=terms[1];
                bitset<20> immed1(65536);bitset<7> opc1("0010111");
                u_code(opc1,immed1,rd); 
                rs1=terms[1];          
                linn3=label_lineno(hi);
                int offset=(linn3-no_of_machinecodes-1)*4 ;
                int gvg=0;
                if(offset<0){gvg=1;
                offset=offset*(-1);offset=offset;
                }bitset<12> immed(offset);
                if(gvg==1)
                {int brk=0;
                    for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
                    for(int zuz=0;zuz<13 && brk==0;zuz++)
                    {
                        if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                    else{
                        immed[zuz]=0;
                    }
                    }
                }                
                bitset<7> opc("0000011");bitset<3> f3("101");
                i_code(opc,immed,f3,rs1,rd);

            }
            if(tkt==1){
                        string hi = terms[2];
                        int gp=0,sum=0,kp=0,mp=0,t1,t2;
                        char fed[21],fed1[21];
                        int prod;
                        while(hi[gp]!='('){
                                fed[20-gp]=hi[gp];                            
                                gp++;
                            }
                            while(hi[kp]!=')'){
                                    if(t1==1){
                                        rsr[mp]=hi[kp];                                    
                                        mp++;
                                    }
                                    if(hi[kp]=='('){
                                        t1=1;
                                    }
                                    kp++;
                                }
                                rsr[mp]=NULL;
                                rs1=rsr;
                            for(int kk=21-gp;kk<21 ;kk++)
                            {
                                prod=pow(10,kk+gp-21);
                                if(fed[kk]!='-')
                                sum=sum+(((int)fed[kk]-48)*prod);
                            }bitset<12> immed(sum);
                             if((int)hi[0]=='-')
                            {int brk=0;
                                for(int vuv=0;vuv<12;vuv++){immed[vuv]=1-immed[vuv];}
                                for(int zuz=0;zuz<12 && brk==0;zuz++)
                                {
                                    if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                                    else{
                                        immed[zuz]=0;
                                    }
                                }
                            }
                                    rd=terms[1];     
                                        rd=terms[1];bitset<7> opc("0000011");bitset<3> f3("101");
                                        i_code(opc,immed,f3,rs1,rd);
            }
    }



    
if(terms[0]=="lwu")
    {  
                int gp=0,sum=0,kp=0,mp=0,t1=0,t2;
                string hi;
                char rsr[3];
                hi=terms[2];
                int linn3=0;
                char fed[21],fed1[21];
                int prod,tkt=0;
                if((int)hi[0]<60)
                {tkt=1;}
            if(tkt==0)
            {
                rd=terms[1];
                bitset<20> immed1(65536);bitset<7> opc1("0010111");
                u_code(opc1,immed1,rd); 
                rs1=terms[1];          
                linn3=label_lineno(hi);
                int offset=(linn3-no_of_machinecodes-1)*4 ;
                int gvg=0;
                if(offset<0){gvg=1;
                offset=offset*(-1);offset=offset;
                }bitset<12> immed(offset);
                if(gvg==1)
                {int brk=0;
                    for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
                    for(int zuz=0;zuz<13 && brk==0;zuz++)
                    {
                        if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                    else{
                        immed[zuz]=0;
                    }
                    }
                }                
                bitset<7> opc("0000011");bitset<3> f3("110");
                i_code(opc,immed,f3,rs1,rd);

            }
            if(tkt==1){
                        string hi = terms[2];
                        int gp=0,sum=0,kp=0,mp=0,t1,t2;
                        char fed[21],fed1[21];
                        int prod;
                        while(hi[gp]!='('){
                                fed[20-gp]=hi[gp];                            
                                gp++;
                            }
                            while(hi[kp]!=')'){
                                    if(t1==1){
                                        rsr[mp]=hi[kp];                                    
                                        mp++;
                                    }
                                    if(hi[kp]=='('){
                                        t1=1;
                                    }
                                    kp++;
                                }
                                rsr[mp]=NULL;
                                rs1=rsr;
                            for(int kk=21-gp;kk<21 ;kk++)
                            {
                                prod=pow(10,kk+gp-21);
                                if(fed[kk]!='-')
                                sum=sum+(((int)fed[kk]-48)*prod);
                            }bitset<12> immed(sum);
                             if((int)hi[0]=='-')
                            {int brk=0;
                                for(int vuv=0;vuv<12;vuv++){immed[vuv]=1-immed[vuv];}
                                for(int zuz=0;zuz<12 && brk==0;zuz++)
                                {
                                    if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                                    else{
                                        immed[zuz]=0;
                                    }
                                }
                            }
                                    rd=terms[1];     
                                        rd=terms[1];bitset<7> opc("0000011");bitset<3> f3("110");
                                        i_code(opc,immed,f3,rs1,rd);
            }
    }



    if(terms[0]=="addi")
    {         
        string hi=terms[3];
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
        while(hi[gp]!='(' && hi[gp]!=NULL){
        fed[20-gp]=hi[gp];gp++;}
    for(int kk=21-gp;kk<21 ;kk++){
        prod=pow(10,kk+gp-21);
        if(fed[kk]!='-')
        sum=sum+(((int)fed[kk]-48)*prod);
    }
     rd=terms[1];       rs1=terms[2];bitset<12> immed(sum);
        if((int)hi[0]=='-')
        {int brk=0;
            for(int vuv=0;vuv<12;vuv++){immed[vuv]=1-immed[vuv];}
            for(int zuz=0;zuz<12 && brk==0;zuz++)
            {
                if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                else{
                    immed[zuz]=0;
                }
            }
        }
        rd=terms[1];bitset<7> opc("0010011");bitset<3> f3("000");
        i_code(opc,immed,f3,rs1,rd);
    }

    if(terms[0]=="slli")
    {   string hi=terms[3];
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
        while(hi[gp]!='(' && hi[gp]!=NULL){
        fed[20-gp]=hi[gp];gp++;}
    for(int kk=21-gp;kk<21 ;kk++){
        prod=pow(10,kk+gp-21);
        sum=sum+(((int)fed[kk]-48)*prod);
    }
     rd=terms[1];       rs1=terms[2];bitset<12> immed(sum);
        rd=terms[1];bitset<7> opc("0010011");bitset<3> f3("001");
        i_code(opc,immed,f3,rs1,rd);
    }

    if(terms[0]=="lui"){
            rd=terms[1];
            string hi=terms[2];
               int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
            while(hi[gp]!=NULL){
            fed[20-gp]=hi[gp];gp++;}
        for(int kk=21-gp;kk<21 ;kk++){
            prod=pow(10,kk+gp-21);
            sum=sum+(((int)fed[kk]-48)*prod);
        }
        bitset<20> immed(sum);bitset<7> opc("0110111");
        u_code(opc,immed,rd);
    }
    if(terms[0]=="auipc"){
            rd=terms[1];
               int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
            string hi=terms[2];
            while(hi[gp]!=NULL){
            fed[20-gp]=hi[gp];gp++;}
        for(int kk=21-gp;kk<21 ;kk++){
            prod=pow(10,kk+gp-21);
            sum=sum+(((int)fed[kk]-48)*prod);
        }
        bitset<20> immed(sum);bitset<7> opc("0010111");
        u_code(opc,immed,rd);
    }




     if(terms[0]=="slti")
    {         
        string hi=terms[3];
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
        while(hi[gp]!='(' && hi[gp]!=NULL){
        fed[20-gp]=hi[gp];gp++;}
    for(int kk=21-gp;kk<21 ;kk++){
        prod=pow(10,kk+gp-21);
        sum=sum+(((int)fed[kk]-48)*prod);
    }
     rd=terms[1];       rs1=terms[2];
        bitset<12> immed(sum);rd=terms[1];bitset<7> opc("0010011");bitset<3> f3("010");
        i_code(opc,immed,f3,rs1,rd);
    }   
        
     if(terms[0]=="srai")
    {         
        string hi=terms[3];
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
        while(hi[gp]!='(' && hi[gp]!=NULL){
        fed[20-gp]=hi[gp];gp++;}
    for(int kk=21-gp;kk<21 ;kk++){
        prod=pow(10,kk+gp-21);
        sum=sum+(((int)fed[kk]-48)*prod);
    }
    sum=sum+pow(2,10);
     rd=terms[1];       rs1=terms[2];
        bitset<12> immed(sum);
        rd=terms[1];bitset<7> opc("0010011");bitset<3> f3("101");
        i_code(opc,immed,f3,rs1,rd);
    }   
        
    if(terms[0]=="xori")
    {
         string hi=terms[3];
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
        while(hi[gp]!='(' && hi[gp]!=NULL){
            fed[20-gp]=hi[gp];gp++;}
        for(int kk=21-gp;kk<21 ;kk++){
            prod=pow(10,kk+gp-21);
            sum=sum+(((int)fed[kk]-48)*prod);
         }
         rd=terms[1];       rs1=terms[2];
        bitset<12> immed(sum);rd=terms[1];bitset<7> opc("0010011");bitset<3> f3("100");
        i_code(opc,immed,f3,rs1,rd);
    }

    if(terms[0]=="srli")
    {   
            string hi=terms[3];
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
        while(hi[gp]!='(' && hi[gp]!=NULL){
            fed[20-gp]=hi[gp];gp++;}
        for(int kk=21-gp;kk<21 ;kk++){
            prod=pow(10,kk+gp-21);
            sum=sum+(((int)fed[kk]-48)*prod);
        }
            rd=terms[1];       rs1=terms[2];
            bitset<12> immed(sum);rd=terms[1];bitset<7> opc("0010011");bitset<3> f3("101");
            i_code(opc,immed,f3,rs1,rd);
    }

    if(terms[0]=="ori")
    {    string hi=terms[3];
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
        while(hi[gp]!='(' && hi[gp]!=NULL){
            fed[20-gp]=hi[gp];gp++;}
        for(int kk=21-gp;kk<21 ;kk++){
            prod=pow(10,kk+gp-21);
            sum=sum+(((int)fed[kk]-48)*prod);
        }
            rd=terms[1];       rs1=terms[2];
            bitset<12> immed(sum);rd=terms[1];bitset<7> opc("0010011");bitset<3> f3("110");
            i_code(opc,immed,f3,rs1,rd);
    }

    if(terms[0]=="andi")
    {    string hi=terms[3];
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
        char fed[21],fed1[21];int prod;
        while(hi[gp]!='(' && hi[gp]!=NULL){
            fed[20-gp]=hi[gp];gp++;}
        for(int kk=21-gp;kk<21 ;kk++){
            prod=pow(10,kk+gp-21);
            sum=sum+(((int)fed[kk]-48)*prod);
        }
            rd=terms[1];       rs1=terms[2];
            bitset<12> immed(sum);rd=terms[1];bitset<7> opc("0010011");bitset<3> f3("111");
            i_code(opc,immed,f3,rs1,rd);
    }

    if(terms[0]=="jal")
    {   string hi=terms[1];int lin=label_lineno(hi);int diff =(lin-line_bck)*4;
        bitset<20> immed(diff);rd="x1";bitset<7> opc("1101111");
        uj_code(opc,immed,rd);
    }
    if(terms[0]=="jalr")
    {   
        string hi=terms[2];int gp=0,sum=0,kp=0,mp=0;
        char fed[21],fed1[21],rsr[4];int prod,t1,t2;
        while(hi[gp]!='('){fed[20-gp]=hi[gp];}
        while(hi[kp]!=')'){
             if(t1==1 && t2!=1){rsr[mp]=hi[kp];mp++;}if(hi[kp]=='('){t1=1;}
            if(hi[kp]==')'){t2=1;} kp++;}rs1=rsr;
        for(int kk=21-gp;kk<21 ;kk++){prod=pow(10,kk+gp-21);
            sum=sum+(((int)fed[kk]-48)*prod);}
        bitset<12> immed(sum);rd=terms[1];bitset<7> opc("1100111");bitset<3> f3("000");
        i_code(opc,immed,f3,rs1,rd);
    }
      if(terms[0]=="beq")
    {   string hi=terms[3];int lin=label_lineno(hi);int diff =(lin-line_bck)*4;
       int gvg=0;
        if(diff<0){gvg=1;
            diff=diff*(-1);diff=diff-4;
        }bitset<13> immed(diff);
        if(gvg==1)
        {int brk=0;
            for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
            for(int zuz=0;zuz<13 && brk==0;zuz++)
            {
                if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                else{
                    immed[zuz]=0;
                }
            }
        }
       rs1=terms[1];rs2=terms[2];bitset<7> opc("1100011");bitset<3> f3("000");
        sb_code(opc,immed,f3,rs1,rs2);
    }
        if(terms[0]=="bne")
    {   string hi=terms[3];int lin=label_lineno(hi);int diff =(lin-line_bck)*4;
       int gvg=0;
        if(diff<0){gvg=1;
            diff=diff*(-1);diff=diff-4;
        }bitset<13> immed(diff);
        if(gvg==1)
        {int brk=0;
            for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
            for(int zuz=0;zuz<13 && brk==0;zuz++)
            {
                if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                else{
                    immed[zuz]=0;
                }
            }
        }
       rs1=terms[1];rs2=terms[2];bitset<7> opc("1100011");bitset<3> f3("001");
        sb_code(opc,immed,f3,rs1,rs2);
    }
        if(terms[0]=="bge")
    {   string hi=terms[3];int lin=label_lineno(hi);int diff =(lin-line_bck)*4;
       int gvg=0;
        if(diff<0){gvg=1;
            diff=diff*(-1);diff=diff-4;
        }bitset<13> immed(diff);
        if(gvg==1)
        {int brk=0;
            for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
            for(int zuz=0;zuz<13 && brk==0;zuz++)
            {
                if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                else{
                    immed[zuz]=0;
                }
            }
        }
       rs1=terms[1];rs2=terms[2];bitset<7> opc("1100011");bitset<3> f3("101");
        sb_code(opc,immed,f3,rs1,rs2);
    }
        if(terms[0]=="blt")
    {   string hi=terms[3];int lin=label_lineno(hi);int diff =(lin-line_bck)*4;
       int gvg=0;
        if(diff<0){gvg=1;
            diff=diff*(-1);diff=diff-4;
        }bitset<13> immed(diff);
        if(gvg==1)
        {int brk=0;
            for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
            for(int zuz=0;zuz<13 && brk==0;zuz++)
            {
                if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                else{
                    immed[zuz]=0;
                }
            }
        }
       rs1=terms[1];rs2=terms[2];bitset<7> opc("1100011");bitset<3> f3("100");
        sb_code(opc,immed,f3,rs1,rs2);
    }
        if(terms[0]=="bgeu")
    {   string hi=terms[3];int lin=label_lineno(hi);int diff =(lin-line_bck)*4;
       int gvg=0;
        if(diff<0){gvg=1;
            diff=diff*(-1);diff=diff-4;
        }bitset<13> immed(diff);
        if(gvg==1)
        {int brk=0;
            for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
            for(int zuz=0;zuz<13 && brk==0;zuz++)
            {
                if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                else{
                    immed[zuz]=0;
                }
            }
        }
       rs1=terms[1];rs2=terms[2];bitset<7> opc("1100011");bitset<3> f3("111");
        sb_code(opc,immed,f3,rs1,rs2);
    }
        if(terms[0]=="bltu")
    {   string hi=terms[3];int lin=label_lineno(hi);int diff =(lin-line_bck)*4;
       int gvg=0;
        if(diff<0){gvg=1;
            diff=diff*(-1);diff=diff-4;
        }bitset<13> immed(diff);
        if(gvg==1)
        {int brk=0;
            for(int vuv=0;vuv<13;vuv++){immed[vuv]=1-immed[vuv];}
            for(int zuz=0;zuz<13 && brk==0;zuz++)
            {
                if(immed[zuz]==0){immed[zuz]=1;brk=1;}
                else{
                    immed[zuz]=0;
                }
            }
        }
       rs1=terms[1];rs2=terms[2];bitset<7> opc("1100011");bitset<3> f3("110");
        sb_code(opc,immed,f3,rs1,rs2);
    }

    if(terms[0]=="sw")
    {
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
   char fed[21],fed1[21];
   int prod;
   rs2=terms[1];
   char rsr[4];
   string hi=terms[2];
   while(hi[gp]!='('){
        fed[20-gp]=hi[gp];
        gp++;
    }
    while(hi[kp]!=')'){
             if(t1==1 && t2!=1){
                rsr[mp]=hi[kp];
                mp++;
            }
            if(hi[kp]=='('){
                t1=1;
            }
            if(hi[kp]==')'){
                t2=1;
            }kp++;
        }
        rsr[mp]=NULL;
        rs1=rsr;        
    for(int kk=21-gp;kk<21 ;kk++)
    {
        prod=pow(10,kk+gp-21);
        sum=sum+(((int)fed[kk]-48)*prod);
    }
    bitset<13> immed(sum);bitset<7>opc("0100011");bitset<3> f3("010");
    sb_code(opc,immed,f3,rs1,rs2);
    }

 if(terms[0]=="sb")
    {
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
   char fed[21],fed1[21];
   int prod;
   rs2=terms[1];
   char rsr[4];
   string hi=terms[2];
   while(hi[gp]!='('){
        fed[20-gp]=hi[gp];        
        gp++;
    }
    while(hi[kp]!=')'){
             if(t1==1 && t2!=1){
                rsr[mp]=hi[kp];
                mp++;
            }
            if(hi[kp]=='('){
                t1=1;
            }
            if(hi[kp]==')'){
                t2=1;
            }kp++;
        }
        rsr[mp]=NULL;
        rs1=rsr;        
    for(int kk=21-gp;kk<21 ;kk++)
    {
        prod=pow(10,kk+gp-21);
        sum=sum+(((int)fed[kk]-48)*prod);
    }
    bitset<13> immed(sum);bitset<7>opc("0100011");bitset<3> f3("000");
    sb_code(opc,immed,f3,rs1,rs2);
    }

     if(terms[0]=="sh")
    {
        int gp=0,sum=0,kp=0,mp=0,t1,t2;
   char fed[21],fed1[21];
   int prod;
   rs2=terms[1];
   char rsr[4];
   string hi=terms[2];
   while(hi[gp]!='('){
        fed[20-gp]=hi[gp];        
        gp++;
    }
    while(hi[kp]!=')'){
             if(t1==1 && t2!=1){
                rsr[mp]=hi[kp];
                mp++;
            }
            if(hi[kp]=='('){
                t1=1;
            }
            if(hi[kp]==')'){
                t2=1;
            }kp++;
        }
        rsr[mp]=NULL;
        rs1=rsr;        
    for(int kk=21-gp;kk<21 ;kk++)
    {
        prod=pow(10,kk+gp-21);
        sum=sum+(((int)fed[kk]-48)*prod);
    }
    bitset<13> immed(sum);bitset<7>opc("0100011");bitset<3> f3("001");
    sb_code(opc,immed,f3,rs1,rs2);
    }
    else{
        
        err=1;
    }
}
int main(){
    string line,na;
        line_no=0;
       linn= label_lineno(".text");
    ifstream fin1("assem_code.asm");
        myfile.open ("mach_code.mc");
    while( getline(fin1,line)){
        line_bck++;
       // line_no++;
        extract_terms(line);
    }
    
        myfile.close();
}

