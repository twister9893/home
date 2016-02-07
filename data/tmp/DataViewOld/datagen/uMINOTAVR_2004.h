QList<QVariant> tmp;
//  
tmp.clear();
tmp<<f.getkol_fcel();
tableNumbers.append(0);
data.append(tmp);

// Формуляр цели 1
tmp.clear();
tmp<<f.getnum_f()<<f.getnum_cel_GAK()<<f.getnum_cel_kor()<<f.gettip_kor()<<f.getist_inf()<<f.getvkl_TG();
tableNumbers.append(1);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getclass_cel()<<f.getkod_class()<<f.getgos_prin()<<f.getstat_sopr();
tableNumbers.append(2);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getpel_cel()<<f.getCKO_pel()<<f.getpriz_neod_pel()<<f.getdist()<<f.getCKOdist()<<f.getskor()<<f.getCKO_skor();
tableNumbers.append(3);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getkurs()<<f.getCKO_kurs()<<f.getglub()<<f.getCKO_glub()<<f.getvir()<<f.getCKO_vir()<<f.getvip()<<f.getCKO_vip();
tableNumbers.append(4);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getnal_dan()<<f.getnapr_error()<<f.getgrad_shir()<<f.getmin_shir()<<f.getsec_shir();
tableNumbers.append(5);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getgrad_dol()<<f.getmin_dol()<<f.getsec_dol();
tableNumbers.append(6);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdatetime_ob()<<f.getdatetime_ob_rez()<<f.getdatetime_oc()<<f.getdatetime_oc_rez();
tableNumbers.append(7);
data.append(tmp);
