void DataProcess(unsigned char *ByteData,unsigned long uLong) //对获取的数据进行处理
{
	
	unsigned long ii;
	Numoc2=0;
	Numoc1=0;
	double dbA,dbB,dbC,dbD,dbTmp,epoch;
	double dbChannelA,dbChannelB;
	double dbABChannelDataA,dbABChannelDataA1,dbABChannelDataB,dbABChannelDataB1,dbABChannelData;
	double dbABChannelDataC,dbABChannelDataC1,dbABChannelDataD,dbABChannelDataD1;

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
			double dbTmpCuJishu=0,dbTmpCuJishuA=0,dbTmpCuJishuB=0,dbTmpCuJishuC=0,dbTmpCuJishuD=0;

			nTmp=ByteData[ii] & 0x30;//判断第几通道
            dbTmpCuJishu=((ByteData[ii] & 0x3) * pow(2.0,16.0) + ByteData[ii + 1] * pow(2.0,8.0) 
				+ ByteData[ii + 2] ) * 7.0; //每个通道时刻周期计数6.99999744
			dbTmp=(ByteData[ii + 3] * pow(2.0,32.0) + ByteData[ii + 4] * pow(2.0,24.0) + ByteData[ii + 5] * pow(2.0,16.0)
				+  ByteData[ii + 6] * pow(2.0,8.0) + ByteData[ii + 7])*db13PS_Unit; //*db13PS_Unit= 0.00000001 / (64.0 * 12.0); //每个通道时刻周期内数据
		    
			//dbTmp=dbTmp/1000000000000.0;

			CString strTMPP,strHEXdata;
            strHEXdata="";
			for(int ij=0;ij<8;ij++)
			{
			    strTMPP=HexToStrHex(ByteData[ii+ij]);
				strHEXdata+=strTMPP;
			}
			strHEXdata+="\n";
			

			dTimeTek=dbTmp;
			if(dbTmp>0.000000001)
			{
				nFlag=-1;
				switch(nTmp) //判断通道数
				{
				case 0x10:				//b
					//dbB=dbTmp;
					
					dbABChannelDataB= dbTmp;
					dbTmpCuJishuB=dbTmpCuJishu;
					dbABChannelDataB1=dbTmpCuJishu+dbABChannelDataB;
					
					//dbABChannelDataB=dbTmpCuJishu1+dbABChannelDataB;
					//dbABChannelDataB=dbTmpCuJishu+dbABChannelDataB;
					nFlag=2;

					break;
				case 0x20:				//a===回波
					//dbD=dbTmp;            
					dbABChannelDataA = dbTmp;
					dbTmpCuJishuA=dbTmpCuJishu;
					dbABChannelDataA1=dbTmpCuJishu+dbABChannelDataA;
					
					//dbABChannelDataA=dbTmpCuJishu+dbABChannelDataA;
					//dbTmpCuJishu1=dbTmpCuJishu;
					//dbABChannelDataA=dbABChannelDataA1;
					nFlag=1;
					break;
				case 0x30:				//c
					dbC=dbTmp;

					dbABChannelDataC= dbTmp;
					dbTmpCuJishuC=dbTmpCuJishu;
					dbABChannelDataC1=dbTmpCuJishu+dbABChannelDataC;
					
					//dbABChannelDataB=dbTmpCuJishu1+dbABChannelDataB;
					//dbABChannelDataB=dbTmpCuJishu+dbABChannelDataB;
					nFlag=3;
					break;
					
				case  0x0 :				//d==主波
					//dbA=dbTmp;
					dbABChannelDataD= dbTmp;
					dbTmpCuJishuD=dbTmpCuJishu;
					dbABChannelDataD1=dbTmpCuJishu+dbABChannelDataD;
					
					//dbABChannelDataB=dbTmpCuJishu1+dbABChannelDataB;
					//dbABChannelDataB=dbTmpCuJishu+dbABChannelDataB;
					nFlag=4;
					break;
				}

			if(nFlag==1) //a 通道
			{
				dbABChannelData=dbABChannelDataA1;
                //dbABChannelData=dbABChannelDataA;
				
				//dbABChannelData=dbABChannelData; //ns-->s
			    
				double dbNS;
				dbNS=int(dbABChannelData*1000000.0)/1000000.0; //123.12340012345==123.123400
				dbNS=(dbABChannelData-dbNS)*1000000000.0;//

				timeInfroFile->Write(strHEXdata,strlen(strHEXdata));
				timeInfroFile->Write("\r\n",2);


				CString strTime;
				strTime.Format("A:%.12f      \r\n",dbABChannelDataA1);
			    if(dbABChannelDataA1<86400.0 && dbABChannelDataA1>0.0)
				{
				   timeInfroFile->Write(strTime,strlen(strTime));
				}

			}else if(nFlag==2) //b通道
			{
				dbABChannelData=dbABChannelDataB1;
				//dbABChannelData=dbABChannelDataB;
				
				//dbABChannelData=dbABChannelData; //ns-->s

				timeInfroFile->Write(strHEXdata,strlen(strHEXdata));
                timeInfroFile->Write("\r\n",2);
				CString strTime;
				strTime.Format("B:%.12f      \r\n",dbABChannelDataB1);
			    if(dbABChannelDataB1<86400.0 &&dbABChannelDataB1>0.0)
				{
				   timeInfroFile->Write(strTime,strlen(strTime));
				}

				dbTmp11=(dbABChannelData-dbABChannelDataA)*1000000.0;

				if(abs(dbTmp11)<100000.0 && abs(dbTmp11)>1)
				{
					//CString strTime;
					//strTime.Format("B:%.12f      \r\n",dbABChannelData);
					//timeInfroFile->Write(strTime,strlen(strTime));
					
				}
			}else if(nFlag==3) //C通道
			{
				dbABChannelData=dbABChannelDataC1;
				//dbABChannelData=dbABChannelDataB;
				
				//dbABChannelData=dbABChannelData; //ns-->s

				timeInfroFile->Write(strHEXdata,strlen(strHEXdata));
				timeInfroFile->Write("\r\n",2);

				CString strTime;
				strTime.Format("C:%.12f      \r\n",dbABChannelDataB1);
			    if(dbABChannelDataC1<86400.0 &&dbABChannelDataC1>0.0)
				{
				   timeInfroFile->Write(strTime,strlen(strTime));
				}

				dbTmp11=(dbABChannelData-dbABChannelDataC)*1000000.0;

				if(abs(dbTmp11)<100000.0 && abs(dbTmp11)>1)
				{
					//CString strTime;
					//strTime.Format("B:%.12f      \r\n",dbABChannelData);
					//timeInfroFile->Write(strTime,strlen(strTime));
					
				}
			}else if(nFlag==4) //D通道
			{
				dbABChannelData=dbABChannelDataD1;
				//dbABChannelData=dbABChannelDataB;
				
				//dbABChannelData=dbABChannelData; //ns-->s

				timeInfroFile->Write(strHEXdata,strlen(strHEXdata));
                timeInfroFile->Write("\r\n",2);
				CString strTime;
				strTime.Format("D:%.12f      \r\n",dbABChannelDataD1);
			    if(dbABChannelDataD1<86400.0 &&dbABChannelDataD1>0.0)
				{
				   timeInfroFile->Write(strTime,strlen(strTime));
				}

				dbTmp11=(dbABChannelData-dbABChannelDataD)*1000000.0;

				if(abs(dbTmp11)<100000.0 && abs(dbTmp11)>1)
				{
					//CString strTime;
					//strTime.Format("B:%.12f      \r\n",dbABChannelData);
					//timeInfroFile->Write(strTime,strlen(strTime));
					
				}
			}
			
			eventNumb++;
			
			epoch=dbABChannelData;
			if(epoch<0.00000005) nFlag=-1; 

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
					StartEp[NStart] =dbTmpCuJishuA ;//epoch;
					StartEp1[NStart] =dbABChannelDataA;//dbABChannelDataA1;
					//epochtmp=epoch;

					CString strTime;
					//strTime.Format("a: %.10f\r\n",epoch);
					//timeInfroFile->Write(strTime,strlen(strTime));

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
					
					
					
					//strTime.Format("%0.9f",epoch);
					//m_label_mptime.SetCaption(strTime);
					if((StartEp[NStart] - Stime1) >= 1.0 && (StartEp[NStart] - Stime1) < 1.1)
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
						Stime1 = StartEp[NStart];
						Numoc2 = 1;
					}
					if ((StartEp[NStart] - Stime1) >= 1.0 && (StartEp[NStart] - Stime1) < 1.1)
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
						EchoPulseTmp =dbTmpCuJishuB ;//epoch;

						EchoPulseTmpI=dbABChannelDataB;
						
						CString strTime;
						//strTime.Format("b: %.10f\r\n",epoch);
						//timeInfroFile->Write(strTime,strlen(strTime));
						
						if (Numoc1 == 0)
						{
							preEchoPulseTmp = EchoPulseTmp;
							Numoc1 = 1;
						}
						if ((EchoPulseTmp - preEchoPulseTmp) >= 1.0 && (EchoPulseTmp - preEchoPulseTmp) < 1.1)
						{
							if (Numoc1>20000) Numoc1=20000;
							//printf("每秒钟回波数% d \n",Numoc1);
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

}
