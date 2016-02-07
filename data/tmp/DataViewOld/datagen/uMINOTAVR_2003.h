QList<QVariant> tmp;
// Запросы БИУС
tmp.clear();
tmp<<f.getgraf_kadr()<<f.getpol_VRSZ()<<f.getprog_dal();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.gettip_prog_dal()<<f.getglub_prog_dal()<<f.getglub_GPBA();
tableNumbers.append(1);
data.append(tmp);
