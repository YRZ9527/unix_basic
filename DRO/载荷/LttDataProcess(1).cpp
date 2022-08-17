// LttDataProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LttDataProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#include <iostream.h>
#include <io.h>
#include <ctype.h>
#include <stdlib.h>
#include <Mmsystem.h>
#include "time.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>


struct OFmidrec
{
   double R;   
   double A;   
   double H ;  
   double th;  
   double Tf; 
};

double dbUpLimit=0.0,dbDownLimit=0.0;
double dbSigma=2.2,dbFre=10000,dbPointsPerZu=5000;
long nNumResult=0;

CFile *outputFile;
CFile *outputFile1;
CFile *timeInfroFile;

OFmidrec result[100000] ;//As OFmidrec
OFmidrec result1[100000] ;//As OFmidrec

double resid; //As Double
int num1,num2,numocTmp=0,numocTmp1=0,numResult=0;
int Numlasd1 , Numlasd2,echopulse,numocTmp2=0;
char chTimerDataFile[100];
__int64 nCurrent64Tmp=0;
int bflagaa;
double epochtmp;
double RangeTmp ;//As Double
double preStartPulse;// As Double
double preStopPulse ;//As Double
double CorrTime=0;
int TimerCount=0;
int	ITBms=0;
int NumOC_Combine=0;
double Stime=0;
int Numoc1=0;
double Ptime=0;// As Double
int Numoc2=0;// As Long
double Stime1=0;// As Double
double ra1, ra2 , ra3 ;
int StartFlag;
int DataFlag;
double StartEp[20000] ;//As Double
double StartEp1[20000] ;//As Double
double StopEp[20000] ;//As Double
int StartEpI[20000];// As Integer
int StopEpI[20000] ;//As Integer
int NStart;// As Long
int NStop ;//As Long
double RGD[20000] ;//As Double 'predict range
int Icomb ;//As Integer     'signal
int nFlagSecondProcess=-1;
double dbFlagRMS=0.0;

int NumEchoPulse ;//As Long
int NumStartPulse ;//As Long
int NumO_C ;//As Long
double EchoPulseTmp; //As Double
double EchoPulseTmpI; //As Double
double preEchoPulseTmp; //As Double
BOOL bNearTarget=TRUE;
BOOL bChange ;//As Boolean                             'Combine_Start_Stop
float picScaleChange ;//As Single

double DiffLim;// As Double
int CurNStop ;//As Integer
int IFlag;// As Integer

double ET_TI;// As Double 'main pluse
double ET_Ep ;//As Double 'observed range
int num400Old ;//As Long
int nGateScale;					//门控调节的尺度
int Differ;						//调节距离门时的一个变量
double Diff;					//距离残差O-C
int inum;
LONG Imaxnum;
double Fmean,FSqd,Rerate,Arv,dsigma;
long intselect;
long intselect2;
CString strtt,strtt1,strtt2;
double ddtmp,ddtmp1;
int nfreq;
long Numtmp;
int  sflag;
int  ssflag;
double sstarttime;
BOOL Flagfile=false;            //文件保存
BOOL Flagsigma1=false;   
BOOL Flagsigma2=false;
CString strCurDate;//current date
/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

void getComputerDate()
{
	CString strY,strM,strD,strPath,strDate;
	int nY,nM,nD;
	CTime time=CTime::GetCurrentTime ();
    nY=time.GetYear();
	nM=time.GetMonth ();
	nD=time.GetDay();

	strY.Format("%d",nY);
	strM.Format("%d",nM);
	strD.Format("%d",nD);
	 
    if (nM < 10) strM.Format("0%d",nM);
    if (nD < 10) strD.Format("0%d",nD);
    strDate= strY + "-" + strM + "-" + strD;
	strCurDate=strDate;
    //m_date.SetWindowText(strDate);
}

void GetMean()
{
	Fmean=0;
    for(int i=0;i<intselect;i++)
	{
		Fmean=Fmean+result1[i].R;	

	}
	if(intselect!=0)  Fmean=Fmean/intselect;
}

void calMean() 
{
    long intselect1,i,j;
    int intnumber;
	double timeDiffer,nsigma;
	CString strtt3,strtt4,strtmp;
	
	
    intselect=0;
	for(i=0;i<(int)dbPointsPerZu;i++)
	{
		Fmean=Fmean+result[i].R;	
		//	
		result1[intselect]=result[i];
		intselect=intselect+1;
		//strtmp.Format("%.12f,  %.12f",result1[1].th,result1[intselect].th);
		//	MessageBox(strtmp);
	}
	//m_rate.GetWindowText(strtt3);
	
    timeDiffer=(result1[intselect].th-result1[1].th)*dbFre;
	if(intselect>0)  Fmean=Fmean/intselect;
	
	if(intselect>0) 
	{
		intselect1=intselect;
xia:
		intnumber=0;
		FSqd=0;
		intselect1=intselect;
		GetMean();
		for(i=0;i<intselect;i++)
		{
			FSqd=FSqd+(result1[i].R-Fmean)*(result1[i].R-Fmean);
		}
		FSqd=sqrt(FSqd/(intselect-1));
		
		for(i=0;i<intselect;i++)
		{
			if(fabs(result1[i].R-Fmean)>FSqd*dbSigma)
			{
				for(j=i;j<intselect1-1;j++)
				{
					result1[j]=result1[j+1];
				}
				intselect1=intselect1-1;
				intnumber=intnumber+1;
			}
			if(i>intselect1) break;
		}
		intselect=intselect-intnumber;
		
		//	curDBval=Fmean;
		//	MessageBox("ccc2");
		//	strtmp.Format("%.12f,  %.12f",result1[1].th,result1[intselect].th);
		//	MessageBox(strtmp);
		intselect2=intselect;
		
		FSqd=0;
		intselect1=intselect;
		intselect2=intselect;
		GetMean();
		for(i=0;i<intselect;i++)
		{
			FSqd=FSqd+(result1[i].R-Fmean)*(result1[i].R-Fmean);
		}
		FSqd=sqrt(FSqd/(intselect-1));
		
		if(intnumber!=0) goto xia;
		
		//Arv=(result1[intselect-1].th-result1[0].th)/2;
		timeDiffer=(result1[intselect-1].th-result1[0].th)*dbFre;
		if(timeDiffer>0) Rerate=(intselect/timeDiffer*100.);
		//dsigma=nsigma;
		//	intselect2=intselect;
		intselect=0;
	}
	//屏幕显示
    double dbRMS1=FSqd*1000000;
	CString strTemp;
    if(nFlagSecondProcess==0)//不进行二次处理
	{
		printf(" %14.12f     %8.6f    %8.6f     %3.1f     %5.2f     %5d\n",result1[0].th,result1[intselect2-1].th-result1[0].th,Fmean*1000,FSqd*1000000.0,Rerate,intselect2);
		//文件保存
		DWORD dwFileEnd;
		dwFileEnd=outputFile1->SeekToEnd();//文件写指针指向文件最后
		
		strTemp.Format("1= %.12f             %.6f            %.6f           %.1f          %.2f           %ld",result1[1].th,result1[intselect2-1].th-result1[1].th,Fmean*1000000,FSqd*1000000,Rerate,intselect2);//,result[pointnum].A);
		strTemp+="        "+strCurDate;//+strDBFileName;
		strTemp+="\r\n";
		outputFile1->Write(strTemp,strlen(strTemp));
	}else if(nFlagSecondProcess==1)//进行二次处理
	{
		if(dbRMS1<dbFlagRMS)
		{
			printf("2= %14.12f     %8.6f    %8.6f     %3.1f     %5.2f     %5d\n",result1[0].th,result1[intselect2-1].th-result1[0].th,Fmean*1000,FSqd*1000000.0,Rerate,intselect2);
			//文件保存
			DWORD dwFileEnd;
			dwFileEnd=outputFile1->SeekToEnd();//文件写指针指向文件最后
			//CString strTemp;
			strTemp.Format(" %.12f             %.6f            %.6f           %.1f          %.2f           %ld",result1[1].th,result1[intselect2-1].th-result1[1].th,Fmean*1000000,FSqd*1000000,Rerate,intselect2);//,result[pointnum].A);
			strTemp+="        "+strCurDate;//+strDBFileName;
			strTemp+="\r\n";
			outputFile1->Write(strTemp,strlen(strTemp));
		}

	}
	if(nNumResult % 4==0)
	{
		CStdioFile file;
		//CString strTemp;
		if(!file.Open("d:\\kHz_SLR\\TR\\ltt_process_result.DAT",CFile::modeCreate|CFile::modeWrite))
		{
			return;
		}
        file.WriteString(strTemp);
		file.Close();
        nNumResult=0;
	
	
	}
	nNumResult++;


}

void Combine_Start_Stop() //''''''''''''''''''''''''''''''处理主回波对应
{
	//*****time for test start
	 LARGE_INTEGER litmp; 
	 LONGLONG QPart1,QPart2; 
	 
     double  dfMinus,dfFreq, dfTim; 
	 CString strtmp;
	// double ddtmp,ddtmp1;
	 QueryPerformanceFrequency(&litmp); 
	 dfFreq = (double)litmp.QuadPart; // 获得计数器的时钟频率
	 QueryPerformanceCounter(&litmp); 
	 QPart1 = litmp.QuadPart; // 获得初始值
	//******
	double diff;
	int Nval;
	float DiffOCTmp;
	CString strTmp;
	
	DiffLim = 30.0 / 1000000.0;
	Icomb = 0;
	IFlag = -1;
	//' If (NStart > 0) And (NStop > 0) Then
	if (NStart > 0)
	{
		for(int i = 0;i<=NStart - 1;i++)
		{
			diff = EchoPulseTmp - StartEp[i] - RGD[i];

			//strTmp.Format("%.12f\r\n",RGD[i]);
			//MessageBox(strTmp);
			//m_oc_num.SetCaption(strTmp);
			//timeInfroFile->Write(strTmp,strlen(strTmp));
			if (fabs(diff) < DiffLim)// 'And diff > (0.0000001 * PreRange)
			{
				IFlag = i;
				if( NumOC_Combine == 0)
				{
					Stime = StartEp[i];
					NumOC_Combine++;
				}
				if ((StartEp[i] - Stime) >= 1.0)
				{
					if (NumOC_Combine>300000) NumOC_Combine=300000;
					
					
					//strTime.Format("AB******%d\r\n",Numoc2);
					
					//timeInfroFile->Write(strTmpNum,strlen(strTmpNum));
					
				    //if(nNumResult%)printf("每秒钟主回波配对数 %d \n",NumOC_Combine);
				//	SendMessage(WM_SHOW_NUM_OC,0,0);
				
					NumOC_Combine = 0;
				}
				else
					NumOC_Combine++;

				numocTmp++;
				if (numocTmp==10)
				{
					//strTmpNum.Format("%d",NumO_C);
					//m_oc_num.SetCaption(strTmpNum);
					numocTmp=0;
				}
				
				break;
			}
		}
		if (IFlag >= 0 )
		{
			
			//*****
			//***time test stop
/*			QueryPerformanceCounter(&litmp); 
			QPart2 = litmp.QuadPart;// 获得中止值 
			dfMinus = (double)(QPart2-QPart1); 
			dfTim = dfMinus / dfFreq; // 获得对应的时间值，单位为秒
			
			CString strTime;
			strTime.Format("Combine Time: %.7f\r\n",dfTim);
			timeInfroFile->Write(strTime,strlen(strTime));*/
			//*****	
			//*****
			
			//' ET_TI = StopEp(0) - StartEp(IFlag)
			ET_TI = EchoPulseTmp - StartEp[IFlag];
			ET_TI =-ET_TI;

			// 'ET_TI = (Int(ET_TI * 10000000000# + 1) * 100 + StopEpI(0) - StartEpI(IFlag)) * 0.000000000001
			//ET_TI = (Int(ET_TI * 10000000000# + 1) * 100 + EchoPulseTmpI - StartEpI(IFlag)) * 0.000000000001
			//         Label24.Caption = Format(ET_TI * 1000000, "#0.00") + "us"
			ET_Ep = StartEp[IFlag];
			resid = ET_TI - RGD[IFlag];
		/*	CString strTime;
			strTime.Format("A: %.10f\r\n",ET_Ep);
			timeInfroFile->Write(strTime,strlen(strTime));*/
            numocTmp1++;
			if(numocTmp1==35000)
			{
		    	//strTmpNum.Format("%.3f",resid*1000000.0);
				//m_oc.SetCaption(strTmpNum);
			//	SendMessage(WM_SHOW_OC);
				numocTmp1=0;
				
			}
			
			Diff=resid*1000000.0; //距离残差us as unit

			/*m_rg.GetWindowText(strtt);
			m_rg1.GetWindowText(strtt1);
			m_imaxnum.GetWindowText(strtt2);
			if(strtt!="" && strtt1!="")
			{
               ddtmp=atof(strtt);
               ddtmp1=atof(strtt1);
			}
			else		
			{
				ddtmp1=0.1;
				ddtmp=0.3;
			}*/

		//	ddtmp1=0.0;
		//	ddtmp=0.5;
            //	strtmp.Format("%.12f, %.12f",fabs(ET_TI),ddtmp1);
				
			if(((ET_TI)* 1000000.0>dbDownLimit) && ((ET_TI)* 1000000.0<dbUpLimit))//if (true)//((resid * 1000000.0 < picScaleChange) && (resid * 1000000.0 > -1.0*picScaleChange))// 'within limite of oc
			{

				result[numResult].th = StartEp1[IFlag]; // s as unit
				result[numResult].A = EchoPulseTmp; // us as unit
				result[numResult].H = 43.0766;
				result[numResult].R = ET_TI * 1000000.0; //us as unit
			
				RangeTmp = RGD[IFlag];
				numResult = numResult + 1;
		
				// '**** two filter
				//bReturnDetected=FALSE;
                if((fabs(ET_TI)* 1000000.0>dbDownLimit) && (fabs(ET_TI)* 1000000.0<dbUpLimit))
				{
				  if(NumO_C % 5 ==0) //当10万点时事件计时器初始化
				  {
				//    ReturnDetetion();
				  }
				}

				NumO_C++;
				
				//if(numResult == 1)
				/*m_rg.GetWindowText(strtt);
				if(strtt!="")
				{
                ddtmp=atof(strtt);
				}
				else
					ddtmp=0.1;*/
				
/*
				if(fabs(ET_TI * 1000000.0-ddtmp)<0.2/300)
				{
				AutoSave();
				}*/

		//		numResult = 0;
			

				if(bNearTarget==TRUE) //在测量地靶时，当采集的数据点大于5万时，调用地靶处理程序
				{
				//	MessageBox("aaa");
					
				//	Imaxnum=5000;
					if(NumO_C>dbPointsPerZu)
					{
										
						
						//	strtmp.Format("%.12f,  %.12f",result[1].th,result[numResult].th);
						//	MessageBox(strtmp);
						calMean();
						if(Flagfile==true)
						{	
							//	AutoSave();
						}	
						//Resave();
						//Showparam();
						NumO_C=0;	
						numResult=0;
							//	  OnKeyDown(76,0,0); //开始数据采集
						}
						
				}
				//if(NumO_C % 10000 ==0) //当10万点时事件计时器初始化
				//{
					//Start_Measure();
				//}

			}
			numocTmp2++;
			//if(numocTmp2==nScalePointShow)
			{
				//if((Diff>double(nPreRange)/nGateScale))
				{
				//	PaintRes();
					
				}
				numocTmp2=0;
			}
			
			Nval = 0;
			for(int i = IFlag + 1;i<=NStart - 1;i++)
			{
				StartEp[Nval] = StartEp[i];
				StartEp1[Nval] = StartEp1[i];
				//StartEpI[Nval] = StartEpI[i];
				RGD[Nval] = RGD[i];
				Nval++;
			}
			NStart = Nval;
			Icomb = 1;
		}
		//'Debug.Print "xx"; ET_Ep, ET_TI, Resid
		// '''''''''''''''''''''''''''''''''''''''
		//''       For i = 1 To NStop - 1
		//''               StopEp(i - 1) = StopEp(i)
		//''               StopEpI(i - 1) = StopEpI(i)
		//''       Next i
		//''       NStop = NStop - 1
		//''''''''''''''''''''''''''''''''''''''''''
	}
	//*****
	//***time test stop
	QueryPerformanceCounter(&litmp); 
	QPart2 = litmp.QuadPart;// 获得中止值 
	dfMinus = (double)(QPart2-QPart1); 
	dfTim = dfMinus / dfFreq; // 获得对应的时间值，单位为秒
	
	//CString strTime;
	//strTime.Format("Combine Time: %.7f\r\n",dfTim);
	//timeInfroFile->Write(strTime,strlen(strTime));
	//*****	
	//*****
}

void DataProcess(unsigned char *ByteData,unsigned long uLong) //对获取的数据进行处理
{
	
	unsigned long ii;
	Numoc2=0;
	Numoc1=0;
	double dbA,dbB,dbC,dbD,dbTmp,epoch;
	double dbChannelA,dbChannelB;
	double dbABChannelDataA,dbABChannelDataA1,dbABChannelDataB,dbABChannelDataB1,dbABChannelData;

	double 	
		dPeriod,				// periodicity (ms)
		//dTime[POINTNUMB],		// time points for above functions
		startTime,				// the measurement beginning
	    dTimePreA, 
		dbTimeCyclesA,
		dTimePreB, 
		dbTimeCyclesB,vvvTmp,
		dTimeTek;			// Variables for counter overflow control.

	int eventNumb=0,nTimeCyclesA=0,nTimeCyclesB=0;
	int nFlag=-1;
	double dbTmp11,dbTmpCuJishu1;

	for(ii=0;ii<uLong;ii+=8) //正在解析计时器数据,八个字节
	{
		double dbII,dbFileLen;		
		if(ii < (uLong - 8))
		{
			int nTmp;
			nTmp=ByteData[ii + 4] & 0x30;

            double dbTmpCuJishu=0;
			dbTmpCuJishu=((ByteData[ii + 4] & 0x3) * pow(2.0,16.0) + ByteData[ii + 5] * pow(2.0,8.0)  + ByteData[ii + 6] ) * 6.99999744;
			
			//printf("粗计数：%f\n",dbTmpCuJishu);

			dbTmp=(ByteData[ii + 7] * pow(2.0,32.0) + ByteData[ii + 8] * pow(2.0,24.0) + ByteData[ii + 9] * pow(2.0,16.0)+ ByteData[ii + 10] * pow(2.0,8.0) + ByteData[ii + 11]) * 0.00000001 / (64.0 * 12.0);
			dTimeTek=dbTmp;
			nFlag=-1;
			switch(nTmp) //判断通道数
			{
			case 0x10:				//b
				dbB=dbTmp;
				break;
			case 0x20   :				//a===回波
				dbD=dbTmp;            
				dbABChannelDataA = dbTmp;
				dbABChannelDataA1=dbTmpCuJishu+dbABChannelDataA;
				//dbABChannelDataA=dbTmpCuJishu+dbABChannelDataA;
				//dbTmpCuJishu1=dbTmpCuJishu;
				//dbABChannelDataA=dbABChannelDataA1;
				nFlag=1;
				break;
			case 0x30:				//c
				dbC=dbTmp;
				break;
				
			case  0x0 :				//d==主波
				dbA=dbTmp;
				dbABChannelDataB= dbTmp;
				//dbABChannelDataB1=dbTmpCuJishu1+dbABChannelDataB;
				//dbABChannelDataB=dbTmpCuJishu1+dbABChannelDataB;
                //dbABChannelDataB=dbTmpCuJishu+dbABChannelDataB;
				nFlag=2;
				break;
			}

			if(nFlag==1) 
			{
				dbABChannelData=dbABChannelDataA;
				//dbABChannelData=dbABChannelData; //ns-->s
			    
				double dbNS;
				dbNS=int(dbABChannelData*1000000.0)/1000000.0; //123.12340012345==123.123400
				dbNS=(dbABChannelData-dbNS)*1000000000.0;//


				CString strTime;
				strTime.Format("A:%.12f      \r\n",dbABChannelDataA1);
			    if(dbABChannelDataA1<86400.0)
				{
				  // timeInfroFile->Write(strTime,strlen(strTime));
				}

			}else if(nFlag==2) 
			{
				dbABChannelData=dbABChannelDataB;
				//dbABChannelData=dbABChannelData; //ns-->s

				CString strTime;
				strTime.Format("b:%.12f      \r\n",dbABChannelDataB1);
			    if(dbABChannelDataB1<86400.0)
				{
				   //timeInfroFile->Write(strTime,strlen(strTime));
				}

				dbTmp11=(dbABChannelData-dbABChannelDataA)*1000000.0;

				if(abs(dbTmp11)<100000.0 && abs(dbTmp11)>1)
				{
					//CString strTime;
				//	strTime.Format("A:%.12f    %.12f\r\n",dbABChannelData,dbTmp11);
				//	timeInfroFile->Write(strTime,strlen(strTime));
					
				}
			}
			
			eventNumb++;
			
			epoch=dbABChannelData;
			if(epoch<0.000005) nFlag=-1; 

			//对于A，B通道进行处理
			if(nFlag == 1)
			{
				if (NStart >= 15000)
				{
					NStart = 0;
					for(int i=0 ;i<20000;i++)
					{
						StartEp[i] = 0.0;
						StartEp1[i] = 0.0;
						StopEp[i] = 0.0;
					}
				}
				
				//if (fabs(epoch-preStartPulse ) > (1.0 / (2.0 * 20000.0)))
				{
					
					StartEp[NStart] = epoch;
					StartEp1[NStart] = dbABChannelDataA1;
					//epochtmp=epoch;
					if(sflag==0)
					{
						sstarttime=epoch;
						sflag=2;
					}
					if(epoch-sstarttime>=21600) //86400
					{
						//OnKeyDown(76,0,0);
						//Sleep(500);
						ssflag=0;
					}
					
					CString strTime;
					
					//strTime.Format("%0.9f",epoch);
					//m_label_mptime.SetCaption(strTime);
					if((StartEp[NStart] - Stime1) >= 1.0)
					{
						//SendMessage(WM_SHOW_MP,0,0);
					}
					
					
					//StartEpI[NStart] = s11 %100;
					//bNearTarget=TRUE;
					bNearTarget=TRUE;
					if (bNearTarget==FALSE)
					{
						//CurRangeTmp=CalRng(StartEp[NStart]);
						//RGD[NStart] = CurRangeTmp / 1000000.0;//+ 2.8 * 0.000001;//  S AS UNIT
					}
					else
					{
						//CurRangeTmp=CalRng(StartEp[NStart]);
						//RGD[NStart] = CurRangeTmp / 1000000.0;//+ 2.8 * 0.000001;//  S AS UNIT
						//m_rg.GetWindowText(strtt);
						//m_rg1.GetWindowText(strtt1);
						if(1 )//strtt!="" && strtt1!=""
						{
						    ddtmp=dbUpLimit;//atof(strtt);
							ddtmp1=dbDownLimit;//atof(strtt1);
							RGD[NStart] = (ddtmp+ddtmp1)/2000000.0;//0.1/ 1000000.0;
						//	RGD[NStart] = (ddtmp+ddtmp1)/2000000.0;//0.1/ 1000000.0;
							//				strtmp.Format("%.12f,  %.12f,  %.12f",ddtmp,ddtmp1,RGD[NStart]);
							//				MessageBox(strtmp);
						}
						else
							RGD[NStart] =0.1/ 1000000.0;
						
					}
					if(Numoc2==0)
					{
						Stime1 = StartEp1[NStart];
						Numoc2 = 1;
					}
					if ((StartEp1[NStart] - Stime1) >= 1.0)
					{
						
						if (Numoc2>200000) Numoc2=200000;
						//strTmpNum.Format("%d",Numoc2);
						//strTime.Format("AA******%d\r\n",Numoc2);
						//printf("每秒钟主波数%d\n",Numoc2);
					
					    //timeInfroFile->Write(strTime,strlen(strTime));
						//m_mp_s.SetCaption(strTmpNum);
						//SendMessage(WM_SHOW_NUM_MP,0,0);
						Numoc2 = 0;
					}
					else
						Numoc2++;
					//ABFlag = 1;
					NStart++;
					preStartPulse = epoch;
					if(1)//bflagaa==
					{
						Combine_Start_Stop();
						bflagaa=0;
					}
				}   
			}
			else
			{
				if (nFlag == 2)
				{
					//if (fabs(epoch-preStopPulse ) > (1.0 / (2.0 * 20000.0)))
					{	
						EchoPulseTmp = epoch;
						
						CString strTime;
						//strTime.Format("b: %.10f\r\n",epoch);
						//timeInfroFile->Write(strTime,strlen(strTime));
						
						if (Numoc1 == 0)
						{
							preEchoPulseTmp = EchoPulseTmp;
							Numoc1 = 1;
						}
						if ((EchoPulseTmp - preEchoPulseTmp) >= 1.0)
						{
							if (Numoc1>20000) Numoc1=20000;
						//	printf("每秒钟回波数% d \n",Numoc2);
				            //timeInfroFile->Write(strTime,strlen(strTime));
							Numoc1 = 0;
						}
						else
							Numoc1++;
						NStop++;
						preStopPulse = epoch;
						if(1)//epoch-epochtmp<0.0001
						{
							//Combine_Start_Stop();
						}
						else
						{
							bflagaa=1;
						}
					}
				}
			}
		}
	}

}


void ReadTimerDataFile(char *chFileName)
{
	printf("计时器数据文件名称: %s\n",chFileName);

	CString strFileName;
	strFileName.Format("%s",chFileName);

	getComputerDate();
	outputFile1=NULL;
	CString FileNameOutput;
	FileNameOutput = "d:\\kHz_SLR\\exe\\"+strCurDate.Mid(0,4)+ strCurDate.Mid(5,2)+ strCurDate.Mid(8,2)+".dat";//+"\\"+ strCurDate.Mid(5,2)+ strCurDate.Mid(8,2);
	outputFile1=new CFile(FileNameOutput,CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	if(outputFile1==NULL)
	{
		printf("打开输出结果文件 %s 失败!\n",FileNameOutput);
		return;
	}
	const char *filename=strFileName;

	struct _stati64 buf;
	__int64 result;
	result = _stati64( filename, &buf );
    
	if( result != 0 )
	{
      printf( "Problem getting information\n" );
	  //return ;
	}
	//创建映射文件
	HANDLE hFile=CreateFile(strFileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		printf("创建文件对象失败\n");
		return;
	}
	//创建文件映射对象
	HANDLE hFileMap=CreateFileMapping(hFile,NULL,PAGE_READONLY,0,0,NULL);
	if(hFileMap==NULL)
	{
		printf("创建文件映射对象失败\n");
		return;
	}
	//获得系统分配颗粒度
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	DWORD dwGran=sysInfo.dwAllocationGranularity;
	//得到文件尺寸
	DWORD dwFileSizeHigh;
	__int64 qwFileSize=GetFileSize(hFile,&dwFileSizeHigh);

    qwFileSize|=(((__int64)dwFileSizeHigh)<<32);
	//关闭文件对象
	CloseHandle(hFile);
	//偏移地址SPAN
	__int64 qwFileOffset=0,qwFileSizeLast=0;
	//块大小
	DWORD dwBlockBytes=1000*dwGran;
	if(qwFileSize<1000*dwGran)
         dwBlockBytes=(DWORD)qwFileSize;
   
    qwFileSizeLast=qwFileSize;

	__int64 n64Tmp=0;
	int nTmp=0;

	unsigned char *ByteData; //1024M byte

	while(qwFileSize>0) // qwFileOffset
	{
	    CString strtMPPP;
		//strtMPPP.Format("%d%%",(nCurrent64Tmp)/qwFileSizeLast*100.0);

		printf("当前处理字节数:  %f Mbyte /总字节数： %f Mbyte  \n",nCurrent64Tmp/1024.0/1024.0,qwFileSizeLast/1024.0/1024.0);
		//et_timeDlg->m_time.SetCaption(strtMPPP);

		//相应外部消息
		
		LPBYTE lpMapAddress=NULL;
		if(qwFileSize>dwBlockBytes)
		{
		//映射视图
		    lpMapAddress=(LPBYTE) MapViewOfFile(hFileMap,FILE_MAP_READ,(DWORD)(qwFileOffset>>32),
			(DWORD)(qwFileOffset&0xFFFFFFFF),dwBlockBytes);
		}
        else
		{
		    lpMapAddress=(LPBYTE) MapViewOfFile(hFileMap,FILE_MAP_READ,(DWORD)(qwFileOffset>>32),
			(DWORD)(qwFileOffset&0xFFFFFFFF),qwFileSize);
			qwFileSizeLast=qwFileSize;
		}
		if(lpMapAddress==NULL)
		{
			printf("映射文件失败\n");
	     	return;
		}
		//对映射的视图进行访问
		if(qwFileSize>dwBlockBytes)
		{
			ByteData=(unsigned char *)malloc(dwBlockBytes*sizeof(unsigned char));//Attention: Free the memory!
			for(DWORD i=0;i<dwBlockBytes;i++)
			{
				BYTE temp=*(lpMapAddress+i);
				ByteData[i]=temp;
				nCurrent64Tmp++;
			}
			DataProcess(ByteData,dwBlockBytes);
			free(ByteData);

		}else
		{
			ByteData=(unsigned char *)malloc(qwFileSize*sizeof(unsigned char));//Attention: Free the memory!
			for(DWORD i=0;i<qwFileSize;i++)
			{
				BYTE temp=*(lpMapAddress+i);
				ByteData[i]=temp;
				nCurrent64Tmp++;
			}
			DataProcess(ByteData,qwFileSize);
			free(ByteData);
		}
		nTmp++;

		if(nTmp>99)nTmp=99;
		//撤销文件映射
		UnmapViewOfFile(lpMapAddress);
			//修正参数
		qwFileOffset+=dwBlockBytes;
		qwFileSize-=dwBlockBytes;
	}
	//关闭文件映射对象句柄
	CloseHandle(hFileMap);

	outputFile1->Close();
	printf("数据处理完毕!!\n");

}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		//cout << (LPCTSTR)strHello << endl;
	}

	timeInfroFile=new CFile("TimeInfor.dat",CFile::modeCreate|CFile::modeWrite);

	char inputFile[128],outputFile1[128],outputFile2[128],buf[130],buf1[20];
	FILE *fp,*fp1;
	int nAddSod=0,nAddDay=0,nReadLine=0;
	
	strcpy(inputFile,"d:\\kHz_SLR\\TR\\parameter.dat");//        !"SLRBD.txt"
	if((fp=fopen(inputFile,"r"))==NULL)
	{
		printf("The File %s doesnot exist!\n",inputFile);
		return 0;
	}
	fgets(buf,130,fp);
	fgets(buf,10,fp);
	buf[10]='\0';
	dbUpLimit=atof(buf);
	//sscanf(buf,"%0.2f",&dbUpLimit);

	fgets(buf,130,fp);
	fgets(buf,10,fp);
	buf[10]='\0';
	dbDownLimit=atof(buf);

	fgets(buf,130,fp);
	fgets(buf,10,fp);
	buf[10]='\0';
	dbSigma=atof(buf);

	fgets(buf,130,fp);
	fgets(buf,10,fp);
	buf[10]='\0';
	dbFre=atof(buf);


	fgets(buf,130,fp);
	fgets(buf,10,fp);
	dbPointsPerZu=atof(buf);

	fgets(buf,130,fp);
	fgets(buf,130,fp);
	strcpy(chTimerDataFile,buf);//        !"SLRBD.txt"
	int nlen=strlen(buf);
	chTimerDataFile[nlen-1]='\0';

	fclose(fp);
	
	printf("%f   %f   %f   %f    %f\n",dbUpLimit,dbDownLimit,dbSigma,dbFre,dbPointsPerZu);


	CStdioFile file2;
	CString strTmp;
		if(!file2.Open("d:\\kHz_SLR\\TR\\FlagSecondProces.dat",CFile::modeRead))
		{
			return 0;
		}
        file2.ReadString(strTmp);
		file2.ReadString(strTmp);
        nFlagSecondProcess=atoi(strTmp);
		file2.ReadString(strTmp);
		file2.ReadString(strTmp);
        dbFlagRMS=atoi(strTmp);

		file2.Close();


	

	CStdioFile file1;
		if(!file1.Open("d:\\kHz_SLR\\TR\\ltt_process_over.DAT",CFile::modeCreate|CFile::modeWrite))
		{
			return 0;
		}
        file1.WriteString("1");
		file1.Close();
	//读取二进制文件
	ReadTimerDataFile(chTimerDataFile);

	CStdioFile file;
		if(!file.Open("d:\\kHz_SLR\\TR\\ltt_process_over.DAT",CFile::modeCreate|CFile::modeWrite))
		{
			return 0;
		}
        file.WriteString("0");
		file.Close();
    
	return nRetCode;
}


