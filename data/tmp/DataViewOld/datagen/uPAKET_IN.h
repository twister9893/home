QList<QVariant> tmp;
// Прием данных изделием "СУ МТПК Пакет"
tmp.clear();
tmp<<f.getp_author()<<f.getKupr()<<f.getRsu()<<f.getKrmpt1()<<f.getKrmpt2();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getKrat()<<f.getKst()<<f.getCst()<<f.getSm();
tableNumbers.append(1);
data.append(tmp);

// Формуляр ПЛ - цели:
tmp.clear();
tmp<<f.getNplo()<<f.getDtar()<<f.getPtar()<<f.getVtar()<<f.getKtar()<<f.getTgl_pl();
tableNumbers.append(2);
data.append(tmp);
