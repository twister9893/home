QList<QVariant> tmp;
// Параметры из СПиУ
tmp.clear();
tmp<<f.gettakt_zad()<<f.getdatetime_takt_zad()<<f.getdatatime_takt_zad_rez();
tableNumbers.append(0);
data.append(tmp);

// Параметры тактической задачи
tmp.clear();
tmp<<f.getnum_cel_GAK()<<f.getnum_cel_kor()<<f.gettip_cel_cor()<<f.getpel()<<f.getdist();
tableNumbers.append(1);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdatetime_pot()<<f.getdatetime_pot_rez()<<f.getdatetime_naz()<<f.getdatetime_naz_rez()<<f.getnaz_cel();
tableNumbers.append(2);
data.append(tmp);

// Признаки принятия рекомендаций ГАК
tmp.clear();
tmp<<f.getid_rec_man()<<f.getdatetime_rec_man()<<f.getdatetime_rec_man_rez()<<f.getrec_man_GAK();
tableNumbers.append(3);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getid_rec_buk()<<f.getdatetime_rec_buk()<<f.getdatetime_rec_buk_rez()<<f.getrec_buk_GAK();
tableNumbers.append(4);
data.append(tmp);
