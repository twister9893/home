QList<QVariant> tmp;
// Установленные зоны обзора
tmp.clear();
tmp<<f.getkol_zon()<<f.getdatetime_zon()<<f.getdatetime_zon_rez()<<f.getpriz_zon();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getnpel1_zon()<<f.getkpel1_zon()<<f.getnpel2_zon()<<f.getkpel2_zon();
tableNumbers.append(1);
data.append(tmp);

// Разрешенные сектора для маневрирования
tmp.clear();
tmp<<f.getkol_sek()<<f.getpriz_sek()<<f.getnpel1_sek()<<f.getkpel1_sek()<<f.getnpel2_sek()<<f.getkpel2_sek();
tableNumbers.append(2);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getnpel3_sek()<<f.getkpel3_sek()<<f.getnpel4_sel()<<f.getkpel4_sek();
tableNumbers.append(3);
data.append(tmp);

// Признак и параметры текущего собственного маневра
tmp.clear();
tmp<<f.getpriz_man()<<f.getdatetime_nman()<<f.getdatetime_nman_rez()<<f.getdatetime_kman()<<f.getdatetime_kman_rez();
tableNumbers.append(4);
data.append(tmp);

// Планируемый галс
tmp.clear();
tmp<<f.getkurs_gals()<<f.getskor_gals();
tableNumbers.append(5);
data.append(tmp);
