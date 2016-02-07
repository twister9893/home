QList<QVariant> tmp;
// Координаты района выполнения задачи
tmp.clear();
tmp<<f.getgrad_shir1()<<f.getmin_shir1()<<f.getsec_shir1()<<f.getgrad_dol1()<<f.getmin_dol1()<<f.getsec_dol1();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getgrad_shir2()<<f.getmin_shir2()<<f.getsec_shir2()<<f.getgrad_dol2()<<f.getmin_dol2()<<f.getsec_dol2();
tableNumbers.append(1);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getnaz_r();
tableNumbers.append(2);
data.append(tmp);
