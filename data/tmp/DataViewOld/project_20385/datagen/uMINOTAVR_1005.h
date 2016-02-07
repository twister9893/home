QList<QVariant> tmp;
// Параметры замера
tmp.clear();
tmp<<f.getist_VRSZ()<<f.getdatetime_VRSZ()<<f.getdatetime_VRSZ_rez()<<f.getgrad_shir()<<f.getmin_shir();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getgrad_dol()<<f.getmin_dol()<<f.getkol_izmer()<<f.gethar_grunt()<<f.getskor_vetr();
tableNumbers.append(1);
data.append(tmp);

// Массив пар значений
tmp.clear();
tmp<<f.getglub_1()<<f.getskor_zv_1()<<f.getglub_30()<<f.getskor_zv_30();
tableNumbers.append(2);
data.append(tmp);
