{
  const int nXY = 128;
  const int nIC = 256;
  const int nj = 257;
  FILE *fp;
  char filename[nIC];
  int runnum;
  int nsample;
  int N;
  int adc;
  int sch;
  int gain;
  double current;
  float px;
  float py;
  double isumX[nXY];
  double isumY[nXY];
  double isumI[nIC];
  double isumC[nIC];

  TString Save_dir;
  Save_dir = "/cms/scratch/yjeong/GEM_CI/plots/";

  TCanvas *c1[nj];

  TH1F *hoscd1[nj];
  TH1F *hoscd2[nj];
  TH1F *hoscd3[nj];
  TH1F *hoscd4[nj];

 /* TH1F *hoscd1 = new TH1F("hoscd1", "x-distribution", 128, 0, 128);
  TH1F *hoscd2 = new TH1F("hoscd2", "y-distribution", 128, 0, 128);
  TH1F *hoscd3 = new TH1F("hoscd3", "Current",256,0,256);
  TH1F *hoscd4 = new TH1F("hoscd4", "Charge",256,0,256);*/

  printf("enter run number : ");
  scanf("%d", &runnum);

  printf("enter gain value : ");
  scanf("%d", &gain);

for (int j = runnum; j < nj; j++)
{
  c1[j] = new TCanvas(Form("c1_%d",j), Form("KIMS_%d",j), 1000, 1000);
  c1[j]->Divide(1,2);

  hoscd1[j] = new TH1F(Form("hoscd1_%d",j), "x-distribution", 128, 0, 128);
  hoscd2[j] = new TH1F(Form("hoscd2_%d",j), "y-distribution", 128, 0, 128);
  hoscd3[j] = new TH1F(Form("hoscd3_%d",j), "Current", 256, 0, 256);
  hoscd4[j] = new TH1F(Form("hoscd4_%d",j), "Charge", 256, 0, 256);

  sprintf(filename, "170818/gemdaq_%d.txt", j);

  fp = fopen(filename, "rt");

  fscanf(fp, "%d", &nsample);
 
  cout<<"nsample value :"<< nsample << endl;
  
  hoscd1[j]->Reset();

  switch(gain)
	{
	 case 0:
	    current = 5.2;
	    break;
	 case 1:
	    current = 10;
	    break;
	 case 2:
	    current = 20;
	    break;
	 case 3:
	    current = 48;
	    break;
	 case 4:
	    current= 96;
	    break;
	 case 5:
	    current = 192;
	    break;
	 case 6:
	    current = 288;
	    break;
	 case 7:
	    current = 384;
	    break;
	}

  for (int i = 0; i < nXY; i++) 
  {
    isumX[i] = 0;
    isumY[i] = 0;
  }

  for (int i = 0; i < nIC; i++)
        {
         isumI[i] = 0;
	 isumC[i] = 0;
        }
  
  for (int i = 0; i < nsample; i++) 
  {
    for (int ch = 0; ch < nXY; ch++) 
    {
      fscanf(fp, "%d", &adc);
      isumX[ch] = isumX[ch] + adc;    //<- x-distribution(adc value_1~128)
    }

    for (int ch = 0; ch < nXY; ch++) 
    {
      fscanf(fp, "%d", &adc);
      isumY[ch] = isumY[ch] + adc;   //<- y-distribution(adc value_129~256)
    }
    for (int ch = 0; ch<nIC; ch++)
    {
     fscanf(fp, "%d", &adc);
     isumI[ch] = isumI[ch] + adc;   //<- Current value(ch 1~256)
    }
    for (int ch = 0; ch<nIC; ch++)
    {
     fscanf(fp, "%d", &adc);
     isumC[ch] = isumC[ch] + adc;   //<- Charge value(ch 1~256)
    }
  }

  fclose(fp);

  for (int i = 0; i < nXY; i++) 
  {
      px = i + 0.5;			
      adc = isumX[i];
      hoscd1[j]->Fill(px, adc);
      adc = isumY[i];
      hoscd2[j]->Fill(px, adc);
  }

  for (int i = 0; i < nIC; i++)
	{
	 px = i+0.5;
	 adc = (isumI[i]*current/4096);
	// adc = isumI[i]*0.09375;
	 hoscd3[j]->Fill(px, adc);
	 N = current*28/4096;
	 adc = isumC[i]*N;
	 hoscd4[j]->Fill(px, adc);
	}
  c1[j]->cd(1);
  hoscd1[j]->Draw();
  c1[j]->cd(2);
  hoscd2[j]->Draw();

  c1[j]->Modified();
  c1[j]->Update();

//c1[j]->Print(Form("GEM_CI_%d.png",j));
c1[j]->SaveAs(Save_dir+Form("GEM_CI_%d.png",j));
}

//  TCanvas *c2 = new TCanvas("c2","Current_Distribution",1000,1000);
//  c2->Divide(1,2);
/* for (int ch = 0; ch<nIC; ch++)
                {
                 fscanf(fp, "%d", &adc);
                 isum[ch] = isum[ch] + adc;
                }
*/

//                   isumX[ch] = isumX[ch] + current;
//                   c2->Divide(1,2);
//  TCanvas *c2;
//  TH1F *hoscd3 = new TH1F("hoscd3","Current",256,0,256);
  
//  printf("Enter gain value");
//  scanf("%d", &gain);
/*  fp = fopen(filename, "rt");
  fscanf(fp, "%d", &nsample);
  
  hoscd3->Reset();
  

  for (int i = 0; i < nIC; i++)
  	{
	 isum[i] = 0;
	}

  for (int i = 0; i > nsample; i++)
 	{
	  for (int ch = 0; ch<nIC; ch++)
		{	 
		 fscanf(fp, "%d", &adc);
		 isum[ch] = isum[ch] + adc;
		}
	}
  fclose(fp); 
*/  
/*  for (i=0; i>nIC; i++)
  	{
  	 px = i + 0.5;
	 adc = isum[i]*0.09375;
	 hoscd3->Fill(px, adc);
	} */

/*
  c2->cd(1);
  hoscd3->Draw();

  leg = new TLegend(0.9,0.7,0.8,0.775);
  leg -> SetHeader("Current unit calibration");
  leg -> AddEntry(hoscd3, "value * 10^(-9)", "hoscd3");
  leg -> Draw();

  c2->cd(2);
  hoscd4->Draw();

  leg = new TLegend(0.9,0.7,0.8,0.775);
  leg -> SetHeader("Charge unit calibration");
  leg -> AddEntry(hoscd4, "value * 10^(-15)", "hoscd4");
  leg -> Draw();  

  c2->Modified();
  c2->Update();
*/
  
    
//  c2->cd(1);
//  csumX[ch] = isumX[ch] + current;
//  2->cd(2);
  
/*
  TCanvas *c4 = new TCanvas("c4", "Gaussian", 600, 600);
  TH1F *hoscd5 = new TH1F("hoscd5", "distribution", 4096, 0, 4096);

//  printf("enter run number : ");
//  scanf("%d", &runnum);
//  sprintf(filename, "gemdaq_%d.txt", runnum);

  printf("enter channel number to show : ");
  scanf("%d", &sch);

  fp = fopen(filename, "rt");

  fscanf(fp, "%d", &nsample);

  hoscd5->Reset();

  for (int i = 0; i < nsample; i++) 
	{
        for (int ch = 0; ch <= sch; ch++)
          fscanf(fp, "%d", &adc);

        px = adc;
        hoscd5->Fill(px);

        for (ch = sch + 1; ch < nIC; ch++)
          fscanf(fp, "%d", &adc);
	}

  fclose(fp);

  hoscd5->Draw();
  c4->Modified();
  c4->Update();
*/

}
    
