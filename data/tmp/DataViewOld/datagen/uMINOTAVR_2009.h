QList<QVariant> tmp;
// Запрещенные параметры и режимы работы:
tmp.clear();
tmp<<f.getreg_rab_PA()<<f.getreg_rab_GPBA()<<f.getreg_iz_PA()<<f.getbort_iz()<<f.gettip_ZS_PA()<<f.getkol_imp_ZS();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdiap_PA()<<f.gettip_ZS_PA_BGL()<<f.getkol_imp_ZS_BGL()<<f.getdiap_PA_BGL()<<f.getshkala_PA()<<f.getpower_iz_PA();
tableNumbers.append(1);
data.append(tmp);

//  
tmp.clear();
tmp<<f.gettip_ZS_GPBA()<<f.getmod_GPBA()<<f.getchast_GPBA()<<f.getkol_imp_ZS_GPBA()<<f.getshkala_GPBA();
tableNumbers.append(2);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getpower_iz_GPBA()<<f.gettime_iz_PSPA()<<f.getper_ZS_PSPA()<<f.gettime_iz_PSGPBA()<<f.getper_ZS_PSGPBA();
tableNumbers.append(3);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getnach1()<<f.getkon1()<<f.getnach2()<<f.getkon2()<<f.getnach3()<<f.getkon3();
tableNumbers.append(4);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getnach4()<<f.getkon4()<<f.getnach5()<<f.getkon5()<<f.getnach6()<<f.getkon6();
tableNumbers.append(5);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getrec_glub_ant_GPBA()<<f.getrec_GAK();
tableNumbers.append(6);
data.append(tmp);
