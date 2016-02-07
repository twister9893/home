QList<QVariant> tmp;
//  
tmp.clear();
tmp<<f.getundersist()<<f.gettract();
tableNumbers.append(0);
data.append(tmp);

// Входные параметры расчёта
tmp.clear();
tmp<<f.getglub_GPBA()<<f.gettip_cel()<<f.getglub_cel()<<f.getkol_zon()<<f.getnach_zon1();
tableNumbers.append(1);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getkon_zon1()<<f.getnach_zon2()<<f.getkon_zon2()<<f.getnach_zon10()<<f.getkon_zon10();
tableNumbers.append(2);
data.append(tmp);
