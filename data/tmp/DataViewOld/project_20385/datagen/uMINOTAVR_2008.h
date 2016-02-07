QList<QVariant> tmp;
// Параметры первого НКТГ
tmp.clear();
tmp<<f.getnum_cel_GAK()<<f.getnum_cel_kor()<<f.getsost_GAK()<<f.getreg_GAK()<<f.getreg_PA();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getreg_GPBA()<<f.getreg_iz_PA()<<f.getnapr_iz()<<f.getbort_iz()<<f.gettip_ZS_PA();
tableNumbers.append(1);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getkol_imp_ZS()<<f.getdiap_PA()<<f.gettip_ZS_PA_BGL()<<f.getkol_imp_ZS_BGL()<<f.getdiap_PA_BGL();
tableNumbers.append(2);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getshkala_PA()<<f.getpower_iz_PA()<<f.gettip_ZS_GPBA()<<f.getmod_GPBA()<<f.getchast_GPBA();
tableNumbers.append(3);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getkol_imp_ZS_GPBA()<<f.getshkala_GPBA()<<f.getpower_iz_GPBA()<<f.getpol_ant()<<f.getglub_ant_GPBA();
tableNumbers.append(4);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdlin_tros_GPBA()<<f.getkurs_ant_GPBA()<<f.getotst_GPBA_PA()<<f.getdatatime_nach_PA()<<f.getdatatime_nach_PA_rez()<<f.gettime_nach_PA();
tableNumbers.append(5);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdatetime_kon_PA()<<f.getdatetime_kon_PA_rez()<<f.gettime_kon_PA();
tableNumbers.append(6);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdatetime_nach_GPBA()<<f.getdatetime_nach_GPBA_rez()<<f.gettime_nach_GPBA();
tableNumbers.append(7);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdatetime_kon_GPBA()<<f.getdatetime_kon_GPBA_rez()<<f.gettime_kon_GPBA();
tableNumbers.append(8);
data.append(tmp);
