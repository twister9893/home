QList<QVariant> tmp;
//  
tmp.clear();
tmp<<f.getkol_fcel();
tableNumbers.append(0);
data.append(tmp);

// Формуляр цели 1
tmp.clear();
tmp<<f.getnum_for()<<f.getnum_cel_GAK()<<f.getnum_cel_kor()<<f.gettip_cel_kor()<<f.getist_inf()<<f.getpriznak_TG();
tableNumbers.append(1);
data.append(tmp);

//   
tmp.clear();
tmp<<f.getclass_cel()<<f.getkod_class()<<f.getgos_prin()<<f.getstat_cel()<<f.getpel_cel()<<f.getCKO_pel();
tableNumbers.append(2);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getpriz_neopr()<<f.getdist()<<f.getCKO_dist()<<f.getskor()<<f.getCKO_skor()<<f.getkurs()<<f.getCKO_kurs();
tableNumbers.append(3);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getglub()<<f.getCKO_glub()<<f.getvir()<<f.getCKO_vir()<<f.getvip()<<f.getCKO_vip();
tableNumbers.append(4);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getnal_dan()<<f.getnapr_error()<<f.getgrad_shir()<<f.getmin_shir()<<f.getsec_shir()<<f.getgrad_dol();
tableNumbers.append(5);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getmin_dol()<<f.getsec_dol()<<f.getdatetime_ob()<<f.getdatetime_ob_rez()<<f.getdatetime_oc()<<f.getdatetime_oc_rez();
tableNumbers.append(6);
data.append(tmp);
