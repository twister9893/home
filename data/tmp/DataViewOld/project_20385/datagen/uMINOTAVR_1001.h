QList<QVariant> tmp;
//  
tmp.clear();
tmp<<f.getsostGAK()<<f.getreg_funGAK()<<f.getdokl_rezerv()<<f.getreg_workPA();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getreg_workGPBA()<<f.getreg_izPA()<<f.getnapr_iz()<<f.getbort_iz()<<f.gettipZC_PA()<<f.getkolimp_PA();
tableNumbers.append(1);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdiap_PA()<<f.gettip_ZS_PA_BGL()<<f.getkol_imp_ZS_BGL()<<f.getdiap_PA_BGL()<<f.getshkala_PA()<<f.getpoweriz_PA()<<f.gettipZC_GPBA()<<f.getmodGPBA();
tableNumbers.append(2);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getchastGPBA()<<f.getkolimp_GPBA()<<f.getshkala_GPBA()<<f.getpoweriz_GPBA()<<f.getpolba_GPBA()<<f.getglubba_GPBA()<<f.getdlinkt_GPBA();
tableNumbers.append(3);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getkursba_GPBA()<<f.getgoriz_GPBAotPA()<<f.getdatetimenach_PA()<<f.getdatetimenach_rez_PA()<<f.gettimenach_PA()<<f.getdatetimekon_PA();
tableNumbers.append(4);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdatetimekon_rez_PA()<<f.gettimekon_PA()<<f.getdatetimenach_GPBA()<<f.getdatetimenach_rez_GPBA()<<f.gettimenach_GPBA()<<f.getdatetimekon_GPBA();
tableNumbers.append(5);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdatetimekon_rez_GPBA()<<f.gettimekon_GPBA()<<f.getnal_YKCYC()<<f.getnal_Paket();
tableNumbers.append(6);
data.append(tmp);
